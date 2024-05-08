#ifndef ARTIST_H
#define ARTIST_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QTableView>


class Artiste
{
    int cin;
    int tel;
    QString nom;
    QString prenom;
    QString adresse;
    QString mail;
    QString domaine;
    QString description;
    QString sexe;
    QByteArray image; // Nouveau champ pour l'image

public:
    // Constructeurs
    Artiste(){}
    Artiste(int, int, QString, QString, QString, QString, QString, QString, QString, QByteArray);

    // Getters
    int getCin(){ return cin; }
    int getTel(){ return tel; }
    QString getNom(){ return nom; }
    QString getPrenom(){ return prenom; }
    QString getAdresse(){ return adresse; }
    QString getMail(){ return mail; }
    QString getDomaine(){ return domaine; }
    QString getDescription(){ return description; }
    QString getSexe(){ return sexe; }
    QByteArray getImage(){ return image; } // Getter pour l'image

    // Setters
    void setCin(int cin){ this->cin = cin; }
    void setTel(int tel){ this->tel = tel; }
    void setNom(QString nom){ this->nom = nom; }
    void setPrenom(QString prenom){ this->prenom = prenom; }
    void setAdresse(QString adresse){ this->adresse = adresse; }
    void setMail(QString mail){ this->mail = mail; }
    void setDomaine(QString domaine){ this->domaine = domaine; }
    void setDescription(QString description){ this->description = description; }
    void setSexe(QString sexe){ this->sexe = sexe; }
    void setImage(QByteArray image){ this->image = image; } // Setter pour l'image

    // Fonctions
    bool ajouter();
    QSqlQueryModel *afficher();
    QSqlQueryModel *affichers();
    bool supprimer(int cin);

    QSqlQueryModel* afficher_tri_cin_descendant();
    QSqlQueryModel* afficher_tri_cin_ascendant();
    QSqlQueryModel* afficher_tri_nom_descendant();
    QSqlQueryModel* afficher_tri_nom_ascendant();
    QSqlQueryModel* afficher_tri_prenom_descendant();
    QSqlQueryModel* afficher_tri_prenom_ascendant();
    QSqlQueryModel* afficher_tri_tel_descendant();
    QSqlQueryModel* afficher_tri_tel_ascendant();
    QSqlQueryModel* afficher_tri_adresse_descendant();
    QSqlQueryModel* afficher_tri_adresse_ascendant();
    QSqlQueryModel* afficher_tri_email_descendant();
    QSqlQueryModel* afficher_tri_email_ascendant();
    QSqlQueryModel* afficher_tri_domaine_descendant();
    QSqlQueryModel* afficher_tri_domaine_ascendant();



    QSqlQueryModel *rechercher(QString lettreOuMot);
    bool modifier(int cin, int tel, QString nom, QString prenom, QString adresse, QString mail, QString domaine, QString description, QString sexe, QByteArray image);

    // liste des artistes
    QStringList obtenirTousArtistes();

};




#endif // ARTIST_H
