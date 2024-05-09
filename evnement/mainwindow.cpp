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

#include <QFileDialog>

#include <QPrinter>

#include <QPainter>
#include <QProcess>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::selectButton(QPushButton *button) {
    button->setStyleSheet("background: #8BD086;box-shadow: 0px 4px 4px rgba(0, 0, 0, 0.25);border: none;font-family: 'Athiti';font-style: normal;font-weight: 700;font-size: 20px;line-height: 32px;text-align: center;color: #2A501F;border-radius:15px;border-bottom:3px solid #669B37;");
}

// Fonction pour désélectionner un bouton
void MainWindow::deselectButton(QPushButton *button) {
    button->setStyleSheet("QPushButton {background: #A9E4A4;border: none;font-family: 'Athiti';font-style: normal;font-weight: 700;font-size: 20px;line-height: 32px;text-align: center;color: #2A501F;border-radius:15px;border-bottom:3px solid #669B37;}QPushButton:hover {background: #8BD086;box-shadow: 0px 4px 4px rgba(0, 0, 0, 0.25);}");
}

//                                            Partie Event
void MainWindow::on_pushButtonEvents_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidgetEvent->setCurrentIndex(2);

    selectButton(ui->pushButtonEvents);
    deselectButton(ui->pushButtonProduct);
    deselectButton(ui->pushButtonGuest);
    deselectButton(ui->pushButtonArtist);
    deselectButton(ui->pushButtonAssociation);
    deselectButton(ui->pushButtonSetting);
}

//                                            Partie Product
void MainWindow::on_pushButtonProduct_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->stackedWidgetProduct->setCurrentIndex(0);

    deselectButton(ui->pushButtonEvents);
    selectButton(ui->pushButtonProduct);
    deselectButton(ui->pushButtonGuest);
    deselectButton(ui->pushButtonArtist);
    deselectButton(ui->pushButtonAssociation);
    deselectButton(ui->pushButtonSetting);
}

//                                            Partie Guest
void MainWindow::on_pushButtonGuest_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->stackedWidgetGuest->setCurrentIndex(0);

    deselectButton(ui->pushButtonEvents);
    deselectButton(ui->pushButtonProduct);
    selectButton(ui->pushButtonGuest);
    deselectButton(ui->pushButtonArtist);
    deselectButton(ui->pushButtonAssociation);
    deselectButton(ui->pushButtonSetting);
    //ui->tableView->setModel(g.afficher());
}


//                                            Partie Artist
void MainWindow::on_pushButtonArtist_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidgetArtist->setCurrentIndex(0);

    deselectButton(ui->pushButtonEvents);
    deselectButton(ui->pushButtonProduct);
    deselectButton(ui->pushButtonGuest);
    selectButton(ui->pushButtonArtist);
    deselectButton(ui->pushButtonAssociation);
    deselectButton(ui->pushButtonSetting);
}



void MainWindow::on_addEmpButton_clicked()
{

    ui->stackedWidgetArtist->setCurrentIndex(1);
}


void MainWindow::on_searchButton_clicked()
{

    ui->stackedWidgetArtist->setCurrentIndex(0);

}


void MainWindow::on_updateEmpButton_clicked()
{
    ui->stackedWidgetArtist->setCurrentIndex(2);

}


void MainWindow::on_deleteEmpButton_clicked()
{
    ui->stackedWidgetArtist->setCurrentIndex(3);

}

//                                            Partie Association
void MainWindow::on_pushButtonAssociation_clicked()
{
    ui->tableView_22->setModel(a.afficher());

    ui->stackedWidget->setCurrentIndex(4);
    ui->stackedWidgetAssociation->setCurrentIndex(0);

    deselectButton(ui->pushButtonEvents);
    deselectButton(ui->pushButtonProduct);
    deselectButton(ui->pushButtonGuest);
    deselectButton(ui->pushButtonArtist);
    selectButton(ui->pushButtonAssociation);
    deselectButton(ui->pushButtonSetting);
}

//                                            Partie Setting
void MainWindow::on_pushButtonSetting_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->stackedWidgetSetting->setCurrentIndex(1);

    deselectButton(ui->pushButtonEvents);
    deselectButton(ui->pushButtonProduct);
    deselectButton(ui->pushButtonGuest);
    deselectButton(ui->pushButtonArtist);
    deselectButton(ui->pushButtonAssociation);
    selectButton(ui->pushButtonSetting);
}

//




void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidgetGlobal->setCurrentIndex(0);
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidgetEvent->setCurrentIndex(2);

}

