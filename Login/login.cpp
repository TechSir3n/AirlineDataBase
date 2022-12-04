#include "login.h"
#include "ui_login.h"

#include <QMainWindow>
#include <QScopedPointer>

Login::Login(QWidget* parent) :
	QMainWindow(parent),
	ui(new Ui::Login)
{
	ui->setupUi(this);

	connect(ui->btnLogin, SIGNAL(clicked(bool)), this, SLOT(DatabaseEntry()));
	connect(ui->btnPassword, SIGNAL(clicked(bool)), this,
		SLOT(ChoiceViewPassword()));

	Storage* st = new Storage;

	QObject::connect(ui->ActChangePassword, &QAction::triggered, st, &Storage::ChangePassword);
	QObject::connect(ui->actionClose, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
}

Login::~Login()
{
	delete ui;
}

void Login::DatabaseEntry() noexcept {
	QString password = ui->LinePassword->text();
	QString login = ui->LineLogin->text();

	if (CheckCorrectInput()) {
		if (t_st->CorrectlyLogin(password, login)) {
			t_db.Connect();
			t_db.show();
		}
		else {
			QMessageBox::information(this, "Failed", "Wrong enter login");
		}
	}
	else {
		QMessageBox::warning(this, "Failed to login", "User enter wrong data");
	}
}


Login* Login::getInstance() noexcept
{
	static Login instance;
	return &instance;
}

void Login::ChoiceViewPassword() noexcept {
	if (ui->btnPassword->isChecked()) {
		ui->LinePassword->setEchoMode(QLineEdit::Normal);
	}
	else {
		ui->LinePassword->setEchoMode(QLineEdit::Password);
	}
}

auto Login::CheckCorrectInput() noexcept -> bool {
	if (ui->LinePassword->text().isEmpty()) {
		QMessageBox::critical(this, "Error Authorisation",
			"User doesn't password enter,input is ::empty()");
		return false;
	}

	if (ui->LineLogin->text().isEmpty()) {
		QMessageBox::critical(this, "Error Authorisation",
			"User doesn't login enter,input is ::empty()");
		return false;
	}

	return true;
}
