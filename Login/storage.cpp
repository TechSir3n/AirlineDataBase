#include "storage.h"


auto Storage::UserLogin() noexcept -> bool
{
    QString password;
      QString login;

      QFile file;
      file.setFileName("C:/Users/Ruslan/Documents/AirlineDB/UserLogin.txt");

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
    QFile file("C:/Users/Ruslan/Documents/AirlineDB/StoragePassword.txt.");

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
    QFile file("C:/Users/Ruslan/Documents/AirlineDB/UserLogin.txt");
    if (!file.exists()) {
      log.error("File doesn't exists !");
      return false;
    }

    if (!file.open(QIODevice::ReadOnly)) {
      log.error("Failed to open file for read,::CorecntyLogin(...)");
        return false;
    }
      QString str;
      str.append(file.readAll());

      QStringList list_str = str.split(':');

      QString t_password = list_str[0].trimmed();
      QString t_login = list_str[1].trimmed();

    file.flush();
    file.close();

    if (t_password==password && t_login==login) {
        return true;
    }else{
        return false;
    }
}

bool Storage::ChangePassword()
{
    bool result;
    wgt = new QWidget;

    const QString new_password = QInputDialog::getText(wgt,tr("Input for update old name"),
                                         tr("Enter new password: "),QLineEdit::Normal,
                                         QDir::home().dirName(),&result);

    std::size_t sz = std::size(new_password);

    if(sz<6){
        log.error("Password cannot be less then six symbol");
        return false;
    }else{
        QFile file("C:/Users/Ruslan/Documents/AirlineDB/UserLogin.txt");
        if(!file.open(QIODevice::WriteOnly | QIODevice::ReadOnly)){
            log.error("Failed open file,::ChangePassword(...)");
        }else{
            QString f_str;
            f_str.append(file.readAll());
            QStringList list=f_str.split(":");

            list[0] = new_password;
            log.info(list[1]);

            QTextStream stream(&file);
            stream<<list.join(":");

            StoragePassword(list[0],list[1]);
        }

        delete wgt;
        file.close();

        return true;
    }
}