void MainWindow::on_pushButtonProduct_2_clicked()
{
     ui->stackedWidgetProduct->setCurrentIndex(1);
}


void MainWindow::on_pushButtonProduct_3_clicked()
{
    ui->stackedWidgetProduct->setCurrentIndex(2);

}

void MainWindow::on_supprimer_5_clicked()
{
    ui->stackedWidgetProduct->setCurrentIndex(0);

}


void MainWindow::on_ajouterArt_clicked()
{
    ui->stackedWidgetProduct->setCurrentIndex(2);

}

void MainWindow::on_list_clicked()
{
    ui->stackedWidgetProduct->setCurrentIndex(0);
}
/*
void MainWindow::on_supprimer_11_clicked()
{
    ui->stackedWidgetEvent->setCurrentIndex(1);
}*/

void MainWindow::on_ajouterArt_7_clicked()
{
    ui->stackedWidgetEvent->setCurrentIndex(0);

}

void MainWindow::on_ajouterArt_4_clicked()
{
    ui->stackedWidgetEvent->setCurrentIndex(1);

}

void MainWindow::on_ajouterArt_8_clicked()
{
    ui->stackedWidgetEvent->setCurrentIndex(0);

}

void MainWindow::on_ajouterArt_9_clicked()
{
    ui->stackedWidgetEvent->setCurrentIndex(2);
}

void MainWindow::on_save_clicked()
{
     ui->stackedWidgetSetting->setCurrentIndex(2);
}

void MainWindow::on_updateEmployee_clicked()
{
    ui->stackedWidgetSetting->setCurrentIndex(0);

}

void MainWindow::on_addEmployee_clicked()
{
    ui->stackedWidgetSetting->setCurrentIndex(3);

}

void MainWindow::on_save_2_clicked()
{
    ui->stackedWidgetSetting->setCurrentIndex(1);
}



void MainWindow::on_supprimer_11_clicked()
{
    ui->stackedWidgetEvent->setCurrentIndex(3);

}

void MainWindow::on_supprimer_35_clicked()
{
    ui->stackedWidgetGuest->setCurrentIndex(1);

}

void MainWindow::on_listtoaddass_clicked()
{
    ui->stackedWidgetAssociation->setCurrentIndex(1);

   /* ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
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
    ui->stackedWidgetAssociation->setCurrentIndex(1);*/

}

void MainWindow::on_listtoaddpro_clicked()
{
    ui->stackedWidgetProduct->setCurrentIndex(1);

}

void MainWindow::on_supprimer_38_clicked()
{
    ui->stackedWidgetArtist->setCurrentIndex(1);

}

void MainWindow::on_supprimer_22_clicked()
{
    ui->stackedWidgetSetting->setCurrentIndex(3);

}

void MainWindow::on_updateAssociaton_clicked()
{
    ui->stackedWidgetAssociation->setCurrentIndex(2);

}


void MainWindow::on_save_3_clicked()
{
    ui->stackedWidgetAssociation->setCurrentIndex(0);

}

void MainWindow::on_save_8_clicked()
{
    ui->stackedWidgetGuest->setCurrentIndex(3);

}

void MainWindow::on_ajouterArt_14_clicked()
{
    ui->stackedWidgetArtist->setCurrentIndex(0);

}

void MainWindow::on_updateEmployee_3_clicked()
{
    ui->stackedWidgetProduct->setCurrentIndex(3);

}

void MainWindow::on_updateEmployee_4_clicked()
{
    ui->stackedWidgetEvent->setCurrentIndex(1);

}

void MainWindow::on_updateEmployee_2_clicked()
{
    ui->stackedWidgetGuest->setCurrentIndex(2);

}

void MainWindow::on_save_5_clicked()
{
    ui->stackedWidgetProduct->setCurrentIndex(2);
}

void MainWindow::on_save_7_clicked()
{
    ui->stackedWidgetEvent->setCurrentIndex(0);

}

void MainWindow::on_save_6_clicked()
{
    ui->stackedWidgetGuest->setCurrentIndex(3);

}




//-------------------------------***** partie association *****-------------------------------

