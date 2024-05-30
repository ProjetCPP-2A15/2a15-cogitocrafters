#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QString>
#include<QDate>
#include <QSqlQueryModel>
#include<QByteArray>
#include<QLabel>
#include<QtDebug>
class employee
{
public:
    employee();
    employee(int ,QString , QString ,QString ,QString,QString,QString ,QString ,QDate, int,QString ) ;
    employee(int ,QString , QString ,QString ,QString,QString,QString ,QString ,QDate, int ) ;

    int getId(){return id;}
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

    QSqlQueryModel* afficher_tri_id_descendant();
    QSqlQueryModel* afficher_tri_name_descendant();
    QSqlQueryModel* afficher_tri_lastname_descendant();
    QSqlQueryModel* afficher_tri_address_descendant();
    QSqlQueryModel* afficher_tri_function_descendant();
    QSqlQueryModel* afficher_tri_mail_descendant();

    QSqlQueryModel* afficher_tri_id_aescendant();
    QSqlQueryModel* afficher_tri_name_aescendant();
    QSqlQueryModel* afficher_tri_lastname_aescendant();
    QSqlQueryModel* afficher_tri_address_aescendant();
    QSqlQueryModel* afficher_tri_function_aescendant();
    QSqlQueryModel* afficher_tri_mail_aescendant();

    int genererEntierQuatreChiffres() ;
    int sendEmail(const QString &to, const QString &subject, const QString &body);
    void sendSMS(const QString& accountSid, const QString& authToken, const QString& fromNumber, QString toNumber, QString message);
    bool chercherMail(QString );
    int chercherMailId(QString);
    QString chercherFunction(QString);
    bool SaveNewPassword(QString,QString);
    void afficherPieChart(QLabel *label);
    int chercherMailPhoneNumber(QString mail);

private:
  int id,phoneNumber;
  QString name,lastname,address,sex,mail,function,password,imagePath;
  QDate dateBirth;
  QByteArray imageData;

};
#endif // EMPLOYEE_H
