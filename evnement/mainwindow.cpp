#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "artist.h"
#include <QSqlQuery>
#include <QDebug>
#include "detecte.h"
#include "article.h"
#include "guest.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->artableView_3->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->artableView_3->setSelectionMode(QAbstractItemView::ExtendedSelection);
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
     ui->tableView_6->setModel(article.afficher());
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
    ui->tableView->setModel(g.afficher());

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
    ui->artableView->setModel(a.afficher());
    ui->artableView_3->setModel(a.afficher());//refresh
    ui->artableView_2->setModel(a.afficher());//refresh

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
    ui->stackedWidgetSetting->setCurrentIndex(4);

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




void MainWindow::on_save_7_clicked()
{
    ui->stackedWidgetEvent->setCurrentIndex(0);

}

void MainWindow::on_save_6_clicked()
{
    ui->stackedWidgetGuest->setCurrentIndex(3);

}



//partie artist

void MainWindow::on_ararriere_2_clicked()
{
    ui->stackedWidgetArtist->setCurrentIndex(0);
}

void MainWindow::on_ararriere_3_clicked()
{
    ui->stackedWidgetArtist->setCurrentIndex(0);
}

void MainWindow::on_ararriere_7_clicked()
{
    ui->stackedWidgetArtist->setCurrentIndex(0);
}


void MainWindow::on_ararriere_clicked()
{
    ui->stackedWidgetArtist->setCurrentIndex(0);
}


void MainWindow::on_aradd_clicked()
{
    ui->stackedWidgetArtist->setCurrentIndex(1);
}


void MainWindow::on_arupdate_clicked()
{
    ui->stackedWidgetArtist->setCurrentIndex(2);
}


void MainWindow::on_arsupp_clicked()
{
    ui->stackedWidgetArtist->setCurrentIndex(3);
}





// ########################################--- AFFICHAGE SIMPLE SEUL ARTIST ###########################################################################
void MainWindow::on_artableView_doubleClicked(const QModelIndex &index)
{
    const int CIN_COLUMN = 0;
    const int NOM_COLUMN = 3;
    const int PRENOM_COLUMN = 2;
    const int TEL_COLUMN = 1;
    const int ADRESSE_COLUMN = 4;
    const int MAIL_COLUMN = 5;
    const int DOMAINE_COLUMN = 6;
    const int DESCRIPTION_COLUMN = 7;
    const int SEXE_COLUMN = 8;
    const int IMAGE_COLUMN = 9; // Nouveau champ pour l'image

    // Récupérer les détails de l'artiste à partir de la ligne sélectionnée dans artableView
    int cin = index.sibling(index.row(), CIN_COLUMN).data().toInt();
    QString nom = index.sibling(index.row(), NOM_COLUMN).data().toString();
    QString prenom = index.sibling(index.row(), PRENOM_COLUMN).data().toString();
    int tel = index.sibling(index.row(), TEL_COLUMN).data().toInt();
    QString adresse = index.sibling(index.row(), ADRESSE_COLUMN).data().toString();
    QString mail = index.sibling(index.row(), MAIL_COLUMN).data().toString();
    QString domaine = index.sibling(index.row(), DOMAINE_COLUMN).data().toString();
    QString description = index.sibling(index.row(), DESCRIPTION_COLUMN).data().toString();
    QString sexe = index.sibling(index.row(), SEXE_COLUMN).data().toString();
    QByteArray imageBytes = index.sibling(index.row(), IMAGE_COLUMN).data().toByteArray(); // Convertir les données BLOB en QByteArray

    // Remplir les champs d'entrée avec les données récupérées
    ui->arcin_5->setText(QString::number(cin));
    ui->arnom_5->setText(nom);
    ui->arprenom_5->setText(prenom);
    ui->artelephone_5->setText(QString::number(tel));
    ui->aradresse_5->setText(adresse);
    ui->armail_5->setText(mail);
    ui->ardomaine_5->setText(domaine);
    ui->ardescription_5->setText(description);

    // Afficher l'image BLOB dans image_artist
    QPixmap pixmap;
    if (!imageBytes.isEmpty()) {
        pixmap.loadFromData(imageBytes);
        ui->image_artist->setPixmap(pixmap.scaled(ui->image_artist->size(), Qt::KeepAspectRatio));
    } else {
        // Si les données d'image sont vides, vous pouvez afficher une image par défaut ou un message indiquant qu'aucune image n'est disponible.
        ui->image_artist->setText("Aucune image disponible");
    }

    // Désactiver tous les champs d'entrée
    QList<QWidget*> inputWidgets = {
        ui->arcin_5,
        ui->arnom_5,
        ui->arprenom_5,
        ui->artelephone_5,
        ui->aradresse_5,
        ui->armail_5,
        ui->ardomaine_5,
        ui->ardescription_5,
        ui->arsexe_5
    };

    for (QWidget *widget : inputWidgets) {
        widget->setEnabled(false);
    }

    // Changer la page actuelle pour la page avec l'index 4
    ui->stackedWidgetArtist->setCurrentIndex(4);
    qDebug() << "Button clicked";

    QString rawQr = QString("CIN: %1\nTel: %2\nNom: %3\nPrenom: %4\nAdresse: %5\nMail: %6\nDomaine: %7\nDescription: %8\nSexe: %9")
                  .arg(cin)
                  .arg(tel)
                  .arg(nom)
                  .arg(prenom)
                  .arg(adresse)
                  .arg(mail)
                  .arg(domaine)
                  .arg(description)
                  .arg(sexe);

    // Générer le code QR
    qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(rawQr.toUtf8().constData(), qrcodegen::QrCode::Ecc::HIGH);

    // Convertir le code QR en une image
    QImage qrImage(qr.getSize(), qr.getSize(), QImage::Format_RGB888);
    for (int y = 0; y < qr.getSize(); y++) {
        for (int x = 0; x < qr.getSize(); x++) {
            int color = qr.getModule(x, y);  // 0 pour blanc, 1 pour noir
            if (color == 0)
                qrImage.setPixel(x, y, qRgb(254, 254, 254));
            else
                qrImage.setPixel(x, y, qRgb(0, 0, 0));
        }
    }

    // Redimensionner l'image du code QR
    qrImage = qrImage.scaled(200, 200);

    // Afficher l'image du code QR dans qrlabel_2
    ui->qrlabel_2->setPixmap(QPixmap::fromImage(qrImage));
}


void MainWindow::on_arsupp_2_clicked()
{
    a.supprimer(ui->arcin_5->text().toInt());
    ui->artableView->setModel(a.afficher());
    ui->artableView_2->setModel(a.afficher());
    ui->artableView_3->setModel(a.afficher());
    ui->stackedWidgetArtist->setCurrentIndex(0);

}



//-------------------------------------------------PDF UN SEUL ARTIST-----------------------------------------------------------------