void MainWindow::on_save_a_clicked()
{
    // Récupérer les valeurs des champs
        QString budgetText = ui->budget_a->text();
        QString nom = ui->name_a->text();
        QString adresse = ui->adress_a->text();
        QString description = ui->desc_a->text();
        QString type;

        if(ui->radioButton->isChecked())
            type = "Private";
        else if(ui->radioButton_2->isChecked())
            type = "Public";

        // Vérifier si les champs sont vides
        if (budgetText.isEmpty() || nom.isEmpty() || adresse.isEmpty() || description.isEmpty()) {
            QMessageBox::warning(this, "Champs vides", "Veuillez remplir tous les champs.");
            return;
        }

        // Vérifier si le budget est valide
        bool ok;
        int budget = budgetText.toInt(&ok);
        if (!ok || budget <= 0) {
            QMessageBox::warning(this, "Budget invalide", "Veuillez entrer un budget valide (supérieur à zéro).");
            return;
        }

        // Créer une nouvelle association
        Association a(budget, nom, adresse, description,type);

        // Ajouter l'association
        bool ajoutReussi = a.ajouter();

        if (ajoutReussi)
        {
            // Effacer les champs après l'ajout réussi
            ui->budget_a->clear();
            ui->name_a->clear();
            ui->adress_a->clear();
            ui->desc_a->clear();

            // Afficher les informations dans le tableau
            ui->stackedWidgetAssociation->setCurrentIndex(0);
            ui->tableView_22->setModel(a.afficher());
            ui->tableView_23->setModel(a.afficher2());

            QMessageBox::information(this, "Ajout réussi", "Association ajoutée avec succès.");
        }
        else
        {
            QMessageBox::critical(this, "Erreur lors de l'ajout", "Erreur lors de l'ajout de l'association.");
        }
}



            void MainWindow::on_tableView_23_doubleClicked(const QModelIndex &index)
            {
                // Check if the index is valid
                if (!index.isValid()) {
                    // Handle the invalid index if necessary, e.g., show an error message
                    return;
                }

                // Define the column indices based on your table's actual structure
                const int ID_COLUMN = 0;
                const int NOM_COLUMN = 1;
                const int ADRESS_COLUMN = 2;
                const int BUDGET_COLUMN = 3;
                const int DESCRIPTION_COLUMN = 4;


                // Retrieve the artist's details from the selected row in updateview_2.
                int id = index.sibling(index.row(), ID_COLUMN).data().toInt();
                int budget = index.sibling(index.row(), BUDGET_COLUMN).data().toInt();
                QString nom = index.sibling(index.row(), NOM_COLUMN).data().toString();
                QString adress = index.sibling(index.row(), ADRESS_COLUMN).data().toString();
                QString description = index.sibling(index.row(), DESCRIPTION_COLUMN).data().toString();


                // Fill the input fields with the retrieved data.
                ui->asid->setText(QString::number(id));
                ui->asid->setReadOnly(true);
                ui->asbudget->setText(QString::number(budget));
                ui->asname->setText(nom);
                ui->asadress->setText(adress);
                ui->asdescription->setText(description);



                // Now the user can modify the data in the input fields.
            }


            void MainWindow::getCityName(double latitude, double longitude) {
                QString apiUrl = QString("https://maps.googleapis.com/maps/api/geocode/json?latlng=%1,%2&key=YOUR_API_KEY").arg(latitude).arg(longitude);

                QNetworkAccessManager *manager = new QNetworkAccessManager(this);
                connect(manager, &QNetworkAccessManager::finished, [=](QNetworkReply *reply) {
                    if (reply->error() == QNetworkReply::NoError) {
                        QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
                        QJsonObject jsonObject = jsonResponse.object();

                        QString cityName;
                        QJsonArray results = jsonObject["results"].toArray();
                        if (!results.isEmpty()) {
                            QJsonObject firstResult = results.first().toObject();
                            for (const QJsonValue &component : firstResult["address_components"].toArray()) {
                                QString componentType = component.toObject()["types"].toArray().first().toString();
                                if (componentType == "locality") {
                                    cityName = component.toObject()["long_name"].toString();
                                    break;
                                }
                            }
                        }
                        // Émettre le signal pour mettre à jour le texte dans l'interface utilisateur
                        emit updateInfoText("City Name: " + cityName);
                    } else {
                        qDebug() << "Error: " << reply->errorString();
                    }
                    reply->deleteLater();
                });

                QNetworkRequest request(apiUrl);
                manager->get(request);
            }

            void MainWindow::updateInfoText(QString info) {
                ui->adress_a->setText(info);
            }

            void MainWindow::on_asupdate_clicked() {
                ui->stackedWidgetAssociation->setCurrentIndex(1);
                ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
                ui->quickWidget->show();

                // Obtenir l'objet root du QML
                auto obj = ui->quickWidget->rootObject(); // Assurez-vous que "obj" est déclaré ici

                // Connecter le signal infoTextChanged du QML au slot updateInfoText de MainWindow
                connect(obj, SIGNAL(infoTextChanged(QString)), this, SLOT(updateInfoText(QString)));
            }


