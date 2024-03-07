#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "evenement.h"
#include <QApplication>
#include "connection.h"
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView_14->setModel(e.afficherEvenement());
    connect(ui->searchevent, &QLineEdit::textEdited, this, &MainWindow::on_searchevent_textEdited);
    ui->tableView_14->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_14->setSelectionMode(QAbstractItemView::ExtendedSelection);
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
    ui->tableView_14->setModel(e.afficherEvenement());
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

 //                                         Partie Artist
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
void MainWindow::on_add_event_clicked()
{
    int id_event =e.generateNewID();
    //int id_event = ui->id_event->text().toInt();
    QString event_noun = ui->event_noun->text();
    int nb_employee = ui->nb_employee->value();
    QString location = ui->location->text();
    QString description = ui->description->toPlainText();
    QDate start_d = QDate::fromString(ui->start_d->text(), "dd/MM/yyyy");
    QDate end_d = QDate::fromString(ui->end_d->text(), "dd/MM/yyyy");
    QTime start_h = ui->start_h->time();
    QTime end_h = ui->end_h->time();
    float price_tick = ui->price_tick->value();
    if (event_noun.isEmpty() || location.isEmpty() || description.isEmpty() || start_d.isNull() || end_d.isNull() || start_h.isNull() || end_h.isNull()||nb_employee == 0 || price_tick == 0.0)
           {
               QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                     QObject::tr(" All fields are required."),
                                     QMessageBox::Cancel);
               return;
           }
       if (start_d < QDate::currentDate()) {
           QMessageBox::critical(nullptr, QObject::tr("Error"),
                                 QObject::tr("Start date must be from %1 onwards.").arg(QDate::currentDate().toString("MM/dd/yyyy")),
                                 QMessageBox::Cancel);
           return;
       }


           if (end_d <= start_d) {
               QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                     QObject::tr("End date must be after the start date."),
                                     QMessageBox::Cancel);
               return;
           }
          /* if (start_h < QTime(7, 0) || start_h > QTime(20, 0)) {
                   QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                         QObject::tr("Start time must be between 7AM and 8PM."),
                                         QMessageBox::Cancel);
                   return;
               }*/

               /*if (end_h < QTime(7, 0) || end_h > QTime(20, 0)) {
                   QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                         QObject::tr("End time must be between 7AM and 8PM."),
                                         QMessageBox::Cancel);
                   return;
               }
*/
               if (end_h <= start_h) {
                   QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                         QObject::tr("End time must be after the start time."),
                                         QMessageBox::Cancel);
                   return;
               }

    evenement e(id_event, nb_employee, event_noun, location, description, start_d, end_d, start_h, end_h, price_tick);
    bool test = e.ajouterEvenement();
    if (test)
    {
        // Afficher l'événement ajouté dans la vue détaillée
        ui->stackedWidgetEvent->setCurrentIndex(0);
        ui->nount->setText(event_noun);
        ui->idt->setText(QString::number(id_event));
        ui->nbt->setText(QString::number(nb_employee));
        ui->pricet->setText(QString::number(price_tick));
        ui->sht->setTime(start_h);
        ui->eht->setTime(end_h);
        ui->sdt->setDate(start_d);
        ui->edt->setDate(end_d);
        ui->locationt->setText(location);
        ui->descriptiont->setText(description);

        // Mettre à jour le modèle de la table pour refléter les modifications
        ui->tableView_14->setModel(e.afficherEvenement());
        // Afficher un message de succès
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("the event has been added successfully.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("The event could not be added.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
    clearEventFields();
}
void MainWindow::on_tableView_14_clicked(const QModelIndex &index)
{
    if (index.isValid())
           {
               QVariant data = index.data();
               if(index.column()==0)
               {
                   ui->stackedWidgetEvent->setCurrentIndex(0);
                   int id_event = index.data().toInt();
                   evenement ev = e.chercher(id_event);
                   ui->nount->setText(ev.getEventNoun());
                   ui->idt->setText(QString::number(ev.getIdEvent()));
                   ui->nbt->setText(QString::number(ev.getNbEmployee()));
                   ui->pricet->setText(QString::number(ev.getPriceTick()));
                   ui->sht->setTime(ev.getStartH());
                   ui->eht->setTime(ev.getEndH());
                   ui->sdt->setDate(ev.getStartD());
                   ui->edt->setDate(ev.getEndD());
                   ui->locationt->setText(ev.getLocation());
                   ui->descriptiont->setText(ev.getDescription());
               }
           }
}
void MainWindow::on_supprimer_event_clicked()
{
    QString noun=ui->nount->text();
        bool test=e.supprimerEvenement(noun);
        QMessageBox msgBox;
        if(test){
            clearEventFields();
            clearEventdetailFields();
            QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("deleted successfully \n"
                                                                            "Clicke Cancel to exite"),
                                     QMessageBox::Cancel);
            ui->tableView_14->setModel(e.afficherEvenement());
            ui->stackedWidgetSetting->setCurrentIndex(1);

        }
        else{ QMessageBox::critical(nullptr , QObject::tr("Not Ok "),QObject::tr(" not deleted successfully\n"
                                                                                  "Click Cancel to exit ."),
                                     QMessageBox::Cancel);
        }

}
void MainWindow::clearEventFields()
{
    // Efface les champs du formulaire
    //ui->id_event->clear();
    ui->event_noun->clear();
    ui->nb_employee->setValue(0);
    ui->location->clear();
    ui->description->clear();
    ui->start_d->setDate(QDate::currentDate());
    ui->end_d->setDate(QDate::currentDate());
    ui->start_h->setTime(QTime(0, 0));
    ui->end_h->setTime(QTime(0, 0));
    ui->price_tick->setValue(0.0);
}
void MainWindow::clearEventdetailFields()
{
    // Efface les champs du l'affichage d'un evenement
    ui->idt->clear();
    ui->nount->clear();
    ui->nbt->clear();
    ui->pricet->clear();
    ui->sht->clear();
    ui->eht->clear();
    ui->sdt->clear();
    ui->edt->clear();
    ui->locationt->clear();
    ui->descriptiont->clear();
}

