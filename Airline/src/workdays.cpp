#include "workdays.h"
#include "ui_workdays.h"

WorkDays::WorkDays(QWidget *parent) : QWidget(parent), ui(new Ui::WorkDays) {
  QTableView *table = new QTableView;

  QStringList nWeek{"Days Of Week", "Start of work", "End of work"};

  QStandardItemModel *model = new QStandardItemModel;
  QStandardItem *item;

  timer = new QTimer(this);
  timer->setTimerType(Qt::VeryCoarseTimer);
  lcd = new QLCDNumber(12);

  QObject::connect(timer, &QTimer::timeout, this, &WorkDays::ChangeTime);
  timer->start(1000);

  lcd->setSegmentStyle(QLCDNumber::Filled);
  lcd->setMode(QLCDNumber::Dec);
  lcd->setMinimumSize(110, 60);

  model->setHorizontalHeaderLabels(nWeek);

  for (int i = 0; i < model->columnCount(); ++i) {
    table->setColumnWidth(i, 190);
    for (int j = 0; j < model->rowCount(); ++j) {
      table->setRowHeight(j, 200);
    }
  }
  // days when work airline
  item = new QStandardItem(QString("Monday"));
  model->setItem(0, 0, item);
  item = new QStandardItem(QString("Tuesday"));
  model->setItem(1, 0, item);
  item = new QStandardItem(QString("Wensday"));
  model->setItem(2, 0, item);
  item = new QStandardItem(QString("Tuersday"));
  model->setItem(3, 0, item);
  item = new QStandardItem(QString("Friday"));
  model->setItem(4, 0, item);
  item = new QStandardItem(QString("Saturday"));
  model->setItem(5, 0, item);
  item = new QStandardItem(QString("Sunday"));
  model->setItem(6, 0, item);

  // time when start work airline
  item = new QStandardItem(QString("9:30"));
  model->setItem(0, 1, item);
  item = new QStandardItem(QString("9:30"));
  model->setItem(1, 1, item);
  item = new QStandardItem(QString("11:00"));
  model->setItem(2, 1, item);
  item = new QStandardItem(QString("11:15"));
  model->setItem(3, 1, item);
  item = new QStandardItem(QString("11:30"));
  model->setItem(4, 1, item);
  item = new QStandardItem(QString("14:30"));
  model->setItem(5, 1, item);
  item = new QStandardItem(QString("16:00"));
  model->setItem(6, 1, item);

  // time when end of work airline
  item = new QStandardItem(QString("21:00"));
  model->setItem(0, 2, item);
  item = new QStandardItem(QString("21:00"));
  model->setItem(1, 2, item);
  item = new QStandardItem(QString("19:30"));
  model->setItem(2, 2, item);
  item = new QStandardItem(QString("19:00"));
  model->setItem(3, 2, item);
  item = new QStandardItem(QString("18:50"));
  model->setItem(4, 2, item);
  item = new QStandardItem(QString("20:10"));
  model->setItem(5, 2, item);
  item = new QStandardItem(QString("22:15"));
  model->setItem(6, 2, item);

  table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  model->setRowCount(7);
  model->setColumnCount(3);
  table->setModel(model);

  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->addWidget(lcd);
  layout->addWidget(table);

  this->setWindowTitle("Airline working days");
}

WorkDays::~WorkDays() { delete ui; }

void WorkDays::ChangeTime() {
  lcd->display(QTime::currentTime().toString("hh:mm:ss"));
}
