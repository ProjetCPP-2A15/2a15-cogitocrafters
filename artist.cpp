#include "artist.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPieSeries>
#include <QPushButton>
#include "artist.h"
//#include "qrcode.h"
#include "QSqlTableModel"
#include <QtCharts/QLegend>
#include <QtCharts>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QPrinter>
#include <QPrintDialog>
#include "QSqlTableModel"
#include "QSqlRecord"
#include <QThread>
#include <QWidget>
#include <QFileDialog>
#include <QFile>
#include <QProcess>
#include <QStringListModel>
#include <QListView>
#include <QCompleter>





Artiste::Artiste(int cin, int tel, QString nom, QString prenom, QString adresse, QString mail, QString domaine, QString description, QString sexe, QByteArray image)
{
   this->cin = cin;
   this->tel = tel;
   this->nom = nom;
   this->prenom = prenom;
   this->adresse = adresse;
   this->mail = mail;
   this->domaine = domaine;
   this->description = description;
   this->sexe = sexe;
   this->image = image;
}


bool Artiste::ajouter()
{
   QSqlQuery query;
   query.prepare("INSERT INTO TABLE1 VALUES(:cin, :tel, :nom, :prenom, :adresse, :mail, :domaine, :description, :sexe, :image)");
   query.bindValue(":cin", cin);
   query.bindValue(":tel", tel);
   query.bindValue(":nom", nom);
   query.bindValue(":prenom", prenom);
   query.bindValue(":adresse", adresse);
   query.bindValue(":mail", mail);
   query.bindValue(":domaine", domaine);
   query.bindValue(":description", description);
   query.bindValue(":sexe", sexe);
   query.bindValue(":image", image);
   return query.exec();
}


QSqlQueryModel *Artiste::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT CAST(CIN AS VARCHAR(255)), CAST(TEL AS VARCHAR(255)), NOM, PRENOM, ADRESSE, MAIL, DOMAINE, DESCRIPTION, SEXE, IMAGE FROM TABLE1");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TEL"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("MAIL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("DOMAINE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("SEXE"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("IMAGE"));
    return model;
}



QSqlQueryModel * Artiste::affichers()
{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("SELECT CIN, NOM, DOMAINE FROM TABLE1");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DOMAINE"));
    return model;
}






bool Artiste::supprimer(int cin) {
   QSqlQuery query;
   query.prepare("DELETE FROM TABLE1 WHERE CIN = :cin");
   query.bindValue(":cin", cin);
   if (!query.exec()) {
       qDebug() << "Delete failed: " << query.lastError().text();  // Detailed error message
       return false;
   }
   return true;
}



QSqlQueryModel* Artiste::rechercher(QString lettreOuMot)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QString queryStr = "SELECT CAST(CIN AS VARCHAR(255)), CAST(TEL AS VARCHAR(255)), NOM, PRENOM, ADRESSE, MAIL, DOMAINE, DESCRIPTION, SEXE, IMAGE FROM TABLE1";

    // Construire la clause WHERE pour rechercher la lettre ou le mot dans le nom, le prénom ou le mail
    QString whereClause = "";
    if (!lettreOuMot.isEmpty()) {
        whereClause += " WHERE (NOM LIKE '%" + lettreOuMot + "%' OR PRENOM LIKE '%" + lettreOuMot + "%' OR MAIL LIKE '%" + lettreOuMot + "%')";
    }

    // Ajouter la clause WHERE à la requête si des conditions ont été ajoutées
    if (!whereClause.isEmpty()) {
        queryStr += whereClause;
    }

    model->setQuery(queryStr);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TEL"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("MAIL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("DOMAINE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("SEXE"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("IMAGE"));
    return model;
}




bool Artiste::modifier(int cin, int tel, QString nom, QString prenom, QString adresse, QString mail, QString domaine, QString description, QString sexe, QByteArray image)
{
   QSqlQuery query;
   query.prepare("UPDATE TABLE1 SET TEL=:tel, NOM=:nom, PRENOM=:prenom, ADRESSE=:adresse, MAIL=:mail, DOMAINE=:domaine, DESCRIPTION=:description, SEXE=:sexe, IMAGE=:image WHERE CIN=:cin ");
   query.bindValue(":cin", cin);
   query.bindValue(":tel", tel);
   query.bindValue(":nom", nom);
   query.bindValue(":prenom", prenom);
   query.bindValue(":adresse", adresse);
   query.bindValue(":mail", mail);
   query.bindValue(":domaine", domaine);
   query.bindValue(":description", description);
   query.bindValue(":sexe", sexe);
   query.bindValue(":image", image);
   return query.exec();
}





//----------------------   TRIE    --------------------------------------