void MainWindow::on_arpdf_3_clicked()
{
    // Assurez-vous que les variables nécessaires sont déclarées et initialisées
    int cin = ui->arcin_5->text().toInt();
    QString nom = ui->arnom_5->text();
    QString prenom = ui->arprenom_5->text();
    int tel = ui->artelephone_5->text().toInt();
    QString adresse = ui->aradresse_5->text();
    QString mail = ui->armail_5->text();
    QString domaine = ui->ardomaine_5->text();
    QString description = ui->ardescription_5->text();
    QString sexe = ui->arsexe_5->currentText();

    // Ouvrir un fichier PDF
    QPdfWriter pdfWriter("C:/Users/DELL/Downloads/pdf2.pdf");

    QPainter painter(&pdfWriter);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    // Définir la taille de la page A4
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));

    // Remplir le fond avec une couleur claire
    painter.fillRect(QRectF(0, 0, pdfWriter.width(), pdfWriter.height()), Qt::white);

    // Dessiner la barre verte à gauche
    painter.fillRect(0, 0, 100, pdfWriter.height(), Qt::green);

    // Définir la couleur et la taille du texte pour les titres
    QFont titleFont;
    titleFont.setPointSize(20);
    titleFont.setBold(true);
    painter.setFont(titleFont);

    // Dessiner le titre "CV de l'Artiste" en gris
    painter.setPen(Qt::gray);
    QString titleText = "information de l'Artiste";
    QRect titleRect = painter.boundingRect(0, 0, 1000, 1000, Qt::AlignLeft, titleText);
    int titleWidth = titleRect.width();
    int titleX = (pdfWriter.width() - titleWidth) / 2; // Coordonnée X pour centrer le texte
    painter.drawText(titleX, 200, titleText);


    // Définir la couleur et la taille du texte pour les informations
    QFont infoFont;
    infoFont.setPointSize(12);
    painter.setFont(infoFont);
    painter.setPen(Qt::black); // Couleur du texte noir pour les informations

    // Coordonnées de départ pour dessiner les informations
    int x = 1500; // Augmenter la marge à gauche pour laisser de l'espace pour la barre verte
    int y = 400; // Position verticale initiale

    // Espacement entre les lignes de texte
    int lineSpacing = 1500;

    // Dessiner les informations de l'artiste
    painter.setPen(Qt::green); // Couleur verte pour les titres
    painter.drawText(x, y+500, "Nom:");
    painter.setPen(Qt::black); // Retour à la couleur noire pour le texte des informations
    painter.drawText(x + 1000, y+500, QString("%1 %2").arg(prenom).arg(nom));
    y += lineSpacing;
    painter.setPen(Qt::green); // Couleur verte pour les titres
    painter.drawText(x, y, "CIN:");
    painter.setPen(Qt::black); // Retour à la couleur noire pour le texte des informations
    painter.drawText(x + 1500, y, QString::number(cin));
    y += lineSpacing;
    painter.setPen(Qt::green); // Couleur verte pour les titres
    painter.drawText(x, y, "Téléphone:");
    painter.setPen(Qt::black); // Retour à la couleur noire pour le texte des informations
    painter.drawText(x + 1500, y, QString::number(tel));
    y += lineSpacing;
    painter.setPen(Qt::green); // Couleur verte pour les titres
    painter.drawText(x, y, "Adresse:");
    painter.setPen(Qt::black); // Retour à la couleur noire pour le texte des informations
    painter.drawText(x + 1500, y, adresse);
    y += lineSpacing;
    painter.setPen(Qt::green); // Couleur verte pour les titres
    painter.drawText(x, y, "Mail:");
    painter.setPen(Qt::black); // Retour à la couleur noire pour le texte des informations
    painter.drawText(x + 1500, y, mail);
    y += lineSpacing;
    painter.setPen(Qt::green); // Couleur verte pour les titres
    painter.drawText(x, y, "Domaine:");
    painter.setPen(Qt::black); // Retour à la couleur noire pour le texte des informations
    painter.drawText(x + 1500, y, domaine);
    y += lineSpacing;
    painter.setPen(Qt::green); // Couleur verte pour les titres
    painter.drawText(x, y, "Description:");
    painter.setPen(Qt::black); // Retour à la couleur noire pour le texte des informations
    painter.drawText(x + 1500, y, description);
    y += lineSpacing;
    painter.setPen(Qt::green); // Couleur verte pour les titres
    painter.drawText(x, y, "Sexe:");
    painter.setPen(Qt::black); // Retour à la couleur noire pour le texte des informations
    painter.drawText(x + 1500, y, sexe);

    // Dessiner une ligne séparatrice
    y += lineSpacing;
    painter.drawLine(x, y, 550, y);

    // Dessiner une note de bas de page
    QFont noteFont;
    noteFont.setItalic(true);
    painter.setFont(noteFont);
    painter.drawText(500, pdfWriter.height() - 100, "Ce CV a été généré automatiquement.");

    // Générer le texte pour le code QR
    QString rawQr = QString("CIN: %1\nTéléphone: %2\nNom: %3 %4\nAdresse: %5\nMail: %6\nDomaine: %7\nDescription: %8\nSexe: %9")
            .arg(cin)
            .arg(tel)
            .arg(prenom)
            .arg(nom)
            .arg(adresse)
            .arg(mail)
            .arg(domaine)
            .arg(description)
            .arg(sexe);

    // Générer le code QR avec une taille plus grande
    qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(rawQr.toUtf8().constData(), qrcodegen::QrCode::Ecc::HIGH);
    const int qrSize = qr.getSize(); // Taille du code QR
    const int qrMargin = 8; // Marge autour du code QR
    const int qrBlockSize = 20; // Taille de chaque bloc du code QR
    const int qrImageSize = qrSize * qrBlockSize; // Taille de l'image contenant le code QR

    // Dessiner le code QR à droite du document PDF
    QImage qrImage(qrImageSize, qrImageSize, QImage::Format_RGB32);
    qrImage.fill(Qt::white);
    QPainter qrPainter(&qrImage);
    qrPainter.setPen(Qt::black);
    for (int y = 0; y < qrSize; ++y) {
        for (int x = 0; x < qrSize; ++x) {
            if (qr.getModule(x, y) == 1) {
                qrPainter.fillRect((x * qrBlockSize) + qrMargin, (y * qrBlockSize) + qrMargin, qrBlockSize, qrBlockSize, Qt::black);
            }
        }
    }
    qrPainter.end();
    painter.drawImage(pdfWriter.width() - qrImageSize - 100, 200, qrImage);

    // Terminer le dessin
    painter.end();

    // Ouvrir le fichier PDF avec l'application par défaut
    QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/DELL/Downloads/pdf2.pdf"));
}









//------------------------------------------------------------L'AJOUT------------------------------------------------------------------







void MainWindow::on_arpicture_clicked() {
    // Ouvrir une boîte de dialogue pour permettre à l'utilisateur de sélectionner une image
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Choisir une image"), QString(), tr("Images (*.png *.jpg *.jpeg *.bmp)"));

    // Vérifier si l'utilisateur a sélectionné une image
    if (!imagePath.isEmpty()) {
        // Afficher l'image dans un QLabel ou dans une autre zone de votre interface utilisateur
        QPixmap image(imagePath);
        if (!image.isNull()) {
            // Redimensionner l'image pour qu'elle s'adapte à la taille du QLabel
            ui->image_artist_2->setPixmap(image.scaled(ui->image_artist_2->size(), Qt::KeepAspectRatio));

            // Enregistrer le chemin de l'image sélectionnée dans une variable membre de la classe MainWindow
            selectedImagePath = imagePath;
        } else {
            QMessageBox::warning(this, tr("Erreur de chargement d'image"), tr("Impossible de charger l'image sélectionnée."));
        }
    }
}












void MainWindow::on_arajouter_clicked() {
    QString cinStr = ui->arcin->text();
    QString telStr = ui->artelephone->text();
    QString nom = ui->arnom->text();

    // Vérification que les champs obligatoires ne sont pas vides
    if (cinStr.isEmpty() || telStr.isEmpty() || nom.isEmpty() || !ui->armail->text().contains("@")) {
        QMessageBox::critical(nullptr, QObject::tr("Champs obligatoires vides ou mail invalide"),
                              QObject::tr("Les champs CIN, Téléphone, Nom et Mail sont obligatoires et le mail doit contenir '@'.\n"
                                          "Veuillez remplir tous les champs obligatoires."), QMessageBox::Ok);
        return;
    }

    // Récupérer le chemin de l'image à partir de la variable locale imagePath
    QString imagePath = selectedImagePath;

    // Vérification si une image est sélectionnée
    if (imagePath.isEmpty()) {
        QMessageBox::warning(this, tr("Image manquante"), tr("Veuillez sélectionner une image."), QMessageBox::Ok);
        return;
    }

    // Exécuter la fonction de vérification de l'image en utilisant Python
    QProcess process;
    process.start("python", QStringList() << "C:/Users/DELL/OneDrive/Bureau/CIN.py" << imagePath);
    process.waitForFinished();

    QString output = process.readAllStandardOutput();
    // Utiliser la variable 'output' pour récupérer le résultat de la vérification

    // Si l'image contient une personne, ajoutez l'artiste
    if (output.contains("L'image contient une personne")) {
        // Création d'un objet Artiste avec les données des champs
        Artiste a;
        a.setCin(cinStr.toInt());
        a.setTel(telStr.toInt());
        a.setNom(nom);
        a.setPrenom(ui->arprenom->text());
        a.setAdresse(ui->aradresse->text());
        a.setMail(ui->armail->text());
        a.setDomaine(ui->ardomaine->text());
        a.setDescription(ui->ardescription->text());
        a.setSexe(ui->arsexe->currentText());

        // Charger l'image sélectionnée et la convertir en QByteArray
        QPixmap pixmap(imagePath);
        QByteArray imageData;
        QBuffer buffer(&imageData);
        buffer.open(QIODevice::WriteOnly);
        pixmap.save(&buffer, "PNG");

        // Enregistrer l'image dans l'objet Artiste
        a.setImage(imageData);

        // Ajouter l'artiste à la base de données
        bool test = a.ajouter();
        if (test)
        {
            // Effacer les champs de saisie après l'ajout réussi
            ui->arcin->clear();
            ui->artelephone->clear();
            ui->arnom->clear();
            ui->arprenom->clear();
            ui->aradresse->clear();
            ui->armail->clear();
            ui->ardomaine->clear();
            ui->ardescription->clear();
            ui->arsexe->setCurrentIndex(0); // Réinitialise la sélection du sexe

            // Effacer l'image affichée dans image_artist_2
            ui->image_artist_2->clear();

            ui->stackedWidgetArtist->setCurrentIndex(0);
            ui->artableView_2->setModel(a.afficher());
            ui->artableView->setModel(a.afficher());
            ui->artableView_3->setModel(a.afficher());

            QMessageBox::information(nullptr, QObject::tr("Ajout réussi"),
                                     QObject::tr("Artiste ajouté avec succès."), QMessageBox::Ok);
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Erreur lors de l'ajout"),
                                  QObject::tr("Erreur lors de l'ajout de l'artiste.\n"
                                              "Veuillez réessayer."), QMessageBox::Ok);
        }
    } else {
        // Afficher un message d'avertissement indiquant que l'image ne contient pas de personne
        QMessageBox::warning(this, tr("Image invalide"), tr("L'image sélectionnée ne contient pas de personne. Veuillez sélectionner une autre image."), QMessageBox::Ok);
    }
}











void MainWindow::on_arclear_clicked()
{
    ui->arcin->setText("");
    ui->arnom->setText("");
    ui->arprenom->setText("");
    ui->artelephone->setText("");
    ui->aradresse->setText("");
    ui->armail->setText("");
    ui->ardomaine->setText("");
    ui->ardescription->setText("");
    ui->image_artist_2->clear();
    ui->image_artist_2->setPixmap(QPixmap());
}






//------------------------------------------------------------      L'UPDATE     -------------------------------------------------------






