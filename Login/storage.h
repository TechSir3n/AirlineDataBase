#ifndef STORAGE_H
#define STORAGE_H


#include "Logger.h"
#include <QFile>
#include <QTextStream>
#include <QinputDialog>
#include <QByteArray>
#include <QDir>

class Storage:public QObject
{
 Q_OBJECT
public:
   Storage () = default ;

public:
     auto UserLogin() noexcept -> bool;

     auto StoragePassword(const QString &password, const QString &login) noexcept
          -> bool;

     auto CorrectlyLogin(const QString &password, const QString &login) noexcept
          -> bool;

public slots:
     bool ChangePassword();

private:
     QWidget *wgt;
     Logger log;
};

#endif // STORAGE_H
