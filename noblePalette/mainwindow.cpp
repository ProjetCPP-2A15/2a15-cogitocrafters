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
#include <QTimer>
#include <QPrinter>

#include <QPainter>
#include <QProcess>
#include <QDebug>
#include <QQuickItem>
#include <QObject>


#include <QWidget>
//#include <QVideoWidget>
//#include <QQuickWidget>
#include <QVideoProbe>
#include <QMovie>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,manager(new QNetworkAccessManager(this))//weather
{
    ui->setupUi(this);
    eventCheckLoop();
    // Vérification de la connexion du signal readyRead() et débogage de la réception des données
    //QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_labels())); // permet de lancer
    qDebug() << "Connexion du signal readyRead() établie.";        //le slot update_label suite à la reception du signal readyRead (reception des données).

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

             QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label1())); // permet de lancer



//################################################# IYED&DHIA################################################################################


                   // Initialize nbrvue with the current number from the QLineEdit
                     QString existingCount = ui->nbvu->text();
                     nbrvue =  existingCount.isEmpty() ? 0 : existingCount.toInt();

                     // Initialize other components and variables as necessary
                     safe = false;  // Ensure 'safe' is initialized
                     connect(ui->on, &QPushButton::clicked, this, &MainWindow::displayMostViewedArticleName);

//###########################################################################################################################################



                     //animation:
                     QMovie *movie = new QMovie("C:/Users/meddh/Desktop/noblePalette/noblePalette/images/logogi.gif");
                     movie->setScaledSize(ui->logo->size());
                     ui->logo->setMovie(movie);
                     movie->start();



}

MainWindow::~MainWindow()
{
    delete ui;
    delete manager;
    delete speech;

}
void MainWindow::selectButton(QPushButton *button) {
    button->setStyleSheet("background: rgb(113, 161, 88);box-shadow: 0px 4px 4px rgba(0, 0, 0, 0.25);border: none;font-family: 'Athiti';font-style: normal;font-weight: 700;font-size: 20px;line-height: 32px;text-align: center;color: #000;border-radius:15px;border-bottom:3px solid #000;");
}


// Fonction pour désélectionner un bouton
void MainWindow::deselectButton(QPushButton *button) {
    button->setStyleSheet("QPushButton {background: transparent;border: none;font-family: 'Athiti';font-style: normal;font-weight: 700;font-size: 20px;line-height: 32px;text-align: center;color: #000;border-radius:15px;border-bottom:3px solid #000;}QPushButton:hover {background: rgb(113, 161, 88);box-shadow: 0px 4px 4px rgba(0, 0, 0, 0.25);}");
}

void MainWindow::on_pushButtonEmployee_2_clicked()
{
    ui->StackedWidget->setCurrentIndex(7);
    deselectButton(ui->pushButtonEvents);
    deselectButton(ui->pushButtonProduct);
    deselectButton(ui->pushButtonGuest);
    deselectButton(ui->pushButtonArtist);
    deselectButton(ui->pushButtonAssociation);
    selectButton(ui->pushButtonEmployee_2);

    //deselectButton(ui->pushButtonSetting);
    deselectButton(ui->pushButtonEmployee);

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
    deselectButton(ui->pushButtonEmployee_2);

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
        deselectButton(ui->pushButtonEmployee);
        deselectButton(ui->pushButtonEmployee_2);

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
    deselectButton(ui->pushButtonEmployee);
    deselectButton(ui->pushButtonEmployee_2);


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
    deselectButton(ui->pushButtonEmployee);
    deselectButton(ui->pushButtonEmployee_2);


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

    QString latitude = coordinateList[0].trimmed();
    QString longitude = coordinateList[1].trimmed();
    qDebug() << "Latitude :" << latitude;
    qDebug() << "Longitude :" << longitude;

    // Créer un processus pour exécuter le script Python
    QProcess *process = new QProcess(this);

    // Définir le chemin du script Python et ses arguments
    QString pythonScript = "C:/Users/meddh/Desktop/noblePalette/noblePalette/script/city.py";
    QStringList arguments;
    QString tude = latitude+","+longitude;
    arguments << pythonScript << tude; // Passer les coordonnées en tant qu'une seule chaîne avec une virgule comme séparateur

    // Lancer le script Python en tant que processus externe
    process->start("python", arguments);
    process->waitForFinished();

    // Lire la sortie standard du processus (nom de la ville)
    QByteArray result = process->readAllStandardOutput();
    QString city = QString::fromUtf8(result).trimmed(); // Convertir la sortie en QString et supprimer les espaces inutiles

    // Afficher le nom de la ville dans le label adress_a_2
    ui->adress_a_2->setText(city);
    qDebug() << "Nom de la ville reçu depuis l'API de Nominatim :" << city;
}