void MainWindow::on_artableView_2_doubleClicked(const QModelIndex &index)
{
    // Check if the index is valid
    if (!index.isValid()) {
        // Handle the invalid index if necessary, e.g., show an error message
        return;
    }

    // Define the column indices based on your table's actual structure
    const int CIN_COLUMN = 0;
    const int NOM_COLUMN = 2;
    const int PRENOM_COLUMN = 3;
    const int TEL_COLUMN = 1;
    const int ADRESSE_COLUMN = 4;
    const int MAIL_COLUMN = 5;
    const int DOMAINE_COLUMN = 6;
    const int DESCRIPTION_COLUMN = 7;
    const int SEXE_COLUMN = 8;
    const int IMAGE_COLUMN = 9; // Assuming the image column index is 9

    // Retrieve the artist's details from the selected row in updateview_2.
    int cin = index.sibling(index.row(), CIN_COLUMN).data().toInt();
    QString nom = index.sibling(index.row(), NOM_COLUMN).data().toString();
    QString prenom = index.sibling(index.row(), PRENOM_COLUMN).data().toString();
    int tel = index.sibling(index.row(), TEL_COLUMN).data().toInt();
    QString adresse = index.sibling(index.row(), ADRESSE_COLUMN).data().toString();
    QString mail = index.sibling(index.row(), MAIL_COLUMN).data().toString();
    QString domaine = index.sibling(index.row(), DOMAINE_COLUMN).data().toString();
    QString description = index.sibling(index.row(), DESCRIPTION_COLUMN).data().toString();
    QString sexe = index.sibling(index.row(), SEXE_COLUMN).data().toString();

    // Load image data from the model
    QByteArray imageData = index.sibling(index.row(), IMAGE_COLUMN).data().toByteArray();

    // Load image from data if available, otherwise load the placeholder image
    QPixmap imagePixmap;
    if (!imageData.isEmpty()) {
        imagePixmap.loadFromData(imageData);
    } else {
        imagePixmap = *(ui->image_artist_3->pixmap());
    }

    // Fill the input fields with the retrieved data.
    ui->arcin_2->setText(QString::number(cin));
    ui->arcin_2->setEnabled(false);

    ui->arnom_2->setText(nom);
    ui->arprenom_2->setText(prenom);
    ui->artelephone_2->setText(QString::number(tel));
    ui->aradresse_2->setText(adresse);
    ui->armail_2->setText(mail);
    ui->ardomaine_2->setText(domaine);
    ui->ardescription_2->setText(description);

    // Assuming sexe_2 is a QComboBox that has "Male" and "Female" as items
    int sexeIndex = -1; // Default to -1 if not found
    if (sexe == "Man") {
        sexeIndex = 0;
    } else if (sexe == "Woman") {
        sexeIndex = 1;
    }else if (sexe == "Other") {
        sexeIndex = 2;
    }
    ui->arsexe_2->setCurrentIndex(sexeIndex);

    // Display the image in the QLabel
    ui->image_artist_3->setPixmap(imagePixmap.scaled(ui->image_artist_3->size(), Qt::KeepAspectRatio));

    // Now the user can modify the data in the input fields.
}







// Fonction pour sélectionner une image
void MainWindow::on_arpicture_2_clicked() {
    selectedImagePathu = QFileDialog::getOpenFileName(this, tr("Choisir une image"), QString(), tr("Images (*.png *.jpg *.jpeg *.bmp)"));
    if (!selectedImagePathu.isEmpty()) {
        imagePixmap.load(selectedImagePathu);
        if (!imagePixmap.isNull()) {
            ui->image_artist_3->setPixmap(imagePixmap.scaled(ui->image_artist_3->size(), Qt::KeepAspectRatio));
        } else {
            qDebug() << "Failed to load image.";
            // Afficher un message d'erreur ou charger une autre image de substitution
        }
    }
}



// Fonction de modification d'un artiste
void MainWindow::on_arupdate_2_clicked() {
    // Récupérer le chemin de l'image sélectionnée
    QString imagePath = selectedImagePathu;
    if (imagePath.isEmpty()) {
        QMessageBox::warning(this, tr("Image manquante"), tr("Veuillez sélectionner une image."), QMessageBox::Ok);
        return;
    }

    // Exécuter la fonction de vérification de l'image en utilisant Python
    QProcess process;
    process.start("python", QStringList() << "C:/Users/DELL/OneDrive/Bureau/CIN.py" << imagePath);
    process.waitForFinished();
    QString output = process.readAllStandardOutput();

    // Vérifier si l'image contient une personne
    if (!output.contains("L'image contient une personne")) {
        QMessageBox::warning(this, tr("Image invalide"), tr("L'image sélectionnée ne contient pas de personne. Veuillez sélectionner une autre image."), QMessageBox::Ok);
        return;
    }

    // Récupérer les valeurs des champs de l'artiste à modifier
    int cin = ui->arcin_2->text().toInt();
    int tel = ui->artelephone_2->text().toInt();
    QString nom = ui->arnom_2->text();
    QString prenom = ui->arprenom_2->text();
    QString adresse = ui->aradresse_2->text();
    QString mail = ui->armail_2->text();
    QString domaine = ui->ardomaine_2->text();
    QString description = ui->ardescription_2->text();
    QString sexe = ui->arsexe_2->currentText();

    // Charger l'image sélectionnée
    QPixmap imagePixmap(imagePath);

    // Convertir l'image en QByteArray
    QByteArray imageData;
    QBuffer buffer(&imageData);
    buffer.open(QIODevice::WriteOnly);
    imagePixmap.save(&buffer, "PNG");

    // Vérifier si tous les champs obligatoires sont remplis
    if (nom.isEmpty() || prenom.isEmpty() || adresse.isEmpty() || mail.isEmpty() || domaine.isEmpty() || sexe.isEmpty()) {
        // Afficher un message d'erreur
        QMessageBox::critical(nullptr, QObject::tr("Modifier un artiste"),
                    QObject::tr("Veuillez remplir tous les champs obligatoires."), QMessageBox::Cancel);
        return;
    }

    // Vérifier si l'email contient le symbole '@'
    if (!mail.contains("@")) {
        QMessageBox::critical(nullptr, QObject::tr("Modifier un artiste"),
                    QObject::tr("L'adresse email doit contenir le symbole '@'."), QMessageBox::Cancel);
        return;
    }

    // Vérifier si le numéro de téléphone est un nombre valide
    if (tel == 0 || ui->artelephone_2->text().isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Modifier un artiste"),
                    QObject::tr("Le numéro de téléphone ne peut pas être vide et doit être un nombre."), QMessageBox::Cancel);
        return;
    }

    // Vérifier si le nom contient uniquement des lettres
    QRegExp nomRegex("^[A-Za-zÀ-ÿ\\s]+$"); // Expression régulière pour vérifier que la chaîne contient uniquement des lettres et des espaces
    if (!nomRegex.exactMatch(nom)) {
        QMessageBox::critical(nullptr, QObject::tr("Modifier un artiste"),
                    QObject::tr("Le nom doit contenir uniquement des lettres."), QMessageBox::Cancel);
        return;
    }

    // Modifier l'artiste avec l'image
    bool test = a.modifier(cin, tel, nom, prenom, adresse, mail, domaine, description, sexe, imageData);

    // Effacer les champs après la modification
    ui->arcin_2->clear();
    ui->artelephone_2->clear();
    ui->arnom_2->clear();
    ui->arprenom_2->clear();
    ui->aradresse_2->clear();
    ui->armail_2->clear();
    ui->ardomaine_2->clear();
    ui->ardescription_2->clear();
    ui->arsexe_2->setCurrentIndex(0); // Réinitialiser la sélection du sexe
    ui->image_artist_3->clear();
    ui->image_artist_3->setPixmap(QPixmap());
    // Rafraîchir les modèles de tableaux
    ui->artableView->setModel(a.afficher());
    ui->artableView_3->setModel(a.afficher());
    ui->artableView_2->setModel(a.afficher());

    // Afficher un message de réussite ou d'échec
    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("Modifier un artiste"),
                    QObject::tr("Artiste modifié avec succès."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Modifier un Artiste"),
                    QObject::tr("Erreur lors de la modification de l'artiste."), QMessageBox::Cancel);
    }
}




void MainWindow::on_arclear_2_clicked()
{
    ui->arcin_2->setText("");
    ui->arnom_2->setText("");
    ui->arprenom_2->setText("");
    ui->artelephone_2->setText("");
    ui->aradresse_2->setText("");
    ui->armail_2->setText("");
    ui->ardomaine_2->setText("");
    ui->ardescription_2->setText("");

    // Effacer l'image affichée dans image_artist_2
    ui->image_artist_3->clear();

    // Réinitialiser explicitement le pixmap du QLabel
    ui->image_artist_3->setPixmap(QPixmap());
}









//----------------------------------------------------------SUPPRESSION-----------------------------------------------------------------------









void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked) {
           // Cocher toutes les lignes dans artableView_3
           ui->artableView_3->selectAll();
       } else {
           // Décocher toutes les lignes dans artableView_3
           ui->artableView_3->clearSelection();
       }
}





void MainWindow::on_artableView_3_doubleClicked(const QModelIndex &index)
{
    int row = index.row();
    cinn = ui->artableView_3->model()->index(row, 0).data().toInt(); // Store the CIN in the member variable
    qDebug() << "CIN selected: " << cinn; // Debug message to confirm CIN is selected
}




void MainWindow::on_ardelete_clicked() {
    QModelIndexList selectedIndexes = ui->artableView_3->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select at least one artist to delete.");
        return;
    }

    int count = selectedIndexes.count();
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation", "Are you sure you want to delete " + QString::number(count/10) + " selected artist(s)?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::No)
        return;

    QList<int> artistsToDelete;
    foreach(const QModelIndex &index, selectedIndexes) {
        int cin = index.sibling(index.row(), 0).data(Qt::DisplayRole).toInt();
        artistsToDelete.append(cin);
    }

    int successfulDeletions = 0;
    foreach(int cin, artistsToDelete) {
        bool suppressionReussie = a.supprimer(cin);
        if (suppressionReussie) {
            successfulDeletions++;
        }
    }

    // Refresh the table view if at least one artist was successfully deleted
    if (successfulDeletions > 0) {
        ui->artableView_3->setModel(a.afficher());
        ui->artableView_2->setModel(a.afficher());
        ui->artableView->setModel(a.afficher());
        QMessageBox::information(this, "Success", QString::number(successfulDeletions/10) + " artist(s) deleted successfully.");
    } else {
        QMessageBox::critical(this, "Error", "Failed to delete selected artist(s).");
    }
}







//--------------------------------------------      RECHERCHE       ------------------------------------------------------------------







void MainWindow::on_arsearchTextBox_textChanged(const QString &arg1)
{
    QString searchText = arg1;
    QSqlQueryModel* model;

    // Vérifier si le texte de recherche est vide
    if (searchText.isEmpty()) {
        // Charger tous les enregistrements sans filtre
        model = a.rechercher("");
    } else {
        // Charger les enregistrements correspondants au texte de recherche
        model = a.rechercher(searchText);
    }

    // Remplacer le modèle précédent dans le QTableView
    if(ui->artableView->model())
        delete ui->artableView->model();
    ui->artableView->setModel(model);
}










