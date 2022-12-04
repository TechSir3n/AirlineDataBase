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

auto Passengers::ChoiceUpdatePassengers()noexcept -> QString
{
	const QString text = QInputDialog::getText(this, tr("Enter new code for update "),
		tr("Enter:"), QLineEdit::Normal,
		QDir::home().dirName());

	return text;
}

void Passengers::UpdateBaseDataPassengers()
{
	const QString old_code = ChoiceUpdatePassengers();
	const QString code_update = ui->LineCodePassenger->text();
	const QString update = "UPDATE Passengfers SET=:code_update WHERE code=:old_code";

	query->prepare(update);
	query->bindValue(":code", old_code);
	query->bindValue(":code_update", code_update);

	if (!query->exec()) {
		log.error(query->lastError().text());
	}
	else {
		log.info(old_code + " Success update on -> " + code_update);

	}

	model->select();
}

void Passengers::DeleteBaseDataPassengers()
{
	const QString delete_code = ui->LineCodePassenger->text();
	const QString delete_tb = "DELETE FROM Passengers WHERE code=:code";

	query->prepare(delete_tb);
	query->bindValue(":code", delete_code);

	if (!query->exec()) {
		log.error(query->lastError().text());
	}
	else {
		log.info(delete_code + " Removed successfully ");
	}

	model->select();
}

void Passengers::CloseBaseDataPassengers()
{
	p_db.close();
}