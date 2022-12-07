#ifndef LOGIN_H
#define LOGIN_H

#include "airlinedb.h"
#include "flights.h"
#include "passengers.h"
#include "storage.h"
#include "tickets.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Login;
}
QT_END_NAMESPACE

class Login : public QMainWindow {
  Q_OBJECT

public:
  explicit Login(QWidget *parent = nullptr);
  ~Login();

public slots:
  void DatabaseEntry() noexcept;

  void ChoiceViewPassword() noexcept;

public:
  auto CheckCorrectInput() noexcept -> bool;

public:
  static Login *getInstance() noexcept;

private:
  QScopedPointer<Storage> t_st;
  Storage *m_st;

private:
  AirlineDB t_db;
  Passengers p_db;
  Flights f_db;
  Tickets ts_db;

private:
  Ui::Login *ui;
};

#endif // LOGIN_H
