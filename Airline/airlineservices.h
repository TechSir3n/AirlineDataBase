#ifndef AIRLINESERVICES_H
#define AIRLINESERVICES_H

#include "Logger.h"
#include "workdays.h"
#include "tickets.h"
#include <QDir>
#include <QInputDialog>
#include <QSql>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QMainWindow>
#include <vector>
#include <QStringListModel>


namespace Ui {
class AirlineServices;
}

class AirlineServices : public QMainWindow {
  Q_OBJECT

public:
  explicit AirlineServices(QWidget *parent = nullptr);
  ~AirlineServices();

public:
  bool ShowPriceTickets();

public slots:
  void HelpMenu();

private:
  Logger log;
  Tickets ticket;
  WorkDays wDays;
  Ui::AirlineServices *ui;
};

#endif // AIRLINESERVICES_H
