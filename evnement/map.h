#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QMainWindow>
#include <QVariant>
#include <QtCore>
#include <QtGui>
#include <QtQuick>

namespace Ui {

class map;
}

class map : public QWidget
{
    Q_OBJECT

public:
    explicit map(QWidget *parent = nullptr);
    ~map();

private slots:
    void on_list_2_clicked();


private:
    Ui::map *ui;


signals:
    void setCenter(QVariant, QVariant);
    void addMarker(QVariant lat, QVariant lng);


};

#endif // MAP_H
