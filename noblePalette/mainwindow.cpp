#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>
#include <QPdfWriter>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QDebug>
#include <QFileDialog>

#include <QPrinter>

#include <QPainter>
#include <QProcess>
#include <QDebug>
#include <QQuickItem>
#include <QObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,manager(new QNetworkAccessManager(this))//weather
{
    ui->setupUi(this);

 //employee
    ui->tabEmployee->setModel(emp.afficherEmployee());
    connect(ui->searchTextBox_employee, &QLineEdit::textEdited, this, &MainWindow::on_searchTextBox_employee_textEdited);
    // Dans votre constructeur ou initialisation
    //connect(ui->lineEdit_PasswordEmployee, &QLineEdit::textChanged, this, &MainWindow::verifyPasswordStrength);
    ui->tabEmployee->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tabEmployee->setSelectionMode(QAbstractItemView::ExtendedSelection);

    //event
    // connect(ui->generateAffiche, &QPushButton::clicked, this, &MainWindow::on_generateAffiche_clicked);
    ui->table_event->setModel(e.afficherEvenement());
    connect(ui->searchevent, &QLineEdit::textEdited, this, &MainWindow::on_searchevent_textEdited);
    ui->table_event->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_event->setSelectionMode(QAbstractItemView::ExtendedSelection);


    //Guest
    connect(ui->searchGuest, &QLineEdit::textEdited, this, &MainWindow::on_searchGuest_textEdited);
    ui->tableViewGuest->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewGuest->setSelectionMode(QAbstractItemView::ExtendedSelection);

    ui->tableViewParticiper->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewParticiper->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableViewParticiper_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewParticiper_2->setSelectionMode(QAbstractItemView::ExtendedSelection);



    //ui->stackedWidgetGlobal->setCurrentIndex(0);
//partie artiste et article
    ui->artableView_3->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->artableView_3->setSelectionMode(QAbstractItemView::ExtendedSelection);
 // Activez la sélection multiple

 //connect(ui->rating, &QPushButton::clicked, this, &MainWindow::on_rating_clicked);
 connect(ui->gerervedio, &QPushButton::clicked, this, &MainWindow::on_gerervedio_clicked);


 // ################pour le recherchearticle################################
 connect(ui->searchTextBox_19, &QLineEdit::textChanged, this, &MainWindow::on_searchTextBox_19_textChanged);
 // Connexion du signal currentIndexChanged du comboBoxTri à la méthode de tri appropriée
     ui->tableView_4->setSelectionBehavior(QAbstractItemView::SelectRows);
     ui->tableView_4->setSelectionMode(QAbstractItemView::ExtendedSelection);
speech = new QTextToSpeech(this);

int ret=A.connect_arduino();
               // lancer la connexion à arduino
              switch(ret){
              case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
                  break;
              case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
                 break;
              case(-1):qDebug() << "arduino is not available";
              }

}

MainWindow::~MainWindow()
{
    delete ui;
    delete manager;
    delete speech;

}
void MainWindow::selectButton(QPushButton *button) {
    button->setStyleSheet("background: #8BD086;box-shadow: 0px 4px 4px rgba(0, 0, 0, 0.25);border: none;font-family: 'Athiti';font-style: normal;font-weight: 700;font-size: 20px;line-height: 32px;text-align: center;color: #2A501F;border-radius:15px;border-bottom:3px solid #669B37;");
}

// Fonction pour désélectionner un bouton
void MainWindow::deselectButton(QPushButton *button) {
    button->setStyleSheet("QPushButton {background: #A9E4A4;border: none;font-family: 'Athiti';font-style: normal;font-weight: 700;font-size: 20px;line-height: 32px;text-align: center;color: #2A501F;border-radius:15px;border-bottom:3px solid #669B37;}QPushButton:hover {background: #8BD086;box-shadow: 0px 4px 4px rgba(0, 0, 0, 0.25);}");
}

void MainWindow::on_pushButtonEmployee_clicked()
{
    ui->StackedWidget->setCurrentIndex(0);
    ui->stackedWidgetEmployee->setCurrentIndex(1);
    ui->tabEmployee->setModel(emp.afficherEmployee());
    deselectButton(ui->pushButtonEvents);
    deselectButton(ui->pushButtonProduct);
    deselectButton(ui->pushButtonGuest);
    deselectButton(ui->pushButtonArtist);
    deselectButton(ui->pushButtonAssociation);
    //deselectButton(ui->pushButtonSetting);
    selectButton(ui->pushButtonEmployee);

}

void MainWindow::on_AddEmployee_2_clicked()
{
    ui->stackedWidgetEmployee->setCurrentIndex(3);

}

void MainWindow::on_pushButtonEvents_clicked()
{
    ui->StackedWidget->setCurrentIndex(1);
        ui->stackedWidgetEvent->setCurrentIndex(2);
        ui->table_event->setModel(e.afficherEvenement());
        selectButton(ui->pushButtonEvents);
        deselectButton(ui->pushButtonProduct);
        deselectButton(ui->pushButtonGuest);
        deselectButton(ui->pushButtonArtist);
        deselectButton(ui->pushButtonAssociation);
        //deselectButton(ui->pushButtonSetting);
        ui->weather->clear();
        ui->weatherIcon->clear();
}










