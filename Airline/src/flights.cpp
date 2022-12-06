#include "flights.h"
#include "ui_flights.h"

Flights::Flights(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Flights)
{
    ui->setupUi(this);

    QObject::connect(ui->btnAdd,SIGNAL(clicked(bool)),this,SLOT(InsertTableFlights()));
    QObject::connect(ui->btnUpdate,SIGNAL(clicked(bool)),this,SLOT(UpdateTableFlights()));
    QObject::connect(ui->btnDelete,SIGNAL(clicked(bool)),this,SLOT(DeleteTableFlights()));
    QObject::connect(ui->btnClose,SIGNAL(cliked(bool)),this,SLOT(CloseDateBaseFlights()));

    this->setWindowTitle("Table Flights");
}

Flights::~Flights()
{
    delete ui;
    delete model;
}

auto Flights::ConnectFlights()noexcept -> void
{
    const QString path = "./FlightAB.db";
    f_db = QSqlDatabase::addDatabase("QSQLITE");
    f_db.setDatabaseName(path);

    if(!f_db.open()){
        log.error(QString::number(f_db.isOpenError()));
    }else{
        log.info("Connect to Database successfuly");
        CreateTableFlights();
    }

}

auto Flights::CreateTableFlights()noexcept ->void
{
   const QString table = "CREATE TABLE Flights ("
                         "NumberFlight SMALINT UNSIGNED,"
                         "Departure DATETIME,"
                         "Arrival DATETIME,"
                         "PassengerCode SMALINT UNSIGNED);";

   QSqlQuery query(f_db);
   query.prepare(table);

   if(!query.exec()){
       log.error(query.lastError().text());
   }

   model = new QSqlTableModel(this);
   model->setTable("Flights");
   model->select();
   ui->tableView->setModel(model);

}

auto Flights::ClearLine()noexcept -> void
{
    ui->LineArrive->clear();
    ui->LineCode->clear();
    ui->LineDeparture->clear();
    ui->LineFlight->clear();
}

void Flights::InsertTableFlights()
{
   const QString number_flight = ui->LineFlight->text();
   const QString departure = ui->LineDeparture->text();
   const QString arrival = ui->LineArrive->text();
   const QString passenger_code = ui->LineCode->text();

   const QString insert = "INSERT INTO Flights "
                          "(NumberFlight,Departure,Arrival,PassengerCode) "
                          "VALUES(?, ?, ?, ?)";


   model->select();

   QSqlQuery query(f_db);

   if(query.prepare(insert)){
       query.addBindValue(number_flight);
       query.addBindValue(departure);
       query.addBindValue(arrival);
       query.addBindValue(passenger_code);
       query.exec();
   }else{
      log.error(query.lastError().text() + "::InsertTableFlight(...)");
   }

    ClearLine();
}

void Flights::DeleteTableFlights()
{
   const QString code_passenger = ui->LineCode->text();
   const QString delete_passenger = "DELETE FROM Flights WHERE PassengerCode=:PassengerCode";

   QSqlQuery query(f_db);
   query.prepare(delete_passenger);
   query.bindValue(":PassengerCode",code_passenger);

   if(!query.exec()){
       log.error(query.lastError().text() + " ::DeleteFlights(...)");
   }else{
        log.info(code_passenger + " Successfully removed !");
  }

    model->select();
    ClearLine();
}

auto Flights::ChoiceUpdate() noexcept -> QString
{
    const QString text=QInputDialog::getText(this,tr("Input for update old code"),
                                            tr("Enter: "),QLineEdit::Normal,
                                            QDir::home().dirName());


   return text;
}

void Flights::UpdateTableFlights()
{
  const QString code_update = ChoiceUpdate();
  const QString old_code = ui->LineCode->text();

  const QString update = "UPDATE Flights SET PassengerCode=:code_update WHERE PassengerCode=:old_code";

  QSqlQuery query(f_db);
  query.prepare(update);
  query.bindValue(":code_update",code_update);
  query.bindValue(":old_code",old_code);

  if(!query.exec()){
        log.error(query.lastError().text());
  }else{
      log.info(old_code + " Successfuly update on " + code_update);
  }

  model->select();
  ClearLine();
}

bool Flights::ToEmptyFlights()
{
   QSqlQuery query(f_db);

   if(!query.exec("DROP FROM Flights")){
       log.error(query.lastError().text() + " ::ToEmptyFlights(...)");
       return false;
   }

   model->select();

   return true;
}

bool Flights::CloseDateBaseFlights()
{
    if(f_db.isOpen()){
        f_db.close();
        return true;
    }else{
        return false;
    }
}
