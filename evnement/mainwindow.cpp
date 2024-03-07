#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employee.h"
#include <QMessageBox>
#include <QApplication>
#include "connection.h"
#include <QtWidgets>
#include <QPrinter>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabEmployee->setModel(emp.afficherEmployee());

    connect(ui->searchTextBox_employee, &QLineEdit::textEdited, this, &MainWindow::on_searchTextBox_employee_textEdited);
    ui->tabEmployee->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tabEmployee->setSelectionMode(QAbstractItemView::ExtendedSelection);
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
/*
void MainWindow::on_pushButton_15_clicked()
{
    int cin = ui->empCin_addGuest->text().toInt();
    QString name = ui->empName_addGuest->text();
    int age = ui->empAge_addGuest->text().toInt();
    QString gender = ui->empGender_addGuest->text();
    QString address = ui->empAdress_addGuest->text();
    QString email = ui->empEmail_addGuest->text();
    int phone = ui->empPhone_addGuest->text().toInt();

    Guest g(cin, name, age, gender, address, phone, email);

    bool test = g.ajouter();
    if (test)
    {

        // Efface les champs de saisie après l'ajout réussi
        ui->empCin_addGuest->clear();
        ui->empName_addGuest->clear();
        ui->empAge_addGuest->clear();
        ui->empGender_addGuest->clear();
        ui->empAdress_addGuest->clear();
        ui->empEmail_addGuest->clear();
        ui->empPhone_addGuest->clear(); // Réinitialise la sélection du sexe

        ui->stackedWidgetGuest->setCurrentIndex(0);
        ui->tableView->setModel(g.afficher());
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                                 QObject::tr("connection successful.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                              QObject::tr("connection failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}*/



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
    ui->tabEmployee->setModel(emp.afficherEmployee());
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





