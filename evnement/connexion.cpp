#include "connexion.h"

connexion::connexion()
{

}

bool connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("mybase");
db.setUserName("maroua");//inserer nom de l'utilisateur
db.setPassword("maroua");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
