#include "passengers.h"
#include "ui_passengers.h"

Passengers::Passengers(QWidget* parent) :
	QMainWindow(parent),
	ui(new Ui::Passengers)
{
	ui->setupUi(this);

	QObject::connect(ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(CloseBaseDataPassengers()));
	QObject::connect(ui->btnAdd, SIGNAL(clicked(bool)), this, SLOT(InsertBaseDataPassengers()));
	QObject::connect(ui->btnDelete, SIGNAL(clicked(bool)), this, SLOT(DeleteBaseDataPassengers()));
	QObject::connect(ui->btnUpdate, SIGNAL(clicked(bool)), this, SLOT(UpdateBaseDataPassengers()));
}
Passengers::~Passengers()
{
	delete ui;
	delete query;
	delete model;
}

auto Passengers::ConnectPassengers() -> void
{
	const QString path = "./PassengersDB.db";
	p_db = QSqlDatabase::addDatabase("QSQLITE");
	p_db.setDatabaseName(path);

	if (!p_db.open()) {
		log.error("Failed open dataBase,::Passengers(...)");
	}
	else {
		log.info("Connect to DataBase successfully,::Passengers(...)");
		CreateTableBaseDataPassengers();
	}

}

auto Passengers::CreateTableBaseDataPassengers()noexcept -> void
{
	const QString table = "CREATE TABLE Passengers ( "
		"Name VARCHAR(15),"
		"Surname VARCHAR(15),"
		"Fatherland VARCHAR(15),"
		"Passport VARCHAR(20),"
		"Birth_date DATE,"
		"Gender VARCHAR(10),"
		"Code Passenger SMALLINT UNSIGNED);";


	query = new QSqlQuery(p_db);
	query->prepare(table);

	if (!query->exec()) {
		log.error(query->lastError().text());
	}

	model = new QSqlTableModel(this);
	model->setTable("Passengers");
	model->select();
	ui->tableView->setModel(model);
}


void Passengers::InsertBaseDataPassengers()
{
	const QString name = ui->LineName->text();
	const QString surname = ui->LineSurname->text();
	const QString fatherland = ui->LineFatherland->text();
	const QString passport = ui->LinePassport->text();
	const QString birth_date = ui->LineDateOfBirth->text();
	const QString gender = ui->LineGender->text();
	const QString code = ui->LineCodePassenger->text();

	const QString insert = "INSERT INTO Passengers (name,surname,fatherland,passport,birth_date,gender,code) "
		"VALUES (?, ?, ?, ?, ?, ?, ?)";
	model->select();

	if (query->prepare(insert)) {
		query->addBindValue(name);
		query->addBindValue(surname);
		query->addBindValue(fatherland);
		query->addBindValue(passport);
		query->addBindValue(birth_date);
		query->addBindValue(gender);
		query->addBindValue(code);
		query->exec();
	}
	else {
		log.error(query->lastError().text());
	}
}


void Passengers::UpdateBaseDataPassengers()
{

}

void Passengers::DeleteBaseDataPassengers()
{

}

void Passengers::CloseBaseDataPassengers()
{
	p_db.close();
}
