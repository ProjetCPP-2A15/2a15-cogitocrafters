#include "guest.h"
#include<QDebug>
#include <QFile>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"evenement.h"

Guest::Guest(int c,QString n, int a, QString g, QString adr, int ph, QString e,QString i)
{
    CIN = c;
    phone = ph;
    age = a;
    name = n;
    address = adr;
    email = e;
    gender = g;
    imagePath =i;
}

bool Guest::ajouter()
{
    Connection connection;

    // Lire l'image depuis le fichier
    QFile file(imagePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Erreur: Impossible de lire l'image:" << file.errorString();
        qDebug() << imagePath;
        return false;
    }
    QByteArray imageData = file.readAll();
    file.close();

    QSqlQuery query;
    query.prepare("INSERT INTO GUEST (CIN, name, age, gender, address, phone, email, image) VALUES (:CIN, :name, :age, :gender, :address, :phone, :email, :image)");

    query.bindValue(":CIN", this->CIN);
    query.bindValue(":name", this->name);
    query.bindValue(":age", this->age);
    query.bindValue(":gender", this->gender);
    query.bindValue(":address", this->address);
    query.bindValue(":phone", this->phone);
    query.bindValue(":email", this->email);
    query.bindValue(":image", imageData);

    if (!query.exec()) {
        qDebug() << "Erreur d'exécution de la requête SQL:" << query.lastError().text();
        return false;
    }

    return true; // Retourner true si l'ajout a réussi
}



QSqlQueryModel* Guest::afficher() {
    QSqlQueryModel *model = new QSqlQueryModel();

    QString query = "SELECT CAST(CIN AS varchar(255)), name, age, gender, address, CAST(phone AS varchar(255)), email FROM GUEST WHERE CIN >1 ";
    model->setQuery(query);

    return model;
}

QSqlQueryModel *Guest::afficherId(int cin)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT CAST(CIN AS varchar(255)), name, age, gender, address, PHONE , email,image FROM GUEST WHERE CIN = :cin");
    query.bindValue(":cin", cin);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
        delete model; // Libérer la mémoire allouée avant de retourner nullptr
        return nullptr;
    }

    model->setQuery(query);
    return model;
}



bool Guest::supprimer(int cin)
{
    QSqlQuery query;
    query.prepare("DELETE FROM GUEST WHERE CIN = :cin");
    query.bindValue(":cin", cin);

    if (!query.exec()) {
        qDebug() << "Erreur SQL:" << query.lastError().text(); // Utiliser qDebug() au lieu de QDebug()
        return false;
    }
    return true; // Retourner true si l'ajout a réussi
}


bool Guest::modifierImage(int ancienCin, int nouveauCin, QString n, int a, QString g, QString adr, QString e, int ph,QString img) {

    // Lire l'image depuis le fichier
    QFile file(img);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Erreur: Impossible de lire l'image:" << file.errorString();
        qDebug() << img;
        return false;
    }
    QByteArray imageData = file.readAll();
    file.close();

    QSqlQuery query;
    query.prepare("UPDATE GUEST SET CIN=:nouveauCin, NAME=:name, AGE=:age, GENDER=:gender, ADDRESS=:address, PHONE=:phone, EMAIL=:email, IMAGE=:image WHERE CIN=:ancienCin");
    query.bindValue(":nouveauCin", nouveauCin);
    query.bindValue(":ancienCin", ancienCin);
    query.bindValue(":name", n);
    query.bindValue(":age", a);
    query.bindValue(":gender", g);
    query.bindValue(":address", adr);
    query.bindValue(":phone", ph);
    query.bindValue(":email", e);
    query.bindValue(":image", imageData);


    if (!query.exec()) {
        qDebug() << "Erreur SQL:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Guest::modifier(int ancienCin, int nouveauCin, QString n, int a, QString g, QString adr, QString e, int ph) {

    QSqlQuery query;
    query.prepare("UPDATE GUEST SET CIN=:nouveauCin, NAME=:name, AGE=:age, GENDER=:gender, ADDRESS=:address, PHONE=:phone, EMAIL=:email WHERE CIN=:ancienCin");
    query.bindValue(":nouveauCin", nouveauCin);
    query.bindValue(":ancienCin", ancienCin);
    query.bindValue(":name", n);
    query.bindValue(":age", a);
    query.bindValue(":gender", g);
    query.bindValue(":address", adr);
    query.bindValue(":phone", ph);
    query.bindValue(":email", e);


    if (!query.exec()) {
        qDebug() << "Erreur SQL:" << query.lastError().text();
        return false;
    }
    return true;
}

