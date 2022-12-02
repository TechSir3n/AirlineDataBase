#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QScopedPointer>
#include <QMessageBox>
#include "storage.h"

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

public slots:
  auto DatabaseEntry() noexcept -> bool;

  auto ChoiceViewPassword() noexcept -> void;

public:
  auto CheckCorrectInput() noexcept -> bool;

public:
    static Login *getInstance()noexcept;

private:
    QScopedPointer<Storage> t_st;
    Ui::Login *ui;
};

#endif // LOGIN_H
