#include "airlinedb.h"
#include "ui_airlinedb.h"

AirlineDB::AirlineDB(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::AirlineDB) {
  ui->setupUi(this);

  QObject::connect(ui->btnAdd, SIGNAL(clicked(bool)), this,
                   SLOT(InsertDataTableAirline()));
  QObject::connect(ui->btnClose, SIGNAL(clicked(bool)), this,
                   SLOT(CloseBaseDataAirline()));
  QObject::connect(ui->btnDelete, SIGNAL(clicked(bool)), this,
                   SLOT(DeleteBaseDataAirline()));
  QObject::connect(ui->btnUpdate, SIGNAL(clicked(bool)), this,
                   SLOT(UpdateBaseDataAirline()));
  QObject::connect(ui->actionClearAirline, SIGNAL(triggered(bool)), this,
                   SLOT(ToEmptyAilrline()));
  QObject::connect(ui->actionOrderBy, SIGNAL(triggered(bool)), this,
                   SLOT(OrderByAirline()));

  this->setWindowTitle("The Airline");
}

AirlineDB::~AirlineDB() {
  delete ui;
  delete model;
}

auto AirlineDB::ClearLine() noexcept -> void {
  ui->LineCode->clear();
  ui->LineAddress->clear();
  ui->LineName->clear();
  ui->LineTelephone->clear();
}

auto AirlineDB::ConnectAirline() -> void {
  const QString path = "./Airlines.db";
  db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(path);

  if (!db.open()) {
    log.error("Cannot open dataBase" + db.lastError().text());

  } else {
    log.info("Connect to baseData seccessfully,::Airline(...)");

    CreateTableBaseDataAirline();
  }
}

void AirlineDB::CreateTableBaseDataAirline() noexcept {

  const QString table = "CREATE TABLE AirlineDB ("
                        "Name VARCHAR(20),"
                        "Telephone VARCHAR(7),"
                        "Address VARCHAR(20),"
                        "Code SMALLINT UNSIGNED);";

  QSqlQuery query(db);
  if (!query.exec(table)) {
    log.error(query.lastError().text() + " ::CreateAirline(...)");
  }

  model = new QSqlTableModel(this, db);
  model->setTable("AirlineDB");
  model->select();

  ui->tableView->setModel(model);
}

AirlineDB *AirlineDB::getInstance() noexcept {
  static AirlineDB instance;
  return &instance;
}

auto AirlineDB::InsertDataTableAirline() -> void {
  const QString name = ui->LineName->text();
  const QString telephone = ui->LineTelephone->text();
  const QString address = ui->LineAddress->text();
  const QString code = ui->LineCode->text();

  const QString insert =
      "INSERT INTO AirlineDB (name, telephone, address,code) "
      "VALUES (?, ?, ?, ?)";

  model->select();

  QSqlQuery query(db);

  if (query.prepare(insert)) {
    query.addBindValue(name);
    query.addBindValue(telephone);
    query.addBindValue(address);
    query.addBindValue(code);
    query.exec();
  } else {
    log.error(query.lastError().text() + " ::InsertAirline(...)");
  }

  ClearLine();
}

void AirlineDB::DeleteBaseDataAirline() {
  const QString name_del = ui->LineName->text();
  const QString delete_db = "DELETE FROM AirlineDB WHERE name=:name";

  if (ui->LineName->text().isEmpty()) {
    QMessageBox::warning(this, "The Error",
                         "You did not enter a name that you have delete");
  }

  QSqlQuery query(db);
  query.prepare(delete_db);
  query.bindValue(":name", name_del);

  if (!query.exec()) {
    log.error(query.lastError().text() + "::DeleteAirine(...)");
  } else {
    log.info(name_del + " removed successfully ! ");
  }

  model->select();
  ClearLine();
}

auto AirlineDB::ChoiceUpdateAirline() noexcept -> QString {
  const QString text = QInputDialog::getText(
      this, tr("Input for update old name"), tr("Enter: "), QLineEdit::Normal,
      QDir::home().dirName());

  return text;
}

void AirlineDB::UpdateBaseDataAirline() {
  const QString choice_update = ChoiceUpdateAirline();
  const QString choice_name = ui->LineName->text();

  const QString update_db =
      "UPDATE AirlineDB SET name=:choice_update WHERE name=:choice_name";

  if (ui->LineName->text().isEmpty()) {
    QMessageBox::warning(this, "The Error",
                         "You did not enter a name that you have updated");
  }

  QSqlQuery query(db);
  query.prepare(update_db);
  query.bindValue(":choice_update", choice_update);
  query.bindValue(":choice_name", choice_name);

  if (!query.exec()) {
    log.error(query.lastError().text() + "::UpdateAirline(...)");
  } else {
    log.info(choice_name + " update successfully on " + choice_update);
  }

  model->select();
  ClearLine();
}

bool AirlineDB::CloseBaseDataAirline() {
  if (db.isOpen()) {
    db.close();
    QSqlDatabase::removeDatabase("AirlineDB");
    return true;
  } else {
    return false;
  }
}

bool AirlineDB::OrderByAirline() {

  QSqlQuery query(db);

  if (!query.exec("SELECT * FROM AirlineDB ORDER BY Code ASC,Name ASC")) {
    log.error(query.lastError().text() + " ::OrderByAirline(...)");
    return false;
  } else {
    model->select();
    return true;
  }
}

bool AirlineDB::ToEmptyAilrline() {

  QSqlQuery query(db);
  if (!query.exec("DROP TABLE AirlineDB")) {
    log.error(query.lastError().text() + " ::ToEmptyAirline(...)");
    return false;
  } else {
    model->select();
    return true;
  }
}
