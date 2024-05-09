#ifndef GUEST_H
#define GUEST_H

#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QString>
#include<QSqlTableModel>
#include<QMessageBox>
#include"connection.h"


class Guest {
private:
    int CIN;
    QString name;
    int age;
    QString gender;
    QString address;
    int phone;
    QString email;
    QString imagePath;

public:
    // Constructeur avec initialisation des attributs
    Guest(){}
    Guest(int ,QString , int , QString , QString , int , QString, QString );

    // Méthodes pour accéder aux attributs
    QString getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    QString getGender() const {
        return gender;
    }

    QString getAddress() const {
        return address;
    }

    int getPhone() const {
        return phone;
    }

    QString getEmail() const {
        return email;
    }

    QString getImage() const {
        return imagePath;
    }

    // Setters pour modifier les attributs
    void setName(const QString& n) {
        name = n;
    }

    void setAge(int a) {
        age = a;
    }

    void setGender(const QString& g) {
        gender = g;
    }

    void setAddress(const QString& adr) {
        address = adr;
    }

    void setPhone(int ph) {
        phone = ph;
    }

    void setEmail(const QString& e) {
        email = e;
    }
    void setImage(const QString& i) {
        imagePath = i;
    }

    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int cin);
    bool modifierImage(int ,int ,QString ,int ,QString ,QString ,QString ,int,QString);
    bool modifier(int ,int ,QString ,int ,QString ,QString ,QString ,int);

    QSqlQueryModel* rechercher(QString );
    QSqlQueryModel* afficher_tri(const QString &critere);
    QSqlQueryModel *afficherId(int cin);

    QSqlQueryModel* afficher_tri_CIN(bool checked);
    QSqlQueryModel* afficher_tri_Name(bool checked);
    QSqlQueryModel* afficher_tri_Age(bool checked);
    QSqlQueryModel* afficher_tri_Gender(bool checked);
    QSqlQueryModel* afficher_tri_Address(bool checked);
    QSqlQueryModel* afficher_tri_Phone(bool checked);
    QSqlQueryModel* afficher_tri_Email(bool checked);
    QSqlQueryModel* precence(int id_event);








};


#endif // GUEST_H
