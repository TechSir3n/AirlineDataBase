#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    connect(ui->btnLogin, SIGNAL(clicked(bool)), this, SLOT(DatabaseEntry()));
       connect(ui->btnPassword, SIGNAL(clicked(bool)), this,
               SLOT(ChoiceViewPassword()));
}

Login::~Login()
{
    delete ui;
}

auto Login::DatabaseEntry() noexcept -> bool {
  QString password = ui->LinePassword->text();
  QString login = ui->LineLogin->text();

  if (CheckCorrectInput()) {
      if(t_st->CorrectlyLogin(password,login)){
            QMessageBox::information(this,"Is Valid","Login is true");
      }
  } else {
    QMessageBox::warning(this, "Failed to login", "User enter wrong data");
    return false;
  }

  return true;
}


Login *Login::getInstance() noexcept
{
   static Login instance;
   return &instance;
}

auto Login::ChoiceViewPassword() noexcept -> void {
  if (ui->btnPassword->isChecked()) {
    ui->LinePassword->setEchoMode(QLineEdit::Normal);
  } else {
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
