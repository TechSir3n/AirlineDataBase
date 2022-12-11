#include "airlineservices.h"
#include "ui_airlineservices.h"

AirlineServices::AirlineServices(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::AirlineServices) {
  ui->setupUi(this);

  QObject::connect(ui->actionScheduleView, SIGNAL(triggered(bool)), this,
                   SLOT(HelpMenu()));
  QObject::connect(ui->actionShowPriceTickets, SIGNAL(triggered(bool)), this,
                   SLOT(HelpMenu()));
}

AirlineServices::~AirlineServices() { delete ui; }

void AirlineServices::HelpMenu() {
  int choice = QInputDialog::getInt(this, tr("Make your choice"), tr("Enter:"),
                                    QLineEdit::Normal);

  switch (choice) {
  case 1:
    if (ui->actionScheduleView->isEnabled()) {
      wDays.show();
      wDays.resize(650, 350);
    }

    break;

  case 2:
    if (ui->actionShowPriceTickets->isEnabled()) {
      ShowPriceTickets();
    }

    break;

  default:
    break;
  }
}

bool AirlineServices::ShowPriceTickets() {

  QStandardItemModel *model = new QStandardItemModel;
  QStandardItem *item;
  QStringList l_price{"Price Of Tickets", "City"};

  ticket.ConnectTickets();

  QSqlQuery query;

  if (!query.exec("SELECT * FROM Tickets")) {
    log.error(query.lastError().text());
  }

  model->setHorizontalHeaderLabels(l_price);
  QSqlRecord rec = query.record();

  double price_t = 0.0;

  while (query.next()) {

      price_t = query.value(rec.indexOf("Price_Ticket")).toDouble();

      item = new QStandardItem(QString::number(price_t).toDouble());
      model->setItem(0, 0, item);

      model->setRowCount(6);
      model->setColumnCount(2);

    ui->tableView->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);

    ui->tableView->setModel(model);
    ui->tableView->show();

    log.info(QString::number(price_t));
  }

  return true;
}
