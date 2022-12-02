#ifndef STORAGE_H
#define STORAGE_H

#include "logger.h"
#include <QFile>
#include <QTextStream>

class Storage
{
public:
    Storage();

public:
     auto UserLogin() noexcept -> bool;

     auto StoragePassword(const QString &password, const QString &login) noexcept
         -> bool;

     auto CorrectlyLogin(const QString &password, const QString &login) noexcept
           -> bool;

private:
     Logger log;
};

#endif // STORAGE_H
