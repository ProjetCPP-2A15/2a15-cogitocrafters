#ifndef EVENEMENT_H
#define EVENEMENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDateTime>
#include <QtWidgets>
#include <QPrinter>
#include <QPainter>
class evenement
{
private:
    int id_event,nb_employee;
    QString event_noun,location,description;
    QDate start_d,end_d;
    QTime start_h,end_h;
    float price_tick;

public:
    //getters
    int getIdEvent();
    int getNbEmployee();
    QString getEventNoun();
    QString getLocation();
    QString getDescription();
    QDate getStartD();
    QDate getEndD();
    QTime getStartH();
    QTime getEndH();
    float getPriceTick();
    //setters
    void setIdEvent(int);
    void setNbEmployee(int);
    void setEventNoun(QString);
    void setLocation(QString);
    void setDescription(QString);
    void setStartD(QDate);
    void setEndD(QDate);
    void setStartH(QTime);
    void setEndH(QTime);
    void setPriceTick(float);
    //methode
    evenement chercher(int);
    int generateNewID();
    bool ajouterEvenement();
    QSqlQueryModel * afficherEvenement();
    evenement();
    evenement(int,int,QString,QString,QString,QDate,QDate,QTime,QTime,float);
    bool supprimerEvenement(QString event_noun);
    bool modifierEvenement();
    QSqlQueryModel* afficher_tri(const QString &critere);
};

#endif // EVENEMENT_H
