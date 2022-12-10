#ifndef WORKDAYS_H
#define WORKDAYS_H

#include <QHBoxLayout>
#include <QHeaderView>
#include <QLCDNumber>
#include <QMainWindow>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTableView>
#include <QTime>
#include <QTimer>

namespace Ui {
class WorkDays;
}

class WorkDays : public QWidget {
  Q_OBJECT

public:
  explicit WorkDays(QWidget *parent = nullptr);
  ~WorkDays();

public slots:
  void ChangeTime();

private:
  QTimer *timer;
  QLCDNumber *lcd;
  Ui::WorkDays *ui;
};

#endif // WORKDAYS_H
