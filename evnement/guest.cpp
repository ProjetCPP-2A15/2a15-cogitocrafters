#include "guest.h"
#include<QDebug>

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
    Connection connection;

    // Vérifier si la connexion à la base de données est établie
    if (!connection.createconnect()) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur de connexion"), QObject::tr("Impossible de se connecter à la base de données."), QMessageBox::Ok);
        return false; // Retourner false si la connexion a échoué
    }

    QSqlQuery query;
    query.prepare("INSERT INTO GUEST (CIN, name, age, gender, address, phone, email) "
                  "VALUES (:CIN, :name, :age, :gender, :address, :phone, :email)");

    query.bindValue(":CIN", this->CIN); // Utiliser :CIN au lieu de :cin
    query.bindValue(":name", this->name);
    query.bindValue(":age", this->age);
    query.bindValue(":gender", this->gender);
    query.bindValue(":address", this->address);
    query.bindValue(":phone", this->phone);
    query.bindValue(":email", this->email);

    if (!query.exec()) {
        qDebug() << "Erreur SQL:" << query.lastError().text(); // Utiliser qDebug() au lieu de QDebug()
        return false;
    }

    return true; // Retourner true si l'ajout a réussi
}

QSqlQueryModel *Guest::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM GUEST");
   // model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
   // model->setHeaderData(1, Qt::Horizontal, QObject::tr("NAME"));
   // model->setHeaderData(2, Qt::Horizontal, QObject::tr("AGE"));
   // model->setHeaderData(3, Qt::Horizontal, QObject::tr("GENDER"));
   // model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADDRESS"));
   // model->setHeaderData(5, Qt::Horizontal, QObject::tr("PHONE"));
   // model->setHeaderData(6, Qt::Horizontal, QObject::tr("EMAIL"));
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


