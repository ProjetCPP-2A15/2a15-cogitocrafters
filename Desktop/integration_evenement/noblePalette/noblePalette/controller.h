#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QVector>

class controller
{
public:
    controller();
    controller(int,int);
    bool ajouterController();
    QVector<QStringList> getControllerDetails();

private:
    int id_event,id;
};

#endif // CONTROLLER_H