//---------------------------------------------------       STAT        --------------------------------------------------------






void MainWindow::on_arstat_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT sexe FROM TABLE1");

    int countMale = 0;
    int countFemale = 0;
    int countOther = 0;

    for (int i = 0; i < model->rowCount(); ++i) {
        QString sexe = model->record(i).value("sexe").toString();
        if (sexe == "Man") {
            ++countMale;
        } else if (sexe == "Woman") {
            ++countFemale;
        } else {
            ++countOther;
        }
    }

    int total = countMale + countFemale + countOther;

    QPieSeries *series = new QPieSeries();
    if (countMale != 0)
        series->append("Man", countMale);
    if (countFemale != 0)
        series->append("Woman", countFemale);
    if (countOther != 0)
        series->append("Other", countOther);

    // Définir les couleurs des tranches
    QStringList colors = {"#ff0000", "#00ff00", "#0000ff"}; // Rouge, vert, bleu
    int colorIndex = 0;
    for (QPieSlice *slice : series->slices()) {
        slice->setColor(QColor(colors[colorIndex]));
        colorIndex = (colorIndex + 1) % colors.size();
        QString label = slice->label();
        double percentage = (slice->percentage() * 100.0);
        slice->setLabel(QString("%1 %2%").arg(label).arg(percentage, 0, 'f', 1));
        slice->setLabelVisible();
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Total " + QString::number(total));

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1000, 500);

    chart->legend()->hide();
    chartView->show();

}






//--------------------------------------        PDF LISTE DES ARTISTES      -----------------------------------------------





void MainWindow::on_arpdf_clicked()
{
    QDateTime datecreation = QDateTime::currentDateTime();
    QString afficheDC = "Date de Creation PDF : " + datecreation.toString();
    QPdfWriter pdf("C:/Users/DELL/Downloads/pdf.pdf");

    QPainter painter(&pdf);
    int i = 4000;
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 30));
    painter.drawText(1100, 1200, "Liste Des ARTIST ");
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 50));
    painter.drawRect(100, 100, 7300, 2600);
    painter.drawRect(0, 3000, 9600, 500);
    painter.setFont(QFont("Arial", 9));
    painter.drawText(200, 3300, "CIN");
    painter.drawText(1700, 3300, "NOM");
    painter.drawText(3200, 3300, "TEL");
    painter.drawText(4200, 3300, "PRENOM");
    painter.drawText(5200, 3300, "ADRESSE");
    painter.drawText(6200, 3300, "MAIL");
    painter.drawText(7200, 3300, "DOMAINE");
    painter.drawText(8200, 3300, "DESCRIPTION"); // Corrected position for DESCRIPTION
    painter.drawText(9200, 3300, "SEXE"); // Added SEXE

    QSqlQuery query;
    query.prepare("SELECT * FROM TABLE1");
    query.exec();
    while (query.next())
    {
        painter.drawText(200, i, query.value(0).toString());
        painter.drawText(1700, i, query.value(1).toString());
        painter.drawText(3200, i, query.value(2).toString());
        painter.drawText(4200, i, query.value(3).toString());
        painter.drawText(5200, i, query.value(4).toString());
        painter.drawText(6200, i, query.value(5).toString());
        painter.drawText(7200, i, query.value(6).toString());
        painter.drawText(8200, i, query.value(7).toString()); // Changed to value(7) for DESCRIPTION
        painter.drawText(9200, i, query.value(8).toString()); // Changed to value(8) for SEXE

        i = i + 500;
    }

    int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes || reponse == QMessageBox::No)
    {
        painter.end();
    }

    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/DELL/Downloads/pdf.pdf"));
    }
}



















// *****************partie reconnaissance vocale chaque champs ces fonction **********************************//


//-------Nom----------
void MainWindow::updateNom(const QString &text) {
    ui->arnom->setText(text);
}

void MainWindow::on_reconnaissance_2_clicked()
{
    // Démarrez la reconnaissance vocale directement dans cette fonction

    // Créez une instance du travailleur de reconnaissance vocale
    worker = new SpeechRecognitionWorker(this);

    // Créez un thread pour exécuter le travailleur de reconnaissance vocale
    thread = new QThread(this);
    worker->moveToThread(thread);

    // Connectez le signal de travailleur au slot de mise à jour du champ nom_2
    connect(worker, &SpeechRecognitionWorker::recognizedText, this, &MainWindow::updateNom);

    // Démarrez le thread
    thread->start();

    // Démarrez la reconnaissance vocale en appelant la fonction de démarrage du travailleur
    worker->startRecognition();
}



//-------Cin----------

void MainWindow::updateCIN(const QString &text) {
    QString cleanedText = text.trimmed().remove(" "); // Supprimer les espaces du texte reconnu
    ui->arcin->setText(cleanedText);
}



void MainWindow::on_reconnaissance_clicked()
{
    // Créez une instance du travailleur de reconnaissance vocale
    worker = new SpeechRecognitionWorker(this);

    // Créez un thread pour exécuter le travailleur de reconnaissance vocale
    thread = new QThread(this);
    worker->moveToThread(thread);

    // Connectez le signal de travailleur au slot de mise à jour du champ CIN
    connect(worker, &SpeechRecognitionWorker::recognizedText, this, &MainWindow::updateCIN);

    // Démarrez le thread
    thread->start();

    // Démarrez la reconnaissance vocale en appelant la fonction de démarrage du travailleur
    worker->startRecognition();
}



//------Prenom-------

void MainWindow::updatePrenom(const QString &text) {
    ui->arprenom->setText(text);
}


void MainWindow::on_reconnaissance_3_clicked()
{
    // Créez une instance du travailleur de reconnaissance vocale
    worker = new SpeechRecognitionWorker(this);

    // Créez un thread pour exécuter le travailleur de reconnaissance vocale
    thread = new QThread(this);
    worker->moveToThread(thread);

    // Connectez le signal de travailleur au slot de mise à jour du champ CIN
    connect(worker, &SpeechRecognitionWorker::recognizedText, this, &MainWindow::updatePrenom);

    // Démarrez le thread
    thread->start();

    // Démarrez la reconnaissance vocale en appelant la fonction de démarrage du travailleur
    worker->startRecognition();
}



//--------mail-------

void MainWindow::updateMail(const QString &text) {
    QString cleanedText =text;
    cleanedText.replace("alt", "@"); // Remplacer "alt" par "@"
    ui->armail->setText(text);
}


void MainWindow::on_reconnaissance_7_clicked()
{
    // Créez une instance du travailleur de reconnaissance vocale
    worker = new SpeechRecognitionWorker(this);

    // Créez un thread pour exécuter le travailleur de reconnaissance vocale
    thread = new QThread(this);
    worker->moveToThread(thread);

    // Connectez le signal de travailleur au slot de mise à jour du champ CIN
    connect(worker, &SpeechRecognitionWorker::recognizedText, this, &MainWindow::updateMail);

    // Démarrez le thread
    thread->start();

    // Démarrez la reconnaissance vocale en appelant la fonction de démarrage du travailleur
    worker->startRecognition();
}




//--------description-------

void MainWindow::updateDescription(const QString &text) {
    ui->ardescription->setText(text);
}


void MainWindow::on_reconnaissance_8_clicked()
{
    // Créez une instance du travailleur de reconnaissance vocale
    worker = new SpeechRecognitionWorker(this);

    // Créez un thread pour exécuter le travailleur de reconnaissance vocale
    thread = new QThread(this);
    worker->moveToThread(thread);

    // Connectez le signal de travailleur au slot de mise à jour du champ CIN
    connect(worker, &SpeechRecognitionWorker::recognizedText, this, &MainWindow::updateDescription);

    // Démarrez le thread
    thread->start();

    // Démarrez la reconnaissance vocale en appelant la fonction de démarrage du travailleur
    worker->startRecognition();
}



//---------telephone--------

void MainWindow::updateTelephone(const QString &text) {
    ui->artelephone->setText(text);
}


void MainWindow::on_reconnaissance_5_clicked()
{
    // Créez une instance du travailleur de reconnaissance vocale
    worker = new SpeechRecognitionWorker(this);

    // Créez un thread pour exécuter le travailleur de reconnaissance vocale
    thread = new QThread(this);
    worker->moveToThread(thread);

    // Connectez le signal de travailleur au slot de mise à jour du champ CIN
    connect(worker, &SpeechRecognitionWorker::recognizedText, this, &MainWindow::updateTelephone);

    // Démarrez le thread
    thread->start();

    // Démarrez la reconnaissance vocale en appelant la fonction de démarrage du travailleur
    worker->startRecognition();
}



//------adresse------

void MainWindow::updateAdresse(const QString &text) {
    ui->aradresse->setText(text);
}


void MainWindow::on_reconnaissance_4_clicked()
{
    // Créez une instance du travailleur de reconnaissance vocale
    worker = new SpeechRecognitionWorker(this);

    // Créez un thread pour exécuter le travailleur de reconnaissance vocale
    thread = new QThread(this);
    worker->moveToThread(thread);

    // Connectez le signal de travailleur au slot de mise à jour du champ CIN
    connect(worker, &SpeechRecognitionWorker::recognizedText, this, &MainWindow::updateAdresse);

    // Démarrez le thread
    thread->start();

    // Démarrez la reconnaissance vocale en appelant la fonction de démarrage du travailleur
    worker->startRecognition();
}



//------domaine--------

void MainWindow::updateDomaine(const QString &text) {
    ui->ardomaine->setText(text);
}


void MainWindow::on_reconnaissance_6_clicked()
{
    // Créez une instance du travailleur de reconnaissance vocale
    worker = new SpeechRecognitionWorker(this);

    // Créez un thread pour exécuter le travailleur de reconnaissance vocale
    thread = new QThread(this);
    worker->moveToThread(thread);

    // Connectez le signal de travailleur au slot de mise à jour du champ CIN
    connect(worker, &SpeechRecognitionWorker::recognizedText, this, &MainWindow::updateDomaine);

    // Démarrez le thread
    thread->start();

    // Démarrez la reconnaissance vocale en appelant la fonction de démarrage du travailleur
    worker->startRecognition();
}

