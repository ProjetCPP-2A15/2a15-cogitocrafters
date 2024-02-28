#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QComboBox>
#include <QtWidgets>
#include <QPrinter>
#include <QPainter>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidgetEvent->setCurrentIndex(2);
    connect(ui->searchGuest, &QLineEdit::textEdited, this, &MainWindow::on_searchGuest_textEdited);


    //g.afficher_tri(ui->comboBoxSortGuest->setCurrentText());

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
    ui->tableView->setModel(g.afficher());

    deselectButton(ui->pushButtonEvents);
    deselectButton(ui->pushButtonProduct);
    selectButton(ui->pushButtonGuest);
    deselectButton(ui->pushButtonArtist);
    deselectButton(ui->pushButtonAssociation);
    deselectButton(ui->pushButtonSetting);
    //ui->tableView->setModel(g.afficher());
}

void MainWindow::on_save_8_clicked()
{
    int cin = ui->addCinGuest->text().toInt();
    QString name = ui->addNameGuest->text();
    int age = ui->addAgeGuest->text().toInt();
    QString gender = ui->addGenderGuest->currentText();
    QString address = ui->addAddressGuest->text();
    QString email = ui->addEmailGuest->text();
    int phone = ui->addPhoneGuest->text().toInt();
    Guest g(cin, name, age, gender, address, phone, email);
    bool test;


    ui->label_affCIN->setText(QString::number(cin));
    ui->label_affName->setText(name);
    ui->label_affAge->setText(QString::number(age));
    ui->label_affGender->setText(gender);
    ui->label_affAddress->setText(address);
    ui->label_affPhone->setText(QString::number(phone));

    ui->label_affEmail->setText(email);


    QString cinStr = ui->addCinGuest->text();
    QString emailstr = ui->addEmailGuest->text();
    QString ageStr = ui->addAgeGuest->text();
    bool ageConversionOk;
    int ages = ageStr.toInt(&ageConversionOk);
    QRegExp cinRegex("\\d{8}"); // Expression régulière pour un CIN de 8 chiffres
    QRegularExpression emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");

    if (ui->addCinGuest->text().isEmpty() || name.isEmpty() || ui->addAgeGuest->text().isEmpty() || gender.isEmpty() || address.isEmpty() || ui->addPhoneGuest->text().isEmpty()) {
        QMessageBox::critical(this, "Erreur", "Veuillez remplir tous les champs.");
        return;
    }
    else if (!cinRegex.exactMatch(cinStr)) {
        QMessageBox::critical(this, "Erreur", "Veuillez saisir un CIN valide (6 chiffres).");
        return;
    }
    // Contrôle de saisie pour le champ Email
    else if (!emailRegex.match(email).hasMatch()) {
        QMessageBox::critical(this, "Erreur", "Veuillez saisir une adresse email valide.");
        return;
    }
    // Contrôle de saisie pour le champ Age
    else if (!ageConversionOk || ages <= 0) {
        QMessageBox::critical(this, "Erreur", "Veuillez saisir un âge valide (nombre entier positif).");
        return;
    }
    else {
        test= g.ajouter();
    }

    if (test)
    {

        // Efface les champs de saisie après l'ajout réussi
        ui->addCinGuest->clear();
        ui->addNameGuest->clear();
        ui->addAgeGuest->clear();
        ui->addAddressGuest->clear();
        ui->addEmailGuest->clear();
        ui->addPhoneGuest->clear(); // Réinitialise la sélection du sexe

        ui->stackedWidgetGuest->setCurrentIndex(3);
        ui->tableView->setModel(g.afficher());
        ui->tableView->verticalHeader()->setVisible(false);
        ui->tableView->horizontalHeader()->setVisible(false);
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                                 QObject::tr("connection successful.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                              QObject::tr(" connection failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }



}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{

    if (index.isValid()) {
            QVariant cin = index.sibling(index.row(), 0).data();
            QVariant name = index.sibling(index.row(), 1).data();
            QVariant age = index.sibling(index.row(), 2).data();
            QVariant gender = index.sibling(index.row(), 3).data();
            QVariant address = index.sibling(index.row(), 4).data();
            QVariant email = index.sibling(index.row(), 5).data();
            QVariant phone = index.sibling(index.row(), 6).data();

            ui->label_affCIN->setText(cin.toString());
            ui->label_affName->setText(name.toString());
            ui->label_affAge->setText(age.toString());
            ui->label_affGender->setText(gender.toString());
            ui->label_affAddress->setText(address.toString());
            ui->label_affEmail->setText(email.toString());
            ui->label_affPhone->setText(phone.toString());
        }
    ui->stackedWidgetGuest->setCurrentIndex(3);

}
void MainWindow::on_supprimer_Guest_clicked()
{
    g.supprimer(ui->label_affCIN->text().toInt());
    ui->tableView->setModel(g.afficher());
    ui->stackedWidgetGuest->setCurrentIndex(0);
}

void MainWindow::on_updateEmployee_2_clicked()
{
    ui->updateCIN->setText(ui->label_affCIN->text());
    ui->updateName->setText(ui->label_affName->text());
    ui->updateAge->setText(ui->label_affAge->text());
    ui->updateGender->setCurrentText(ui->label_affGender->text());
    ui->updateAddress->setText(ui->label_affAddress->text());
    ui->updateEmail->setText(ui->label_affEmail->text());
    ui->updatePhone->setText(ui->label_affPhone->text());
    ui->stackedWidgetGuest->setCurrentIndex(2);
}

void MainWindow::on_supprimer_35_clicked()
{
    ui->stackedWidgetGuest->setCurrentIndex(1);
   // ui->addCinGuest->setPlaceholderText("CIN (XXXXXXXX) 8 chiffre");

}

void MainWindow::on_save_6_clicked()
{
    //int cin = ui->updateCIN->text().toInt();
    QString name = ui->updateName->text();
    //int age = ui->updateAge->text().toInt();
    QString gender = ui->updateGender->currentText();
    QString address = ui->updateAddress->text();
    QString email = ui->updateEmail->text();
    //int phone = ui->updatePhone->text().toInt();


     QString cinStr = ui->updateCIN->text();
     QString emailstr = ui->updateEmail->text();
     QString ageStr = ui->updateAge->text();
     bool ageConversionOk;
     int ages = ageStr.toInt(&ageConversionOk);
     QRegExp cinRegex("\\d{8}"); // Expression régulière pour un CIN de 8 chiffres
     QRegularExpression emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");

     if (ui->updateCIN->text().isEmpty() || name.isEmpty() || ui->updateAge->text().isEmpty() || gender.isEmpty() || address.isEmpty() || ui->updatePhone->text().isEmpty()) {
        QMessageBox::critical(this, "Erreur", "Veuillez remplir tous les champs.");
        return;
     }
     else if (!cinRegex.exactMatch(cinStr)) {
            QMessageBox::critical(this, "Erreur", "Veuillez saisir un CIN valide (6 chiffres).");
            return;
     }
        // Contrôle de saisie pour le champ Email
     else if (!emailRegex.match(email).hasMatch()) {
            QMessageBox::critical(this, "Erreur", "Veuillez saisir une adresse email valide.");
            return;
     }
        // Contrôle de saisie pour le champ Age
     else if (!ageConversionOk || ages <= 0) {
            QMessageBox::critical(this, "Erreur", "Veuillez saisir un âge valide (nombre entier positif).");
            return;
     }
    else {
        g.modifier(ui->label_affCIN->text().toInt(),ui->updateCIN->text().toInt(),ui->updateName->text(),ui->updateAge->text().toInt(),ui->updateGender->currentText(),ui->updateAddress->text(),ui->updateEmail->text(),ui->updatePhone->text().toInt());
        ui->label_affCIN->setText(ui->updateCIN->text());
        ui->label_affName->setText(ui->updateName->text());
        ui->label_affAge->setText(ui->updateAge->text());
        ui->label_affGender->setText(ui->updateGender->currentText());
        ui->label_affAddress->setText(ui->updateAddress->text());
        ui->label_affEmail->setText(ui->updateEmail->text());
        ui->label_affPhone->setText(ui->updatePhone->text());
        ui->stackedWidgetGuest->setCurrentIndex(3);
    }
}

void MainWindow::on_searchGuest_textEdited(const QString &text)
{
    QSqlQueryModel* model = g.rechercher(text);
    ui->tableView->setModel(model);
}

void MainWindow::on_comboBoxSortGuest_activated(const QString &text)
{
     QSqlQueryModel* model = g.afficher_tri(text);
     if(text == "Name"|| text == "Age"|| text == "CIN") ui->tableView->setModel(model);
}

void MainWindow::on_ajouterArt_21_clicked()
{
    ui->stackedWidgetGuest->setCurrentIndex(0);

}
void MainWindow::on_ajouterArt_18_clicked()
{
    ui->stackedWidgetGuest->setCurrentIndex(0);

}
void MainWindow::on_ajouterArt_22_clicked()
{
    ui->stackedWidgetGuest->setCurrentIndex(0);
}

void MainWindow::on_supprimer_18_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save PDF", ui->label_affCIN->text(), "*.pdf");

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
    additionalInfo << "CIN : " << ui->label_affPhone->text();
    additionalInfo << "Full Name : ";
    additionalInfo << "Information 3";

    int yOffset = 120;
    foreach(const QString &info, additionalInfo) {
        painter.drawText(120, yOffset, info);
        yOffset += 20;
    }

    painter.end();
}
/*
void MainWindow::on_supprimer_34_clicked()
{
    ui->stackedWidgetGuest->setCurrentIndex(4);
}*/

/*
********************************************************************
*/

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


void MainWindow::on_save_5_clicked()
{
    ui->stackedWidgetProduct->setCurrentIndex(2);
}

void MainWindow::on_save_7_clicked()
{
    ui->stackedWidgetEvent->setCurrentIndex(0);

}















