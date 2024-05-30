#include "map.h"
#include "association.h"
#include <QQuickItem>
#include <QGeoRoute>
#include <QGeoRouteRequest>
#include <QGeoCoordinate>
#include <QGeoServiceProvider>
#include <QDebug> // Ajout pour le débogage
#include <QGeoRoutingManager>
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>


map::map(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::map)
{
    ui->setupUi(this);
    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
    ui->quickWidget->show();

    auto obj = ui->quickWidget->rootObject();
    connect(this, SIGNAL(setCenter(QVariant, QVariant)), obj, SLOT(setCenter(QVariant, QVariant)));
    connect(this, SIGNAL(addMarker(QVariant, QVariant)), obj, SLOT(addMarker(QVariant, QVariant)));

    // Connectez le signal infoTextChanged du QML au slot updateInfoText de MainWindow
    connect(obj, SIGNAL(infoTextChanged(QString)), this, SLOT(updateInfoText(QString)));

    // Coordonnées de l'ESPRIT (latitude et longitude)
    double latESPRIT = 36.898521;
    double lngESPRIT = 10.187598;


    emit setCenter(latESPRIT, lngESPRIT); // Définit le centre de la carte sur l'ESPRIT
    emit addMarker(latESPRIT, lngESPRIT);
}

map::~map()
{
    delete ui;
}

void map::on_list_2_clicked()
{
    equipp = new equipment(this);
    equipp->show();
}



// Slot pour mettre à jour le texte de la bulle d'information
// Slot pour mettre à jour le texte de la bulle d'information et contrôler la visibilité du QLabel