/*
//------sexe------

void MainWindow::updateSexe(const QString &text) {
    int index = ui->sexe->findText(text, Qt::MatchFixedString);
    if (index >= 0) {
        ui->sexe->setCurrentIndex(index);
    }
}



void MainWindow::on_reconnaissance_3_clicked()
{
    // Créez une instance du travailleur de reconnaissance vocale
    worker = new SpeechRecognitionWorker(this);

    // Créez un thread pour exécuter le travailleur de reconnaissance vocale
    thread = new QThread(this);
    worker->moveToThread(thread);

    // Connectez le signal de travailleur au slot de mise à jour de la QComboBox "Sexe"
    connect(worker, &SpeechRecognitionWorker::recognizedText, this, &MainWindow::updateSexe);

    // Démarrez le thread
    thread->start();

    // Démarrez la reconnaissance vocale en appelant la fonction de démarrage du travailleur
    worker->startRecognition();
}


*/





//********************************assistant vocale *************************
void MainWindow::on_arassistant_clicked()
{
    // Créer un objet de processus pour exécuter le script Python
    QProcess *process = new QProcess(this);

    // Définir le chemin vers le script Python
    QString pythonScriptPath = "C:/Users/DELL/OneDrive/Bureau/yassine.py";

    // Exécuter le script Python en tant que processus
    process->start("python", QStringList() << pythonScriptPath);

    // Connecter les signaux de processus pour récupérer les sorties de processus
    connect(process, &QProcess::readyReadStandardOutput, [=]() {
        // Lire la sortie standard du processus (résultats de la reconnaissance vocale)
        QByteArray output = process->readAllStandardOutput();

        // Traiter les résultats de la reconnaissance vocale
        QString result = QString::fromUtf8(output);

        // Vérifier si la sortie contient la demande de page ajout
        if (result.contains("pageAjoutRequested")) {
            // Passer à la page ajout
            ui->stackedWidget->setCurrentIndex(2);
            ui->stackedWidgetArtist->setCurrentIndex(1);
        }
        if (result.contains("pageModifierRequested")) {
            // Passer à la page ajout
            ui->stackedWidget->setCurrentIndex(2);
            ui->stackedWidgetArtist->setCurrentIndex(2);
        }
        if (result.contains("pageSupprimerRequested")) {
            // Passer à la page ajout
            ui->stackedWidget->setCurrentIndex(2);
            ui->stackedWidgetArtist->setCurrentIndex(3);
        }
        if (result.contains("pageRechercherRequested")) {
            // Passer à la page ajout
            ui->stackedWidget->setCurrentIndex(2);
            ui->stackedWidgetArtist->setCurrentIndex(0);
        }

    });

    connect(process, &QProcess::readyReadStandardError, [=]() {
        // Gérer les erreurs de processus si nécessaire
        QByteArray error = process->readAllStandardError();
        qDebug() << "Error:" << error;
    });

    // Attendre que le processus se termine (peut être en option)
    process->waitForFinished();
}







//**********************************   scannn   ********************************************************************




//--------cin
void MainWindow::on_scann_clicked()
{

        QProcess process;
        process.start("python", { "C:/Users/DELL/OneDrive/Bureau/scann.py" });
        process.waitForFinished();
        QString output = process.readAllStandardOutput();
       ui->arcin->setText(output);

}


void MainWindow::on_scann_2_clicked()
{

        QProcess process;
        process.start("python", { "C:/Users/DELL/OneDrive/Bureau/scann.py" });
        process.waitForFinished();
        QString output = process.readAllStandardOutput();
       ui->arnom->setText(output);

}


void MainWindow::on_scann_3_clicked()
{

        QProcess process;
        process.start("python", { "C:/Users/DELL/OneDrive/Bureau/scann.py" });
        process.waitForFinished();
        QString output = process.readAllStandardOutput();
       ui->arprenom->setText(output);

}


void MainWindow::on_scann_4_clicked()
{

        QProcess process;
        process.start("python", { "C:/Users/DELL/OneDrive/Bureau/scann.py" });
        process.waitForFinished();
        QString output = process.readAllStandardOutput();
       ui->aradresse->setText(output);

}


void MainWindow::on_scann_5_clicked()
{

        QProcess process;
        process.start("python", { "C:/Users/DELL/OneDrive/Bureau/scann.py" });
        process.waitForFinished();
        QString output = process.readAllStandardOutput();
       ui->artelephone->setText(output);

}


void MainWindow::on_scann_6_clicked()
{

        QProcess process;
        process.start("python", { "C:/Users/DELL/OneDrive/Bureau/scann.py" });
        process.waitForFinished();
        QString output = process.readAllStandardOutput();
       ui->ardomaine->setText(output);

}


void MainWindow::on_scann_7_clicked()
{

        QProcess process;
        process.start("python", { "C:/Users/DELL/OneDrive/Bureau/scann.py" });
        process.waitForFinished();
        QString output = process.readAllStandardOutput();
       ui->armail->setText(output);

}


void MainWindow::on_scann_8_clicked()
{

        QProcess process;
        process.start("python", { "C:/Users/DELL/OneDrive/Bureau/scann.py" });
        process.waitForFinished();
        QString output = process.readAllStandardOutput();
       ui->ardescription->setText(output);

}










//------------------------------********    TRIE      *****-------------------------------------------------------------------------------







void MainWindow::on_desc_1_clicked()
{
    // Trier les données de manière décroissante par CIN
    QSqlQueryModel* sortedModel = a.afficher_tri_cin_descendant();

    // Mettre à jour le modèle de tableView avec les données triées
    if(ui->artableView->model())
        delete ui->artableView->model();
    ui->artableView->setModel(sortedModel);
}

void MainWindow::on_asc_1_clicked()
{


    // Trier les données de manière décroissante par CIN
    QSqlQueryModel* sortedModel = a.afficher_tri_cin_ascendant();

    // Mettre à jour le modèle de tableView avec les données triées
    if(ui->artableView->model())
        delete ui->artableView->model();
    ui->artableView->setModel(sortedModel);

}



void MainWindow::on_desc_2_clicked()
{
    // Trier les données de manière décroissante par CIN
    QSqlQueryModel* sortedModel = a.afficher_tri_tel_descendant();

    // Mettre à jour le modèle de tableView avec les données triées
    if(ui->artableView->model())
        delete ui->artableView->model();
    ui->artableView->setModel(sortedModel);
}

void MainWindow::on_asc_2_clicked()
{


    // Trier les données de manière décroissante par CIN
    QSqlQueryModel* sortedModel = a.afficher_tri_tel_ascendant();

    // Mettre à jour le modèle de tableView avec les données triées
    if(ui->artableView->model())
        delete ui->artableView->model();
    ui->artableView->setModel(sortedModel);

}


void MainWindow::on_desc_3_clicked()
{
    // Trier les données de manière décroissante par CIN
    QSqlQueryModel* sortedModel = a.afficher_tri_nom_descendant();

    // Mettre à jour le modèle de tableView avec les données triées
    if(ui->artableView->model())
        delete ui->artableView->model();
    ui->artableView->setModel(sortedModel);
}

void MainWindow::on_asc_3_clicked()
{


    // Trier les données de manière décroissante par CIN
    QSqlQueryModel* sortedModel = a.afficher_tri_nom_ascendant();

    // Mettre à jour le modèle de tableView avec les données triées
    if(ui->artableView->model())
        delete ui->artableView->model();
    ui->artableView->setModel(sortedModel);

}




void MainWindow::on_desc_4_clicked()
{
    // Trier les données de manière décroissante par CIN
    QSqlQueryModel* sortedModel = a.afficher_tri_prenom_descendant();

    // Mettre à jour le modèle de tableView avec les données triées
    if(ui->artableView->model())
        delete ui->artableView->model();
    ui->artableView->setModel(sortedModel);
}

void MainWindow::on_asc_4_clicked()
{


    // Trier les données de manière décroissante par CIN
    QSqlQueryModel* sortedModel = a.afficher_tri_prenom_ascendant();

    // Mettre à jour le modèle de tableView avec les données triées
    if(ui->artableView->model())
        delete ui->artableView->model();
    ui->artableView->setModel(sortedModel);

}


void MainWindow::on_desc_5_clicked()
{
    // Trier les données de manière décroissante par CIN
    QSqlQueryModel* sortedModel = a.afficher_tri_adresse_descendant();

    // Mettre à jour le modèle de tableView avec les données triées
    if(ui->artableView->model())
        delete ui->artableView->model();
    ui->artableView->setModel(sortedModel);
}

void MainWindow::on_asc_5_clicked()
{


    // Trier les données de manière décroissante par CIN
    QSqlQueryModel* sortedModel = a.afficher_tri_adresse_ascendant();

    // Mettre à jour le modèle de tableView avec les données triées
    if(ui->artableView->model())
        delete ui->artableView->model();
    ui->artableView->setModel(sortedModel);

}



void MainWindow::on_desc_6_clicked()
{
    // Trier les données de manière décroissante par CIN
    QSqlQueryModel* sortedModel = a.afficher_tri_email_descendant();

    // Mettre à jour le modèle de tableView avec les données triées
    if(ui->artableView->model())
        delete ui->artableView->model();
    ui->artableView->setModel(sortedModel);
}

void MainWindow::on_asc_6_clicked()
{


    // Trier les données de manière décroissante par CIN
    QSqlQueryModel* sortedModel = a.afficher_tri_email_ascendant();

    // Mettre à jour le modèle de tableView avec les données triées
    if(ui->artableView->model())
        delete ui->artableView->model();
    ui->artableView->setModel(sortedModel);

}



void MainWindow::on_desc_7_clicked()
{
    // Trier les données de manière décroissante par CIN
    QSqlQueryModel* sortedModel = a.afficher_tri_domaine_descendant();

    // Mettre à jour le modèle de tableView avec les données triées
    if(ui->artableView->model())
        delete ui->artableView->model();
    ui->artableView->setModel(sortedModel);
}

