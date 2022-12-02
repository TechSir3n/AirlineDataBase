#include "storage.h"

Storage::Storage()
{

}

auto Storage::UserLogin() noexcept -> bool
{
    QString password;
      QString login;

      QFile file;
      file.setFileName("./UserLogin.txt");

      if (!file.exists()) {
        log.error("Faield doesn't exists,::UserLogin(...)");
        return false;
      }

      if (!file.open(QIODevice::ReadOnly)) {
        log.error("Failed to open file for Read,::UserLogin(...)");
        return false;
      } else {
        QString temp;
        temp.append(file.readAll());
        QStringList str_list = temp.split('\n');

        password = str_list[0];
        login = str_list[1];

        StoragePassword(password, login);
        return true;
       }


         file.flush();
         file.close();

         return true;
}

auto Storage::StoragePassword(const QString &password, const QString &login) noexcept
    -> bool
{
    QFile file("./StoragePassword.txt");

     if (!file.exists()) {
       log.error("Failed doesn't exists,::StoragePassword(..)");
       return false;
     }

     if (!file.open(QIODevice::Text | QIODevice::WriteOnly)) {
       log.error("Failed to open file,::StoragePassword(...)");
       return false;
     } else {
       QTextStream out(&file);
       out << password << '\n' << login;
       return true;
     }

     file.flush();
     file.close();

     return true;

}

auto Storage::CorrectlyLogin(const QString &password, const QString &login) noexcept
      -> bool
{

    QFile file("./UserLogin.txt");
    if (!file.exists()) {
      log.error("File doesn't exists !");
    }

    if (!file.open(QIODevice::ReadOnly)) {
      log.error("Failed to open file for read,::CorecntyLogin(...)");
    } else {

      QString str;
      str.append(file.readAll());

      QStringList list_str = str.split('\n');

      QString t_password = list_str[0];
      QString t_login = list_str[1];

      if (password == t_password && login == t_login) {
        return true;
      }
    }

    file.flush();
    file.close();

    return false;
}