void MainWindow::on_updateEvent_clicked()
{
    // Récupérer les valeurs des champs d'édition d'un événement
    int id_event = ui->idt->text().toInt();
    int nb_employee = ui->nbt->text().toInt();// Par exemple, récupérez l'ID de l'événement à mettre à jour
    QString event_noun = ui->nount->text();
    QString location = ui->locationt->text();
    QString description = ui->descriptiont->text();
    //QDate start_d = ui->sdt->date();
    QDate start_d=QDate::fromString(ui->sdt->text(), "dd/MM/yyyy");
    //QDate end_d = ui->edt->date();
    QDate end_d=QDate::fromString(ui->edt->text(), "dd/MM/yyyy");
    QString start_h = ui->sht->text();
    QString end_h = ui->eht->text();
    float price_tick = ui->pricet->text().toInt();

    // Mettre à jour les champs de l'écran de mise à jour d'un événement avec les valeurs récupérées
    ui->nbempup->setText(QString::number(nb_employee));
    ui->idup->setText(QString::number(id_event));
    ui->eventnounup->setText(event_noun);
    ui->locationup->setText(location);
    ui->descriptionup->setPlainText(description);
    ui->sdup->setDate(start_d);
    ui->edup->setDate(end_d);
    ui->shup->setTime(QTime::fromString(start_h, "hh:mm"));
    ui->ehup->setTime(QTime::fromString(end_h, "hh:mm"));
    ui->priceup->setValue(price_tick);

    // Passer à l'écran de mise à jour d'un événement
    ui->stackedWidgetEvent->setCurrentIndex(1);
}
void MainWindow::on_saveup_clicked()
{
    // Extracting data from UI elements
    int id_event = ui->idup->text().toInt();
    int nb_employee = ui->nbempup->text().toInt();
    QString event_noun = ui->eventnounup->text();
    QString location = ui->locationup->text();
    QString description = ui->descriptionup->toPlainText();
    QDate start_d = QDate::fromString(ui->sdup->text(), "dd/MM/yyyy");
    QDate end_d = QDate::fromString(ui->edup->text(), "dd/MM/yyyy");
    QTime start_h = QTime::fromString(ui->shup->text(), "hh:mm");
    QTime end_h = QTime::fromString(ui->ehup->text(), "hh:mm");
    float price_tick = ui->priceup->text().toFloat();
    if (start_d < QDate::currentDate()) {
        QMessageBox::critical(nullptr, QObject::tr("Error"),
                              QObject::tr("Start date must be from %1 onwards.").arg(QDate::currentDate().toString("MM/dd/yyyy")),
                              QMessageBox::Cancel);
        return;
    }


        if (end_d <= start_d) {
            QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                  QObject::tr("End date must be after the start date."),
                                  QMessageBox::Cancel);
            return;
        }
        /*if (start_h < QTime(7, 0) || start_h > QTime(20, 0)) {
                QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                      QObject::tr("Start time must be between 7AM and 8PM."),
                                      QMessageBox::Cancel);
                return;
            }*/

            /*if (end_h < QTime(7, 0) || end_h > QTime(20, 0)) {
                QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                      QObject::tr("End time must be between 7AM and 8PM."),
                                      QMessageBox::Cancel);
                return;
            }
*/
            if (end_h <= start_h) {
                QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                      QObject::tr("End time must be after the start time."),
                                      QMessageBox::Cancel);
                return;
            }

    // Creating evenement object and updating the event in the database
    evenement e(id_event, nb_employee, event_noun, location, description, start_d, end_d, start_h, end_h, price_tick);
    bool test = e.modifierEvenement();


    if (test) {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Updated successfully.\nClick Cancel to exit."),
                                 QMessageBox::Cancel);
        ui->tableView_14->setModel(e.afficherEvenement());
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Modification failed.\nClick Cancel to exit."),
                              QMessageBox::Cancel);
    }

    // Changing the current index of stacked widget
    ui->stackedWidgetEvent->setCurrentIndex(2);
}

