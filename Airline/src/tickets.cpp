#include "tickets.h"
#include "ui_tickets.h"

Tickets::Tickets(QWidget *parent) : QMainWindow(parent), ui(new Ui::Tickets) {
  ui->setupUi(this);

  QObject::connect(ui->btnAdd, SIGNAL(clicked(bool)), this,
                   SLOT(InsertDataBaseTickets()));
  QObject::connect(ui->btnDelete, SIGNAL(clicked(bool)), this,
                   SLOT(DeleteDataBaseTickets()));
  QObject::connect(ui->btnUpdate, SIGNAL(clicked(bool)), this,
                   SLOT(UpdateDataBaseTickets()));
  QObject::connect(ui->btnClose, SIGNAL(clicked(bool)), this,
                   SLOT(CloseTickets()));
  QObject::connect(ui->actionClearTicket, SIGNAL(triggered(bool)), this,
                   SLOT(ToEmptyTickets()));
  QObject::connect(ui->actionOrderBy, SIGNAL(triggered(bool)), this,
                   SLOT(OrderByTickets()));

  this->setWindowTitle("The Table Tickets");
}

Tickets::~Tickets() { delete ui; }

auto Tickets::ClearLine() noexcept -> void {
  ui->LineCodePassenger->clear();
  ui->LineDepartureDate->clear();
  ui->LineNumberFlight->clear();
  ui->LinePriceTicket->clear();
}

auto Tickets::ConnectTickets() noexcept -> void {
  const QString path = "./Tickets.db";
  ts_db = QSqlDatabase::addDatabase("QSQLITE");
  ts_db.setDatabaseName(path);

  if (!ts_db.isValid()) {
    log.error("Cannot open dataBase" + ts_db.lastError().text() +
              "::ConnectTickets(...)");
  } else {
    log.info("Connect successfuly dataBase");
    CreateDataBaseTickets();
  }
}

auto Tickets::CreateDataBaseTickets() noexcept -> void {
  const QString create = "CREATE TABLE Tickets ("
                         "Code_Passenger SMALINT UNSIGNED,"
                         "Departure_Date DATETIME,"
                         "Number_Flight INT UNSGINED,"
                         "Price_Ticket DOUBLE);";

  QSqlQuery query(ts_db);
  query.prepare(create);

  if (!query.exec()) {
    log.error(query.lastError().text() + " ::CreateDBTickets(...)");
  }

  model = new QSqlTableModel(this);
  model->setTable("Tickets");
  model->select();

  ui->tableView->setModel(model);
}

void Tickets::InsertDataBaseTickets() {
  const QString price = ui->LinePriceTicket->text();
  const QString departure = ui->LineDepartureDate->text();
  const QString flight = ui->LineNumberFlight->text();
  const QString code = ui->LineCodePassenger->text();

  const QString insert =
      "INSERT INTO Tickets "
      "(Price_Ticket,Departure_Date,Number_Flight,Code_Passenger)"
      "VALUES(?, ?, ?, ?)";

  model->select();

  QSqlQuery query(ts_db);

  if (query.prepare(insert)) {
    query.addBindValue(price);
    query.addBindValue(departure);
    query.addBindValue(flight);
    query.addBindValue(code);
    query.exec();
  } else {
    log.error(query.lastError().text() + " ::InsertTickets(...)");
  }
}

void Tickets::DeleteDataBaseTickets() {
  const QString code = ui->LineCodePassenger->text();
  const QString delete_code =
      "DELETE FROM Tickets Where Code_Passenger=:Code_Passenger";

  if (ui->LineCodePassenger->text().isEmpty()) {
    QMessageBox::warning(this, "The Error",
                         "You did not enter a name that you have delete");
  }

  QSqlQuery query(ts_db);
  query.prepare(delete_code);
  query.bindValue(":Code_Passenger", code);

  if (!query.exec()) {
    log.error(query.lastError().text() + " ::DeleteDBTickets(...)");
  } else {
    log.info(code + " Successfuly removed !");
  }

  model->select();
}

auto Tickets::ChoiceUpdate() noexcept -> QString {
  const QString text = QInputDialog::getText(
      this, tr("Enter new code for update "), tr("Enter:"), QLineEdit::Normal,
      QDir::home().dirName());

  return text;
}

void Tickets::UpdateDataBaseTickets() {
  const QString update_code = ChoiceUpdate();
  const QString old_code = ui->LineCodePassenger->text();
  const QString update = "UPDATE Tickets SET Code_Passenger:update_code "
                         "WHERE Code_Passenger=:old_code";

  if (ui->LineCodePassenger->text().isEmpty()) {
    QMessageBox::warning(this, "The Error",
                         "You did not enter code that you have updated");
  }

  QSqlQuery query(ts_db);
  query.prepare(update);
  query.bindValue(":old_code", old_code);
  query.bindValue(":update_code", update_code);

  if (!query.exec()) {
    log.error(query.lastError().text() + " ::UpdateTickets(...)");
  } else {
    log.info(old_code + "Successfuly update on " + update_code);
  }

  model->select();
}

bool Tickets::ToEmptyTickets() {
  QSqlQuery query(ts_db);
  if (!query.exec("DROP FROM Tickets")) {
    log.error(query.lastError().text() + " ::ToEmptyTickets(...)");
    return false;
  } else {
    model->select();
    return true;
  }
}

bool Tickets::OrderByTickets() {
  QSqlQuery query(ts_db);

  query.prepare(
      "SELECT * FROM Tickets ORDER BY Code_Passenger ASC,Departure_Date ASC");
  if (!query.exec()) {
    log.error(query.lastError().text() + " ::OrderByTickets(...)");
    return false;
  } else {
    model->select();
    return false;
  }
}

bool Tickets::CloseTickets() {
  if (ts_db.isOpen()) {
    ts_db.close();
    return true;
  }

  return false;
}