QSqlQueryModel* Artiste::afficher_tri_cin_descendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CAST(CIN AS VARCHAR(255)), CAST(TEL AS VARCHAR(255)), NOM, PRENOM, ADRESSE, MAIL, DOMAINE, DESCRIPTION, SEXE, IMAGE FROM TABLE1 ORDER BY CIN DESC");
    return model;
}


QSqlQueryModel* Artiste::afficher_tri_cin_ascendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CAST(CIN AS VARCHAR(255)), CAST(TEL AS VARCHAR(255)), NOM, PRENOM, ADRESSE, MAIL, DOMAINE, DESCRIPTION, SEXE, IMAGE  FROM TABLE1 ORDER BY CIN ASC");
    return model;
}


QSqlQueryModel* Artiste::afficher_tri_nom_descendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CAST(CIN AS VARCHAR(255)), CAST(TEL AS VARCHAR(255)), NOM, PRENOM, ADRESSE, MAIL, DOMAINE, DESCRIPTION, SEXE, IMAGE  FROM TABLE1 ORDER BY NOM DESC");
    return model;
}


QSqlQueryModel* Artiste::afficher_tri_nom_ascendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CAST(CIN AS VARCHAR(255)), CAST(TEL AS VARCHAR(255)), NOM, PRENOM, ADRESSE, MAIL, DOMAINE, DESCRIPTION, SEXE, IMAGE  FROM TABLE1 ORDER BY NOM ASC");
    return model;
}



QSqlQueryModel* Artiste::afficher_tri_tel_descendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CAST(CIN AS VARCHAR(255)), CAST(TEL AS VARCHAR(255)), NOM, PRENOM, ADRESSE, MAIL, DOMAINE, DESCRIPTION, SEXE, IMAGE  FROM TABLE1 ORDER BY TEL DESC");
    return model;
}


QSqlQueryModel* Artiste::afficher_tri_tel_ascendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CAST(CIN AS VARCHAR(255)), CAST(TEL AS VARCHAR(255)), NOM, PRENOM, ADRESSE, MAIL, DOMAINE, DESCRIPTION, SEXE, IMAGE  FROM TABLE1 ORDER BY TEL ASC");
    return model;
}



QSqlQueryModel* Artiste::afficher_tri_prenom_descendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CAST(CIN AS VARCHAR(255)), CAST(TEL AS VARCHAR(255)), NOM, PRENOM, ADRESSE, MAIL, DOMAINE, DESCRIPTION, SEXE, IMAGE  FROM TABLE1 ORDER BY PRENOM DESC");
    return model;
}


QSqlQueryModel* Artiste::afficher_tri_prenom_ascendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CAST(CIN AS VARCHAR(255)), CAST(TEL AS VARCHAR(255)), NOM, PRENOM, ADRESSE, MAIL, DOMAINE, DESCRIPTION, SEXE, IMAGE  FROM TABLE1 ORDER BY PRENOM ASC");
    return model;
}


QSqlQueryModel* Artiste::afficher_tri_adresse_descendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CAST(CIN AS VARCHAR(255)), CAST(TEL AS VARCHAR(255)), NOM, PRENOM, ADRESSE, MAIL, DOMAINE, DESCRIPTION, SEXE, IMAGE  FROM TABLE1 ORDER BY ADRESSE DESC");
    return model;
}


QSqlQueryModel* Artiste::afficher_tri_adresse_ascendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CAST(CIN AS VARCHAR(255)), CAST(TEL AS VARCHAR(255)), NOM, PRENOM, ADRESSE, MAIL, DOMAINE, DESCRIPTION, SEXE, IMAGE  FROM TABLE1 ORDER BY ADRESSE ASC");
    return model;
}



QSqlQueryModel* Artiste::afficher_tri_email_descendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CAST(CIN AS VARCHAR(255)), CAST(TEL AS VARCHAR(255)), NOM, PRENOM, ADRESSE, MAIL, DOMAINE, DESCRIPTION, SEXE, IMAGE  FROM TABLE1 ORDER BY MAIL DESC");
    return model;
}


QSqlQueryModel* Artiste::afficher_tri_email_ascendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CAST(CIN AS VARCHAR(255)), CAST(TEL AS VARCHAR(255)), NOM, PRENOM, ADRESSE, MAIL, DOMAINE, DESCRIPTION, SEXE, IMAGE  FROM TABLE1 ORDER BY MAIL ASC");
    return model;
}



QSqlQueryModel* Artiste::afficher_tri_domaine_descendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CAST(CIN AS VARCHAR(255)), CAST(TEL AS VARCHAR(255)), NOM, PRENOM, ADRESSE, MAIL, DOMAINE, DESCRIPTION, SEXE, IMAGE  FROM TABLE1 ORDER BY DOMAINE DESC");
    return model;
}