void MainWindow::on_clear_clicked()
{
    clearEventFields();
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


void MainWindow::on_comboBox_2_activated(const QString &arg1)
{
    QSqlQueryModel* model = e.afficher_tri(arg1);
         if(arg1 == "ID"|| arg1 == "Event Noun"|| arg1 == "Date") ui->tableView_14->setModel(model);
}
void MainWindow::on_pdfevent_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save PDF", ui->idt->text(), "*.pdf");

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
    painter.drawText(100, 100, "Guest information");

    QStringList additionalInfo;
    additionalInfo << "ID : " + ui->idt->text();
    additionalInfo << "Name Event : " + ui->nount->text();
    additionalInfo << "Location : " + ui->locationt->text();
    additionalInfo << "Description : " + ui->descriptiont->text();
    additionalInfo << "Start Hour : " + ui->sht->text();
    additionalInfo << "End Hour : " + ui->eht->text();
    additionalInfo << "Start Date: " + ui->sdt->text();
    additionalInfo << "End Date: " +  ui->edt->text();
    additionalInfo << "Employees number : " + ui->nbt->text();
    additionalInfo << "Price ticket : " + ui->pricet->text();
    int yOffset = 120;
    foreach(const QString &info, additionalInfo) {
        painter.drawText(120, yOffset, info);
        yOffset += 20;
    }

    painter.end();
}

void MainWindow::on_searchevent_textEdited(const QString &arg1)
{
    QSqlQueryModel* model = e.rechercher(arg1);
       ui->tableView_14->setModel(model);
}



void MainWindow::on_tout_supprimer_clicked() {
    QModelIndexList selectedRows = ui->tableView_14->selectionModel()->selectedRows();
    // Parcourez les indices des lignes sélectionnées et supprimez-les une par une
    for (const QModelIndex &index : selectedRows) {
        // Obtenez la valeur dans la deuxième colonne (colonnes sont 1-indexées)
        QString valueToDelete = ui->tableView_14->model()->data(index.sibling(index.row(), 1)).toString();
        // Utilisez cette valeur pour appeler votre fonction de suppression
        e.supprimerEvenement(valueToDelete);
    }
    // Rafraîchissez le modèle de votre table view après la suppression
    ui->tableView_14->setModel(e.afficherEvenement());
}


void MainWindow::on_ajouterArt_19_clicked()
{
    ui->stackedWidgetEvent->setCurrentIndex(2);
}
