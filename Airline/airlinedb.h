#ifndef AIRLINEDB_H
#define AIRLINEDB_H

#include "logger.h"
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QInputDialog>
#include <QDir>
#include <QSqlTableModel>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
	class AirlineDB;
}
QT_END_NAMESPACE

class AirlineDB : public QMainWindow {
	Q_OBJECT

public:
	AirlineDB(QWidget* parent = nullptr);
	~AirlineDB();

public:
	auto ConnectAirline() -> void;

	auto CreateTableBaseDataAirline() noexcept -> void;

	auto ChoiceUpdateAirline()noexcept -> QString;

	auto ClearLine()noexcept -> void;

public:
	static AirlineDB* getInstance()noexcept;

public slots:
	bool CloseBaseDataAirline();

	bool ToEmptyAilrline();

	void InsertDataTableAirline();

	void DeleteBaseDataAirline();

	void UpdateBaseDataAirline();

private:
	QSqlDatabase db;
	QSqlTableModel* model;
	QSqlQuery* query;

private:
	Ui::AirlineDB* ui;
	Logger log;
};

#endif // AIRLINEDB_H
