#ifndef ASSOCIATION_H
#define ASSOCIATION_H

#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QTableView>
class Association
{
private :
    //int id;
    int budget;
    QString nom;
    QString adresse;
    QString description;
public:
    //cons
    Association(){}
    Association(int,QString,QString,QString);

    //get
   // int getId(){return id;}
    int getBudget(){return budget;}
    QString getNom(){return nom;}
    QString getAdresse(){return adresse;}
    QString getDescription(){return description;}

    //setters
  //  void setId(int id){this->id=id;}
    void setBudget(int budget){this->budget=budget;}
    void setNom(QString nom){this->nom=nom;}
    void setAdresse(QString adresse){this->adresse=adresse;}
    void setDescription(QString description){this->description=description;}

    //fonction
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficher2();
    bool supprimer(int cin);
    QSqlQueryModel* afficher_tri_budget();
    QSqlQueryModel* afficher_tri_nom();
    QSqlQueryModel* afficher_tri_adresse();
    QSqlQueryModel* rechercher(QString A);
    bool modifier(int,int,QString,QString,QString);
};



#endif // ASSOCIATION_H
