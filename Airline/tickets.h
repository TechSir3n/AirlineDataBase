#ifndef TICKETS_H
#define TICKETS_H

#include "airlinedb.h"
#include "logger.h"
#include <QMainWindow>

namespace Ui {
class Tickets;
}

class Tickets : public QMainWindow {
  Q_OBJECT

public:
  explicit Tickets(QWidget *parent = nullptr);
  ~Tickets();

public:
  auto ConnectTickets() noexcept -> void;

  auto CreateDataBaseTickets() noexcept -> void;

  auto ClearLine() noexcept -> void;

  auto ChoiceUpdate() noexcept -> QString;

public slots:
  void InsertDataBaseTickets();

  void DeleteDataBaseTickets();

  void UpdateDataBaseTickets();

  bool ToEmptyTickets();

  bool CloseTickets();

  bool OrderByTickets();

private:
  QSqlDatabase ts_db;
  QSqlTableModel *model;
  Logger log;
  Ui::Tickets *ui;
};

#endif // TICKETS_H
