#include "controller.h"
#include "QString"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
controller::controller()
{
this->id_event=0;
this->id=0;
}

controller::controller(int id,int id_event)
{
  this->id_event=id_event;
  this->id=id;
}
bool controller::ajouterController()
{
    QSqlQuery query;

    query.prepare("INSERT INTO controller (id, id_event) "
                  "VALUES (:id, :id_event)");
    query.bindValue(":id", id);
    query.bindValue(":id_event",id_event);

    return query.exec();
}