void MainWindow::on_asc_7_clicked()
{


    // Trier les données de manière décroissante par CIN
    QSqlQueryModel* sortedModel = a.afficher_tri_domaine_ascendant();

    // Mettre à jour le modèle de tableView avec les données triées
    if(ui->artableView->model())
        delete ui->artableView->model();
    ui->artableView->setModel(sortedModel);

}








//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//##############################################################################################################################################################
//#####################################             ARTICLE             ########################################################################################



void MainWindow::on_pushButton_14_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Parcourir..."), QDir::homePath(), tr("Images (*.png *.jpg *.bmp)"));

    // Vérifier si un fichier a été sélectionné
    if (!filePath.isEmpty()) {
        // Charger et afficher l'image
        QImage image(filePath);
        if (!image.isNull()) {
            QPixmap pixmap = QPixmap::fromImage(image);
            ui->imageArticle->setPixmap(pixmap.scaled(ui->imageArticle->size(), Qt::KeepAspectRatio));

            // Mettre à jour le texte du QLineEdit avec le chemin de l'image
            ui->imageline->setText(filePath);
        } else {
            // Afficher un message d'erreur si le chargement de l'image a échoué
            QMessageBox::warning(this, tr("Erreur"), tr("Impossible de charger l'image : ") + filePath);
        }
    }
}




void MainWindow::on_ajouterArt_clicked()
{
    QString domaine = ui->domaineArticleInput->text();
    QString nom = ui->nomArticleInput->text();
    QString date_creation = ui->dateEdit->text();
    QString type = ui->quantiteArticleInput->text();
    QString dimension = ui->dimensionArticleInput->text();
    QString poidsStr = ui->poidsArticleInput->text();
    QString prixStr = ui->prixArticleInput->text();
    QString description = ui->descriptionInput->toPlainText();
    QString imagePath = ui->imageline->text();
    QString idArtistea = ui->idartiste->text();


    // Vérification des champs obligatoires
    if (domaine.isEmpty() || nom.isEmpty() || date_creation.isEmpty() || type.isEmpty() || dimension.isEmpty() || poidsStr.isEmpty() || prixStr.isEmpty() || description.isEmpty() || imagePath.isEmpty()) {
        QMessageBox::critical(this, "Erreur", "Veuillez remplir tous les champs.");
        return;
    }

    // Vérification de la validité des données numériques
    bool poidsConversionOk, prixConversionOk;
    int poids = poidsStr.toInt(&poidsConversionOk);
    int prix = prixStr.toInt(&prixConversionOk);
    int idArtiste = idArtistea.toInt();

    if (!poidsConversionOk || !prixConversionOk || poids <= 0 || prix <= 0) {
        QMessageBox::critical(this, "Erreur", "Veuillez saisir des valeurs numériques valides pour le poids et le prix.");
        return;
    }

    // Création de l'objet Article avec les valeurs récupérées
    Article article(domaine, nom, date_creation, type, dimension, poids, prix, description, imagePath,idArtiste,0);

    // Appel de la méthode d'ajout d'article de votre classe Article
    bool success = article.ajouter();
    if (success) {

        // Effacer les champs de saisie après un ajout réussi
        ui->domaineArticleInput->clear();
        ui->nomArticleInput->clear();
        ui->quantiteArticleInput->clear();
        ui->dimensionArticleInput->clear();
        ui->poidsArticleInput->clear();
        ui->prixArticleInput->clear();
        ui->descriptionInput->clear();
        ui->imageline->clear();
        ui->idartiste->clear();

        ui->stackedWidgetProduct->setCurrentIndex(0);

        // Rafraîchir la vue pour afficher l'article ajouté
        ui->tableView_6->setModel(article.afficher());
        QMessageBox::information(this, "Succès", "Article ajouté avec succès.");
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout de l'article.");

    }

}

void MainWindow::on_tableView_17_doubleClicked(const QModelIndex &index)
{
    // Vérifiez si l'index est valide
    if (!index.isValid()) {
        // Gérez l'index invalide si nécessaire, par exemple, affichez un message d'erreur
        return;
    }

    // Définissez les indices de colonnes en fonction de la structure réelle de votre table
    const int id_COLUMN = 0;

    const int DOMAIN_COLUMN = 1;
    const int NAME_COLUMN = 2;
    const int CREATION_DATE_COLUMN = 3;
    const int TYPE_COLUMN = 4;
    const int DIMENSION_COLUMN = 5;
    const int WEIGHT_COLUMN = 6;
    const int PRICE_COLUMN = 7;
    const int DESCRIPTION_COLUMN = 8;
    const int IMAGE_PATH_COLUMN = 9;
    const int idart = 10;


    // Récupérez les détails de l'article à partir de la ligne sélectionnée dans le QTableView.
    int idA = index.sibling(index.row(), id_COLUMN).data().toInt();
    QString domain = index.sibling(index.row(), DOMAIN_COLUMN).data().toString();
    QString name = index.sibling(index.row(), NAME_COLUMN).data().toString();
    QString creationDate = index.sibling(index.row(), CREATION_DATE_COLUMN).data().toString();
    QString type = index.sibling(index.row(), TYPE_COLUMN).data().toString();
    QString dimension = index.sibling(index.row(), DIMENSION_COLUMN).data().toString();
    int weight = index.sibling(index.row(), WEIGHT_COLUMN).data().toInt();
    int price = index.sibling(index.row(), PRICE_COLUMN).data().toInt();
    QString description = index.sibling(index.row(), DESCRIPTION_COLUMN).data().toString();
    QString imagePath = index.sibling(index.row(), IMAGE_PATH_COLUMN).data().toString();
    int idartiste = index.sibling(index.row(), idart).data().toInt();


    // Remplissez les champs de texte avec les données récupérées.
    ui->ida->setText(QString::number(idA));

    ui->domaineArticleInput_2->setText(domain);
    ui->nomArticleInput_2->setText(name);
    ui->dateEdit_2->setText(creationDate);
    ui->typeArticleInput_2->setText(type);
    ui->dimensionArticleInput_2->setText(dimension);
    ui->poidsArticleInput_2->setText(QString::number(weight));
    ui->prixArticleInput_2->setText(QString::number(price));
    ui->descriptionInput_2->setText(description);
    ui->imagein->setText(imagePath);
    ui->idar->setText(QString::number(idartiste));




    // Chargez et affichez l'image de l'article
    QPixmap image(imagePath);
    if (!image.isNull()) {
        ui->imageLabel->setPixmap(image.scaled(ui->imageLabel->size(), Qt::KeepAspectRatio));
    } else {
      QMessageBox::warning(this, "Erreur", "Impossible de charger l'image : " + imagePath);
    }
}








void MainWindow::on_updateEmployee_5_clicked()
{
    Article article;
    ui->stackedWidgetProduct->setCurrentIndex(3);
    ui->tableView_17->setModel(article.afficher());
}


void MainWindow::on_save_5_clicked()
{
    Article article;
    ui->stackedWidgetProduct->setCurrentIndex(0);

    // Récupérer les valeurs des champs du formulaire d'édition d'articles
    int idArticle = ui->ida->text().toInt();
    QString domaine = ui->domaineArticleInput_2->text();
    QString nom = ui->nomArticleInput_2->text();
    QString dateCreation = ui->dateEdit_2->text();
    QString type = ui->typeArticleInput_2->text();
    QString dimension = ui->dimensionArticleInput_2->text();
    QString poidsStr = ui->poidsArticleInput_2->text();
    QString prixStr = ui->prixArticleInput_2->text();
    QString description = ui->descriptionInput_2->toPlainText();
    QString cheminImage = ui->imagein->text();
    QString idArtt = ui->idar->text();



    // Vérification des champs obligatoires
    if (domaine.isEmpty() || nom.isEmpty() || dateCreation.isEmpty() || type.isEmpty() || dimension.isEmpty() || poidsStr.isEmpty() || prixStr.isEmpty() || description.isEmpty() || cheminImage.isEmpty()) {
        QMessageBox::critical(this, "Erreur", "Veuillez remplir tous les champs.");
        return;
    }

    // Vérification de la validité des données numériques
    bool poidsConversionOk, prixConversionOk;
    int poids = poidsStr.toInt(&poidsConversionOk);
    int prix = prixStr.toInt(&prixConversionOk);
    int idArt = idArtt.toInt();

    if (!poidsConversionOk || !prixConversionOk || poids <= 0 || prix <= 0) {
        QMessageBox::critical(this, "Erreur", "Veuillez saisir des valeurs numériques valides pour le poids et le prix.");
        return;
    }

    // Appeler la méthode de modification de la classe Article
    bool success = article.modifier(idArticle, domaine, nom, dateCreation, type, dimension, poids, prix, description, cheminImage,idArt,0);

    // Effacer les champs après la modification
    ui->domaineArticleInput_2->clear();
    ui->nomArticleInput_2->clear();
    ui->dateEdit_2->clear();
    ui->typeArticleInput_2->clear();
    ui->dimensionArticleInput_2->clear();
    ui->poidsArticleInput_2->clear();
    ui->prixArticleInput_2->clear();
    ui->descriptionInput_2->clear();
    ui->imagein->clear();
    ui->idar->clear();

    // Réinitialiser la sélection de l'image si nécessaire
    // ui->imageLabel->clear(); // Si vous affichez également l'image, réinitialisez-la

    // Actualiser le modèle de votre QTableView pour afficher les modifications
    ui->tableView_6->setModel(article.afficher());

    if (success) {
        QMessageBox::information(this, "Succès", "Article modifié avec succès.");
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la modification de l'article.");
    }}