void MainWindow::on_supprimer_23_clicked()
{
    ui->asname->setText("");
    ui->asadress->setText("");
    ui->asbudget->setText("");
    ui->asdescription->setText("");
}

void MainWindow::on_save_4_clicked()
{
    int id= ui->asid->text().toInt();
    ui->asid->setReadOnly(true);
    int budget= ui->asbudget->text().toInt();
    QString nom=ui->asname->text();
    QString adress=ui->asadress->text();
    QString description=ui->asdescription->text();

    bool test=a.modifier(id,budget,nom,adress,description);
    //ui->asid->clear();



    if (test)
    {
        ui->asbudget->clear();
        ui->asname->clear();
        ui->asadress->clear();
        ui->asdescription->clear();
        ui->tableView_22->setModel(a.afficher());//refresh
        ui->tableView_23->setModel(a.afficher2());//refresh
        //ui->artableView_2->setModel(a.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Modifier un artiste"),
                    QObject::tr("Association modifié.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier une Association"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}



void MainWindow::on_searchTextBox_21_textChanged(const QString &arg1)
{
    QString searchText = arg1;
    QSqlQueryModel* model = a.rechercher(searchText);

    // Remplacer le modèle précédent dans le QTableView
    if(ui->tableView_23->model())
        delete ui->tableView_23->model();
    ui->tableView_23->setModel(model);
}

void MainWindow::on_searchTextBox_18_textChanged(const QString &arg1)
{
    QString searchText = arg1;
    QSqlQueryModel* model = a.rechercher(searchText);

    // Remplacer le modèle précédent dans le QTableView
    if(ui->tableView_22->model())
        delete ui->tableView_22->model();
    ui->tableView_22->setModel(model);
}




void MainWindow::on_comboBox_4_activated(const QString &arg1)
{
    if (arg1 == "Name") {
           ui->tableView_22->setModel(a.afficher_tri_nom());
       } else if (arg1 == "Adress") {
           ui->tableView_22->setModel(a.afficher_tri_adresse());
       } else if (arg1 == "Budget") {
         ui->tableView_22->setModel(a.afficher_tri_budget());
       }
}



void MainWindow::on_tableView_22_doubleClicked(const QModelIndex &index)
{

    if (index.isValid()) {
                QVariant name = index.sibling(index.row(), 0).data();
                QVariant address = index.sibling(index.row(), 1).data();
                QVariant budget = index.sibling(index.row(), 2).data();
                QVariant description = index.sibling(index.row(), 3).data();

                ui->labelaffnameass->setText(name.toString());
                ui->labelaffbudgetass->setText(budget.toString());
                ui->labelaffaddressass->setText(address.toString());
                ui->labelaffdescriptionass->setText(description.toString());
            }

    ui->stackedWidgetAssociation->setCurrentIndex(3);

}

void MainWindow::on_assupprimer_clicked()
{
    a.supprimer(ui->asid->text().toInt());
    ui->tableView_22->setModel(a.afficher());
    ui->stackedWidgetAssociation->setCurrentIndex(0);

}



void MainWindow::on_asPDF_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save PDF", "association n°", "*.pdf");

       QPrinter printer(QPrinter::PrinterResolution);
       printer.setOutputFormat(QPrinter::PdfFormat);
       printer.setPaperSize(QPrinter::A4);
       printer.setOutputFileName(fileName);

       QPainter painter;
       painter.begin(&printer);

       // Dessiner du texte
      // painter.drawText(100, 100, "Hello, World!");

       // Dessiner une image
      // QPixmap pixmap(":/path/to/your/image.png"); // Charger une image à partir du chemin
      // painter.drawPixmap(100, 200, pixmap);

       // Dessiner d'autres informations
       QFont font = painter.font();
       font.setPointSize(12);
       painter.setFont(font);
       painter.drawText(100, 100, "Association information");

       QStringList additionalInfo;
       additionalInfo << "NAME : " + ui->labelaffnameass->text();
       additionalInfo << "ADDRESS : " + ui->labelaffaddressass->text();
       additionalInfo << "BUDGET : " + ui->lineEdit_8->text();
       additionalInfo << "DESCRIPTION : " + ui->labelaffdescriptionass->text();


       int yOffset = 120;
       foreach(const QString &info, additionalInfo) {
           painter.drawText(120, yOffset, info);
           yOffset += 20;
       }

       painter.end();
}
void MainWindow::on_comboBox_10_currentIndexChanged(int index)
{
    // Chemin d'accès vers votre script Python
    QString pythonScriptPath = "C:/Users/Iheb1/OneDrive/Bureau/devise.py";

    // Obtenir la valeur de budget de labelaffbudgetass
    QString budget = ui->labelaffbudgetass->text();
    if (!budget.isEmpty()) {
        // Déterminer le type de sortie en fonction de l'index sélectionné dans le ComboBox
        QString outputType;
        if (index >= 0 && index < ui->comboBox_10->count()) {
            switch (index) {
                case 0:
                    outputType = "EUR";
                    break;
                case 2:
                    outputType = "USD";
                    break;
                case 1:
                    outputType = "TND";
                    break;
                default:
                    outputType = ""; // Gérer le cas par défaut si nécessaire
                    break;
            }

            // Debug: Print arguments before executing Python script
            qDebug() << "Executing Python script with arguments:";
            qDebug() << "Python Script Path:" << pythonScriptPath;
            qDebug() << "Budget:" << budget;
            qDebug() << "Output Type:" << outputType;

            // Create QProcess for Python script execution
            QProcess process(this);

            // Construct command arguments
            QStringList arguments;
            arguments << pythonScriptPath << budget << outputType; // Pass script path, budget, and outputType

            // Redirect standard output for capturing
            process.setStandardOutputProcess(&process);

            // Start the Python script
            process.start("python", arguments);

            // Wait for process to finish (consider timeout if needed)
            process.waitForFinished(-1);

            // Read captured output and handle errors
            if (process.exitStatus() == QProcess::NormalExit) {
                QByteArray output = process.readAllStandardOutput();
                if (!output.isEmpty()) {
                    QString outputStr = QString::fromUtf8(output);
                    ui->labelaffbudgetass->setText(outputStr);
                } else {
                    // Handle empty output (e.g., display a message)
                    qDebug() << "The Python script did not produce any output.";
                }
            } else {
                // Handle non-normal exit status (already implemented in your code)
                QMessageBox::critical(this, "Error", "An error occurred during conversion.");
            }
        }
    }
}


/*void MainWindow::on_confirmer_clicked()
{
    // Récupérer les valeurs de latitude et de longitude de adress_a
    QString coordinates = ui->adress_a->text();

    QStringList coordinateList = coordinates.split(',');
    if (coordinateList.size() != 2) {
        qDebug() << "Erreur : Les coordonnées sont invalides";
        return;
    }

    double latitude = coordinateList[0].trimmed().toDouble();
    double longitude = coordinateList[1].trimmed().toDouble();
    qDebug() << "Latitude:" << latitude;
    qDebug() << "Longitude:" << longitude;

    // Créer un objet QProcess
    QProcess process;

    // Spécifier le chemin vers l'interpréteur Python et le script Python
    QString pythonScriptPath = "C:/Users/Iheb1/OneDrive/Bureau/city.py";

    // Démarrer le script Python
    process.start("python", QStringList() << pythonScriptPath);

    // Écrire les coordonnées dans l'entrée standard du processus Python
    process.write(QString("%1,%2\n").arg(latitude).arg(longitude).toUtf8());
    process.closeWriteChannel();

    // Attendre que le processus Python se termine
    if (!process.waitForFinished()) {
        qDebug() << "Erreur : Le processus Python n'a pas pu se terminer correctement";
        return;
    }

    // Lire la sortie standard du processus Python
    QString output = process.readAllStandardOutput();

    // Afficher la sortie dans le label adress_a_2
    ui->adress_a_2->setText(output.trimmed());
    qDebug() << output.trimmed();
}
*/

#include <QProcess>

void MainWindow::on_confirmer_clicked()
{
    // Récupérer les valeurs de latitude et de longitude depuis la label adress_a
    QString adresse = ui->adress_a->text();
    QStringList coordonnees = adresse.split(",");
    if (coordonnees.size() != 2) {
        qDebug() << "Format invalide pour les coordonnées.";
        return;
    }

    // Exécuter le script Python en tant que processus externe
    QProcess process;
    process.start("python", QStringList() << "C:/Users/Iheb1/OneDrive/Bureau/city.py" << coordonnees);
    if (!process.waitForStarted()) {
        qDebug() << "Erreur : Impossible de démarrer le processus.";
        return;
    }
    process.waitForFinished();

    // Vérifier s'il y a eu des erreurs lors de l'exécution du processus
    if (process.error() != QProcess::UnknownError) {
        qDebug() << "Erreur lors de l'exécution du script Python:" << process.errorString();
        return;
    }

    // Lire la sortie du processus
    QString output = process.readAllStandardOutput();

    // Mettre la sortie dans la label adress_a_2
    ui->adress_a_2->setText(output.trimmed());
}



