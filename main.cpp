#include "mainwindow.h"
#include <QApplication>
#include "QtSql/QSqlDatabase"
#include <QtSql>
#include <QFileDialog>

int main(int argc, char *argv[])
{
     QSqlDatabase maBase = QSqlDatabase::addDatabase("QSQLITE");
     maBase.setDatabaseName("alpes_outillage_reparation.db");
     bool ok = maBase.open();
     QApplication a(argc, argv);
     MainWindow w;

     if(ok==true)
     {
         w.show();
     }

    return a.exec();
}
