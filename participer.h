#ifndef PARTICIPER_H
#define PARTICIPER_H

#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QString>
#include<QSqlTableModel>
#include<QMessageBox>
#include"connection.h"

class Participer {
private:
    int idGuest,idEvent,precence;

public:
    // Constructeur avec initialisation des attributs
    Participer(){}
    Participer(int ,int ,int );

    // Méthodes pour accéder aux attributs
    int getIdGuest() const {
        return idGuest;
    }

    int getIdEvent() const {
        return idEvent;
    }

    int getPrecence() const {
        return precence;
    }

    // Setters pour modifier les attributs

    void setIdGuest(int g) {
        idGuest = g;
    }

    void setIdEvent(int e) {
        idEvent = e;
    }

    void setPrecence(int p) {
        precence = p;
    }
    Participer(int,int);

    QSqlQueryModel* idGuests(int id_event);
    void precenceGuest(int id_event, int id_guest);
    QSqlQueryModel* getGuestsInfo(int idevent);
    bool supprimerp(int cin);
    QSqlQueryModel* getAllGuestsInfo(int idevent);
    bool ajouterp();












};

#endif // PARTICIPER_H
