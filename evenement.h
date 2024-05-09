#ifndef EVENEMENT_H
#define EVENEMENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDateTime>
#include <QtWidgets>
#include <QPrinter>
#include <QPainter>
#include <QCalendarWidget>
class evenement
{
private:
    int id_event,nb_employee;
    QString event_noun,location,description,imagePath;
    QDate start_d,end_d;
    QTime start_h,end_h;
    float price_tick;
    QByteArray affiche;
    QString RFID;

public:
    //getters
    int getIdEvent()const;
    int getNbEmployee()const;
    QString getEventNoun()const;
    QString getLocation()const;
    QString getDescription()const;
    QDate getStartD()const;
    QDate getEndD()const;
    QTime getStartH()const;
    QTime getEndH()const;
    float getPriceTick()const;
    QByteArray getAffiche()const;
    QString getImagePath()const;

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
    void setAffiche(QByteArray);
    void setImagePath(QString);

    //methode
    evenement chercher(int);
    int generateNewID();
    bool ajouterEvenement();
    QSqlQueryModel * afficherEvenement();
    evenement();
    evenement(int,int,QString,QString,QString,QDate,QDate,QTime,QTime,float);
    evenement(int,int,QString,QString,QString,QDate,QDate,QTime,QTime,float,QString);
    int rechercherRFID(QString rfid);

    evenement(int,QString);
    bool supprimerEvenement(QString event_noun);
    bool modifierEvenement();
    QSqlQueryModel* afficher_tri(const QString &critere);
    QSqlQueryModel* rechercher(QString G);
    QSqlQueryModel* afficher_tri_id_descendant();
    QSqlQueryModel* afficher_tri_id_ascendant();
    QSqlQueryModel* afficher_tri_nom_descendant();
    QSqlQueryModel* afficher_tri_nom_ascendant();
    QSqlQueryModel* afficher_tri_location_descendant();
    QSqlQueryModel* afficher_tri_location_ascendant();
    QSqlQueryModel* afficher_tri_start_descendant();
    QSqlQueryModel* afficher_tri_start_ascendant();
    QSqlQueryModel* afficher_tri_end_descendant();
    QSqlQueryModel* afficher_tri_end_ascendant();
    QSqlQueryModel* afficher_tri_price_descendant();
    QSqlQueryModel* afficher_tri_price_ascendant();
    void afficherPieChart(QLabel *label);
    bool ajouterImage(int id);
    void updateEventComboBox(QComboBox *comboBox);


};

#endif // EVENEMENT_H
