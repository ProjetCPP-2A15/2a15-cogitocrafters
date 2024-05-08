#include "guest.h"
#include<QDebug>
#include <QFile>
Guest::Guest(int c,QString n, int a, QString g, QString adr, int ph, QString e,QString i)
{
    CIN = c;
    phone = ph;
    age = a;
    name = n;
    address = adr;
    email = e;
    gender = g;
    imagePath =i;
}

bool Guest::ajouter()
{
    Connection connection;

    // Lire l'image depuis le fichier
    QFile file(imagePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Erreur: Impossible de lire l'image:" << file.errorString();
        qDebug() << imagePath;
        return false;
    }
    QByteArray imageData = file.readAll();
    file.close();

    QSqlQuery query;
    query.prepare("INSERT INTO GUEST (CIN, name, age, gender, address, phone, email, image) VALUES (:CIN, :name, :age, :gender, :address, :phone, :email, :image)");

    query.bindValue(":CIN", this->CIN);
    query.bindValue(":name", this->name);
    query.bindValue(":age", this->age);
    query.bindValue(":gender", this->gender);
    query.bindValue(":address", this->address);
    query.bindValue(":phone", this->phone);
    query.bindValue(":email", this->email);
    query.bindValue(":image", imageData);

    if (!query.exec()) {
        qDebug() << "Erreur d'exécution de la requête SQL:" << query.lastError().text();
        return false;
    }

    return true; // Retourner true si l'ajout a réussi
}



QSqlQueryModel* Guest::afficher() {
    QSqlQueryModel *model = new QSqlQueryModel();

    QString query = "SELECT CAST(CIN AS varchar(255)), name, age, gender, address, CAST(phone AS varchar(255)), email FROM GUEST WHERE CIN>0";
    model->setQuery(query);

    return model;
}

QSqlQueryModel *Guest::afficherId(int cin)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM GUEST WHERE CIN = :cin");
    query.bindValue(":cin", cin);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
        delete model; // Libérer la mémoire allouée avant de retourner nullptr
        return nullptr;
    }

    model->setQuery(query);
    return model;
}



bool Guest::supprimer(int cin)
{
    QSqlQuery query;
    query.prepare("DELETE FROM GUEST WHERE CIN = :cin");
    query.bindValue(":cin", cin);

    if (!query.exec()) {
        qDebug() << "Erreur SQL:" << query.lastError().text(); // Utiliser qDebug() au lieu de QDebug()
        return false;
    }
    return true; // Retourner true si l'ajout a réussi
}


bool Guest::modifierImage(int ancienCin, int nouveauCin, QString n, int a, QString g, QString adr, QString e, int ph,QString img) {

    // Lire l'image depuis le fichier
    QFile file(img);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Erreur: Impossible de lire l'image:" << file.errorString();
        qDebug() << img;
        return false;
    }
    QByteArray imageData = file.readAll();
    file.close();

    QSqlQuery query;
    query.prepare("UPDATE GUEST SET CIN=:nouveauCin, NAME=:name, AGE=:age, GENDER=:gender, ADDRESS=:address, PHONE=:phone, EMAIL=:email, IMAGE=:image WHERE CIN=:ancienCin");
    query.bindValue(":nouveauCin", nouveauCin);
    query.bindValue(":ancienCin", ancienCin);
    query.bindValue(":name", n);
    query.bindValue(":age", a);
    query.bindValue(":gender", g);
    query.bindValue(":address", adr);
    query.bindValue(":phone", ph);
    query.bindValue(":email", e);
    query.bindValue(":image", imageData);


    if (!query.exec()) {
        qDebug() << "Erreur SQL:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Guest::modifier(int ancienCin, int nouveauCin, QString n, int a, QString g, QString adr, QString e, int ph) {

    QSqlQuery query;
    query.prepare("UPDATE GUEST SET CIN=:nouveauCin, NAME=:name, AGE=:age, GENDER=:gender, ADDRESS=:address, PHONE=:phone, EMAIL=:email WHERE CIN=:ancienCin");
    query.bindValue(":nouveauCin", nouveauCin);
    query.bindValue(":ancienCin", ancienCin);
    query.bindValue(":name", n);
    query.bindValue(":age", a);
    query.bindValue(":gender", g);
    query.bindValue(":address", adr);
    query.bindValue(":phone", ph);
    query.bindValue(":email", e);


    if (!query.exec()) {
        qDebug() << "Erreur SQL:" << query.lastError().text();
        return false;
    }
    return true;
}

QSqlQueryModel* Guest::rechercher(QString G)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM GUEST WHERE NAME LIKE '%" + G + "%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NAME"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("AGE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("GENDER"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADDRESS"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("PHONE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("EMAIL"));
    return model;
}

QSqlQueryModel* Guest::afficher_tri(const QString &critere) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QString query = "SELECT * FROM GUEST ORDER BY ";

    if(critere == "CIN") {
        query += "CIN";
    } else if(critere == "Age") {
        query += "AGE";
    } else if(critere == "Name") {
        query += "NAME";
    }

    model->setQuery(query);
    return model;
}
/*


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
}
*/