void MainWindow::on_addEmployee_clicked()
{
    ui->stackedWidgetSetting->setCurrentIndex(3);

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
/*************employee**********/

void MainWindow::on_save_clicked()
{
     int id=ui->lineEdit_IdEmployee->text().toUInt();
     QString name=ui->lineEdit_NameEmployee->text();
     QString lastname=ui->lineEdit_LastameEmployee->text();
     QString address=ui->lineEdit_AddressEmployee->text();
     QString sex=ui->comboBox_AddEmployee->currentText();
     QDate dateBirth = QDate::fromString(ui->lineEdit_DateBirthEmployee->text(), "dd/MM/yyyy");
     QString mail=ui->lineEdit_MailEmployee->text();
     QString function=ui->comboBox_AddFunctionEmployee->currentText();
     QString password=ui->lineEdit_PasswordEmployee->text();
     int phoneNumber=ui->lineEdit_PhoneNumberEmployee->text().toUInt();

     QRegularExpression emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
     QRegExp cinRegex("\\d{8}"); // Expression régulière pour un CIN de 8 chiffres

     employee e(id,name,lastname,address,sex,mail,function,password,dateBirth,phoneNumber,emp.getImagePath());
     if (name.isEmpty() || lastname.isEmpty() || address.isEmpty() ||dateBirth.isNull() || sex.isEmpty() || mail.isEmpty() || function.isEmpty()||password.isEmpty())
             {
                 QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                       QObject::tr(" Tous les champs sont obligatoires."),
                                       QMessageBox::Cancel);
                 return;
             }
         if (dateBirth> QDate(1960, 1, 1) and dateBirth> QDate(2000, 1, 1)) {
                 QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                       QObject::tr("date of birth should be between 1960 and 2000 ."),
                                       QMessageBox::Cancel);
                 return; }
         if (!emailRegex.match(mail).hasMatch()) {
                 QMessageBox::critical(this, "Erreur", "Veuillez saisir une adresse email valide.");
                 return;
             }
         if (!cinRegex.exactMatch(ui->lineEdit_IdEmployee->text())) {
                QMessageBox::critical(this, "Erreur", "Veuillez saisir un CIN valide (8 chiffres).");
                return;
            }
         if (!cinRegex.exactMatch(ui->lineEdit_PhoneNumberEmployee->text())) {
                QMessageBox::critical(this, "Erreur", "Veuillez saisir un phoneNumber valide (8 chiffres).");
                return;
            }
     bool test=e.ajouterEmployee();
     if(test)
     {
         QMessageBox::information(nullptr, QObject::tr("ok"),
                     QObject::tr("Ajout effectué.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
         ui->lineEdit_IdEmployee->clear();
         ui->lineEdit_NameEmployee->clear();
         ui->lineEdit_LastameEmployee->clear();
         ui->lineEdit_AddressEmployee->clear();
         ui->comboBox_AddEmployee->clear();
         ui->lineEdit_DateBirthEmployee->clear();
         ui->lineEdit_MailEmployee->clear();
         ui->comboBox_AddFunctionEmployee->clear();
         ui->lineEdit_PasswordEmployee->clear();
         ui->lineEdit_PhoneNumberEmployee->clear();
         ui->stackedWidgetSetting->setCurrentIndex(1);

     }
     else
      {
         QMessageBox::critical(nullptr, QObject::tr("not ok"),
                     QObject::tr("Ajout non effectué.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
     }
     ui->tabEmployee->setModel(emp.afficherEmployee());



}

void MainWindow::on_tabEmployee_clicked(const QModelIndex &index)
{
    if (index.isValid())
       {
           QVariant data = index.data();
           if(index.column()==0)
           {
               ui->stackedWidgetSetting->setCurrentIndex(2);
               int id_chercher = index.data().toInt();
               employee e = emp.chercher(id_chercher);
               ui->lineEdit_AffCIN->setText(QString::number(id_chercher));
               ui->lineEdit_AffName->setText(e.getName());
               ui->lineEdit_AffLastname->setText(e.getLastname());
               ui->lineEdit_AffSex->setText(e.getSex());
               ui->lineEdit_AffMail->setText(e.getMail());
               ui->lineEdit_AffAddress->setText(e.getAddress());

               ui->lineEdit_AffPhoneNumber->setText(QString::number(e.getPhoneNumber()));
               QString encryptedPassword = QString(e.getPassword().length(), '*');

               ui->lineEdit_AffFunction->setText(e.getFunction());
               ui->lineEdit_AffPassword->setText(encryptedPassword);
               ui->lineEdit_AffDateBirth->setText(e.getDateBirth().toString("dd/MM/yyyy"));

               QPixmap pixmap;
               pixmap.loadFromData(e.getImageData());
               if (!pixmap.isNull()) {
                   // Redimensionner l'image pour s'adapter à la taille de la QLabel
                   pixmap = pixmap.scaled(ui->label_AffImageEmployee->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                   ui->label_AffImageEmployee->setPixmap(pixmap);
               } else {
                   qDebug() << "Erreur: Impossible de charger l'image depuis les données ByteArray.";
                 }
           }
       }
}

void MainWindow::on_supprimer_Employee_clicked()
{
    int id=ui->lineEdit_AffCIN->text().toInt();
    bool test=emp.suprimerEmployee(id);
    QMessageBox msgBox;
    if(test){
        QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("Suppression effectuée \n"
                                                                        "Clicke Cancel to exite"),
                                 QMessageBox::Cancel);
        ui->tabEmployee->setModel(emp.afficherEmployee());
        ui->stackedWidgetSetting->setCurrentIndex(1);

    }
    else{ QMessageBox::critical(nullptr , QObject::tr("Not Ok "),QObject::tr("Suppression non effectuée\n"
                                                                              "Click Cancel to exit ."),
                                 QMessageBox::Cancel);
    }
}
void MainWindow::on_updateEmployee_clicked()
{
    int id=ui->lineEdit_AffCIN->text().toUInt();

    QString name=ui->lineEdit_AffName->text();
    QString lastname=ui->lineEdit_AffLastname->text();
    QString address=ui->lineEdit_AffAddress->text();
    QString sex=ui->lineEdit_AffSex->text();
    QString mail=ui->lineEdit_AffMail->text();
    QString function=ui->lineEdit_AffFunction->text();
    QString password=ui->lineEdit_AffPassword->text();
    QDate dateBirth=QDate::fromString(ui->lineEdit_AffDateBirth->text(), "dd/MM/yyyy");;
    int phoneNumber=ui->lineEdit_AffPhoneNumber->text().toUInt();
   QString encryptedPassword = QString(password.length(), '*');

    ui->lineEdit_UpDateIdEmployee->setText(QString::number(id));
    ui->lineEdit_UpDateNameEmployee->setText(name);
    ui->lineEdit_UpDateLastnameEmployee->setText(lastname);
    ui->comboBox_UpDateEmployee->setCurrentText(sex);
    ui->lineEdit_UpDateMailEmployee->setText(mail);
    ui->lineEdit_UpDateAddressEmployee->setText(address);
    ui->lineEdit_UpDatePhoneNumberEmployee->setText(QString::number(phoneNumber));
    ui->comboBox_UpDateFunctionEmployee->setCurrentText(function);
    ui->lineEdit_UpDatePasswordEmployee->setText(encryptedPassword);
    ui->dateEdit_UpDateEmployee->setDate(dateBirth);

    ui->stackedWidgetSetting->setCurrentIndex(0);

}
void MainWindow::on_save_2_clicked()
{
    int id=ui->lineEdit_UpDateIdEmployee->text().toUInt();
    QString name=ui->lineEdit_UpDateNameEmployee->text();
    QString lastname=ui->lineEdit_UpDateLastnameEmployee->text();
    QString address=ui->lineEdit_UpDateAddressEmployee->text();
    QString sex=ui->comboBox_UpDateEmployee->currentText();
    QString mail=ui->lineEdit_UpDateMailEmployee->text();
    QString function=ui->comboBox_UpDateFunctionEmployee->currentText();
    QString password=ui->lineEdit_UpDatePasswordEmployee->text();
    QDate dateBirth=QDate::fromString(ui->dateEdit_UpDateEmployee->text(), "dd/MM/yyyy");;
    int phoneNumber=ui->lineEdit_UpDatePhoneNumberEmployee->text().toUInt();
    QRegularExpression emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    QRegExp cinRegex("\\d{8}"); // Expression régulière pour un CIN de 8 chiffres

    if (name.isEmpty() || lastname.isEmpty() || address.isEmpty() ||dateBirth.isNull() || sex.isEmpty() || mail.isEmpty() || function.isEmpty()||password.isEmpty())
            {
                QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                      QObject::tr(" Tous les champs sont obligatoires."),
                                      QMessageBox::Cancel);
                return;
            }
        if (dateBirth> QDate(1960, 1, 1) and dateBirth> QDate(2000, 1, 1)) {
                QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                      QObject::tr("date of birth should be between 1960 and 2000 ."),
                                      QMessageBox::Cancel);
                return; }
        if (!emailRegex.match(mail).hasMatch()) {
                QMessageBox::critical(this, "Erreur", "Veuillez saisir une adresse email valide.");
                return;
            }
       /* if (!cinRegex.exactMatch(ui->lineEdit_IdEmployee->text())) {
               QMessageBox::critical(this, "Erreur", "Veuillez saisir un CIN valide (8 chiffres).");
               return;
           }*/
        if (!cinRegex.exactMatch(ui->lineEdit_UpDatePhoneNumberEmployee->text())) {
               QMessageBox::critical(this, "Erreur", "Veuillez saisir un phoneNumber valide (8 chiffres).");
               return;
           }
    employee e(id,name,lastname,address,sex,mail,function,password,dateBirth,phoneNumber);
    bool test=e.modifierEmployee();
    if(test){
        QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("Modification effectuée\n"
                                                                        "Clicke Cancel to exite"),QMessageBox::Cancel);

        ui->tabEmployee->setModel(emp.afficherEmployee());


    }else{ QMessageBox::critical(nullptr , QObject::tr("Not Ok "),QObject::tr("Modification échouée.\n"
                                                                              "Click Cancel to exit."),
                                 QMessageBox::Cancel);

    }
    ui->tabEmployee->setModel(emp.afficherEmployee());
    ui->stackedWidgetSetting->setCurrentIndex(1);
}

