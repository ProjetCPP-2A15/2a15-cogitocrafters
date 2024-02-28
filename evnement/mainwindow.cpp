#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QDebug>
#include "article.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QProcess>
#include <QDebug>
#include <QtWidgets>
#include <QPrinter>
#include <QPainter>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // ################pour le recherchearticle################################
    connect(ui->searchTextBox_19, &QLineEdit::textChanged, this, &MainWindow::on_searchTextBox_19_textChanged);
    // Connexion du signal currentIndexChanged du comboBoxTri à la méthode de tri appropriée
    connect(ui->comboBox_5, SIGNAL(currentIndexChanged(int)), this, SLOT(trierArticles(int)));



    speech = new QTextToSpeech(this);


}

MainWindow::~MainWindow()
{
    delete ui;
    delete speech;

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

void MainWindow::on_supprimer_35_clicked()
{
    ui->stackedWidgetGuest->setCurrentIndex(1);

}

void MainWindow::on_listtoaddass_clicked()
{
    ui->stackedWidgetAssociation->setCurrentIndex(1);

}

void MainWindow::on_listtoaddpro_clicked()
{   qDebug() << "Button clicked";
    speech->say("Tu es dans la page d'ajout.");
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



void MainWindow::on_updateEmployee_4_clicked()
{
    ui->stackedWidgetEvent->setCurrentIndex(1);

}

void MainWindow::on_updateEmployee_2_clicked()
{
    ui->stackedWidgetGuest->setCurrentIndex(2);

}



void MainWindow::on_save_7_clicked()
{
    ui->stackedWidgetEvent->setCurrentIndex(0);

}

void MainWindow::on_save_6_clicked()
{
    ui->stackedWidgetGuest->setCurrentIndex(3);

}

// ########################################## ARTICLE##########################################################################
//#########################################################################################################################

//########################################AJOUTER ARTICLE #########################################################################

void MainWindow::on_updateEmployee_3_clicked()
{
    Article article;
    ui->stackedWidgetProduct->setCurrentIndex(3);
    ui->tableView_17->setModel(article.afficher());



}



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


    // Récupération des valeurs saisies par l'utilisateur à partir des champs de votre formulaire
    QString domaine = ui->domaineArticleInput->text();
    QString nom = ui->nomArticleInput->text();
    QString date_creation = ui->dateEdit->text();
    QString type = ui->quantiteArticleInput->text();
    QString dimension = ui->dimensionArticleInput->text();
    QString poidsStr = ui->poidsArticleInput->text();
    QString prixStr = ui->prixArticleInput->text();
    QString description = ui->descriptionInput->toPlainText();
    QString imagePath = ui->imageline->text();

    // Vérification des champs obligatoires
    if (domaine.isEmpty() || nom.isEmpty() || date_creation.isEmpty() || type.isEmpty() || dimension.isEmpty() || poidsStr.isEmpty() || prixStr.isEmpty() || description.isEmpty() || imagePath.isEmpty()) {
        QMessageBox::critical(this, "Erreur", "Veuillez remplir tous les champs.");
        return;
    }

    // Vérification de la validité des données numériques
    bool poidsConversionOk, prixConversionOk;
    int poids = poidsStr.toInt(&poidsConversionOk);
    int prix = prixStr.toInt(&prixConversionOk);

    if (!poidsConversionOk || !prixConversionOk || poids <= 0 || prix <= 0) {
        QMessageBox::critical(this, "Erreur", "Veuillez saisir des valeurs numériques valides pour le poids et le prix.");
        return;
    }

    // Création de l'objet Article avec les valeurs récupérées
    Article article(domaine, nom, date_creation, type, dimension, poids, prix, description, imagePath);

    // Appel de la méthode d'ajout d'article de votre classe Article
    bool success = article.ajouter();
    if (success) {
        qDebug() << "Button clicked";
        speech->say("le produit a ete ajouter.");
        // Effacer les champs de saisie après un ajout réussi
        ui->domaineArticleInput->clear();
        ui->nomArticleInput->clear();
        ui->quantiteArticleInput->clear();
        ui->dimensionArticleInput->clear();
        ui->poidsArticleInput->clear();
        ui->prixArticleInput->clear();
        ui->descriptionInput->clear();
        ui->imageline->clear();

        ui->stackedWidgetProduct->setCurrentIndex(0);

        // Rafraîchir la vue pour afficher l'article ajouté
        ui->tableView_6->setModel(article.afficher());
        QMessageBox::information(this, "Succès", "Article ajouté avec succès.");
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout de l'article.");

    }

}


// ###########################"lire description ai #####################################
void MainWindow::executePythonScript(const QString &scriptPath, const QStringList &arguments) {
    // Créer un processus pour exécuter l'interpréteur Python avec le script
    QProcess process;

    // Spécifier le chemin du script Python et les arguments
    process.start("python", QStringList() << scriptPath << arguments);

    // Attendre que le processus se termine
    process.waitForFinished();

    // Afficher la sortie du processus (si nécessaire)
    qDebug() << QString(process.readAllStandardOutput());
}




void MainWindow::on_lireai_clicked()
{

        // Récupérer le contenu de votre QTextBrowser
        QString description = ui->textEdit_description->toPlainText();

        // Spécifier le chemin du script Python et les arguments (si nécessaire)
        QString scriptPath = "C:\\Users\\asus\\Desktop\\jdid\\evnement\\audio.py";
        QStringList arguments;
        arguments << description; // Ajouter le contenu du QTextBrowser comme argument

        // Exécuter le script Python
        executePythonScript(scriptPath, arguments);


}

//########################################MODIFIER ARTICLE #########################################################################


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


        // Chargez et affichez l'image de l'article
        QPixmap image(imagePath);
        if (!image.isNull()) {
            ui->imageLabel->setPixmap(image.scaled(ui->imageLabel->size(), Qt::KeepAspectRatio));
        } else {
          QMessageBox::warning(this, "Erreur", "Impossible de charger l'image : " + imagePath);
        }

        // Maintenant, l'utilisateur peut modifier les données dans les champs de texte.


}
void MainWindow::on_updateEmployee_5_clicked()
{
    Article article;
    ui->stackedWidgetProduct->setCurrentIndex(3);
    ui->tableView_17->setModel(article.afficher());
    qDebug() << "Button clicked";
    speech->say("page de mise a jour des articles.");
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

    // Vérification des champs obligatoires
    if (domaine.isEmpty() || nom.isEmpty() || dateCreation.isEmpty() || type.isEmpty() || dimension.isEmpty() || poidsStr.isEmpty() || prixStr.isEmpty() || description.isEmpty() || cheminImage.isEmpty()) {
        QMessageBox::critical(this, "Erreur", "Veuillez remplir tous les champs.");
        return;
    }

    // Vérification de la validité des données numériques
    bool poidsConversionOk, prixConversionOk;
    int poids = poidsStr.toInt(&poidsConversionOk);
    int prix = prixStr.toInt(&prixConversionOk);

    if (!poidsConversionOk || !prixConversionOk || poids <= 0 || prix <= 0) {
        QMessageBox::critical(this, "Erreur", "Veuillez saisir des valeurs numériques valides pour le poids et le prix.");
        return;
    }

    // Appeler la méthode de modification de la classe Article
    bool success = article.modifier(idArticle, domaine, nom, dateCreation, type, dimension, poids, prix, description, cheminImage);
    qDebug() << "Button clicked";
    speech->say("le produit a ete modifier.");
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

    // Réinitialiser la sélection de l'image si nécessaire
    // ui->imageLabel->clear(); // Si vous affichez également l'image, réinitialisez-la

    // Actualiser le modèle de votre QTableView pour afficher les modifications
    ui->tableView_6->setModel(article.afficher());

    if (success) {
        QMessageBox::information(this, "Succès", "Article modifié avec succès.");
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la modification de l'article.");
    }
}


