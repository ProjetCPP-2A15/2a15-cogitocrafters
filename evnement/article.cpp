#include "article.h"
#include <QSqlQuery>
#include <QDebug>

Article::Article(QString domaine_article, QString nom_article, QString date_creation_article, QString type_article, QString dimension_article, int poids_article, int prix_article, QString description_article, QString chemin_image)
{
    this->domaine_article = domaine_article;
    this->nom_article = nom_article;
    this->date_creation_article = date_creation_article;
    this->type_article = type_article;
    this->dimension_article = dimension_article;
    this->poids_article = poids_article;
    this->prix_article = prix_article;
    this->description_article = description_article;
    this->chemin_image = chemin_image;

}

bool Article::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO ARTICLE (domaine_article, nom_article, date_creation_article, type_article, dimension_article, poids_article, prix_article, description_article, chemin_image) "
                      "VALUES (:domaine_article, :nom_article, :date_creation_article, :type_article, :dimension_article, :poids_article, :prix_article, :description_article, :chemin_image)");
    query.bindValue(":id_article", id_article);
    query.bindValue(":domaine_article", domaine_article);
    query.bindValue(":nom_article", nom_article);
    query.bindValue(":date_creation_article", date_creation_article);
    query.bindValue(":type_article", type_article);
    query.bindValue(":dimension_article", dimension_article);
    query.bindValue(":poids_article", poids_article);
    query.bindValue(":prix_article", prix_article);
    query.bindValue(":description_article", description_article);
    query.bindValue(":chemin_image", chemin_image); // Lié au champ d'image

    return query.exec();
}

QSqlQueryModel * Article::afficher()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from ARTICLE");
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Domaine"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de création"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Dimension"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Poids"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Description"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("gfb"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("image"));



    return model;
}

bool Article::supprimer(int id_article)
{
    QSqlQuery query;
    query.prepare("DELETE FROM ARTICLE WHERE id_article = :id_article");
    query.bindValue(":id_article", id_article);
    if (!query.exec()) {
        qDebug() << "Delete failed: " ; // Detailed error message
        return false;
    }
    return true;
}

QSqlQueryModel* Article::rechercher(QString nom)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ARTICLE WHERE nom_article LIKE '%" + nom + "%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Domaine"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de création"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Dimension"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Poids"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Description"));
    return model;
}

bool Article::modifier(int id_article, const QString &domaine, const QString &nom, const QString &date_creation, const QString &type, const QString &dimension, int poids, int prix, const QString &description, const QString &chemin_image) {
    QSqlQuery query;
    query.prepare("UPDATE ARTICLE SET domaine_article = :domaine, nom_article = :nom, date_creation_article = :date_creation, type_article = :type, dimension_article = :dimension, poids_article = :poids, prix_article = :prix, description_article = :description, chemin_image = :chemin_image WHERE id_article = :id_article");
    query.bindValue(":id_article", id_article);
    query.bindValue(":domaine", domaine);
    query.bindValue(":nom", nom);
    query.bindValue(":date_creation", date_creation);
    query.bindValue(":type", type);
    query.bindValue(":dimension", dimension);
    query.bindValue(":poids", poids);
    query.bindValue(":prix", prix);
    query.bindValue(":description", description);
    query.bindValue(":chemin_image", chemin_image);

    return query.exec();
}


QSqlQueryModel* Article::afficherTriId() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ARTICLE ORDER BY id_article");
    return model;
}

QSqlQueryModel* Article::afficherTriNom() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ARTICLE ORDER BY nom_article");
    return model;
}

QSqlQueryModel* Article::afficherTriDate() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ARTICLE ORDER BY date_creation_article");
    return model;
}



