#ifndef PASSENGERS_H
#define PASSENGERS_H

#include "airlinedb.h"
#include <QMainWindow>

namespace Ui {
class Passengers;
}

class Passengers : public QMainWindow {
  Q_OBJECT

public:
  explicit Passengers(QWidget *parent = nullptr);
  ~Passengers();

public:
  auto CreateTableBaseDataPassengers() noexcept -> void;

  auto ConnectPassengers() -> void;

  auto ChoiceUpdatePassengers() noexcept -> QString;

  auto ClearLine() noexcept -> void;

public slots:
  void InsertBaseDataPassengers();

  void UpdateBaseDataPassengers();

  void DeleteBaseDataPassengers();

  bool CloseBaseDataPassengers();

  bool ToEmptyPassengers();

  bool OrderByPassengers();

private:
  Logger log;
  QSqlDatabase p_db;
  QSqlTableModel *model;
  Ui::Passengers *ui;
};

#endif // PASSENGERS_H
