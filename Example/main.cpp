#include "airlinedb.h"
#include "login.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AirlineDB *airline=AirlineDB::getInstance();
    Login *login=Login::getInstance();

    login->show();

    if(login->DatabaseEntry()){
        airline->Connect();
         airline->show();
    }else{
       qWarning()<<"Wrong enter login,not connect !";
    }






    return a.exec();
}
