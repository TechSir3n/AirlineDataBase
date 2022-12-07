#include "login.h"
#include "ui_login.h"

#include <QMainWindow>
#include <QScopedPointer>

Login::Login(QWidget *parent) : QMainWindow(parent), ui(new Ui::Login) {
  ui->setupUi(this);

  QObject::connect(ui->btnLogin, SIGNAL(clicked(bool)), this,
                   SLOT(DatabaseEntry()));
  QObject::connect(ui->btnPassword, SIGNAL(clicked(bool)), this,
                   SLOT(ChoiceViewPassword()));

  m_st = new Storage;

  QObject::connect(ui->ActChangePassword, &QAction::triggered, m_st,
                   &Storage::ChangePassword);
  QObject::connect(ui->actionClose, SIGNAL(triggered(bool)), qApp,
                   SLOT(quit()));

  delete m_st;
}

Login::~Login() { delete ui; }

void Login::DatabaseEntry() noexcept {
  QString password = ui->LinePassword->text();
  QString login = ui->LineLogin->text();

  if (CheckCorrectInput()) {
    if (t_st->CorrectlyLogin(password, login)) {
      int result = QInputDialog::getInt(this, tr("Choice one of need Table"),
                                        tr("Enter: "));

      switch (result) {
      case 1:
        t_db.ConnectAirline();
        t_db.show();
        break;

      case 2:
        p_db.ConnectPassengers();
        p_db.show();
        break;

      case 3:
        f_db.ConnectFlights();
        f_db.show();
        break;

      case 4:
        ts_db.ConnectTickets();
        ts_db.show();
        break;

      default:
        break;
      }

    } else {
      QMessageBox::warning(this, "The Error", "Authorisation Error");
    }
  } else {
    QMessageBox::warning(this, "The Error",
                         "Login or password entered incorrectly");
  }
}

Login *Login::getInstance() noexcept {
  static Login instance;
  return &instance;
}

void Login::ChoiceViewPassword() noexcept {
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