void MainWindow::on_tableView_6_doubleClicked(const QModelIndex &index)
{
    int row = index.row();
        idA = ui->tableView_6->model()->index(row, 0).data().toInt(); // Store the CIN in the member variable
        qDebug() << "iDa selected: " << idA; // Debug message to confirm CIN is selected

    if (!index.isValid()) {
          return;
      }

    const int NAME_COLUMN = 1; // You should set this to the actual index
    const int DOMAIN_COLUMN = 2;
    const int CREATION_DATE_COLUMN = 3;
    const int TYPE_COLUMN = 4;
    const int DIMENSION_COLUMN = 5;
    const int WEIGHT_COLUMN = 6;
    const int PRICE_COLUMN = 7;
    const int DESCRIPTION_COLUMN = 8;
    const int IMAGE_PATH_COLUMN = 9;

    // Récupérez les détails de l'article à partir de la ligne sélectionnée dans le QTableView.

    QString domain = index.sibling(index.row(), DOMAIN_COLUMN).data().toString();
    QString name = index.sibling(index.row(), NAME_COLUMN).data().toString();
    QString creationDate = index.sibling(index.row(), CREATION_DATE_COLUMN).data().toString();
    QString type = index.sibling(index.row(), TYPE_COLUMN).data().toString();
    QString dimension = index.sibling(index.row(), DIMENSION_COLUMN).data().toString();
    int weight = index.sibling(index.row(), WEIGHT_COLUMN).data().toInt();
    int price = index.sibling(index.row(), PRICE_COLUMN).data().toInt();
    QString description = index.sibling(index.row(), DESCRIPTION_COLUMN).data().toString();
    QString imagePath = index.sibling(index.row(), IMAGE_PATH_COLUMN).data().toString();


      // Change the current page to the page with index 2
      ui->stackedWidgetProduct->setCurrentIndex(2);

      ui->lineEdit_nom_3->setText(name);
      ui->lineEdit_domaine_3->setText(domain);
      ui->lineEdit_date_3->setText(creationDate);
      ui->lineEdit_type_3->setText(type);
      ui->lineEdit_dimension_3->setText(dimension);
      ui->lineEdit_poids_3->setText(QString::number(weight));
      ui->lineEdit_prix_3->setText(QString::number(price));
      ui->textEdit_description_3->setText(description);
      QPixmap image(imagePath);
              if (!image.isNull()) {
                  ui->labelImage_3->setPixmap(image.scaled(ui->labelImage_3->size(), Qt::KeepAspectRatio));
              } else {
                  QMessageBox::warning(this, "Erreur", "Impossible de charger l'image : " + imagePath);
              }
                 ui->lineEdit_nom_3->setEnabled(false);
                 ui->lineEdit_domaine_3->setEnabled(false);
                 ui->lineEdit_date_3->setEnabled(false);
                 ui->lineEdit_type_3->setEnabled(false);
                 ui->lineEdit_dimension_3->setEnabled(false);
                 ui->lineEdit_poids_3->setEnabled(false);
                 ui->lineEdit_prix_3->setEnabled(false);
                 ui->textEdit_description_3->setEnabled(false);
}

void MainWindow::on_supprimer_31_clicked()
{
    qDebug() << "Attempting to delete artist with CIN: " << idA;
        bool success = article.supprimer(idA);
       if (success) {

           ui->tableView_6->setModel(article.afficher());

           QMessageBox::information(this, "Success", "Article deleted successfully.");
           ui->stackedWidgetProduct->setCurrentIndex(0);
       } else {
           QMessageBox::critical(this, "Error", "Failed to delete article.");
      }
}




void MainWindow::on_searchTextBox_19_textChanged(const QString &arg1)
{
    QString searchQuery = "%" + arg1 + "%";
       QSqlQueryModel* filteredModel = article.rechercher(searchQuery);
       ui->tableView_6->setModel(filteredModel);
}




void MainWindow::on_del_all_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView_4->selectionModel()->selectedIndexes();
        if (selectedIndexes.isEmpty()) {
            QMessageBox::warning(this, "Avertissement", "Veuillez sélectionner au moins un article à supprimer.");
            return;
        }

        int count = selectedIndexes.count();
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation", "Êtes-vous sûr de vouloir supprimer " + QString::number(count/12) + " article(s) sélectionné(s)?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::No)
            return;

        QList<int> articlesToDelete;
        foreach(const QModelIndex &index, selectedIndexes) {
            int id_article = index.sibling(index.row(), 0).data(Qt::DisplayRole).toInt();
            articlesToDelete.append(id_article);
        }

        int successfulDeletions = 0;
        foreach(int id_article, articlesToDelete) {
            bool suppressionReussie = article.supprimer(id_article);
            if (suppressionReussie) {
                successfulDeletions++;
            }
        }

        // Rafraîchir la vue de la table si au moins un article a été supprimé avec succès
        if (successfulDeletions > 0) {
            ui->tableView_4->setModel(article.afficher());
            QMessageBox::information(this, "Succès", QString::number((successfulDeletions)/12) + " article(s) supprimé(s) avec succès.");
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la suppression de l'article sélectionné.");
        }
}

void MainWindow::on_suppgen_clicked()
{
    ui->stackedWidgetProduct->setCurrentIndex(4);
    ui->tableView_4->setModel(article.afficher());
}









//------------------------------------------------------    PARTIE GUEST --------------------------------------------------------------------------------------
//################################################################################################################################################################
//*****************************************************************************************************************************************************************




void MainWindow::on_save_8_clicked()
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

    ui->label_affCIN_3->setText(QString::number(cin));
    ui->label_affName_3->setText(name);
    ui->label_affAge_3->setText(QString::number(age));
    ui->label_affGender_3->setText(gender);
    ui->label_affAddress_3->setText(address);
    ui->label_affPhone_3->setText(QString::number(phone));
    ui->label_affEmail_3->setText(email);

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
    g.setImage("");
}




void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
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
                pixmap = pixmap.scaled(ui->label_affImage_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->label_affImage_2->setPixmap(pixmap);
            } else {
                qDebug() << "Erreur: Impossible de charger l'image depuis les données ByteArray.";
            }

            ui->label_affCIN_3->setText(cin.toString());
            ui->label_affName_3->setText(name);
            ui->label_affAge_3->setText(age);
            ui->label_affGender_3->setText(gender);
            ui->label_affAddress_3->setText(address);
            ui->label_affEmail_3->setText(email);
            ui->label_affPhone_3->setText(phone);

            // Changez l'index du widget empilé pour afficher les informations
            ui->stackedWidgetGuest->setCurrentIndex(3);
        } else {
            qDebug() << "Erreur: Aucune donnée trouvée pour cet ID.";
        }
    }
}










void MainWindow::on_supprimer_Guest_2_clicked()
{
    g.supprimer(ui->label_affCIN_3->text().toInt());
    ui->tableView->setModel(g.afficher());
    ui->stackedWidgetGuest->setCurrentIndex(0);
}





void MainWindow::on_updateEmployee_2_clicked()
{
    ui->updateCIN_2->setText(ui->label_affCIN_3->text());
    ui->updateName_2->setText(ui->label_affName_3->text());
    ui->updateAge_2->setText(ui->label_affAge_3->text());
    ui->updateGender_2->setCurrentText(ui->label_affGender_3->text());
    ui->updateAddress_2->setText(ui->label_affAddress_3->text());
    ui->updateEmail_2->setText(ui->label_affEmail_3->text());
    ui->updatePhone_2->setText(ui->label_affPhone_3->text());
    QSqlQueryModel *model = g.afficherId(ui->label_affCIN_3->text().toInt());
    QByteArray imageData = model->record(0).value("Image").toByteArray();
    //QPixmap pixmap = *ui->label_affImage->pixmap();
    // Appliquer l'image au bouton-poussoir
    QPixmap pixmap;
    pixmap.loadFromData(imageData);
    pixmap = pixmap.scaled(ui->labelupdateImage_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->labelupdateImage_2->setPixmap(pixmap);

    ui->stackedWidgetGuest->setCurrentIndex(2);
}


void MainWindow::on_supprimer_35_clicked()
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

void MainWindow::on_save_10_clicked()
{
    //int cin = ui->updateCIN->text().toInt();
    QString name = ui->updateName_2->text();
    //int age = ui->updateAge->text().toInt();
    QString gender = ui->updateGender_2->currentText();
    QString address = ui->updateAddress_2->text();
    QString email = ui->updateEmail_2->text();
    QString image = g.getImage();
    //int phone = ui->updatePhone->text().toInt();


     QString cinStr = ui->updateCIN_2->text();
     QString emailstr = ui->updateEmail_2->text();
     QString ageStr = ui->updateAge_2->text();
     bool ageConversionOk;
     int ages = ageStr.toInt(&ageConversionOk);
     QRegExp cinRegex("\\d{8}"); // Expression régulière pour un CIN de 8 chiffres
     QRegularExpression emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");

     if (ui->updateCIN_2->text().isEmpty() || name.isEmpty() || ui->updateAge_2->text().isEmpty() || gender.isEmpty() || address.isEmpty() || ui->updatePhone_2->text().isEmpty()) {
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
         g.modifier(ui->label_affCIN_3->text().toInt(),ui->updateCIN_2->text().toInt(),ui->updateName_2->text(),ui->updateAge_2->text().toInt(),ui->updateGender_2->currentText(),ui->updateAddress_2->text(),ui->updateEmail_2->text(),ui->updatePhone_2->text().toInt());
         ui->label_affCIN_3->setText(ui->updateCIN_2->text());
         ui->label_affName_3->setText(ui->updateName_2->text());
         ui->label_affAge_3->setText(ui->updateAge_2->text());
         ui->label_affGender_3->setText(ui->updateGender_2->currentText());
         ui->label_affAddress_3->setText(ui->updateAddress_2->text());
         ui->label_affEmail_3->setText(ui->updateEmail_2->text());
         ui->label_affPhone_3->setText(ui->updatePhone_2->text());

     }
     else
     {
        g.modifierImage(ui->label_affCIN_3->text().toInt(),ui->updateCIN_2->text().toInt(),ui->updateName_2->text(),ui->updateAge_2->text().toInt(),ui->updateGender_2->currentText(),ui->updateAddress_2->text(),ui->updateEmail_2->text(),ui->updatePhone_2->text().toInt(),g.getImage());
        ui->label_affCIN_3->setText(ui->updateCIN_2->text());
        ui->label_affName_3->setText(ui->updateName_2->text());
        ui->label_affAge_3->setText(ui->updateAge_2->text());
        ui->label_affGender_3->setText(ui->updateGender_2->currentText());
        ui->label_affAddress_3->setText(ui->updateAddress_2->text());
        ui->label_affEmail_3->setText(ui->updateEmail_2->text());
        ui->label_affPhone_3->setText(ui->updatePhone_2->text());
        ui->label_affImage_2->setPixmap(g.getImage());
        g.setImage("");

        ui->stackedWidgetGuest->setCurrentIndex(3);
     }
}

void MainWindow::on_searchTextBox_17_textEdited(const QString &arg1)
{
    QSqlQueryModel* model = g.rechercher(arg1);
    ui->tableView->setModel(model);
}

void MainWindow::on_supprimer_18_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save PDF", ui->label_affCIN_3->text(), "*.pdf");

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
    additionalInfo << "CIN : " + ui->label_affCIN_3->text();
    additionalInfo << "Full Name : " + ui->label_affName_3->text();
    additionalInfo << "Age : " + ui->label_affAge_3->text();
    additionalInfo << "Gender : " + ui->label_affGender_3->text();
    additionalInfo << "Address : " + ui->label_affAddress_3->text();
    additionalInfo << "Phone Number : " + ui->label_affPhone_3->text();
    additionalInfo << "Email : " + ui->label_affEmail_3->text();


    int yOffset = 120;
    foreach(const QString &info, additionalInfo) {
        painter.drawText(120, yOffset, info);
        yOffset += 20;
    }

    painter.end();
}

