#ifndef LOGIN_H
#define LOGIN_H


#include "airlinedb.h"
#include "storage.h"
#include "passengers.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QMainWindow
{
	Q_OBJECT

public:
	explicit Login(QWidget* parent = nullptr);
	~Login();

public slots:
	void DatabaseEntry() noexcept;

	void ChoiceViewPassword() noexcept;

public:
	auto CheckCorrectInput() noexcept -> bool;

public:
	static Login* getInstance()noexcept;

private:
	QScopedPointer<Storage> t_st;
	Storage* m_st;

private:
	AirlineDB t_db;
	Passengers p_db;

private:
	Ui::Login* ui;
};

#endif // LOGIN_H