QSqlQueryModel* Artiste::afficher_tri_domaine_ascendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CAST(CIN AS VARCHAR(255)), CAST(TEL AS VARCHAR(255)), NOM, PRENOM, ADRESSE, MAIL, DOMAINE, DESCRIPTION, SEXE, IMAGE  FROM TABLE1 ORDER BY DOMAINE ASC");
    return model;
}





// fonction pour obteni tout les artistes

QStringList Artiste::obtenirTousArtistes()
{
    QStringList artistes;
    QSqlQuery query;
    query.prepare("SELECT NOM FROM TABLE1"); // Remplacez TABLE1 par le nom de votre table d'artistes
    if(query.exec())
    {
        while(query.next())
        {
            QString nomArtiste = query.value(0).toString();
            artistes.append(nomArtiste);
        }
    }
    return artistes;
}














//***********************************************************************************************************************************************************************************************************************************


/*
********************************************************************
*/

//                                            Partie Artist


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


/*void MainWindow::on_arsupp_2_clicked()
{
    a.supprimer(ui->arcin_5->text().toInt());
    ui->artableView->setModel(a.afficher());
    ui->artableView_2->setModel(a.afficher());
    ui->artableView_3->setModel(a.afficher());
    ui->stackedWidgetArtist->setCurrentIndex(0);

}

*/

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
    process.start("python", QStringList() << "C:/Users/Emna Nkhili/Downloads/CIN.py" << imagePath);
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
    process.start("python", QStringList() << "C:/Users/Emna Nkhili/Downloads/CIN.py" << imagePath);
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
    QString pythonScriptPath = "C:/Users/Emna Nkhili/Downloads/yassine.py";

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
            ui->StackedWidget->setCurrentIndex(3);
            ui->stackedWidgetArtist->setCurrentIndex(1);
        }
        if (result.contains("pageModifierRequested")) {
            // Passer à la page ajout
            ui->StackedWidget->setCurrentIndex(3);
            ui->stackedWidgetArtist->setCurrentIndex(2);
        }
        if (result.contains("pageSupprimerRequested")) {
            // Passer à la page ajout
            ui->StackedWidget->setCurrentIndex(3);
            ui->stackedWidgetArtist->setCurrentIndex(3);
        }
        if (result.contains("pageRechercherRequested")) {
            // Passer à la page ajout
            ui->StackedWidget->setCurrentIndex(3);
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
    process.start("python", { "C:/Users/Emna Nkhili/Downloads/scann.py" });
    process.waitForFinished();

    // Afficher les messages de débogage dans la console
    qDebug() << "Sortie standard :" << process.readAllStandardOutput();
    qDebug() << "Erreurs standard :" << process.readAllStandardError();

    QString output = process.readAllStandardOutput();
    ui->arcin->setText(output);
}

void MainWindow::on_scann_2_clicked()
{

        QProcess process;
        process.start("python", { "C:/Users/Emna Nkhili/Downloads/scann.py" });
        process.waitForFinished();
        QString output = process.readAllStandardOutput();
       ui->arnom->setText(output);

}


void MainWindow::on_scann_3_clicked()
{

        QProcess process;
        process.start("python", { "C:/Users/Emna Nkhili/Downloads/scann.py" });
        process.waitForFinished();
        QString output = process.readAllStandardOutput();
       ui->arprenom->setText(output);

}


void MainWindow::on_scann_4_clicked()
{

        QProcess process;
        process.start("python", { "C:/Users/Emna Nkhili/Downloads/scann.py" });
        process.waitForFinished();
        QString output = process.readAllStandardOutput();
       ui->aradresse->setText(output);

}


void MainWindow::on_scann_5_clicked()
{

        QProcess process;
        process.start("python", { "C:/Users/Emna Nkhili/Downloads/scann.py" });
        process.waitForFinished();
        QString output = process.readAllStandardOutput();
       ui->artelephone->setText(output);

}


void MainWindow::on_scann_6_clicked()
{

        QProcess process;
        process.start("python", { "C:/Users/Emna Nkhili/Downloads/scann.py" });
        process.waitForFinished();
        QString output = process.readAllStandardOutput();
       ui->ardomaine->setText(output);

}


void MainWindow::on_scann_7_clicked()
{

        QProcess process;
        process.start("python", { "C:/Users/Emna Nkhili/Downloads/scann.py" });
        process.waitForFinished();
        QString output = process.readAllStandardOutput();
       ui->armail->setText(output);

}


void MainWindow::on_scann_8_clicked()
{

        QProcess process;
        process.start("python", { "C:/Users/Emna Nkhili/Downloads/scann.py" });
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
















