void MainWindow::on_pushButton_clicked()
{
    process = new QProcess(this);
      QString scriptPath = "C:/Users/meddh/Desktop/noblePalette/noblePalette/script/article/sonwithmicro.py";

      // Démarrer le script Python
      process->start("python", QStringList() << scriptPath);

      // Connexion pour lire la sortie standard
      connect(process, &QProcess::readyReadStandardOutput, this, &MainWindow::updateOutput);
      //connect(process, &QProcess::finished, process, &QProcess::deleteLater);

      // Optionnellement, gérer la sortie d'erreur
      connect(process, &QProcess::readyReadStandardError, this, &MainWindow::handleError);
}
void MainWindow::updateOutput() {
    QByteArray data = process->readAllStandardOutput();
    QString output(data);
    // Mettez à jour une interface utilisateur ou un widget avec 'output' si nécessaire
}

void MainWindow::handleError() {
    QByteArray data = process->readAllStandardError();
    QString error(data);
    // Afficher l'erreur dans un widget de journalisation ou la console
    qDebug() << "Error:" << error;
}

//scenario iyed
void MainWindow::update_label()
{
    data = A.read_from_arduino();  // A doit être une instance d'un objet qui a la méthode read_from_arduino()
    ui->label_57->setText(data);

    if (!data.trimmed().isEmpty() && data.trimmed() != "0") {
        int currentDistance = data.trimmed().toInt();
        if (currentDistance <= 10 && !safe) {

            QString nb = ui->nbvu->text();
            int nombre = nb.toInt();

            safe = true;
            nombre=nombre+1;
            ui->nbvu->setText(QString::number(nombre));

            Article article;
            article.updateNbVu(idA, nombre);
            displayMostViewedArticleName();

        }
        else if (currentDistance > 10 && safe) {
                   safe = false;
               }
}
    qDebug() << data.trimmed();
    ui->nbvu->setEnabled(false);

    qDebug() << safe;
}





void MainWindow::on_off_clicked()
{
    if(arduinoA==10)
    A.write_to_arduino("2"); //envoyer 1 à arduino
    else if(arduinoA==20)
    A.write_to_arduino("F"); //envoyer 1 à arduino




}

void MainWindow::on_on_clicked()
{
    A.write_to_arduino("1"); //envoyer 1 à arduino
    arduinoA=10;


}

void MainWindow::displayMostViewedArticleName() {
    QSqlQuery query;
    query.prepare("SELECT nom_article FROM ARTICLE WHERE nbvu = (SELECT MAX(nbvu) FROM ARTICLE)");

    if (query.exec() && query.next()) {
        QString articleName = query.value(0).toString();
        ui->lineEditMostViewedArticleName->setText(articleName.isEmpty() ? "No articles found" : articleName);
        if (!articleName.isEmpty()) {
                    sendArticleNameToArduino(articleName);
                }
    } else {
        ui->lineEditMostViewedArticleName->setText("No articles found or error in query execution");
        qDebug() << "Failed to execute query or no articles found:" << query.lastError().text();
    }
}

void MainWindow::sendArticleNameToArduino(const QString &name) {
    if (A.connect_arduino()) {
        QString command = name + '\n';
        A.write_to_arduino(command.toUtf8());
    }
}
















//--------------------------------------- ARDUINO ------------------------------------------


void MainWindow::eventCheckLoop() {
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::checkEventStatus);
    timer->start(500); // Vérifier toutes les minutes (60000 ms)
}