void MainWindow::on_listEmployee_clicked()
{
    ui->tabEmployee->setModel(emp.afficherEmployee());
    ui->stackedWidgetSetting->setCurrentIndex(1);

}

void MainWindow::on_clearEmployee_clicked()
{
    ui->lineEdit_IdEmployee->clear();
    ui->lineEdit_NameEmployee->clear();
    ui->lineEdit_LastameEmployee->clear();
    ui->lineEdit_AddressEmployee->clear();
    ui->comboBox_AddEmployee->clear();
    ui->lineEdit_DateBirthEmployee->clear();
    ui->lineEdit_MailEmployee->clear();
    ui->comboBox_AddFunctionEmployee->clear();
    ui->lineEdit_PasswordEmployee->clear();
    ui->lineEdit_PhoneNumberEmployee->clear();
}

void MainWindow::on_comboBox_Employee_activated(const QString &arg1)
{
    QSqlQueryModel* model = emp.afficher_tri(arg1);
     if(arg1 == "Name"|| arg1 == "Address"|| arg1 == "CIN") ui->tabEmployee->setModel(model);
}

void MainWindow::on_pdf_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save PDF", ui->lineEdit_AffCIN->text(), "*.pdf");

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
        painter.drawText(100, 100, "Employee's information");

        QStringList additionalInfo;
        additionalInfo << "CIN : " + ui->lineEdit_AffCIN->text();
        additionalInfo << "Name : " + ui->lineEdit_AffName->text();
        additionalInfo << "Lastname : " + ui->lineEdit_AffLastname->text();
        additionalInfo << "DateBirth : " + ui->lineEdit_AffDateBirth->text();
        additionalInfo << "Address : " + ui->lineEdit_AffSex->text();
        additionalInfo << "Phone Number : " + ui->lineEdit_AffPhoneNumber->text();
        additionalInfo << "Function : " + ui->lineEdit_AffFunction->text();
        additionalInfo << "Email : " + ui->lineEdit_AffMail->text();


        int yOffset = 120;
        foreach(const QString &info, additionalInfo) {
            painter.drawText(120, yOffset, info);
            yOffset += 20;
        }
        painter.end();
}

