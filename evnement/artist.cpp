#include "artist.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

Artiste::Artiste(int cin, int tel, QString nom, QString prenom, QString adresse, QString mail, QString domaine, QString description, QString sexe, QByteArray image)
{
   this->cin = cin;
   this->tel = tel;
   this->nom = nom;
   this->prenom = prenom;
   this->adresse = adresse;
   this->mail = mail;
   this->domaine = domaine;
   this->description = description;
   this->sexe = sexe;
   this->image = image;
}


bool Artiste::ajouter()
{
   QSqlQuery query;
   query.prepare("INSERT INTO TABLE1 VALUES(:cin, :tel, :nom, :prenom, :adresse, :mail, :domaine, :description, :sexe, :image)");
   query.bindValue(":cin", cin);
   query.bindValue(":tel", tel);
   query.bindValue(":nom", nom);
   query.bindValue(":prenom", prenom);
   query.bindValue(":adresse", adresse);
   query.bindValue(":mail", mail);
   query.bindValue(":domaine", domaine);
   query.bindValue(":description", description);
   query.bindValue(":sexe", sexe);
   query.bindValue(":image", image);
   return query.exec();
}


QSqlQueryModel *Artiste::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT CAST(CIN AS VARCHAR(255)), CAST(TEL AS VARCHAR(255)), NOM, PRENOM, ADRESSE, MAIL, DOMAINE, DESCRIPTION, SEXE, IMAGE FROM TABLE1");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TEL"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("MAIL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("DOMAINE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("SEXE"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("IMAGE"));
    return model;
}



QSqlQueryModel * Artiste::affichers()
{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("SELECT CIN, NOM, DOMAINE FROM TABLE1");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DOMAINE"));
    return model;
}






bool Artiste::supprimer(int cin) {
   QSqlQuery query;
   query.prepare("DELETE FROM TABLE1 WHERE CIN = :cin");
   query.bindValue(":cin", cin);
   if (!query.exec()) {
       qDebug() << "Delete failed: " << query.lastError().text();  // Detailed error message
       return false;
   }
   return true;
}



QSqlQueryModel* Artiste::rechercher(QString lettreOuMot)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QString queryStr = "SELECT CAST(CIN AS VARCHAR(255)), CAST(TEL AS VARCHAR(255)), NOM, PRENOM, ADRESSE, MAIL, DOMAINE, DESCRIPTION, SEXE, IMAGE FROM TABLE1";

    // Construire la clause WHERE pour rechercher la lettre ou le mot dans le nom, le prénom ou le mail
    QString whereClause = "";
    if (!lettreOuMot.isEmpty()) {
        whereClause += " WHERE (NOM LIKE '%" + lettreOuMot + "%' OR PRENOM LIKE '%" + lettreOuMot + "%' OR MAIL LIKE '%" + lettreOuMot + "%')";
    }

    // Ajouter la clause WHERE à la requête si des conditions ont été ajoutées
    if (!whereClause.isEmpty()) {
        queryStr += whereClause;
    }

    model->setQuery(queryStr);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TEL"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("MAIL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("DOMAINE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("SEXE"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("IMAGE"));
    return model;
}




bool Artiste::modifier(int cin, int tel, QString nom, QString prenom, QString adresse, QString mail, QString domaine, QString description, QString sexe, QByteArray image)
{
   QSqlQuery query;
   query.prepare("UPDATE TABLE1 SET TEL=:tel, NOM=:nom, PRENOM=:prenom, ADRESSE=:adresse, MAIL=:mail, DOMAINE=:domaine, DESCRIPTION=:description, SEXE=:sexe, IMAGE=:image WHERE CIN=:cin ");
   query.bindValue(":cin", cin);
   query.bindValue(":tel", tel);
   query.bindValue(":nom", nom);
   query.bindValue(":prenom", prenom);
   query.bindValue(":adresse", adresse);
   query.bindValue(":mail", mail);
   query.bindValue(":domaine", domaine);
   query.bindValue(":description", description);
   query.bindValue(":sexe", sexe);
   query.bindValue(":image", image);
   return query.exec();
}





//----------------------   TRIE    --------------------------------------



QSqlQueryModel* Artiste::afficher_tri_cin_descendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CAST(CIN AS VARCHAR(255)), CAST(TEL AS VARCHAR(255)), NOM, PRENOM, ADRESSE, MAIL, DOMAINE, DESCRIPTION, SEXE, IMAGE FROM TABLE1 ORDER BY CIN DESC");
    return model;
}


QSqlQueryModel* Artiste::afficher_tri_cin_ascendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CAST(CIN AS VARCHAR(255)), CAST(TEL AS VARCHAR(255)), NOM, PRENOM, ADRESSE, MAIL, DOMAINE, DESCRIPTION, SEXE, IMAGE  FROM TABLE1 ORDER BY CIN ASC");
    return model;
}