QSqlQueryModel* Guest::rechercher(QString G)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CAST(CIN AS varchar(255)), name, age, gender, address, CAST(phone AS varchar(255)), email FROM GUEST WHERE (NAME LIKE '%" + G + "%') AND (CIN >1) ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NAME"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("AGE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("GENDER"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADDRESS"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("PHONE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("EMAIL"));
    return model;
}

QSqlQueryModel* Guest::afficher_tri(const QString &critere) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QString query = "SELECT * FROM GUEST ORDER BY ";

    if(critere == "CIN") {
        query += "CIN";
    } else if(critere == "Age") {
        query += "AGE";
    } else if(critere == "Name") {
        query += "NAME";
    }

    model->setQuery(query);
    return model;
}

QSqlQueryModel* Guest::afficher_tri_CIN(bool checked)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QString query = "SELECT CAST(CIN AS varchar(255)), name, age, gender, address, CAST(phone AS varchar(255)), email FROM GUEST WHERE (CIN >1) ORDER BY CIN ";
    if (!checked)
        query += " DESC";

    model->setQuery(query);
    return model;

}
QSqlQueryModel* Guest::afficher_tri_Name(bool checked)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QString query = "SELECT CAST(CIN AS varchar(255)), name, age, gender, address, CAST(phone AS varchar(255)), email FROM GUEST WHERE (CIN >1) ORDER BY NAME";
    if (!checked)
        query += " DESC";

    model->setQuery(query);

    return model;

}
QSqlQueryModel* Guest::afficher_tri_Age(bool checked)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QString query = "SELECT CAST(CIN AS varchar(255)), name, age, gender, address, CAST(phone AS varchar(255)), email FROM GUEST WHERE (CIN >1) ORDER BY AGE";
    if (!checked)
        query += " DESC";

    model->setQuery(query);
    return model;

}
QSqlQueryModel* Guest::afficher_tri_Gender(bool checked)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QString query = "SELECT CAST(CIN AS varchar(255)), name, age, gender, address, CAST(phone AS varchar(255)), email FROM GUEST WHERE (CIN >1) ORDER BY GENDER";
    if (!checked)
        query += " DESC";
    model->setQuery(query);

    return model;

}
QSqlQueryModel* Guest::afficher_tri_Address(bool checked)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QString query = "SELECT CAST(CIN AS varchar(255)), name, age, gender, address, CAST(phone AS varchar(255)), email FROM GUEST WHERE (CIN >1) ORDER BY ADDRESS";
    if (!checked)
        query += " DESC";

    model->setQuery(query);
    return model;

}
QSqlQueryModel* Guest::afficher_tri_Phone(bool checked)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QString query = "SELECT CAST(CIN AS varchar(255)), name, age, gender, address, CAST(phone AS varchar(255)), email FROM GUEST WHERE (CIN >1) ORDER BY PHONE";
    if (!checked)
        query += " DESC";

    model->setQuery(query);
    return model;

}

QSqlQueryModel* Guest::afficher_tri_Email(bool checked)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QString query = "SELECT CAST(CIN AS varchar(255)), name, age, gender, address, CAST(phone AS varchar(255)), email FROM GUEST WHERE (CIN >1) ORDER BY EMAIL";
    if (!checked)
        query += " DESC";

    model->setQuery(query);
    return model;

}



//                                            Partie Guest

