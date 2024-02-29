#include "guest.h"


Guest::Guest(int c,QString n, int a, QString g, QString adr, int ph, QString e)
{
    CIN = c;
    phone = ph;
    age = a;
    name = n;
    address = adr;
    email = e;
    gender = g;
}

bool Guest::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO GUEST VALUES(:cin, :name, :age, :gender, :address, :email, :phone)");
    query.bindValue(":cin", CIN);
    query.bindValue(":name", name);
    query.bindValue(":age", age);
    query.bindValue(":gender", gender);
    query.bindValue(":address", address);
    query.bindValue(":email", email);
    query.bindValue(":phone", phone);
    return query.exec();
}

QSqlQueryModel *Guest::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM GUEST");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NAME"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("AGE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("GENDER"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADDRESS"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("PHONE"));
    return model;
}

bool Guest::supprimer(int cin)
{
    QSqlQuery query;
    query.prepare("DELETE FROM GUEST WHERE CIN = :cin");
    query.bindValue(":cin", cin);
    return query.exec();
}


bool Guest::modifier(int c,QString n,int a,QString g,QString adr,QString e,int ph)
{
    QSqlQuery query;
    query.prepare("UPDATE GUEST set CIN=:cin,NAME=:name,AGE=:age,GENDER=:gender,ADDRESS=:address,EMAIL=:email,PHONE=:phone");
    query.bindValue(":cin",c);
    query.bindValue(":phone",n);
    query.bindValue(":nom",a);
    query.bindValue(":prenom",g);
    query.bindValue(":adresse",adr);
    query.bindValue(":mail",e);
    query.bindValue(":phone",ph);

    return query.exec();
}

/*
QSqlQueryModel* Artiste::rechercher(QString A)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM TABLE1 WHERE nom LIKE '%" + A + "%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TEL"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("MAIL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("DOMAINE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("SEXE"));
    return model;
}





QSqlQueryModel* Artiste::afficher_tri_cin() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM TABLE1 ORDER BY cin");
    return model;
}

QSqlQueryModel* Artiste::afficher_tri_nom() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM TABLE1 ORDER BY nom");
    return model;
}

QSqlQueryModel* Artiste::afficher_tri_prenom() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM TABLE1 ORDER BY prenom");
    return model;
}*/


