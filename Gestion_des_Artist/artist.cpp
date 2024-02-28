 #include "artist.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

Artiste::Artiste(int cin,int tel,QString nom,QString prenom,QString adresse,QString mail,QString domaine,QString description,QString sexe)
{
    this->cin=cin;
    this->tel=tel;
    this->nom=nom;
    this->prenom=prenom;
    this->adresse=adresse;
    this->mail=mail;
    this->domaine=domaine;
    this->description=description;
    this->sexe=sexe;
}

bool Artiste::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO TABLE1 VALUES(:cin,:tel,:nom,:prenom,:adresse,:mail,:domaine,:description,:sexe)");
    query.bindValue(":cin",cin);
    query.bindValue(":tel",tel);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":adresse",adresse);
    query.bindValue(":mail",mail);
    query.bindValue(":domaine",domaine);
    query.bindValue(":description",description);
    query.bindValue(":sexe",sexe);
    return query.exec();
}


QSqlQueryModel * Artiste::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from TABLE1");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TEL"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("PRENOM"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("ADRESSE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("MAIL"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("DOMAINE"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("DESCRIPTION"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("SEXE"));
    return model;
}



QSqlQueryModel * Artiste::affichers()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from TABLE1");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("DOMAINE"));
    return model;
}





bool Artiste::supprimer(int cin) {
    QSqlQuery query;
    query.prepare("DELETE FROM TABLE1 WHERE CIN = :cin");
    query.bindValue(":cin", cin);
    if (!query.exec()) {
        qDebug() << "Delete failed: " ;  // Detailed error message
        return false;
    }
    return true;
}


QSqlQueryModel* Artiste::rechercher(QString A)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM TABLE1 WHERE NOM LIKE '%" + A + "%'");
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


bool Artiste::modifier(int cin,int tel,QString nom,QString prenom,QString adresse,QString mail,QString domaine,QString description,QString sexe)
{
    QSqlQuery query;
    query.prepare("UPDATE TABLE1 set CIN=:cin,TEL=:tel,NOM=:nom,PRENOM=:prenom,ADRESSE=:adresse,MAIL=:mail,DOMAINE=:domaine,DESCRIPTION=:description,SEXE=:sexe where CIN= :cin ");
    query.bindValue(":cin",cin);
    query.bindValue(":tel",tel);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":adresse",adresse);
    query.bindValue(":mail",mail);
    query.bindValue(":domaine",domaine);
    query.bindValue(":description",description);
    query.bindValue(":sexe",sexe);

    return query.exec();
}


QSqlQueryModel* Artiste::afficher_tri_cin() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM TABLE1 ORDER BY CIN");
    return model;
}

QSqlQueryModel* Artiste::afficher_tri_nom() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM TABLE1 ORDER BY NOM");
    return model;
}

QSqlQueryModel* Artiste::afficher_tri_prenom() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM TABLE1 ORDER BY PRENOM");
    return model;
}