/******************************************* Go To Affichage Simple From Add ****************************************************/
void MainWindow::on_go_to_affSimple_from_addGuest_clicked()
{
    int cin = ui->addCinGuest->text().toInt();
    QString name = ui->addNameGuest->text();
    int age = ui->addAgeGuest->text().toInt();
    QString gender = ui->addGenderGuest->currentText();
    QString address = ui->addAddressGuest->text();
    QString email = ui->addEmailGuest->text();
    int phone = ui->addPhoneGuest->text().toInt();
    Guest ge(cin, name, age, gender, address, phone, email,g.getImage());
    bool test;

    ui->label_affCIN->setText(QString::number(cin));
    ui->label_affName->setText(name);
    ui->label_affAge->setText(QString::number(age));
    ui->label_affGender->setText(gender);
    ui->label_affAddress->setText(address);
    ui->label_affPhone->setText(QString::number(phone));
    ui->label_affEmail->setText(email);
    QPixmap pixmap(g.getImage());

    // Redimensionner l'image pour qu'elle s'adapte à la taille du label
    QPixmap scaledPixmap = pixmap.scaled(ui->label_affImage->size(), Qt::KeepAspectRatio);

    // Définir l'image sur le label
    ui->label_affImage->setPixmap(scaledPixmap);

    QString cinStr = ui->addCinGuest->text();
    QString emailstr = ui->addEmailGuest->text();
    QString ageStr = ui->addAgeGuest->text();
    bool ageConversionOk;
    int ages = ageStr.toInt(&ageConversionOk);
    QRegExp cinRegex("\\d{8}"); // Expression régulière pour un CIN de 8 chiffres
    QRegularExpression emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");

    QProcess process;
    QString scriptPath = "C:/Users/Emna Nkhili/Desktop/noblePalette/noblePalette/script/guest/persondetector/2.py";
    QStringList arguments;
    arguments << g.getImage(); // Ajoutez vos arguments ici
    process.start("python", QStringList() << scriptPath << arguments);

    if (!process.waitForStarted()) {
        qDebug() << "Erreur: Impossible de démarrer le processus.";
        return; // Sortir de la fonction en cas d'erreur
    }

    if (!process.waitForFinished(-1)) {
        qDebug() << "Erreur: Le processus a échoué ou a pris trop de temps.";
        return; // Sortir de la fonction en cas d'erreur
    }

    QString result = process.readAllStandardOutput();
    result = result.trimmed();
    if (result != "person") {
        QMessageBox::critical(this, "Erreur", "Veuillez inserer image d'une personne.");
        qDebug() << result;
        return;    }
    else if (ui->addCinGuest->text().isEmpty() || name.isEmpty() || ui->addAgeGuest->text().isEmpty() || gender.isEmpty() || address.isEmpty() || ui->addPhoneGuest->text().isEmpty()) {
        QMessageBox::critical(this, "Erreur", "Veuillez remplir tous les champs.");
        return;
    }
    else if (!cinRegex.exactMatch(cinStr)) {
        QMessageBox::critical(this, "Erreur", "Veuillez saisir un CIN valide (8 chiffres).");
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
        test= ge.ajouter();
    }

    if (test)
    {
        // Efface les champs de saisie après l'ajout réussi
        ui->addCinGuest->clear();
        ui->addNameGuest->clear();
        ui->addAgeGuest->clear();
        ui->addAddressGuest->clear();
        ui->addEmailGuest->clear();
        ui->addPhoneGuest->clear();

        ui->stackedWidgetGuest->setCurrentIndex(3);
        ui->tableViewGuest->setModel(g.afficher());
        ui->tableViewGuest->verticalHeader()->setVisible(false);
        ui->tableViewGuest->horizontalHeader()->setVisible(false);
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
    g.setImage("");

}
/************************************** Go to AFFICHAGE SIMPLE **************************************************/
void MainWindow::on_tableViewGuest_doubleClicked(const QModelIndex &index)
{
    if (index.isValid()) {
        QVariant cin = index.sibling(index.row(), 0).data();
        int cinValue = cin.toInt();
        QSqlQueryModel *model = g.afficherId(cinValue);

        if (model && model->rowCount() > 0) {
            QString name = model->record(0).value("Name").toString();
            QString age = model->record(0).value("Age").toString();
            QString gender = model->record(0).value("Gender").toString();
            QString address = model->record(0).value("Address").toString();
            QString phone = model->record(0).value("Phone").toString();
            QString email = model->record(0).value("Email").toString();

            QByteArray imageData = model->record(0).value("Image").toByteArray();
            QPixmap pixmap;
            pixmap.loadFromData(imageData);

            if (!pixmap.isNull()) {
                // Redimensionner l'image pour s'adapter à la taille de la QLabel
                pixmap = pixmap.scaled(ui->label_affImage->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->label_affImage->setPixmap(pixmap);
            } else {
                qDebug() << "Erreur: Impossible de charger l'image depuis les données ByteArray.";
                ui->label_affImage->setText("Aucune image disponible");
            }

            // Affichage des autres informations
            ui->label_affCIN->setText(cin.toString());
            ui->label_affName->setText(name);
            ui->label_affAge->setText(age);
            ui->label_affGender->setText(gender);
            ui->label_affAddress->setText(address);
            ui->label_affEmail->setText(email);
            ui->label_affPhone->setText(phone);

            // Changer l'index du widget empilé pour afficher les informations
            ui->stackedWidgetGuest->setCurrentIndex(3);
        } else {
            qDebug() << "Erreur: Aucune donnée trouvée pour cet ID.";
        }
    }

}

/******************************************* DELETE ****************************************************/

void MainWindow::on_supprimer_Guest_clicked()
{
    g.supprimer(ui->label_affCIN->text().toInt());
    ui->tableViewGuest->setModel(g.afficher());
    ui->stackedWidgetGuest->setCurrentIndex(0);
}
/******************************************* Go To UPDATE ****************************************************/
void MainWindow::on_go_to_updateGuest_clicked()
{
    ui->updateCIN->setText(ui->label_affCIN->text());
    ui->updateName->setText(ui->label_affName->text());
    ui->updateAge->setText(ui->label_affAge->text());
    ui->updateGender->setCurrentText(ui->label_affGender->text());
    ui->updateAddress->setText(ui->label_affAddress->text());
    ui->updateEmail->setText(ui->label_affEmail->text());
    ui->updatePhone->setText(ui->label_affPhone->text());
    QSqlQueryModel *model = g.afficherId(ui->label_affCIN->text().toInt());
    QByteArray imageData = model->record(0).value("Image").toByteArray();
    //QPixmap pixmap = *ui->label_affImage->pixmap();
    // Appliquer l'image au bouton-poussoir
    QPixmap pixmap;
    pixmap.loadFromData(imageData);
    pixmap = pixmap.scaled(ui->labelupdateImage->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->labelupdateImage->setPixmap(pixmap);

    ui->stackedWidgetGuest->setCurrentIndex(2);
}

void MainWindow::on_go_to_addGuest_clicked()
{
    ui->stackedWidgetGuest->setCurrentIndex(1);
    ui->addImageGuest->setStyleSheet(
                             "border-width: 2px;"
                             "border-style: solid;"
                             "border-color: #000000;"
                             "border-radius:15px;"
                             "text-align: center;"    // Aligner le texte au centre du bouton (en dehors de l'image)
                             "color: transparent;"
                             );
   // ui->addCinGuest->setPlaceholderText("CIN(XXXXXXXX) 8 chiffre");
}
/******************************************************* Fonction UPDATE ************************************************************************************************/
void MainWindow::on_go_to_addSimple_from_update_clicked()
{
    //int cin = ui->updateCIN->text().toInt();
    QString name = ui->updateName->text();
    //int age = ui->updateAge->text().toInt();
    QString gender = ui->updateGender->currentText();
    QString address = ui->updateAddress->text();
    QString email = ui->updateEmail->text();
    QString image = g.getImage();
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
     else if (!emailRegex.match(emailstr).hasMatch()) {
            QMessageBox::critical(this, "Erreur", "Veuillez saisir une adresse email valide." + emailstr);
            return;
     }
        // Contrôle de saisie pour le champ Age
     else if (!ageConversionOk || ages <= 0) {
            QMessageBox::critical(this, "Erreur", "Veuillez saisir un âge valide (nombre entier positif).");
            return;
     }
     else if(g.getImage().isEmpty()) {
         g.modifier(ui->label_affCIN->text().toInt(),ui->updateCIN->text().toInt(),ui->updateName->text(),ui->updateAge->text().toInt(),ui->updateGender->currentText(),ui->updateAddress->text(),ui->updateEmail->text(),ui->updatePhone->text().toInt());
         ui->label_affCIN->setText(ui->updateCIN->text());
         ui->label_affName->setText(ui->updateName->text());
         ui->label_affAge->setText(ui->updateAge->text());
         ui->label_affGender->setText(ui->updateGender->currentText());
         ui->label_affAddress->setText(ui->updateAddress->text());
         ui->label_affEmail->setText(ui->updateEmail->text());
         ui->label_affPhone->setText(ui->updatePhone->text());

     }
     else
     {

         QProcess process;
         QString scriptPath = "C:/Users/Emna Nkhili/Desktop/noblePalette/noblePalette/script/guest/persondetector/2.py";

         QStringList arguments;
         arguments << g.getImage(); // Ajoutez vos arguments ici
         process.start("python", QStringList() << scriptPath << arguments);

         if (!process.waitForFinished(-1)) {
             qDebug() << "Erreur: Le processus a échoué ou a pris trop de temps.";
             return; // Sortir de la fonction en cas d'erreur
         }

         QString result = process.readAllStandardOutput();
         result = result.trimmed();
         if (result != "person") {
             QMessageBox::critical(this, "Erreur", "Veuillez inserer image d'une personne.");
             qDebug() << result;
             return;    }
         else{
            g.modifierImage(ui->label_affCIN->text().toInt(),ui->updateCIN->text().toInt(),ui->updateName->text(),ui->updateAge->text().toInt(),ui->updateGender->currentText(),ui->updateAddress->text(),ui->updateEmail->text(),ui->updatePhone->text().toInt(),g.getImage());
            ui->label_affCIN->setText(ui->updateCIN->text());
            ui->label_affName->setText(ui->updateName->text());
            ui->label_affAge->setText(ui->updateAge->text());
            ui->label_affGender->setText(ui->updateGender->currentText());
            ui->label_affAddress->setText(ui->updateAddress->text());
            ui->label_affEmail->setText(ui->updateEmail->text());
            ui->label_affPhone->setText(ui->updatePhone->text());
            ui->label_affImage->setPixmap(g.getImage());
            g.setImage("");

            ui->stackedWidgetGuest->setCurrentIndex(3);
         }
     }

}

void MainWindow::on_searchGuest_textEdited(const QString &text)
{
    QSqlQueryModel* model = g.rechercher(text);
    ui->tableViewGuest->setModel(model);
}


void MainWindow::on_go_to_listGuest_from_addGuest_clicked()
{
    ui->stackedWidgetGuest->setCurrentIndex(0);
    ui->addCinGuest->clear();
    ui->addNameGuest->clear();
    ui->addAgeGuest->clear();
    ui->addAddressGuest->clear();
    ui->addEmailGuest->clear();
    ui->addPhoneGuest->clear();
}

void MainWindow::on_go_to_listGuest_from_updateGuest_clicked()
{
    ui->stackedWidgetGuest->setCurrentIndex(0);

}
void MainWindow::on_go_to_list_from_affSimple_clicked()
{
    ui->stackedWidgetGuest->setCurrentIndex(0);
}
/******************************************************** PDF ****************************************************************************************************/
void MainWindow::on_pdfGuest_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save PDF", ui->label_affCIN->text(), "*.pdf");

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QPainter painter;
    painter.begin(&printer);


    QImage image = ui->label_affImage->pixmap()->toImage();

    // Afficher l'image dans le QLabel
    ui->label_affImage->setPixmap(QPixmap::fromImage(image));

    // Enregistrer l'image dans un fichier temporaire
    QString tempImagePath = QDir::temp().filePath("temp_image.png");
    image.save(tempImagePath); // Sauvegarder l'image dans le fichier temporaire

    // Dessiner d'autres informations
    QFont font = painter.font();
    font.setPointSize(12);
    painter.setFont(font);
    painter.drawText(100, 100, "Guest information");
    QPixmap imageToDraw(tempImagePath);
    painter.drawPixmap(400, 100, imageToDraw.width(), imageToDraw.height(), imageToDraw);


    QStringList additionalInfo;
    additionalInfo << "CIN : " + ui->label_affCIN->text();
    additionalInfo << "Full Name : " + ui->label_affName->text();
    additionalInfo << "Age : " + ui->label_affAge->text();
    additionalInfo << "Gender : " + ui->label_affGender->text();
    additionalInfo << "Address : " + ui->label_affAddress->text();
    additionalInfo << "Phone Number : " + ui->label_affPhone->text();
    additionalInfo << "Email : " + ui->label_affEmail->text();


    int yOffset = 120;
    foreach(const QString &info, additionalInfo) {
        painter.drawText(120, yOffset, info);
        yOffset += 20;
    }

    painter.end();
}

void MainWindow::on_rechercheCinCart_clicked()
{
    QString pythonScript = "C:/Users/Emna Nkhili/Desktop/noblePalette/noblePalette/script/guest/cinCart.py";

    // Chemin vers l'image à traiter

    QString imagePath = QFileDialog::getOpenFileName(nullptr, "Sélectionner une image", "", "Images (*.png *.jpg *.jpeg *.bmp *.gif)");

    // Créer un processus pour exécuter le script Python
    QProcess process;

    // Arguments pour le script Python
    QStringList arguments;
    arguments << imagePath;

    // Exécuter le script Python
    process.start("python", QStringList() << pythonScript << arguments);

    // Attendre que le processus se termine (bloquant)
    process.waitForFinished(-1);

    // Vérifier le statut de sortie du processus
    if (process.exitStatus() == QProcess::NormalExit && process.exitCode() == 0) {
        qDebug() << "Le script Python s'est exécuté avec succès.";
        // Lire la sortie standard du processus (résultat de la détection)
        QString result = process.readAllStandardOutput();
        qDebug() << result.trimmed() ;
        QSqlQueryModel *model = g.afficherId(result.trimmed().toInt());

        if (model->rowCount() > 0) {
           QString CIN = model->record(0).value("CIN").toString();
            QString Name = model->record(0).value("Name").toString();
            QString Age = model->record(0).value("Age").toString();
            QString Gender = model->record(0).value("Gender").toString();
            QString Address = model->record(0).value("Address").toString();
            QString Phone = model->record(0).value("Phone").toString();
            QString Email = model->record(0).value("Email").toString();

            // Vous pouvez ajouter d'autres attributs de la même manière
           // qDebug() << CIN << Name << Age;

            ui->label_affCIN->setText(CIN);
            ui->label_affName->setText(Name);
            ui->label_affAge->setText(Age);
            ui->label_affGender->setText(Gender);
            ui->label_affAddress->setText(Address);
            ui->label_affPhone->setText(Phone);
            ui->label_affEmail->setText(Email);
            QByteArray imageData = model->record(0).value("Image").toByteArray();
            QPixmap pixmap;
            pixmap.loadFromData(imageData);

            if (!pixmap.isNull()) {
                // Redimensionner l'image pour s'adapter à la taille de la QLabel
                pixmap = pixmap.scaled(ui->label_affImage->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->label_affImage->setPixmap(pixmap);
            } else {
                qDebug() << "Erreur: Impossible de charger l'image depuis les données ByteArray.";
                ui->label_affImage->setText("Aucune image disponible");
            }

            ui->stackedWidgetGuest->setCurrentIndex(3);

            // Assurez-vous que ui->labelNom et ui->labelPrenom sont les pointeurs vers vos labels dans votre interface graphique


    }
    }
    else {
        qDebug() << "Erreur lors de l'exécution du script Python.";
        qDebug() << "Code de sortie:" << process.exitCode();
        qDebug() << imagePath;
    }
}
/******************************************** Insertion image Ajout **********************************/
void MainWindow::on_addImageGuest_clicked()
{
    QString imagePath2 = QFileDialog::getOpenFileName(nullptr, "Sélectionner une image", "", "Images (*.png *.jpg *.jpeg *.bmp *.gif)");
    QPixmap pixmap(imagePath2);

    // Définir l'image comme fond du bouton et styliser le cadre
    ui->addImageGuest->setStyleSheet(
                             "border-image: url("+imagePath2+");"
                             "border-width: 2px;"
                             "border-style: solid;"
                             "border-radius:15px;"
                             "border-color: #000000;" // Couleur du cadre
                             "text-align: center;"    // Aligner le texte au centre du bouton (en dehors de l'image)
                             "color: transparent;"
                             );
     g.setImage(imagePath2);
}
/*********************************************** insertion image update *****************************************************************************/
void MainWindow::on_updateImage_clicked()
{

    QString imagePath2 = QFileDialog::getOpenFileName(nullptr, "Sélectionner une image", "", "Images (*.png *.jpg *.jpeg *.bmp *.gif)");
    QPixmap pixmap(imagePath2);

    // Définir l'image comme fond du bouton et styliser le cadre
    ui->labelupdateImage->setPixmap(pixmap);
     g.setImage(imagePath2);
}


void MainWindow::on_supprimer_GuestSelect_clicked()
{
    QModelIndexList selectedRows = ui->tableViewGuest->selectionModel()->selectedRows();
    // Parcourez les indices des lignes sélectionnées et supprimez-les une par une
    for (const QModelIndex &index : selectedRows) {
        // Obtenez la valeur dans la première colonne (colonnes sont 0-indexées)
        int valueToDelete = ui->tableViewGuest->model()->data(index.sibling(index.row(), 0)).toInt();
        // Utilisez cette valeur pour appeler votre fonction de suppression
        g.supprimer(valueToDelete);
    }

    // Rafraîchissez le modèle de votre table view après la suppression
    ui->tableViewGuest->setModel(g.afficher());

}
/*
******************************************************************** émotion
*/
void MainWindow::on_statEmotion_clicked()
{
    // Chemin d'accès à la vidéo (à remplacer par votre propre chemin d'accès)
    QString videoPath = QFileDialog::getOpenFileName(nullptr, "Sélectionner une vidéo", "", "Fichiers vidéo (*.mp4 *.avi *.mov)");

    // Chemin d'accès à votre script Python
    QString scriptPath = "C:/Users/meddh/Documents/ArtGalleryy/python/py/Emotion_Detection/test.py"; // Remplacez "chemin/vers/votre/script.py" par votre propre chemin d'accès

    // Créer un processus pour exécuter le script Python
    QProcess process;
    process.start("python", QStringList() << scriptPath << videoPath); // Exécuter le script Python avec le chemin de la vidéo en tant qu'argument

    // Attendre que le processus se termine
    if (!process.waitForStarted()) {
        qDebug() << "Erreur: Impossible de démarrer le processus.";
        return;
    }
    else if (!process.waitForFinished()) {
        qDebug() << "Erreur: Le processus a échoué ou a pris trop de temps pour se terminer.";
        return;
    }
    else{

    // Lire la sortie standard du processus s'il y en a
    QByteArray resultat = process.readAllStandardOutput();
    qDebug() << "Sortie du script Python:" << resultat;

    // Lire la sortie d'erreur du processus s'il y en a
    QByteArray erreur = process.readAllStandardError();
    if (!erreur.isEmpty()) {
        qDebug() << "Erreur du script Python:" << erreur;
        return;
    }

    // Calculer le pourcentage de chaque émotion
    QRegularExpression regex("(angry|disgust|fear|happy|neutral|sad|surprise)");

    // Utiliser un QRegularExpressionMatchIterator pour trouver toutes les occurrences dans la chaîne
    QRegularExpressionMatchIterator matchIterator = regex.globalMatch(resultat);

    // Initialiser un QMap pour stocker le compte de chaque émotion
    QMap<QString, int> emotionCount;

    // Itérer sur les correspondances et compter le nombre d'occurrences de chaque émotion
    while (matchIterator.hasNext()) {
        QRegularExpressionMatch match = matchIterator.next();
        QString emotion = match.captured(0);
        emotionCount[emotion]++;
    }

    // Calculer le total des émotions
    int totalEmotions = 0;
    for (auto it = emotionCount.begin(); it != emotionCount.end(); ++it) {
        totalEmotions += it.value();
    }

    // Calculer le pourcentage de chaque émotion et l'afficher
    for (auto it = emotionCount.begin(); it != emotionCount.end(); ++it) {
        double percentage = (static_cast<double>(it.value()) / totalEmotions) * 100.0;
        qDebug() << "Pourcentage de " << it.key() << " : " << percentage << "%";

        // Définir le style HTML avec le pourcentage correspondant
        QString styledPercentage = QString("<html><head/><body><p align=\"center\"><span style=\"font-size:10pt; font-weight:600;\">%1%</span></p></body></html>").arg(percentage);

        // Mettre à jour le label correspondant à l'émotion dans la boucle avec le style HTML
        if (it.key() == "angry") {
            ui->angry_prc->setText(styledPercentage);
        } else if (it.key() == "disgust") {
           // ui->disgust_prc->setText(styledPercentage);
        } else if (it.key() == "fear") {
            ui->fear_prc->setText(styledPercentage);
        } else if (it.key() == "happy") {
            ui->happy_prc->setText(styledPercentage);
        } else if (it.key() == "neutral") {
            ui->neutral_prc->setText(styledPercentage);
        } else if (it.key() == "sad") {
            ui->sad_prc->setText(styledPercentage);
        } else if (it.key() == "surprise") {
            ui->surprise_prc->setText(styledPercentage);
        }
    }

    ui->stackedWidgetGuest->setCurrentIndex(4); // Passer à l'index 4 du stackedWidget après l'exécution du script
    }

}









void MainWindow::on_tri_Ccin_clicked()
{
    //cin +
    QSqlQueryModel* model = g.afficher_tri_CIN(true); // true for ascending
    ui->tableViewGuest->setModel(model);
}

void MainWindow::on_tri_Dcin_clicked()
{
    //cin -
    QSqlQueryModel* model = g.afficher_tri_CIN(false);
    ui->tableViewGuest->setModel(model);
}

void MainWindow::on_tri_Cname_clicked()
{
    //name+
    QSqlQueryModel* model = g.afficher_tri_Name(true);
    ui->tableViewGuest->setModel(model);
}

void MainWindow::on_tri_Dname_clicked()
{
    //name-
    QSqlQueryModel* model = g.afficher_tri_Name(false);

    ui->tableViewGuest->setModel(model);
}

void MainWindow::on_tri_Cage_clicked()
{
    //age+
    QSqlQueryModel* model = g.afficher_tri_Age(true);

    ui->tableViewGuest->setModel(model);
}

void MainWindow::on_tri_Dage_clicked()
{
    //age-
    QSqlQueryModel* model = g.afficher_tri_Age(false);

    ui->tableViewGuest->setModel(model);
}

void MainWindow::on_tri_Cgender_clicked()
{
    //gender+
    QSqlQueryModel* model = g.afficher_tri_Gender(true);
    ui->tableViewGuest->setModel(model);
}

void MainWindow::on_tri_Dgender_clicked()
{
    //gender-
    QSqlQueryModel* model = g.afficher_tri_Gender(false);
    ui->tableViewGuest->setModel(model);
}

void MainWindow::on_tri_Caddress_clicked()
{
    //address+
    QSqlQueryModel* model = g.afficher_tri_Address(true);

    ui->tableViewGuest->setModel(model);
}

void MainWindow::on_tri_Daddress_clicked()
{
    //address-
    QSqlQueryModel* model = g.afficher_tri_Address(false);
    ui->tableViewGuest->setModel(model);
}

void MainWindow::on_tri_Cphone_clicked()
{
    //phone+
    QSqlQueryModel* model = g.afficher_tri_Phone(true);
    ui->tableViewGuest->setModel(model);
}

void MainWindow::on_tri_Dphone_clicked()
{
    //phone-
    QSqlQueryModel* model = g.afficher_tri_Phone(false);
    ui->tableViewGuest->setModel(model);
}

void MainWindow::on_tri_Cemail_clicked()
{
    //email+
    QSqlQueryModel* model = g.afficher_tri_Email(true);
    ui->tableViewGuest->setModel(model);
}

void MainWindow::on_tri_Demail_clicked()
{
    //email-
    QSqlQueryModel* model = g.afficher_tri_Email(false);
    ui->tableViewGuest->setModel(model);
}
/*
******************************************************************** surv
*/
void MainWindow::on_surv_Guest_clicked()
{
    QSqlQueryModel* model = p.idGuests(1);
    QString dossierDeDestination = "C:/Users/meddh/Desktop/py/easy_facial_recognition-master/known_faces";

    for (int row = 0; row < model->rowCount(); ++row) {

        QSqlQueryModel *model1 = g.afficherId(model->record(row).value("idguest").toInt());

        qDebug() << "Image saved successfully:" << model->record(row).value("idguest").toString();

        QByteArray imageData = model1->record(0).value("image").toByteArray();

        QString fileName = QString("%1/%2.png").arg(dossierDeDestination).arg(model->record(row).value("idguest").toString()); // You may use a unique identifier for the file name

        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(imageData);
            file.close();
            qDebug() << "Image saved successfully:" << fileName;
        } else {
            qDebug() << "Error saving image:" << file.errorString();
        }


    }

    QProcess process;
    QString scriptPath = "C:/Users/Emna Nkhili/Desktop/noblePalette/noblePalette/script/guest/easy_facial_recognition-master/easy_facial_recognition.py";

    QString VideoPath = QFileDialog::getOpenFileName(nullptr, "Sélectionner une video", "", "Fichiers vidéo (*.mp4 *.avi *.mov)");
    QStringList arguments;
    arguments << VideoPath;


    process.start("python", QStringList() << scriptPath << arguments);

    // Attendre que le processus se termine
    if (!process.waitForStarted()) {
        qDebug() << "Erreur: Impossible de démarrer le processus.";
    }

    if (!process.waitForFinished()) {
        qDebug() << "Erreur: Le processus a échoué ou a pris trop de temps pour se terminer.";
    }

    // Lire la sortie standard du processus s'il y en a
    QByteArray resultat = process.readAllStandardOutput();
    qDebug() << "Sortie du script Python:" << resultat;

    // Lire la sortie d'erreur du processus s'il y en a
    QByteArray erreur = process.readAllStandardError();
    if (!erreur.isEmpty()) {
        qDebug() << "Erreur du script Python:" << erreur;
    }

    // Expression régulière pour trouver les identifiants de 8 chiffres
    QRegularExpression regex("\\b\\d{8}\\b");

    // Itération sur les correspondances
    QRegularExpressionMatchIterator matchIterator = regex.globalMatch(resultat);
    while (matchIterator.hasNext()) {
        QRegularExpressionMatch match = matchIterator.next();
        //qDebug() << match.captured();
        p.precenceGuest(1,match.captured().toInt());//*************************************** chenzid hne event emna*/
    }

}
