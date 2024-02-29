#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QString>
#include<QDate>
#include <QSqlQueryModel>
class employee
{
public:
    employee();
    employee(int ,QString , QString ,QString ,QString,QString,QString ,QString ,QDate, int ) ;

    int getId();
    QString getName(){return name;}
    QString getLastname(){return lastname;}
    QString getAddress(){return address;}
    QString getSex(){return sex;}
    QDate getDateBirth(){return dateBirth;}
    QString getMail(){return mail;}
    QString getFunction(){return function;}
    QString getPassword(){return password;}
    //QString getProfil(){return profil;}
    int getPhoneNumber(){return phoneNumber;}

    void setId(int);
    void setName(QString);
    void setLastname(QString);
    void setAddress(QString);
    void setSex(QString);
    void setDateBirth(QDate);
    void setMail(QString);
    void setFunction(QString);
    void setPassword(QString);
    //void setProfil(QString);
    void setPhoneNumber(int);

    bool ajouterEmployee();
    bool suprimerEmployee(int);
    QSqlQueryModel * afficherEmployee();
    bool modifierEmployee();

    employee chercher(int id_chercher);
    QSqlQueryModel* afficher_tri(const QString &critere) ;
    QSqlQueryModel* rechercher(QString e);


private:
  int id,phoneNumber;
  QString name,lastname,address,sex,mail,function,password;
  QDate dateBirth;
  QByteArray profil;
};
#endif // EMPLOYEE_H
