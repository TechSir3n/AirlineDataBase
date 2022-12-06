#ifndef FLIGHTS_H
#define FLIGHTS_H

#include "airlinedb.h"
#include <QDir>
#include <QInputDialog>
#include <QMainWindow>

namespace Ui {
class Flights;
}

class Flights : public QMainWindow
{
    Q_OBJECT

public:
    explicit Flights(QWidget *parent = nullptr);
    ~Flights();

public:
   auto ConnectFlights()noexcept -> void;

   auto CreateTableFlights()noexcept ->void;

   auto ClearLine()noexcept -> void;

   auto ChoiceUpdate() noexcept -> QString;

 public slots:
   void InsertTableFlights();

   void DeleteTableFlights();

   void UpdateTableFlights();

   bool ToEmptyFlights();

   bool CloseDateBaseFlights();

 private:
   QSqlDatabase f_db;
   Logger log;
   QSqlTableModel *model;
   Ui::Flights *ui;
};

#endif // FLIGHTS_H