void MainWindow::checkEventStatus() {
    // Récupérer la date et l'heure actuelles du système
    QDateTime currentDateTime = QDateTime::currentDateTime();

    // Vérifier si un événement est sélectionné dans le tableau
    QModelIndex selectedIndex = ui->table_event->selectionModel()->currentIndex();
    if (selectedIndex.isValid()) {
        int row = selectedIndex.row();
        int id_event = ui->table_event->model()->index(row, 0).data().toInt();
        evenement ev = e.chercher(id_event);

        // Créer des objets QDateTime pour les dates et heures de début et de fin de l'événement
        QDateTime startDateTime(ev.getStartD(), ev.getStartH());
        QDateTime endDateTime(ev.getStartD(), ev.getEndH());

        if (currentDateTime >= startDateTime && currentDateTime <= endDateTime) {
            // L'événement est en cours, envoyer "1" à l'Arduino
            iheb =10;
        } else if (currentDateTime > endDateTime) {
            // L'événement est terminé, envoyer "2" à l'Arduino
            iheb =20;
        } else {
            // L'événement n'a pas encore commencé, envoyer "3" à l'Arduino
            iheb =30;
        }


    } else {
        // Aucun événement sélectionné, envoyer "4" à l'Arduino
        iheb =40;
        //qDebug() << "Aucun événement sélectionné.";
    }
}



void MainWindow::update_labels()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();

    // Vérifier si un événement est sélectionné dans le tableau
    QModelIndex selectedIndex = ui->table_event->selectionModel()->currentIndex();
    if (selectedIndex.isValid()) {
        int row = selectedIndex.row();
        int id_event = ui->table_event->model()->index(row, 0).data().toInt();
        evenement ev = e.chercher(id_event);

        // Créer des objets QDateTime pour les dates et heures de début et de fin de l'événement
        QDateTime startDateTime(ev.getStartD(), ev.getStartH());
        QDateTime endDateTime(ev.getStartD(), ev.getEndH());

        if (currentDateTime >= startDateTime && currentDateTime <= endDateTime) {
            // L'événement est en cours
            data = A.read_from_arduino();  // Assurez-vous que A est une instance valide de l'objet avec la méthode read_from_arduino()

            if (!data.trimmed().isEmpty() && data.trimmed() == "0") {
                // Gaz détecté, mettre à jour l'état de l'événement
                if (!ev.updateEventState("danger")) {
                    qDebug() << "Erreur lors de la mise à jour de l'état de l'événement en danger.";
                } else {
                    ui->etat->setText("danger");
                }
            }
        } else if (currentDateTime > endDateTime) {
            // L'événement est terminé
            if (ui->etat->text() != "danger") {
                // Si l'événement n'est pas en danger, mettre à jour l'état de l'événement comme "terminé avec succès"
                if (!ev.updateEventState("terminé avec succès")) {
                    qDebug() << "Erreur lors de la mise à jour de l'état de l'événement terminé avec succès.";
                } else {
                    ui->etat->setText("terminé avec succès");
                }
            }
        } else {
            // L'événement n'a pas encore commencé
        }
    } else {
        qDebug() << "Aucun événement sélectionné.";
    }
}




//dhiaa arduino
void MainWindow::update_label2()
{
    data = A.read_from_arduino();
    ui->label_57->setText(data);
    // int dist = data.toInt();
    if (!data.trimmed().isEmpty() && data.trimmed() != "0") {
        displayArticleViewsById(idA);

        if (data.trimmed().toInt() <= 10 && !safe) {
            safe = true;
            int nbrvue=article.getNbVuById(idA)+1;
            article.modifierNbVu(idA,nbrvue);
        }
        if (data.trimmed().toInt() > 10) {
            safe = false;
        }
    }

    ui->nbvu->setText(QString::number(article.getNbVuById(idA)));


  }


void MainWindow::displayArticleViewsById(int articleId) {
    QSqlQuery query;
    query.prepare("SELECT nbvu FROM ARTICLE WHERE id_article = :id");
    query.bindValue(":id", articleId);

    if (query.exec() && query.next()) {
        QString nbvu = query.value(0).toString();
        if (!nbvu.isEmpty()) {
                    sendArticleNameToArduino("0"+nbvu);
                    qDebug()<<nbvu;
                }
    } else {
        qDebug() << "Failed to execute query or no views found:" << query.lastError().text();
    }
}








void MainWindow::on_on_2_clicked()
{
    A.write_to_arduino("D"); //envoyer 1 à arduino
    arduinoA=20;
}

void MainWindow::on_on_3_clicked()
{
    A.write_to_arduino("O"); //envoyer 1 à arduino
    arduinoA=20;

}



