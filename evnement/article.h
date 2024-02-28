#ifndef ARTICLE_H
#define ARTICLE_H

#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

class Article
{
    int id_article;
    QString domaine_article;
    QString nom_article;
    QString date_creation_article; // Consider using a more specific date type
    QString type_article;
    QString dimension_article;
    int poids_article;
    int prix_article;
    QString description_article;
    QString chemin_image; // Nouveau membre pour le chemin de l'image



public:
    // Constructor
    Article(){}
    Article(QString, QString, QString, QString, QString, int, int, QString ,QString);

    // Getters
    int getIdArticle() { return id_article; }
    QString getDomaineArticle() { return domaine_article; }
    QString getNomArticle() { return nom_article; }
    QString getDateCreationArticle() { return date_creation_article; }
    QString getTypeArticle() { return type_article; }
    QString getDimensionArticle() { return dimension_article; }
    int getPoidsArticle() { return poids_article; }
    int getPrixArticle() { return prix_article; }
    QString getDescriptionArticle() { return description_article; }
    QString getCheminImage() const { return chemin_image; } // Getter pour le chemin de l'image


    // Setters
    void setIdArticle(int id) { id_article = id; }
    void setDomaineArticle(QString domaine) { domaine_article = domaine; }
    void setNomArticle(QString nom) { nom_article = nom; }
    void setDateCreationArticle(QString date) { date_creation_article = date; }
    void setTypeArticle(QString type) { type_article = type; }
    void setDimensionArticle(QString dimension) { dimension_article = dimension; }
    void setPoidsArticle(int poids) { poids_article = poids; }
    void setPrixArticle(int prix) { prix_article = prix; }
    void setDescriptionArticle(QString description) { description_article = description; }
    void setCheminImage(const QString &chemin) { chemin_image = chemin; } // Setter pour le chemin de l'image


    // Methods
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * affichers();
    bool supprimer(int id);
    QSqlQueryModel* afficherTriId();
    QSqlQueryModel* afficherTriNom();
    QSqlQueryModel* afficherTriDate();
    QSqlQueryModel* rechercher(QString);
    bool modifier(int id_article,const QString &domaine, const QString &nom, const QString &date_creation, const QString &type, const QString &dimension, int poids, int prix, const QString &description, const QString &chemin_image);

};

#endif // ARTICLE_H