void MainWindow::on_searchTextBox_employee_textEdited(const QString &arg1)
{
    QSqlQueryModel* model = emp.rechercher(arg1);
        ui->tabEmployee->setModel(model);
}

void MainWindow::on_pushButton_AddImageEmployee_clicked()
{
    QString imagePath2 = QFileDialog::getOpenFileName(nullptr, "Sélectionner une image", "", "Images (*.png *.jpg *.jpeg *.bmp *.gif)");
    QPixmap pixmap(imagePath2);

    // Définir l'image comme fond du bouton et styliser le cadre
    ui->pushButton_AddImageEmployee->setStyleSheet(
                             "border-image: url("+imagePath2+");"
                             "border-width: 2px;"
                             "border-style: solid;"
                             "border-radius:15px;"
                             "border-color: #000000;" // Couleur du cadre
                             "text-align: center;"    // Aligner le texte au centre du bouton (en dehors de l'image)
                             "color: transparent;"
                             );
     emp.setImagePath(imagePath2);
}

void MainWindow::on_pushButton_UpDateImageEmployee_clicked()
{
    QString imagePath2 = QFileDialog::getOpenFileName(nullptr, "Sélectionner une image", "", "Images (*.png *.jpg *.jpeg *.bmp *.gif)");
        QPixmap pixmap(imagePath2);

        // Définir l'image comme fond du bouton et styliser le cadre
        ui->label_AffImageEmployee->setPixmap(pixmap);
         emp.setImagePath(imagePath2);
         int id_chercher=ui->lineEdit_AffCIN->text().toUInt();
         employee e = emp.chercher(id_chercher);
         bool test=e.modifierImage(imagePath2);
         if(test){
             QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("Modification effectuée\n"
                                                                             "Clicke Cancel to exite"),QMessageBox::Cancel);

             ui->tabEmployee->setModel(emp.afficherEmployee());


         }else{ QMessageBox::critical(nullptr , QObject::tr("Not Ok "),QObject::tr("Modification échouée.\n"
                                                                                   "Click Cancel to exit."),
                                      QMessageBox::Cancel);

         }    ui->tabEmployee->setModel(emp.afficherEmployee());

}

void MainWindow::on_listEmployee_2_clicked()
{
    ui->tabEmployee->setModel(emp.afficherEmployee());
    ui->stackedWidgetSetting->setCurrentIndex(1);
}

void MainWindow::on_listEmployeeAdd_clicked()
{
    ui->tabEmployee->setModel(emp.afficherEmployee());
    ui->stackedWidgetSetting->setCurrentIndex(1);
}

void MainWindow::on_supprimer_Employee_2_clicked()
{
    QModelIndexList selectedRows = ui->tabEmployee->selectionModel()->selectedRows();

        // Parcourez les indices des lignes sélectionnées et supprimez-les une par une
        for (const QModelIndex &index : selectedRows) {
            // Obtenez la valeur dans la première colonne (colonnes sont 0-indexées)
            int valueToDelete = ui->tabEmployee->model()->data(index.sibling(index.row(), 0)).toInt();
            // Utilisez cette valeur pour appeler votre fonction de suppression
            emp.suprimerEmployee(valueToDelete);
        }
        // Rafraîchissez le modèle de votre table view après la suppression
        ui->tabEmployee->setModel(emp.afficherEmployee());
}

void MainWindow::on_pushButtonLogin_clicked()
{

    QString mail=ui->lineEdit_LoginEmail->text();
    QString password=ui->lineEdit_LoginPassword->text();
    bool test=emp.login(mail,password);
    if(test){
        ui->tabEmployee->setModel(emp.afficherEmployee());
        QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("login effectuée\n"
                                                                        "Clicke Cancel to exite"),QMessageBox::Cancel);

        ui->stackedWidgetGlobal->setCurrentIndex(0);
        ui->stackedWidget->setCurrentIndex(3);
        ui->stackedWidgetEvent->setCurrentIndex(2);

    }else{ QMessageBox::critical(nullptr , QObject::tr("Not Ok "),QObject::tr("login échouée.\n"
                                                                              "Click Cancel to exit."),
                                 QMessageBox::Cancel);

    }
    ui->tabEmployee->setModel(emp.afficherEmployee());


}

void MainWindow::on_checkBox_stateChanged()
{

    employee e1 = emp.chercher(ui->lineEdit_AffCIN->text().toUInt());

    if (ui->checkBox->isChecked())
     {

        ui->lineEdit_UpDatePasswordEmployee->setText(e1.getPassword());

    }
    else
    {
         QString encryptedPassword = QString(e1.getPassword().length(), '*');
         ui->lineEdit_AffPassword->setText(encryptedPassword);
         ui->lineEdit_UpDatePasswordEmployee->setText(encryptedPassword);
    }

}
