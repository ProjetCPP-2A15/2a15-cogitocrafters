#include "employee.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <qsqlerror.h>
employee::employee()
{
    id=0;
    name="";
    lastname="";
    address="";
    sex="";
    dateBirth=QDate();
    mail="";
    function="";
    password="";
    //profil="";
    phoneNumber=0;
}
employee::employee(int id,QString name, QString lastname,QString address,QString sex,QString mail,QString function,QString password,QDate dateBirth,int phoneNumber)
{
    this->id=id;
    this->name=name;
    this->lastname=lastname;
    this->address=address;
    this->sex=sex;
    this->dateBirth=dateBirth;
    this->mail=mail;
    this->function=function;
    this->password=password;
    //this->profil=profil;
    this->phoneNumber=phoneNumber;
}
void employee::setId(int id){this ->id=id;}
void employee::setName(QString name){this->name=name;}
void employee::setLastname(QString lastname){this->lastname=lastname;}
void employee::setAddress(QString address){this->address=address;}
void employee::setSex(QString sex){this->sex=sex;}
void employee::setDateBirth(QDate dateBirth){this->dateBirth=dateBirth;}
void employee::setMail(QString mail){this->mail=mail;}
void employee::setFunction(QString function){this->function=function;}
void employee::setPassword(QString password){this->password=password;}
//void employee::setProfil(QString profil){this->profil=profil;}
void employee::setPhoneNumber(int phoneNumber){this->phoneNumber=phoneNumber;}



bool employee::ajouterEmployee()
{
    QSqlQuery query;
    QString id_string=QString::number(id);
    QString phoneNumber_string=QString::number(phoneNumber);

    query.prepare("INSERT INTO employee (id, name ,lastname,address ,sex ,dateBirth ,mail,function,password,phoneNumber) "
                        "VALUES (:id,:name ,:lastname,:address ,:sex ,:dateBirth ,:mail,:function,:password,:phoneNumber)");
          query.bindValue(":id",id_string);
          query.bindValue(":name", name);
          query.bindValue(":lastname", lastname);
          query.bindValue(":address", address);
          query.bindValue(":sex", sex);
          query.bindValue(":dateBirth", dateBirth);
          query.bindValue(":mail", mail);
          query.bindValue(":function", function);
          query.bindValue(":password", password);
          //query.bindValue(":profil", profilByteArray);
          //query.bindValue(":profil", profil);
          query.bindValue(":phoneNumber", phoneNumber_string);

          return query.exec();
}
QSqlQueryModel * employee::afficherEmployee()
{
    QSqlQueryModel* model=new  QSqlQueryModel();
          model->setQuery("SELECT id,name,lastname,address,function,mail FROM employee");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("name"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("lastname"));
          //model->setHeaderData(3, Qt::Horizontal, QObject::tr("phoneNumber"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("address"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("function"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("mail"));


    return model;
}
employee employee::chercher(int id_chercher)
{
    employee employee;  // Create an instance of the Employee class
    QString queryStr = QString("SELECT * FROM employee WHERE id = %1").arg(id_chercher);
    QSqlQuery query;
    query.prepare(queryStr);

    if (query.exec())
    {
        if (query.next())
        {
            // Assuming your Employee class has setter methods, update them accordingly
            employee.setId(query.value("id").toInt());
            employee.setName(query.value("name").toString());
            employee.setLastname(query.value("lastname").toString());
            employee.setAddress(query.value("address").toString());
            employee.setSex(query.value("sex").toString());
            employee.setDateBirth(query.value("dateBirth").toDate());
            employee.setMail(query.value("mail").toString());
            employee.setFunction(query.value("function").toString());
            employee.setPassword(query.value("password").toString());
            employee.setPhoneNumber(query.value("phoneNumber").toInt());
        }
        else
        {
            // Handle the case when no records are found for the given ID
            qDebug() << "No records found for ID:" << id_chercher;
        }
    }
    else
    {
        // Handle the case when the query fails, e.g., log an error
        qDebug() << "Query failed:" << query.lastError().text();
    }

    return employee;
}
bool employee::suprimerEmployee(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);
          query.prepare("DELETE FROM employee WHERE id= :id");
          query.bindValue(":id", res);
          return query.exec();
}

bool employee::modifierEmployee()
{
    QSqlQuery query;
          query.prepare("UPDATE EMPLOYEE SET id=:id,name= :name, lastname= :lastname, address= :address, sex= :sex, mail= :mail,function= :function ,phoneNumber= :phoneNumber,password=:password,dateBirth=:dateBirth where id =:id");
          query.bindValue(":id",id);
          query.bindValue(":name", name);
          query.bindValue(":lastname", lastname);
          query.bindValue(":address", address);
          query.bindValue(":sex", sex);
          query.bindValue(":dateBirth", dateBirth);
          query.bindValue(":mail", mail);
          query.bindValue(":function", function);
          query.bindValue(":password", password);
          //query.bindValue(":profil", profilByteArray);
          //query.bindValue(":profil", profil);
          query.bindValue(":phoneNumber", phoneNumber);
           return query.exec();
}
QSqlQueryModel * employee::afficher_tri(const QString &critere)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QString query = "SELECT * FROM EMPLOYEE ORDER BY ";

    if(critere == "CIN") {
        query += "id";
    } else if(critere == "Address") {
        query += "Address";
    } else if(critere == "Name") {
        query += "NAME";
    }

    model->setQuery(query);
    return model;
}
QSqlQueryModel* employee::rechercher(QString e)
{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("SELECT id,name,lastname,address,function,mail FROM employee WHERE NAME LIKE '%" + e + "%'");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("lastname"));
    //model->setHeaderData(3, Qt::Horizontal, QObject::tr("phoneNumber"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("address"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("function"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("mail"));

    return model;
}