// ########################################DOUBLECLICKED AFFICHAGE SIMPLE ###########################################################################
void MainWindow::on_tableView_6_doubleClicked(const QModelIndex &index)
{
    int row = index.row();
        idA = ui->tableView_6->model()->index(row, 0).data().toInt(); // Store the CIN in the member variable
        qDebug() << "iDa selected: " << idA; // Debug message to confirm CIN is selected

    if (!index.isValid()) {
          // Handle the invalid index if necessary
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
      qDebug() << "Button clicked";
      speech->say("affichage simple d article.");
      // Set the text of the QLineEdit widgets with the retrieved data

      ui->lineEdit_nom->setText(name);
      ui->lineEdit_domaine->setText(domain);
      ui->lineEdit_date->setText(creationDate);
      ui->lineEdit_type->setText(type);
      ui->lineEdit_dimension->setText(dimension);
      ui->lineEdit_poids->setText(QString::number(weight));
      ui->lineEdit_prix->setText(QString::number(price));
      ui->textEdit_description->setText(description);
      QPixmap image(imagePath);
              if (!image.isNull()) {
                  ui->labelImage->setPixmap(image.scaled(ui->labelImage->size(), Qt::KeepAspectRatio));
              } else {
                  QMessageBox::warning(this, "Erreur", "Impossible de charger l'image : " + imagePath);
              }
                 ui->lineEdit_nom->setEnabled(false);
                 ui->lineEdit_domaine->setEnabled(false);
                 ui->lineEdit_date->setEnabled(false);
                 ui->lineEdit_type->setEnabled(false);
                 ui->lineEdit_dimension->setEnabled(false);
                 ui->lineEdit_poids->setEnabled(false);
                 ui->lineEdit_prix->setEnabled(false);
                 ui->textEdit_description->setEnabled(false);

}
// ################################################ chat######################################################"
void MainWindow::executePythonChatBot(const QString &userText) {
    QProcess *process = new QProcess(this);
    connect(process, &QProcess::readyReadStandardOutput, this, &MainWindow::handlePythonOutput);
    connect(process, &QProcess::readyReadStandardError, this, &MainWindow::handlePythonError);
    // Spécifier le chemin du script Python et les arguments
    QString scriptPath = "C:\\Users\\asus\\Desktop\\jdid\\evnement\\chat.py";

    // Démarrer le script Python avec le texte de l'utilisateur comme argument
    process->start("python", QStringList() << scriptPath << userText);
    process->write((userText + "\n").toUtf8());

}

void MainWindow::handlePythonOutput() {
        QString output = QString::fromUtf8(process->readAllStandardOutput());

        QTextCursor cursor(ui->textEdit1->textCursor());
        cursor.insertHtml("<font color=\"black\">Bot: " + output + "</font>");
        ui->textEdit1->setTextCursor(cursor);



}

void MainWindow::handlePythonError() {
    QString error = QString::fromUtf8(process->readAllStandardError());
    qDebug() << "Python error: " << error;
}

void MainWindow::on_envoyer_clicked()
{
    QString userText = ui->descriptionInput_3->toPlainText();
    ui->textEdit1->append("You: " + userText);
    ui->descriptionInput_3->clear();

    executePythonChatBot(userText);
}

void MainWindow::on_chatbot_clicked()
{
    qDebug() << "Button clicked";
    speech->say("donner moi des questions sur les produits je suis un bot.");
    ui->stackedWidgetProduct->setCurrentIndex(4);


}
// ################################################ SUPPRIMER ARTICLE ######################################################"

void MainWindow::on_supprimer_25_clicked()
{

    qDebug() << "Attempting to delete artist with CIN: " << idA;
        bool success = article.supprimer(idA);
       if (success) {
           qDebug() << "Button clicked";
           speech->say("le produit a ete supprimer.");
           ui->tableView_6->setModel(article.afficher());

           QMessageBox::information(this, "Success", "Article deleted successfully.");
           ui->stackedWidgetProduct->setCurrentIndex(0);
       } else {
           QMessageBox::critical(this, "Error", "Failed to delete article.");
      }
}
// ################################################ RECHERCHER ARTICLE ######################################################"

void MainWindow::on_searchTextBox_19_textChanged(const QString &arg1)
{
    QString searchQuery = "%" + arg1 + "%";
       QSqlQueryModel* filteredModel = article.rechercher(searchQuery);
       ui->tableView_6->setModel(filteredModel);
}

void MainWindow::on_comboBox_5_activated(int index)
{
    switch(index) {
            case 1: // Tri par ID
                ui->tableView_6->setModel(article.afficherTriId());
                break;
            case 2: // Tri par nom
                ui->tableView_6->setModel(article.afficherTriNom());
                break;
            case 3: // Tri par date de création
                ui->tableView_6->setModel(article.afficherTriDate());
                break;
            default:
                break;
        }
}



void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidgetProduct->setCurrentIndex(5);

        // Assurez-vous que la scène est initialisée
        if (ui->graphicsView->scene() == nullptr) {
            ui->graphicsView->setScene(new QGraphicsScene(this));
        }

        QSqlQuery query("SELECT chemin_image FROM ARTICLE");
        int x = 0, y = 0; // Coordonnées initiales pour les images
        int imageCount = 0; // Compteur pour les images
        int imageSize = 200; // Taille cible pour chaque image (100x100 pixels)
        int imagesPerRow = 4; // Nombre d'images par ligne

        while (query.next()) {
            QString imagePath = query.value(0).toString();
            QPixmap pixmap(imagePath);
            pixmap = pixmap.scaled(imageSize, imageSize, Qt::KeepAspectRatio); // Redimensionner l'image

            QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pixmap);
            item->setPos(x, y);

            ui->graphicsView->scene()->addItem(item);

            // Mise à jour des coordonnées pour la prochaine image
            imageCount++;
            x += imageSize;
            if (imageCount % imagesPerRow == 0) {
                x = 0; // Réinitialiser x à 0 pour une nouvelle ligne
                y += imageSize+10; // Passer à la ligne suivante
            }
        }
}

void MainWindow::on_supprimer_26_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save PDF", QString(), "*.pdf");

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
        //additionalInfo << "CIN : " << ui->label_affPhone->text();
        additionalInfo << "Full Name : ";
        additionalInfo << "Information 3";

        int yOffset = 120;
        foreach(const QString &info, additionalInfo) {
            painter.drawText(120, yOffset, info);
            yOffset += 20;
        }

        painter.end();
}
