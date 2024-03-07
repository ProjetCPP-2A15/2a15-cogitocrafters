#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QString>
#include<QDate>
#include <QSqlQueryModel>
#include<QByteArray>

class employee
{
public:
    employee();
    employee(int ,QString , QString ,QString ,QString,QString,QString ,QString ,QDate, int,QString ) ;
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
    int getPhoneNumber(){return phoneNumber;}
    QString getImagePath(){return imagePath;}
    QByteArray getImageData(){return imageData;}


    void setId(int);
    void setName(QString);
    void setLastname(QString);
    void setAddress(QString);
    void setSex(QString);
    void setDateBirth(QDate);
    void setMail(QString);
    void setFunction(QString);
    void setPassword(QString);
    void setPhoneNumber(int);
    void setImagePath(QString);
    void setImageData(QByteArray);


    bool ajouterEmployee();
    bool suprimerEmployee(int);
    QSqlQueryModel * afficherEmployee();
    bool modifierEmployee();
    bool modifierImage(QString );

    employee chercher(int id_chercher);
    QSqlQueryModel* afficher_tri(const QString &critere) ;
    QSqlQueryModel* rechercher(QString e);
    bool login(QString username, QString password);
    QStringList getEncryptedPasswords();


private:
  int id,phoneNumber;
  QString name,lastname,address,sex,mail,function,password,imagePath;
  QDate dateBirth;
  QByteArray imageData;

};
#endif // EMPLOYEE_H