//dhiaa arduino
void MainWindow::update_label1()
{
    if (arduinoA==10)
    {
        update_label();
    }
    else if(arduinoA==20)
    {
        update_label2();
    }
    else if(arduinoA==40)
    {
        update_labels();
    }
    /*else if(arduinoA==50)
    {
        QTimer *timer = new QTimer(this);
                connect(timer, &QTimer::timeout, this, &MainWindow::verifyRFID);

                // Définir l'intervalle de temps entre chaque vérification RFID (par exemple, toutes les 500 millisecondes)
                timer->start(200);    }*/

 }

void MainWindow::verifyRFID()
{
    QString RFID = QString::fromLatin1(A.read_from_arduino_event()).trimmed(); // Convertit les données en QString
    QString lastScannedRFID;
    // Vérifie si la RFID actuelle est différente de la dernière RFID scannée
    if (RFID != lastScannedRFID)
    {
        qDebug() << "hhhhhhh";

         QString eventDateTime = e.rechercherRFIDTime(RFID);
        if(e.rechercherRFID(RFID) != 0 && !eventDateTime.isEmpty())
        {
            A.write_to_arduino1(eventDateTime.toLatin1());
    qDebug() << "trouvé";
        }
        else
        {
            A.write_to_arduino1("nothing");

    qDebug() << "non trouvé";
        }

        // Mettez à jour la dernière RFID scannée
        lastScannedRFID = RFID;
    }
}
void MainWindow::on_ArduinoEvent_clicked()
{
    QTimer *timer = new QTimer(this);
            connect(timer, &QTimer::timeout, this, &MainWindow::verifyRFID);
            // Définir l'intervalle de temps entre chaque vérification RFID (par exemple, toutes les 500 millisecondes)
            timer->start(200);
   arduinoA=50;
}

void MainWindow::on_weathergenerate_2_clicked()
{

    if(iheb==10)
    {
        A.write_to_arduino("1"); //envoyer 1 à arduino
        arduinoA=40;
    }
    if(iheb==20)
    {
        A.write_to_arduino("2");
        arduinoA=40;

    }
    if(iheb==30)
    {
        A.write_to_arduino("3");
        arduinoA=40;

    }
    if(iheb==40)
    {
        A.write_to_arduino("4");
        arduinoA=40;

    }
}

void MainWindow::on_face_clicked()
{
    // Créer un objet de processus pour exécuter le script Python
    QProcess *process = new QProcess(this);

    // Définir le chemin vers le script Python
    QString pythonScriptPath = "C:/Users/meddh/Desktop/faceidd/faceid.py";

    // Exécuter le script Python en tant que processus
    process->start("python", QStringList() << pythonScriptPath);

    // Connecter les signaux de processus pour récupérer les sorties de processus
    connect(process, &QProcess::readyReadStandardOutput, [=]()
    {
        // Lire la sortie standard du processus (résultats de la reconnaissance faciale)
        QByteArray output = process->readAllStandardOutput();

        // Traiter les résultats de la reconnaissance faciale
        QString result = QString::fromUtf8(output).trimmed();

        // Vérifier si la personne est connue ou non
        if (result == "Inconnu")
        {

             // La personne n'est pas connue, changer l'index du StackedWidget pour afficher la page de connexion
            ui->StackedWidget->setCurrentIndex(0);
            ui->stackedWidgetGlobal->setCurrentIndex(0);
            ui->lineEdit_LoginPassword->clear();

        }
        else if(result=="Connue")
        {
            // Changer l'index du StackedWidget pour afficher la page d'accueil de l'employé
            ui->stackedWidgetGlobal->setCurrentIndex(2);
            ui->StackedWidget->setCurrentIndex(1);
        }
        qDebug()<< result;
    });
}




void MainWindow::on_supprimer_Employee_3_clicked()
{
    speech->say("supprimer");

}

void MainWindow::on_statEmployee_2_clicked()
{
    speech->say("stat");

}

void MainWindow::on_AddEmployee_3_clicked()
{
    speech->say("page d ajout ");

}

void MainWindow::on_clearEmployee_2_clicked()
{
    speech->say("clear");

}

void MainWindow::on_updateEmployee_10_clicked()
{
    speech->say("mise a jour les information");

}

void MainWindow::on_pdfEmployee_2_clicked()
{
    speech->say("pdf");

}

void MainWindow::on_save_AddEmployee_2_clicked()
{
    speech->say("enrgistrer");

}





void MainWindow::on_logout_3_clicked()
{
    ui->StackedWidget->setCurrentIndex(6);

}