void MainWindow::on_supprimer_42_clicked()
{
    QString pythonScript = "C:/Users/meddh/PycharmProjects/pythonProject/proj/2.py";

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
        //qDebug() << "This is result:" << ;
        QSqlQueryModel *model = g.afficherId(result.trimmed().toInt());
        qDebug() << model->rowCount();

        if (model->rowCount() > 0) {
           QString CIN = model->record(0).value("CIN").toString();
            QString Name = model->record(0).value("Name").toString();
            QString Age = model->record(0).value("Age").toString();
            QString Gender = model->record(0).value("Gender").toString();
            QString Address = model->record(0).value("Address").toString();
            QString Phone = model->record(0).value("Phone").toString();
            QString Email = model->record(0).value("Email").toString();

            // Vous pouvez ajouter d'autres attributs de la même manière
            qDebug() << CIN << Name << Age;

            ui->label_affCIN_3->setText(CIN);
            ui->label_affName_3->setText(Name);
            ui->label_affAge_3->setText(Age);
            ui->label_affGender_3->setText(Gender);
            ui->label_affAddress_3->setText(Address);
            ui->label_affPhone_3->setText(Phone);
            ui->label_affEmail_3->setText(Email);
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

void MainWindow::on_updateImage_2_clicked()
{
    QString imagePath2 = QFileDialog::getOpenFileName(nullptr, "Sélectionner une image", "", "Images (*.png *.jpg *.jpeg *.bmp *.gif)");
    QPixmap pixmap(imagePath2);

    // Définir l'image comme fond du bouton et styliser le cadre
    ui->labelupdateImage_2->setPixmap(pixmap);
     g.setImage(imagePath2);
}

void MainWindow::on_supprimer_GuestSelect_2_clicked()
{
    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();

    // Parcourez les indices des lignes sélectionnées et supprimez-les une par une
    for (const QModelIndex &index : selectedRows) {
        // Obtenez la valeur dans la première colonne (colonnes sont 0-indexées)
        int valueToDelete = ui->tableView->model()->data(index.sibling(index.row(), 0)).toInt();

        // Utilisez cette valeur pour appeler votre fonction de suppression
        g.supprimer(valueToDelete);
    }

    // Rafraîchissez le modèle de votre table view après la suppression
    ui->tableView->setModel(g.afficher());
}


void MainWindow::on_arsexe_3_currentIndexChanged(int index)
{
    QTranslator translator;
       switch (index) {
           case 1: // English
               qApp->removeTranslator(&translator);
               //phone
               ui->Nb_Emp_3->setText("phone :");
               ui->label_22->setText("phone :");
               ui->id_127->setText("phone :");
               ui->label_phoneGuest_3->setText("phone :");
               ui->Nb_Emp_6->setText("phone :");

               //Name :
               ui->label_23->setText("Name :");
               ui->Nom_3->setText("Name :");
               ui->ID_5->setText("Name :");
               ui->label_ageGuest_3->setText("Name :");

               //Last Name :
               ui->label_25->setText("Last Name :");
               ui->heure_debut_3->setText("Last Name :");
               ui->ID_6->setText("Last Name :");
               ui->label_nameGuest_3->setText("Last Name :");

               //Adress :
               ui->label_24->setText("Adress :");
               ui->description_3->setText("Adress :");
               ui->id_135->setText("Adress :");
               ui->label_adresseGuest_3->setText("Adress :");

               // Mail :
               ui->label_28->setText("Mail :");
               ui->lieux_3->setText("Mail :");
               ui->id_134->setText("Mail :");
               ui->label_genderGuest_4->setText("Mail :");

               //Domaine :
               ui->label_27->setText("Domain :");
               ui->price_5->setText("Domain :");
               ui->id_136->setText("Domain :");
               ui->label_emailGuest_3->setText("Domain :");


               // Cin Number :
               ui->ID_3->setText("Cin Number :");
               ui->ID_4->setText("Cin Number :");


               // Gender :
               ui->price_4->setText("Gender :");
               ui->id_133->setText("Gender :");
               ui->label_genderGuest_5->setText("Gender :");

               //Description :
               ui->description_5->setText("Description :");
               ui->id_141->setText("Description :");



               ui->pushButtonProduct->setText("p :");

























               break;
           case 0: // Français
               translator.load(":/translations/fr.qm");
               qApp->installTranslator(&translator);

               //phone
               ui->Nb_Emp_3->setText("Telephone :");
               ui->label_22->setText("Telephone :");
               ui->id_127->setText("Telephone :");
               ui->label_phoneGuest_3->setText("Telephone :");
               ui->Nb_Emp_6->setText("Telephone :");

               //Name :
               ui->label_23->setText("Nom :");
               ui->Nom_3->setText("Nom :");
               ui->ID_5->setText("Nom :");
               ui->label_ageGuest_3->setText("Nom :");

               //Last Name :
               ui->label_25->setText("Prenom :");
               ui->heure_debut_3->setText("Prenom :");
               ui->ID_6->setText("Prenom :");
               ui->label_nameGuest_3->setText("Prenom :");

               //Adress :
               ui->label_24->setText("Adresse :");
               ui->description_3->setText("Adresse :");
               ui->id_135->setText("Adresse :");
               ui->label_adresseGuest_3->setText("Adresse :");

               // Mail :
               ui->label_28->setText("Email :");
               ui->lieux_3->setText("Email :");
               ui->id_134->setText("Email :");
               ui->label_genderGuest_4->setText("Email :");

               //Domaine :
               ui->label_27->setText("Domaine :");
               ui->price_5->setText("Domaine :");
               ui->id_136->setText("Domaine :");
               ui->label_emailGuest_3->setText("Domaine :");


               // Cin Number :
               ui->ID_3->setText("Cin Numero :");
               ui->ID_4->setText("Cin Numero :");


               // Gender :
               ui->price_4->setText("Sexe :");
               ui->id_133->setText("Sexe :");
               ui->label_genderGuest_5->setText("Sexe :");

               //Description :
               ui->description_5->setText("Description :");
               ui->id_141->setText("Description :");

               break;
           case 2: // Arabe
               translator.load(":/translations/ar.qm");
               qApp->installTranslator(&translator);
               ui->Nb_Emp_3->setText(tr("مرحبا"));
               break;
       }
}

void MainWindow::on_statEmployee_clicked()
{
    ui->stackedWidgetSetting->setCurrentIndex(4);

}



/*


void MainWindow::on_checkBox_2_clicked()
{
    if(ui->checkBox_2->isChecked()) {
        qDebug() << "Le QCheckBox est coché.";
        // Charger l'image
        QPixmap darkImage("C:/Users/DELL/Downloads/evnement (1)/evnement/images/t.jpg");

        // Vérifier si l'image est valide
        if (darkImage.isNull()) {
            qDebug() << "L'image n'a pas pu être chargée.";
            return;
        }

        // Définir l'image comme arrière-plan de la fenêtre principale
        QPalette palette;
        palette.setBrush(QPalette::Background, darkImage);
        this->setPalette(palette);
        QLabel *imageLabel = new QLabel(this); // Créer un QLabel pour afficher l'image
        imageLabel->setPixmap(darkImage); // Définir l'image dans le QLabel
        ui->stackedWidget->addWidget(imageLabel); // Ajouter le QLabel à votre stackedWidget

    } else {
        qDebug() << "Le QCheckBox est décoché.";
        // Rétablir le fond par défaut de la fenêtre principale
        this->setPalette(QMainWindow().palette());
    }
}

void MainWindow::on_checkBox_3_clicked()
{

}


void MainWindow::on_arsexe_4_currentIndexChanged(int index)
{
    Q_UNUSED(index);

    // Modifier la direction du texte et la police pour prendre en charge l'écriture en arabe
    if (ui->arsexe_4->currentText() == "arabe") {
        // Définir la direction du texte de droite à gauche
        ui->lineEdit->setLayoutDirection(Qt::RightToLeft);

        // Choisir une police qui prend en charge l'arabe
        QFont arabicFont("Arial", 12); // Choisir une police qui prend en charge l'arabe
        arabicFont.setStyleStrategy(QFont::PreferAntialias);
        arabicFont.setStyleHint(QFont::AnyStyle); // Utiliser n'importe quel style de police
        ui->lineEdit->setFont(arabicFont);
    } else {
        // Rétablir la direction du texte et la police par défaut
        ui->lineEdit->setLayoutDirection(Qt::LeftToRight);
        ui->lineEdit->setFont(QFont()); // Rétablir la police par défaut
    }
}
*/
