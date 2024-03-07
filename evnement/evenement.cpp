#include "evenement.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QDebug>
#include <QObject>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <qsqlerror.h>
int evenement::getIdEvent()
{
    return id_event ;
}
int evenement::getNbEmployee()
{
    return nb_employee ;
}
QString evenement::getEventNoun()
{
    return event_noun ;
}
QString evenement::getLocation()
{
    return location ;
}
QString evenement::getDescription()
{
    return description ;
}
QDate evenement::getStartD()
{
    return start_d ;
}
QDate evenement::getEndD()
{
    return end_d ;
}
QTime evenement::getStartH()
{
    return start_h ;
}
QTime evenement::getEndH()
{
    return end_h ;
}
float evenement::getPriceTick()
{
    return price_tick ;
}
//setters
void evenement::setIdEvent(int id_event)
{
     this ->id_event=id_event;
}
void evenement::setNbEmployee(int nb_employee)
{
     this ->nb_employee=nb_employee;
}
void evenement::setEventNoun(QString event_noun)
{
     this ->event_noun=event_noun;
}
void evenement::setLocation(QString location)
{
     this ->location=location;
}
void evenement::setDescription(QString description)
{
     this ->description=description;
}
void evenement::setStartD(QDate start_d)
{
     this ->start_d=start_d;
}
void evenement::setEndD(QDate end_d)
{
     this ->end_d=end_d;
}
void evenement::setStartH(QTime start_h)
{
     this ->start_h=start_h;
}
void evenement::setEndH(QTime end_h)
{
     this ->end_h=end_h;
}
void evenement::setPriceTick(float price_tick)
{
     this ->price_tick=price_tick;
}
evenement::evenement()
{
}
evenement::evenement(int id_event, int nb_employee, QString event_noun, QString location, QString description, QDate start_d, QDate end_d, QTime start_h, QTime end_h, float price_tick)
{
    this->id_event = id_event;
    this->nb_employee = nb_employee;
    this->event_noun = event_noun;
    this->location = location;
    this->description = description;
    this->start_d = start_d;
    this->end_d = end_d;
    this->start_h = start_h;
    this->end_h = end_h;
    this->price_tick = price_tick;
}

evenement evenement::chercher(int id_event)
{
    evenement e;  // Create an instance of the Employee class
    QString queryStr = QString("SELECT * FROM evenement WHERE id_event = %1").arg(id_event);
    QSqlQuery query;
    query.prepare(queryStr);

    if (query.exec())
    {
        if (query.next())
        {
            // Assuming your Employee class has setter methods, update them accordingly
            e.setIdEvent(query.value("id_event").toInt());
            e.setNbEmployee(query.value("nb_employee").toInt());
            e.setEventNoun(query.value("event_noun").toString());
            e.setLocation(query.value("location").toString());
            e.setDescription(query.value("description").toString());
            e.setStartD(query.value("start_d").toDate());
            e.setEndD(query.value("end_d").toDate());
            e.setStartH(query.value("start_h").toTime());
            e.setEndH(query.value("end_h").toTime());
            e.setPriceTick(query.value("price_tick").toInt());
        }
        else
        {
            // Handle the case when no records are found for the given ID
            qDebug() << "No records found for ID:" << id_event;
        }
    }
    else
    {
        // Handle the case when the query fails, e.g., log an error
        qDebug() << "Query failed:" << query.lastError().text();
    }

    return e;
}
bool evenement::ajouterEvenement()
{
    QSqlQuery query;
    //QString res=QString::number(id_event);
    id_event = generateNewID();
    QString nb=QString::number(nb_employee);
    QString prx=QString::number(price_tick);
    query.prepare("INSERT INTO EVENEMENT (ID_EVENT, NB_EMPLOYEE ,EVENT_NOUN,LOCATION ,DESCRIPTION ,START_D ,END_D,START_H,END_H,PRICE_TICK) "
                          "VALUES (:id_event,:nb_employee ,:event_noun,:location ,:description ,:start_d ,:end_d,:start_h,:end_h,:price_tick)");
            //query.bindValue(":id_event",res);
            query.bindValue(":id_event", id_event);
            query.bindValue(":nb_employee", nb);
            query.bindValue(":event_noun", event_noun);
            query.bindValue(":location", location);
            query.bindValue(":description", description);
            query.bindValue(":start_d", start_d);
            query.bindValue(":end_d", end_d);
            query.bindValue(":start_h", start_h);
            query.bindValue(":end_h", end_h);
            query.bindValue(":price_tick", prx);

            return query.exec();
}
QSqlQueryModel *evenement::afficherEvenement()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT ID_EVENT, EVENT_NOUN, LOCATION, CAST(START_D AS varchar(255)),  CAST(END_D AS varchar(255)), PRICE_TICK FROM EVENEMENT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_EVENT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("EVENT_NOUN"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("LOCATION"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("START_D"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("END_D"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("PRICE_TICK"));
    return model;
}

bool evenement::supprimerEvenement(QString event_noun)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EVENEMENT WHERE event_noun = :event_noun");
    query.bindValue(":event_noun", event_noun);
    if (!query.exec()) {
        qDebug() << "Delete failed: " ;  // Detailed error message
        return false;
    }
    return query.exec();
}
int evenement::generateNewID()
{
    QSqlQuery query;
    query.exec("SELECT MAX(id_event) FROM evenement");
    if (query.next()) {
        return query.value(0).toInt() + 1;
    } else {
        return 1;
    }
}

bool evenement::modifierEvenement()
{
    QSqlQuery query;
    query.prepare("UPDATE EVENEMENT SET nb_employee = :nb_employee, event_noun = :event_noun, location = :location, description = :description, start_d = :start_d, end_d = :end_d, start_h = :start_h, end_h = :end_h, price_tick = :price_tick WHERE id_event = :id_event");

    // Convert numeric values to strings
    QString nb = QString::number(nb_employee);
    QString prx = QString::number(price_tick);

    query.bindValue(":id_event", id_event);
    query.bindValue(":nb_employee", nb);
    query.bindValue(":event_noun", event_noun);
    query.bindValue(":location", location);
    query.bindValue(":description", description);
    query.bindValue(":start_d", start_d);
    query.bindValue(":end_d", end_d);
    query.bindValue(":start_h", start_h);
    query.bindValue(":end_h", end_h);
    query.bindValue(":price_tick", prx);

    // Execute the query and return the result
    if (!query.exec()) {
        qDebug() << "Erreur SQL:" << query.lastError().text();
        return false;
    }
    return true;
}




QSqlQueryModel* evenement::afficher_tri(const QString &critere)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QString query = "SELECT * FROM EVENEMENT ORDER BY ";

    if(critere == "ID") {
        query += "ID_EVENT";
    } else if(critere == "Noun Event") {
        query += "EVENT_NOUN";
    } else if(critere == "Date") {
        query += "START_D";
    }

    model->setQuery(query);
    return model;
}
QSqlQueryModel* evenement::rechercher(QString e)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT ID_EVENT, EVENT_NOUN, LOCATION, START_D, START_H, END_D, END_H, PRICE_TICK FROM EVENEMENT WHERE EVENT_NOUN LIKE '%" + e + "%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_EVENT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("EVENT_NOUN"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("LOCATION"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("START_D"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("START_H"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("END_D"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("END_H"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("PRICE_TICK"));
    return model;
}