void MainWindow::on_pushButtonArtist_clicked()
{
    ui->StackedWidget->setCurrentIndex(3);
    ui->stackedWidgetArtist->setCurrentIndex(0);
    ui->artableView->setModel(a.afficher());
    ui->artableView_3->setModel(a.afficher());//refresh
    ui->artableView_2->setModel(a.afficher());//refresh

    deselectButton(ui->pushButtonEvents);
    deselectButton(ui->pushButtonProduct);
    deselectButton(ui->pushButtonGuest);
    selectButton(ui->pushButtonArtist);
    deselectButton(ui->pushButtonAssociation);
    //deselectButton(ui->pushButtonSetting);
}




void MainWindow::on_pushButtonAssociation_clicked()
{
    ui->StackedWidget->setCurrentIndex(5);
    ui->stackedWidgetAssociation->setCurrentIndex(0);

    deselectButton(ui->pushButtonEvents);
    deselectButton(ui->pushButtonProduct);
    deselectButton(ui->pushButtonGuest);
    deselectButton(ui->pushButtonArtist);
    selectButton(ui->pushButtonAssociation);
    //deselectButton(ui->pushButtonSetting);
    ui->tableView_22->setModel(as.afficher());
}





void MainWindow::on_updateEmployee_3_clicked()
{
    Article article;
        ui->stackedWidgetProduct->setCurrentIndex(3);
        ui->tableView_17->setModel(article.afficher());
}


//partie iheb


void MainWindow::updateInfoText(QString info) {
    ui->adress_a->setText(info);
}


void MainWindow::on_listtoaddass_clicked()
{
    ui->stackedWidgetAssociation->setCurrentIndex(1);
    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
    ui->quickWidget->show();

    // Obtain the root QML object
    QQuickItem *item = qobject_cast<QQuickItem*>(ui->quickWidget->rootObject()); // Ensure "item" is declared here

    if (item) {
        QObject *obj = dynamic_cast<QObject*>(item);
        if (obj) {
            // Successfully casted
            // Connect signals and slots here
            QObject::connect(obj, SIGNAL(infoTextChanged(QString)), this, SLOT(updateInfoText(QString)));
        } else {
            // Failed to cast to QObject
            // Handle the error
        }
    } else {
        // Root object is null
        // Handle the error
    }
}




void MainWindow::on_confirmer_clicked()
{
    // Récupérer les valeurs de latitude et de longitude de adress_a
    QString coordinates = ui->adress_a->text();

    QStringList coordinateList = coordinates.split(',');
    if (coordinateList.size() != 2) {
        qDebug() << "Erreur: Coordonnées invalides";
        return;
    }

    double latitude = coordinateList[0].trimmed().toDouble();
    double longitude = coordinateList[1].trimmed().toDouble();
    qDebug() << "Latitude :" << latitude;
    qDebug() << "Longitude :" << longitude;

    // Créer un objet QNetworkAccessManager pour envoyer une requête HTTP
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    // Construire l'URL de l'API de géocodage inverse de Nominatim
    QString apiUrl = "https://nominatim.openstreetmap.org/reverse?format=json&lat="
                     + QString::number(latitude) + "&lon="
                     + QString::number(longitude)
                     + "&zoom=18&addressdetails=1";

    // Envoyer une requête GET à l'API de Nominatim
    QNetworkReply* reply = manager->get(QNetworkRequest(QUrl(apiUrl)));

    // Gérer la réponse lorsque la requête est terminée
    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            // Lire la réponse JSON
            QByteArray responseData = reply->readAll();
            QJsonDocument responseJson = QJsonDocument::fromJson(responseData);

            // Extraire le nom de la ville à partir de la réponse JSON
            QString cityName = "Ville non trouvée";
            QJsonObject result = responseJson.object();
            QString city = result.value("address").toObject().value("city").toString();
            if (!city.isEmpty()) {
                cityName = city;
            } else {
                cityName = result.value("address").toObject().value("town").toString();
                if (cityName.isEmpty()) {
                    cityName = result.value("address").toObject().value("village").toString();
                    if (cityName.isEmpty()) {
                        cityName = result.value("address").toObject().value("county").toString();
                    }
                }
            }

            // Afficher le nom de la ville dans le label adress_a_2
            ui->adress_a_2->setText(cityName);
            qDebug() << "Nom de la ville reçu depuis l'API de Nominatim :" << cityName;
        } else {
            qDebug() << "Erreur lors de la requête HTTP : " << reply->errorString();
        }

        // Nettoyer la mémoire
        reply->deleteLater();
        manager->deleteLater();
    });
}



void MainWindow::verifyRFID(const QByteArray &data)
{
    QString RFID = QString::fromLatin1(data).trimmed(); // Convertit les données en QString
    QString lastScannedRFID;
    // Vérifie si la RFID actuelle est différente de la dernière RFID scannée
    if (RFID != lastScannedRFID)
    {
        if(e.rechercherRFID(RFID) != 0)
        {
            A.write_to_arduino("1");
            qDebug() << "trouvé";
        }
        else
        {
            A.write_to_arduino("0");
            qDebug() << "non trouvé";
        }

        // Mettez à jour la dernière RFID scannée
        lastScannedRFID = RFID;
    }
}
