#include "connection.h"
#include <QMessageBox>
//#include<QDebug>
#include "mainwindow.h"
#include <QApplication>

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("test-bd");
db.setUserName("iheb");//inserer nom de l'utilisateur
db.setPassword("iheb");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;


    return  test;
}
