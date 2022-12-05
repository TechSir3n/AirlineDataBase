#include "airlinedb.h"
#include "ui_airlinedb.h"


AirlineDB::AirlineDB(QWidget* parent)
	: QMainWindow(parent), ui(new Ui::AirlineDB) {
	ui->setupUi(this);

	QObject::connect(ui->btnAdd, SIGNAL(clicked(bool)), this, SLOT(InsertDataTableAirline()));
	QObject::connect(ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(CloseBaseDataAirline()));
	QObject::connect(ui->btnDelete, SIGNAL(clicked(bool)), this, SLOT(DeleteBaseDataAirline()));
	QObject::connect(ui->btnUpdate, SIGNAL(clicked(bool)), this, SLOT(UpdateBaseDataAirline()));
	QObject::connect(ui->actionClearAirline, SIGNAL(triggered(bool)), this, SLOT(ToEmptyAilrline()));
	QObject::connect(ui->actionOrderBy, SIGNAL(triggered(bool)), this, SLOT(OrderByAirline()));

	this->setWindowTitle("The Airline");
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

auto AirlineDB::ConnectAirline() -> void {
	const QString path = "./AirlineDB.db";
	db = QSqlDatabase::addDatabase("QSQLITE", "ConnectionAR");
	db.setDatabaseName(path);

	if (!db.open()) {
		log.error("Failed to connect at baseData,::Airline(...)");

	}
	else {
		log.info("Connect to baseData seccessfully,::Airline(...)");

		CreateTableBaseDataAirline();
		InsertDataTableAirline();

	}
}

void  AirlineDB::CreateTableBaseDataAirline() noexcept {
	query = new QSqlQuery(db);

	const QString table = "CREATE TABLE AirlineDB ("
		"Name VARCHAR(20),"
		"Telephone VARCHAR(7),"
		"Address VARCHAR(20),"
		"Code INTEGER PRIMARY KEY NOT NULL);";

	if (!query->exec(table)) {
		log.error(query->lastError().text() + " ::CreateAirline(...)");
	}

	model = new QSqlTableModel(this, db);
	model->setTable("AirlineDB");
	model->select();

	ui->tableView->setModel(model);
}

AirlineDB* AirlineDB::getInstance() noexcept
{
	static AirlineDB instance;
	return &instance;
}

auto AirlineDB::InsertDataTableAirline() -> void {
	const QString name = ui->LineName->text();
	const QString telephone = ui->LineTelephone->text();
	const QString address = ui->LineAddress->text();
	const QString code = ui->LineCode->text();

	const QString insert = "INSERT INTO AirlineDB (name, telephone, address,code) "
		"VALUES (?, ?, ?, ?)";

	model->select();

	if (query->prepare(insert)) {
		query->addBindValue(name);
		query->addBindValue(telephone);
		query->addBindValue(address);
		query->addBindValue(code);
		query->exec();
	}
	else {
		log.error(query->lastError().text() + " ::InsertAirline(...)");
	}

	ClearLine();
}

void AirlineDB::DeleteBaseDataAirline()
{
	const QString name_del = ui->LineName->text();
	const QString delete_db = "DELETE FROM AirlineDB WHERE name=:name";

	query->prepare(delete_db);
	query->bindValue(":name", name_del);

	if (!query->exec()) {
		log.error(query->lastError().text() + "::DeleteAirine(...)");
	}
	else {
		log.info(name_del + " removed successfully ! ");
	}

	model->select();
}

auto AirlineDB::ChoiceUpdateAirline()noexcept -> QString
{
	const QString text = QInputDialog::getText(this, tr("Input for update old name"),
		tr("Enter: "), QLineEdit::Normal,
		QDir::home().dirName());

	return text;
}


void AirlineDB::UpdateBaseDataAirline()
{
	const QString choice_update = ChoiceUpdateAirline();
	const QString choice_name = ui->LineName->text();

	const QString update_db = "UPDATE AirlineDB SET name=:choice_update WHERE name=:choice_name";

	query->prepare(update_db);
	query->bindValue(":choice_update", choice_update);
	query->bindValue(":choice_name", choice_name);

	if (!query->exec()) {
		log.error(query->lastError().text() + "::UpdateAirline(...)");
	}
	else {
		log.info(choice_name + " update successfully on " + choice_update);
	}

	model->select();
}

bool AirlineDB::CloseBaseDataAirline()
{
	if (db.isOpen()) {
		db.close();
		QSqlDatabase::removeDatabase("AirlineDB");
		return true;
	}
	else {
		return false;
	}
}

bool AirlineDB::OrderByAirline()
{
	if (!query->exec("SELECT * FROM AirlineDB ORDER BY Codef DESC,Name ASC")) {
		log.error(query->lastError().text() + " ::OrderByAirline(...)");
		return false;
	}
	else {
		model->select();
		return true;
	}
}

bool AirlineDB::ToEmptyAilrline()
{
	if (!query->exec("DELETE FROM AirlineDB")) {
		log.error(query->lastError().text() + " ::ToEmptyAirline(...)");
		return false;
	}
	else {
		model->select();
		return true;
	}
}
