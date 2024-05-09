#include "association.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

Association::Association(int budget,QString nom,QString adresse,QString description,QString type)
{
   // this->id=id;
    this->budget=budget;
    this->nom=nom;
    this->adresse=adresse;
    this->description=description;
    this->type=type;
}



bool Association::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO ASSOCIATION (budget,nom, adress, description, type) "
                  "VALUES (:budget, :nom, :adress, :description, :type)");
    query.bindValue(":budget", budget);
    query.bindValue(":nom", nom);
    query.bindValue(":adress", adresse);
    query.bindValue(":description", description);
    query.bindValue(":type", type);
    return query.exec();

}


QSqlQueryModel * Association::afficher()
{
    QSqlQueryModel * model = new QSqlQueryModel();

    // Corrected SQL query with proper column selection
    model->setQuery("SELECT nom, adress, budget, description, type FROM ASSOCIATION");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ADRESS"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("BUDGET"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TYPE"));

    return model;
}



QSqlQueryModel * Association::afficher2()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from ASSOCIATION");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("ADRESS"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("BUDGET"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("DESCRIPTION"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("TYPE"));

    return model;
}








bool Association::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM ASSOCIATION WHERE ID = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Delete failed: " ;  // Detailed error message
        return false;
    }
    return true;
}


QSqlQueryModel* Association::rechercher(QString A)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ASSOCIATION WHERE NOM LIKE '%" + A + "%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ADRESS"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("BUDGET"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("TYPE"));


    return model;
}


bool Association::modifier(int id,int budget,QString nom,QString adresse,QString description)
{
    QSqlQuery query;
    query.prepare("UPDATE ASSOCIATION set ID=:id, NOM=:nom, ADRESS=:adress,BUDGET=:budget,DESCRIPTION=:description WHERE ID= :id");
    query.bindValue(":id",id);
    query.bindValue(":nom",nom);
    query.bindValue(":adress",adresse);
    query.bindValue(":budget",budget);
    query.bindValue(":description",description);

    if (!query.exec()) {
        qDebug() << "Delete failed: " ;  // Detailed error message
        return false;
    }
    return true;
}

QSqlQueryModel* Association::afficher_tri_budget() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ASSOCIATION ORDER BY BUDGET");
    return model;
}

QSqlQueryModel* Association::afficher_tri_nom() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ASSOCIATION ORDER BY NOM");
    return model;
}

QSqlQueryModel* Association::afficher_tri_adresse() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ASSOCIATION ORDER BY ADRESS");
    return model;
}


