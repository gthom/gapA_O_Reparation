#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QtSql>
#include <QFileDialog>

int main(int argc, char *argv[])
{
     QSqlDatabase maBase = QSqlDatabase::addDatabase("QMYSQL");
     maBase.setDatabaseName("alpes_outillage_reparation");
     maBase.setHostName("localhost");
     maBase.setUserName("useraor");
     maBase.setPassword("aor");
     bool baseOuverte = maBase.open();
     if(baseOuverte)
     {
         QApplication a(argc, argv);
         MainWindow w;
         w.show();
         return a.exec();
     }
     else//pb sur la base
     {
         qDebug()<<"La base n'a pas pû être ouverte";
         qDebug()<<"Verifiez que le serveur est lançé et que Mysql est fonctionnel";
         exit(2);
     }
}
