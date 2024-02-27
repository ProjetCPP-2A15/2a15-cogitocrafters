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

public:
    //cons
    Artiste(){}
    Artiste(int,int,QString,QString,QString,QString,QString,QString,QString);

    //get
    int getCin(){return cin;}
    int getTel(){return tel;}
    QString getNom(){return nom;}
    QString getPrenom(){return prenom;}
    QString getAdresse(){return adresse;}
    QString getMail(){return mail;}
    QString getDomaine(){return domaine;}
    QString getDescription(){return description;}
    QString getSexe(){return sexe;}

    //setters
    void setCin(int cin){this->cin=cin;}
    void setTel(int tel){this->tel=tel;}
    void setNom(QString nom){this->nom=nom;}
    void setPrenom(QString prenom){this->prenom=prenom;}
    void setAdresse(QString adresse){this->adresse=adresse;}
    void setMail(QString mail){this->mail=mail;}
    void setDomaine(QString domaine){this->domaine=domaine;}
    void setDescription(QString description){this->description=description;}
    void setSexe(QString sexe){this->sexe=sexe;}

    //fonction
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * affichers();
    bool supprimer(int cin);
    QSqlQueryModel* afficher_tri_cin();
    QSqlQueryModel* afficher_tri_nom();
    QSqlQueryModel* afficher_tri_prenom();
    QSqlQueryModel* rechercher(QString A);
    bool modifier(int,int,QString,QString,QString,QString,QString,QString,QString);
};

#endif // ARTIST_H
