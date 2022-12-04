#include "airlinedb.h"
#include "ui_airlinedb.h"


AirlineDB::AirlineDB(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::AirlineDB) {
  ui->setupUi(this);

  connect(ui->btnAdd, SIGNAL(clicked(bool)), this, SLOT(InsertDataTable()));
  connect(ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(CloseBaseData()));
  connect(ui->btnDelete,SIGNAL(clicked(bool)),this,SLOT(DeleteBaseData()));
  connect(ui->btnUpdate,SIGNAL(clicked(bool)),this,SLOT(UpdateBaseData()));
}

AirlineDB::~AirlineDB()
{
  delete ui;
  delete model;
  delete query;
}

auto AirlineDB::ClearLine()noexcept -> void
{
    ui->LineCode->clear();
    ui->LineAddress->clear();
    ui->LineName->clear();
    ui->LineTelephone->clear();
}

auto AirlineDB::Connect() -> bool {
  const QString path = "./Airline.db";
  db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(path);

  if (!db.open()) {
    log.error("Failed to connect at baseData");
    return false;
  } else {
    log.info("Connect to baseData seccessfull");

    CreateTableBaseData();
    InsertDataTable();

    return true;
  }
}

void  AirlineDB::CreateTableBaseData() noexcept{
  query = new QSqlQuery(db);

  QString table = "CREATE TABLE AirlineDB ("
                  "Name VARCHAR(20),"
                  "Telephone VARCHAR(20),"
                  "Address VARCHAR(20),"
                  "Code INTEGER PRIMARY KEY NOT NULL);";

  if (!query->exec(table)) {
    log.error(query->lastError().text());
  }

  model = new QSqlTableModel(this,db);
  model->setTable("AirlineDB");
  model->select();

  ui->tableView->setModel(model);
}

AirlineDB *AirlineDB::getInstance() noexcept
{
    static AirlineDB instance;
    return &instance;
}

auto AirlineDB::InsertDataTable() noexcept -> void {
  QString name = ui->LineName->text();
  QString telephone = ui->LineTelephone->text();
  QString address = ui->LineAddress->text();
  QString code = ui->LineCode->text();

  QString insert = "INSERT INTO AirlineDB (name, telephone, address,code) "
                   "VALUES (?, ?, ?, ?)";

  model->select();

  if (query->prepare(insert)) {
    query->addBindValue(name);
    query->addBindValue(telephone);
    query->addBindValue(address);
    query->addBindValue(code);
    query->exec();
  } else {
    log.error(query->lastError().text());
  }

  ClearLine();
}

void AirlineDB::DeleteBaseData()noexcept
{
   const QString name_del=ui->LineName->text();
   const QString delete_db="DELETE FROM AirlineDB WHERE name=:name";

   query->prepare(delete_db);
   query->bindValue(":name",name_del);

    if(!query->exec()){
        log.error(query->lastError().text());
    }else{
        log.info(name_del + " removed successfully ! ");
    }

    model->select();
}

auto AirlineDB::ChoiceUpdate()noexcept -> QString
{
   bool ok;
  const QString text=QInputDialog::getText(this,tr("Input for update old name"),
                                        tr("Enter: "),QLineEdit::Normal,
                                        QDir::home().dirName(),&ok);

   return text;
}


void AirlineDB::UpdateBaseData()noexcept
{
   const QString choice_update = ChoiceUpdate();
   const QString choice_name=ui->LineName->text();

   const QString update_db = "UPDATE AirlineDB SET name=:choice_update WHERE name=:choice_name";

   query->prepare(update_db);
   query->bindValue(":choice_update",choice_update);
   query->bindValue(":choice_name",choice_name);

    if(!query->exec()){
        log.error(query->lastError().text());
    }else{
        log.info(choice_name + " update successfully on " + choice_update );
    }

    model->select();
}

void AirlineDB::CloseBaseData() noexcept
{
    db.close();
}