QSqlQueryModel* Artiste::afficher_tri_nom_descendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CAST(CIN AS VARCHAR(255)), CAST(TEL AS VARCHAR(255)), NOM, PRENOM, ADRESSE, MAIL, DOMAINE, DESCRIPTION, SEXE, IMAGE  FROM TABLE1 ORDER BY NOM DESC");
    return model;
}


QSqlQueryModel* Artiste::afficher_tri_nom_ascendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CAST(CIN AS VARCHAR(255)), CAST(TEL AS VARCHAR(255)), NOM, PRENOM, ADRESSE, MAIL, DOMAINE, DESCRIPTION, SEXE, IMAGE  FROM TABLE1 ORDER BY NOM ASC");
    return model;
}



QSqlQueryModel* Artiste::afficher_tri_tel_descendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CAST(CIN AS VARCHAR(255)), CAST(TEL AS VARCHAR(255)), NOM, PRENOM, ADRESSE, MAIL, DOMAINE, DESCRIPTION, SEXE, IMAGE  FROM TABLE1 ORDER BY TEL DESC");
    return model;
}


QSqlQueryModel* Artiste::afficher_tri_tel_ascendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CAST(CIN AS VARCHAR(255)), CAST(TEL AS VARCHAR(255)), NOM, PRENOM, ADRESSE, MAIL, DOMAINE, DESCRIPTION, SEXE, IMAGE  FROM TABLE1 ORDER BY TEL ASC");
    return model;
}



QSqlQueryModel* Artiste::afficher_tri_prenom_descendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CAST(CIN AS VARCHAR(255)), CAST(TEL AS VARCHAR(255)), NOM, PRENOM, ADRESSE, MAIL, DOMAINE, DESCRIPTION, SEXE, IMAGE  FROM TABLE1 ORDER BY PRENOM DESC");
    return model;
}


QSqlQueryModel* Artiste::afficher_tri_prenom_ascendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CAST(CIN AS VARCHAR(255)), CAST(TEL AS VARCHAR(255)), NOM, PRENOM, ADRESSE, MAIL, DOMAINE, DESCRIPTION, SEXE, IMAGE  FROM TABLE1 ORDER BY PRENOM ASC");
    return model;
}


QSqlQueryModel* Artiste::afficher_tri_adresse_descendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CAST(CIN AS VARCHAR(255)), CAST(TEL AS VARCHAR(255)), NOM, PRENOM, ADRESSE, MAIL, DOMAINE, DESCRIPTION, SEXE, IMAGE  FROM TABLE1 ORDER BY ADRESSE DESC");
    return model;
}


QSqlQueryModel* Artiste::afficher_tri_adresse_ascendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CAST(CIN AS VARCHAR(255)), CAST(TEL AS VARCHAR(255)), NOM, PRENOM, ADRESSE, MAIL, DOMAINE, DESCRIPTION, SEXE, IMAGE  FROM TABLE1 ORDER BY ADRESSE ASC");
    return model;
}



QSqlQueryModel* Artiste::afficher_tri_email_descendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CAST(CIN AS VARCHAR(255)), CAST(TEL AS VARCHAR(255)), NOM, PRENOM, ADRESSE, MAIL, DOMAINE, DESCRIPTION, SEXE, IMAGE  FROM TABLE1 ORDER BY MAIL DESC");
    return model;
}


QSqlQueryModel* Artiste::afficher_tri_email_ascendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CAST(CIN AS VARCHAR(255)), CAST(TEL AS VARCHAR(255)), NOM, PRENOM, ADRESSE, MAIL, DOMAINE, DESCRIPTION, SEXE, IMAGE  FROM TABLE1 ORDER BY MAIL ASC");
    return model;
}



QSqlQueryModel* Artiste::afficher_tri_domaine_descendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CAST(CIN AS VARCHAR(255)), CAST(TEL AS VARCHAR(255)), NOM, PRENOM, ADRESSE, MAIL, DOMAINE, DESCRIPTION, SEXE, IMAGE  FROM TABLE1 ORDER BY DOMAINE DESC");
    return model;
}


QSqlQueryModel* Artiste::afficher_tri_domaine_ascendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CAST(CIN AS VARCHAR(255)), CAST(TEL AS VARCHAR(255)), NOM, PRENOM, ADRESSE, MAIL, DOMAINE, DESCRIPTION, SEXE, IMAGE  FROM TABLE1 ORDER BY DOMAINE ASC");
    return model;
}





// fonction pour obteni tout les artistes

QStringList Artiste::obtenirTousArtistes()
{
    QStringList artistes;
    QSqlQuery query;
    query.prepare("SELECT NOM FROM TABLE1"); // Remplacez TABLE1 par le nom de votre table d'artistes
    if(query.exec())
    {
        while(query.next())
        {
            QString nomArtiste = query.value(0).toString();
            artistes.append(nomArtiste);
        }
    }
    return artistes;
}




