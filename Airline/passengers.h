#ifndef PASSENGERS_H
#define PASSENGERS_H

#include <QMainWindow>
#include "airlinedb.h"

namespace Ui {
	class Passengers;
}

class Passengers : public QMainWindow
{
	Q_OBJECT

public:
	explicit Passengers(QWidget* parent = nullptr);
	~Passengers();

public:
	auto CreateTableBaseDataPassengers()noexcept -> void;

	auto ConnectPassengers() -> void;

	auto ChoiceUpdatePassengers()noexcept -> QString;

public slots:
	void InsertBaseDataPassengers();

	void UpdateBaseDataPassengers();

	void DeleteBaseDataPassengers();

	void CloseBaseDataPassengers();

private:
	Logger log;
	QSqlDatabase p_db;
	QSqlQuery* query;
	QSqlTableModel* model;
	Ui::Passengers* ui;
};

#endif // PASSENGERS_H
