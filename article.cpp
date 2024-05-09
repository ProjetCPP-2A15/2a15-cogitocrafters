#include "article.h"
#include <QSqlQuery>
#include <QDebug>
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
#include <QPrinter>
#include <QPainter>
#include <QMovie>
#include <cstdlib>
#include <ctime>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QSqlQuery>
#include <QFont>

#include <QInputDialog>
#include <QMovie>

Article::Article(QString domaine_article, QString nom_article, QString date_creation_article, QString type_article, QString dimension_article, int poids_article, int prix_article, QString description_article, QString chemin_image,int idArtiste,int idVisiteur,int nbvu)
{
    this->domaine_article = domaine_article;
    this->nom_article = nom_article;
    this->date_creation_article = date_creation_article;
    this->type_article = type_article;
    this->dimension_article = dimension_article;
    this->poids_article = poids_article;
    this->prix_article = prix_article;
    this->description_article = description_article;
    this->chemin_image = chemin_image;
    this->id_artiste = idArtiste;
    this->id_visiteur = idVisiteur;
    this->nbvu = nbvu;



}

bool Article::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO ARTICLE (domaine_article, nom_article, date_creation_article, type_article, dimension_article, poids_article, prix_article, description_article, chemin_image,id_artiste,id_visiteur,nbvu) "
                          "VALUES (:domaine_article, :nom_article, :date_creation_article, :type_article, :dimension_article, :poids_article, :prix_article, :description_article, :chemin_image,:id_artiste,:id_visiteur,:nbvu)");
    query.bindValue(":domaine_article", domaine_article);
    query.bindValue(":nom_article", nom_article);
    query.bindValue(":date_creation_article", date_creation_article);
    query.bindValue(":type_article", type_article);
    query.bindValue(":dimension_article", dimension_article);
    query.bindValue(":poids_article", poids_article);
    query.bindValue(":prix_article", prix_article);
    query.bindValue(":description_article", description_article);
    query.bindValue(":chemin_image", chemin_image); // Lié au champ d'image
    query.bindValue(":id_artiste", id_artiste);
    query.bindValue(":id_visiteur", id_visiteur);
    query.bindValue(":nbvu", nbvu);




    return query.exec();
}

QSqlQueryModel * Article::afficher()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from ARTICLE");
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Domaine"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de création"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Dimension"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Poids"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Description"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("gfb"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("image"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("id_artiste"));
    model->setHeaderData(12, Qt::Horizontal, QObject::tr("id_visiteur"));
    model->setHeaderData(12, Qt::Horizontal, QObject::tr("nbvu"));


    return model;
}

bool Article::supprimer(int id_article)
{
    QSqlQuery query;
    query.prepare("DELETE FROM ARTICLE WHERE id_article = :id_article");
    query.bindValue(":id_article", id_article);
    if (!query.exec()) {
        qDebug() << "Delete failed: " ; // Detailed error message
        return false;
    }
    return true;
}

QSqlQueryModel* Article::rechercher(QString nom)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ARTICLE WHERE nom_article LIKE '%" + nom + "%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Domaine"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de création"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Dimension"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Poids"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Description"));
    return model;
}

bool Article::modifier(int id_article, const QString &domaine, const QString &nom, const QString &date_creation, const QString &type, const QString &dimension, int poids, int prix, const QString &description, const QString &chemin_image, int idArtiste,int idVisiteur,int nbvu) {
    QSqlQuery query;
    query.prepare("UPDATE ARTICLE SET domaine_article = :domaine, nom_article = :nom, date_creation_article = :date_creation, type_article = :type, dimension_article = :dimension, poids_article = :poids, prix_article = :prix, description_article = :description, chemin_image = :chemin_image , id_artiste = :id_artiste ,id_visiteur = :id_visiteur,nbvu =:nbvu WHERE id_article = :id_article");
    query.bindValue(":id_article", id_article);
    query.bindValue(":domaine", domaine);
    query.bindValue(":nom", nom);
    query.bindValue(":date_creation", date_creation);
    query.bindValue(":type", type);
    query.bindValue(":dimension", dimension);
    query.bindValue(":poids", poids);
    query.bindValue(":prix", prix);
    query.bindValue(":description", description);
    query.bindValue(":chemin_image", chemin_image);
    query.bindValue(":id_artiste", idArtiste);
    query.bindValue(":id_visiteur", idVisiteur);
    query.bindValue(":nbvu", nbvu);



    return query.exec();
}
/*

QSqlQueryModel* Article::afficherTriId() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ARTICLE ORDER BY id_article");
    return model;
}

QSqlQueryModel* Article::afficherTriNom() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ARTICLE ORDER BY nom_article");
    return model;
}

QSqlQueryModel* Article::afficherTriDate() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ARTICLE ORDER BY date_creation_article");
    return model;
}

*/



QSqlQueryModel* Article::afficher_tri_id_descendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ARTICLE ORDER BY id_article DESC");
    return model;
}

QSqlQueryModel* Article::afficher_tri_id_ascendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ARTICLE ORDER BY id_article ASC");
    return model;
}

QSqlQueryModel* Article::afficher_tri_domaine_descendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ARTICLE ORDER BY domaine_article DESC");
    return model;
}

QSqlQueryModel* Article::afficher_tri_domaine_ascendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ARTICLE ORDER BY domaine_article ASC");
    return model;
}

QSqlQueryModel* Article::afficher_tri_nom_descendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ARTICLE ORDER BY nom_article DESC");
    return model;
}

QSqlQueryModel* Article::afficher_tri_nom_ascendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ARTICLE ORDER BY nom_article ASC");
    return model;
}



QSqlQueryModel* Article::afficher_tri_date_creation_descendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ARTICLE ORDER BY date_creation_article DESC");
    return model;
}

QSqlQueryModel* Article::afficher_tri_date_creation_ascendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ARTICLE ORDER BY date_creation_article ASC");
    return model;
}

QSqlQueryModel* Article::afficher_tri_type_descendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ARTICLE ORDER BY type_article DESC");
    return model;
}

QSqlQueryModel* Article::afficher_tri_type_ascendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ARTICLE ORDER BY type_article ASC");
    return model;
}

QSqlQueryModel* Article::afficher_tri_dimension_descendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ARTICLE ORDER BY dimension_article DESC");
    return model;
}

QSqlQueryModel* Article::afficher_tri_dimension_ascendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ARTICLE ORDER BY dimension_article ASC");
    return model;
}

QSqlQueryModel* Article::afficher_tri_poids_descendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ARTICLE ORDER BY poids_article DESC");
    return model;
}

QSqlQueryModel* Article::afficher_tri_poids_ascendant() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ARTICLE ORDER BY poids_article ASC");
    return model;
}




//************************************************************************************************************************************************



//Partie Product


void MainWindow::on_listtoaddpro_clicked()
{
    QSqlQuery query("SELECT cin FROM TABLE1");
           ui->comboBoxIdArtiste->clear();
           while (query.next()) {
               QString cin = query.value(0).toString();
               ui->comboBoxIdArtiste->addItem(cin);
           }
       qDebug() << "Button clicked";
       speech->say("cette page pour ajouter les produits.");
       ui->stackedWidgetProduct->setCurrentIndex(1);

}


void MainWindow::on_pushButtonProduct_clicked()
{
ui->StackedWidget->setCurrentIndex(4);
ui->stackedWidgetProduct->setCurrentIndex(0);

deselectButton(ui->pushButtonEvents);
selectButton(ui->pushButtonProduct);
deselectButton(ui->pushButtonGuest);
deselectButton(ui->pushButtonArtist);
deselectButton(ui->pushButtonAssociation);
//deselectButton(ui->pushButtonSetting);
ui->tableView_17->setModel(article.afficher());
ui->tableView_6->setModel(article.afficher());
}

void MainWindow::on_liste_2_clicked()
{
    ui->stackedWidgetProduct->setCurrentIndex(0);
}

void MainWindow::on_liste_3_clicked()
{
    ui->stackedWidgetProduct->setCurrentIndex(0);
}

void MainWindow::on_liste_4_clicked()
{
    ui->stackedWidgetProduct->setCurrentIndex(0);
}

void MainWindow::on_liste_5_clicked()
{
    ui->stackedWidgetProduct->setCurrentIndex(0);
}
void MainWindow::on_rating_2_clicked()
{
     ui->stackedWidgetProduct->setCurrentIndex(0);
}
void MainWindow::on_liststat_clicked()
{
    ui->stackedWidgetProduct->setCurrentIndex(0);
}
void MainWindow::on_pushButton_14_clicked()
{

   QString filePath = QFileDialog::getOpenFileName(this, tr("Parcourir..."), QDir::homePath(), tr("Images (*.png *.jpg *.bmp)"));
   if (!filePath.isEmpty()) {
       // Charger et afficher l'image
       QImage image(filePath);
       if (!image.isNull()) {
           QPixmap pixmap = QPixmap::fromImage(image);
           ui->imageArticle->setPixmap(pixmap.scaled(ui->imageArticle->size(), Qt::KeepAspectRatio));
           // pour enregistrer le lien dans qlineedit
           ui->imageline->setText(filePath);
       } else {
           // message d'erreur
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
//QString idArtistea = ui->idartiste->text();
QString idArtistea = ui->comboBoxIdArtiste->currentText();



if (domaine.isEmpty() || nom.isEmpty() || date_creation.isEmpty() || type.isEmpty() || dimension.isEmpty() || poidsStr.isEmpty() || prixStr.isEmpty() || description.isEmpty() || imagePath.isEmpty()) {
   qDebug() << "Button clicked";
   speech->say("il faut remplir tous les champs.");
   QMessageBox::critical(this, "Erreur", "Veuillez remplir tous les champs.");
   return;
}

bool poidsConversionOk, prixConversionOk;
int poids = poidsStr.toInt(&poidsConversionOk);
int prix = prixStr.toInt(&prixConversionOk);
int idArtiste = idArtistea.toInt();

if (!poidsConversionOk || !prixConversionOk || poids <= 0 || prix <= 0) {
   qDebug() << "Button clicked";
   speech->say("Veuillez saisir des valeurs numériques valides pour le poids et le prix.");
   QMessageBox::critical(this, "Erreur", "Veuillez saisir des valeurs numériques valides pour le poids et le prix.");
   return;
}

Article article(domaine, nom, date_creation, type, dimension, poids, prix, description, imagePath,idArtiste,1,0);

bool success = article.ajouter();
if (success) {
   updateArtistComboBox();

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
   ui->imageArticle->clear();

   ui->stackedWidgetProduct->setCurrentIndex(0);

   // Rafraîchir la vue pour afficher l'article ajouté
   ui->tableView_6->setModel(article.afficher());
   QMessageBox::information(this, "Succès", "Article ajouté avec succès.");
} else {
   QMessageBox::critical(this, "Erreur", "Échec de l'ajout de l'article.");

}

}




// ###########################"lire description ai #####################################

// laission entre py et c++

void MainWindow::executePythonScript(const QString &scriptPath, const QStringList &arguments) {
// Créer un processus pour exécuter l'interpréteur Python avec le script
QProcess process;

// Spécifier le chemin du script Python et les arguments
process.start("python", QStringList() << scriptPath << arguments);

// Attendre que le processus se termine
process.waitForFinished();

// Afficher la sortie du processus
qDebug() << QString(process.readAllStandardOutput());
}




void MainWindow::on_lireai_clicked()
{

   // Récupérer le contenu de votre QTextBrowser
   QString description = ui->textEdit_description->toPlainText();

   // Spécifier le chemin du script Python et les arguments (si nécessaire)
   QString scriptPath = "C:/Users/meddh/Desktop/noblePalette/noblePalette/audio.py";
   QStringList arguments;
   arguments << description; // Ajouter le contenu du QTextBrowser comme argument

   // Exécuter le script Python
   executePythonScript(scriptPath, arguments);


}










//########################################      MODIFIER ARTICLE     #########################################################################


//----------------- page prncipale -------->>>>>>>>> page de update
void MainWindow::on_updateEmployee_5_clicked()
{
Article article;
ui->stackedWidgetProduct->setCurrentIndex(3);
ui->tableView_17->setModel(article.afficher());
qDebug() << "Button clicked";
}

//-----------remplire les champs par le doubleclick de tableaux de update ---------------------------

void MainWindow::on_tableView_17_doubleClicked(const QModelIndex &index)
{

   if (!index.isValid()) {
       return;
   }

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

//---------------------       click sur le button update      ----------------------------------------------------------------


void MainWindow::on_save_5_clicked()
{
Article article;

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



if (domaine.isEmpty() || nom.isEmpty() || dateCreation.isEmpty() || type.isEmpty() || dimension.isEmpty() || poidsStr.isEmpty() || prixStr.isEmpty() || description.isEmpty() || cheminImage.isEmpty()) {
   qDebug() << "Button clicked";
   QMessageBox::critical(this, "Erreur", "Veuillez remplir tous les champs.");
   return;
}

bool poidsConversionOk, prixConversionOk;
int poids = poidsStr.toInt(&poidsConversionOk);
int prix = prixStr.toInt(&prixConversionOk);
int idArt = idArtt.toInt();

if (!poidsConversionOk || !prixConversionOk || poids <= 0 || prix <= 0) {
   QMessageBox::critical(this, "Erreur", "Veuillez saisir des valeurs numériques valides pour le poids et le prix.");
   return;
}

bool success = article.modifier(idArticle, domaine, nom, dateCreation, type, dimension, poids, prix, description, cheminImage,idArt,1,0);



if (success) {
   qDebug() << "Button clicked";
   ui->stackedWidgetProduct->setCurrentIndex(0);
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
   ui->imageLabel->clear();



   ui->tableView_6->setModel(article.afficher());

   QMessageBox::information(this, "Succès", "Article modifié avec succès.");
} else {

   QMessageBox::critical(this, "Erreur", "Erreur lors de la modification de l'article.");
}
}


// ########################################DOUBLECLICKED AFFICHAGE SIMPLE ###########################################################################


void MainWindow::on_tableView_6_doubleClicked(const QModelIndex &index)
{
int row = index.row();
   idA = ui->tableView_6->model()->index(row, 0).data().toInt();
   qDebug() << "iDa selected: " << idA;

if (!index.isValid()) {
     return;
 }

const int NAME_COLUMN = 1;
const int DOMAIN_COLUMN = 2;
const int CREATION_DATE_COLUMN = 3;
const int TYPE_COLUMN = 4;
const int DIMENSION_COLUMN = 5;
const int WEIGHT_COLUMN = 6;
const int PRICE_COLUMN = 7;
const int DESCRIPTION_COLUMN = 8;
const int IMAGE_PATH_COLUMN = 9;
const int nbvu = 13;



QString domain = index.sibling(index.row(), DOMAIN_COLUMN).data().toString();
QString name = index.sibling(index.row(), NAME_COLUMN).data().toString();
QString creationDate = index.sibling(index.row(), CREATION_DATE_COLUMN).data().toString();
QString type = index.sibling(index.row(), TYPE_COLUMN).data().toString();
QString dimension = index.sibling(index.row(), DIMENSION_COLUMN).data().toString();
int weight = index.sibling(index.row(), WEIGHT_COLUMN).data().toInt();
int price = index.sibling(index.row(), PRICE_COLUMN).data().toInt();
QString description = index.sibling(index.row(), DESCRIPTION_COLUMN).data().toString();
QString imagePath = index.sibling(index.row(), IMAGE_PATH_COLUMN).data().toString();
int nbvuu = index.sibling(index.row(), nbvu).data().toInt();



 ui->stackedWidgetProduct->setCurrentIndex(2);
 qDebug() << "Button clicked";

 ui->lineEdit_nom->setText(name);
 ui->lineEdit_domaine->setText(domain);
 ui->lineEdit_date->setText(creationDate);
 ui->lineEdit_type->setText(type);
 ui->lineEdit_dimension->setText(dimension);
 ui->lineEdit_poids->setText(QString::number(weight));
 ui->lineEdit_prix->setText(QString::number(price));
 ui->textEdit_description->setText(description);
 ui->nbvu->setText(QString::number(nbvuu));

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
connect(process, &QProcess::readyReadStandardOutput, this, &MainWindow::handleChatBotResponse);

connect(process, &QProcess::readyReadStandardError, this, &MainWindow::handlePythonError);

// Spécifier le chemin du script Python et les arguments
QString scriptPath = "C:/Users/meddh/Desktop/noblePalette/noblePalette/chat.py";

// Démarrer le script Python avec le texte de l'utilisateur comme argument
process->start("python", QStringList() << scriptPath << userText);
process->write((userText + "\n").toUtf8());


}

void MainWindow::handlePythonError() {

QString error = QString::fromUtf8(process->readAllStandardError());
qDebug() << "Python error: " << error;
}


void MainWindow::on_envoyer_clicked()
{

QString userText = ui->descriptionInput_3->toPlainText();
ui->textEdit1->append("You: " + userText);
ui->textEdit1->setEnabled(false);



ui->descriptionInput_3->clear();


executePythonChatBot(userText);

}

/*void MainWindow::handlePythonOutput()
{
QString botResponse = process->readAllStandardOutput().trimmed();
ui->textEdit1->append("Bot: " + botResponse);
}
*/
void MainWindow::on_chatbot_clicked()
{
qDebug() << "Button clicked";
ui->stackedWidgetProduct->setCurrentIndex(4);


}

void MainWindow::handleChatBotResponse() {
QProcess *process = qobject_cast<QProcess *>(sender());
if (!process) return;

// Read the output (chatbot's response)
QString botResponse = process->readAllStandardOutput().trimmed();

// Display the response in the QTextEdit widget
ui->textEdit1->append("Bot: " + botResponse);
ui->textEdit1->setEnabled(false);

}

// ################################################ SUPPRIMER ARTICLE ######################################################"

void MainWindow::on_supprimer_25_clicked()
{

qDebug() << "Attempting to delete artist with CIN: " << idA;
   bool success = article.supprimer(idA);
  if (success) {
      qDebug() << "Button clicked";
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


void MainWindow::on_pushButton_2_clicked()
{
qDebug() << "Button clicked";
  ui->stackedWidgetProduct->setCurrentIndex(5);

  // Assurez-vous que la scène est initialisée
  if (ui->graphicsView->scene() == nullptr) {
      ui->graphicsView->setScene(new QGraphicsScene(this));
  }

  // Initialise le générateur de nombres aléatoires avec une graine basée sur le temps actuel
  srand(static_cast<unsigned int>(time(nullptr)));

  QSqlQuery query("SELECT chemin_image, nom_article FROM ARTICLE");
  int x = 20, y = 20; // Coordonnées initiales pour les images avec un espacement de 20 pixels
  int imageCount = 0; // Compteur pour les images
  int imageSize = 200; // Taille cible pour chaque image (200x200 pixels)
  int imagesPerRow = 4; // Nombre d'images par ligne
  int spacing = 20; // Espacement vertical entre les images
  QFont titleFont("Arial", 10, QFont::Bold); // Police pour les titres

  while (query.next()) {
      QString imagePath = query.value(0).toString();
      QString title = query.value(1).toString();

      QPixmap pixmap(imagePath);
      pixmap = pixmap.scaled(imageSize, imageSize, Qt::KeepAspectRatio); // Redimensionner l'image

      QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pixmap);
      item->setPos(x, y);

      // Effet de transition
      QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect();
      item->setGraphicsEffect(opacityEffect);
      QPropertyAnimation *animation = new QPropertyAnimation(opacityEffect, "opacity");
      animation->setDuration(500);
      animation->setStartValue(0);
      animation->setEndValue(1);
      animation->start(QAbstractAnimation::DeleteWhenStopped);

      ui->graphicsView->scene()->addItem(item);

      // Ajouter l'ombre portée à l'image
      QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
      shadow->setBlurRadius(8);
      shadow->setColor(Qt::black);
      shadow->setOffset(2, 2);
      item->setGraphicsEffect(shadow);

      // Ajouter un titre
      QGraphicsTextItem *titleItem = new QGraphicsTextItem(title);
      titleItem->setFont(titleFont);
      titleItem->setDefaultTextColor(Qt::black);
      titleItem->setPos(x, y + imageSize + 10); // Position sous l'image
      ui->graphicsView->scene()->addItem(titleItem);

      // Mise à jour des coordonnées pour la prochaine image
      imageCount++;
      x += imageSize + spacing;
      if (imageCount % imagesPerRow == 0) {
          x = 20; // Réinitialiser x pour une nouvelle ligne
          y += imageSize + spacing + 30; // Passer à la ligne suivante avec un espace supplémentaire pour le titre
      }
  }
}

void MainWindow::on_supprimer_26_clicked()
{
QString fileName = QFileDialog::getSaveFileName(nullptr, "Save PDF", ui->lineEdit_nom->text(), "*.pdf");
  if (fileName.isEmpty()) return;

  QPrinter printer(QPrinter::PrinterResolution);
  printer.setOutputFormat(QPrinter::PdfFormat);
  printer.setPaperSize(QPrinter::A4);
  printer.setOutputFileName(fileName);

  QPainter painter;
  if (!painter.begin(&printer)) {
      QMessageBox::critical(this, "Erreur", "Impossible de générer le PDF.");
      return;
  }

  QFont font = painter.font();
  font.setPointSize(12);
  font.setBold(true);
  painter.setFont(font);
  painter.setPen(Qt::black);

  // Draw border around the page
  painter.drawRect(0, 0, printer.width(), printer.height());

  QPixmap logo("C:/Users/meddh/Desktop/noblePalette/noblePalette/images/logo app.png");
  if (!logo.isNull()) {
      int logoWidth = 200; // Adjust logo width as needed
      int logoHeight = 100; // Adjust logo height as needed
      painter.drawPixmap(printer.width() / 2 - logoWidth / 2, 20, logoWidth, logoHeight, logo);
  }

  // Retrieve information from QLineEdit widgets
  QString noun = ui->lineEdit_nom->text();
  QString domaine = ui->lineEdit_domaine->text();
  QString creationDate = ui->lineEdit_date->text();
  QString weight = ui->lineEdit_poids->text();
  QString dimension = ui->lineEdit_dimension->text();
  QString type = ui->lineEdit_type->text();
  QString price = ui->lineEdit_prix->text();
  QString description = ui->textEdit_description->toPlainText();
  QImage image;
  if (ui->labelImage->pixmap()) {
      image = ui->labelImage->pixmap()->toImage();
  }

  int yOffset = 150;
  painter.drawText(100, yOffset, "Nom: " + noun);
  yOffset += 20;
  painter.drawText(100, yOffset, "Domaine: " + domaine);
  yOffset += 20;
  painter.drawText(100, yOffset, "Date de création: " + creationDate);
  yOffset += 20;
  painter.drawText(100, yOffset, "Poids: " + weight);
  yOffset += 20;
  painter.drawText(100, yOffset, "Dimension: " + dimension);
  yOffset += 20;
  painter.drawText(100, yOffset, "Type: " + type);
  yOffset += 20;
  painter.drawText(100, yOffset, "Prix: " + price);
  yOffset += 20;
  painter.drawText(100, yOffset, "Description: " + description);

  if (!image.isNull()) {
      yOffset += 20;
      painter.drawPixmap(100, yOffset, QPixmap::fromImage(image).scaled(500, 500, Qt::KeepAspectRatio));
      yOffset += 110;
  }

  painter.end();
  QMessageBox::information(nullptr, "Succès", "PDF généré avec succès.");
}







void MainWindow::on_suppgen_clicked()
{
qDebug() << "Button clicked";

ui->stackedWidgetProduct->setCurrentIndex(6);
ui->tableView_4->setModel(article.afficher());


}


void MainWindow::on_tableView_4_doubleClicked(const QModelIndex &index)
{
    int row = index.row();
   int id_article = ui->tableView_4->model()->index(row, 0).data().toInt(); // Récupérer l'ID de l'article
   qDebug() << "ID de l'article sélectionné: " << id_article; // Message de débogage pour confirmer la sélection
}


void MainWindow::on_del_all_clicked()
{
QModelIndexList selectedIndexes = ui->tableView_4->selectionModel()->selectedIndexes();
   if (selectedIndexes.isEmpty()) {
       qDebug() << "Button clicked";
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
       qDebug() << "Button clicked";

       ui->tableView_4->setModel(article.afficher());
       ui->tableView_6->setModel(article.afficher());
       QMessageBox::information(this, "Succès", QString::number((successfulDeletions)/12) + " article(s) supprimé(s) avec succès.");
   } else {
       QMessageBox::critical(this, "Erreur", "Échec de la suppression de l'article sélectionné.");
   }
}


void MainWindow::updateArtistComboBox() {
ui->comboBoxIdArtiste->addItems(artistCINs);
}

void MainWindow::on_supprimer_4_clicked()
{
ui->domaineArticleInput->clear();
ui->nomArticleInput->clear();
ui->quantiteArticleInput->clear();
ui->dimensionArticleInput->clear();
ui->poidsArticleInput->clear();
ui->prixArticleInput->clear();
ui->descriptionInput->clear();
ui->imageline->clear();
ui->imageArticle->clear();
}


void MainWindow::on_supprimer_24_clicked()
{
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
ui->imageLabel->clear();

}

void MainWindow::on_liste_clicked()
{
ui->tableView_6->setModel(article.afficher());

ui->stackedWidgetProduct->setCurrentIndex(0);
}


//##########################################################################################################################
// -------------------------------------------------    TRI      -----------------------------------------------------------

void MainWindow::on_triid1_clicked()
{
qDebug() << "Button clicked";
ui->tableView_6->setModel(article.afficher_tri_id_descendant());


}

void MainWindow::on_triid2_clicked()
{
qDebug() << "Button clicked";
ui->tableView_6->setModel(article.afficher_tri_id_ascendant());

}

void MainWindow::on_triname1_clicked()
{
qDebug() << "Button clicked";
ui->tableView_6->setModel(article.afficher_tri_nom_descendant());

}

void MainWindow::on_triname2_clicked()
{
qDebug() << "Button clicked";
ui->tableView_6->setModel(article.afficher_tri_nom_ascendant());

}

void MainWindow::on_tridomaine1_clicked()
{
qDebug() << "Button clicked";
ui->tableView_6->setModel(article.afficher_tri_domaine_descendant());

}

void MainWindow::on_tridomaine2_clicked()
{
qDebug() << "Button clicked";

ui->tableView_6->setModel(article.afficher_tri_domaine_ascendant());

}

void MainWindow::on_triid1_9_clicked()
{
qDebug() << "Button clicked";
ui->tableView_6->setModel(article.afficher_tri_date_creation_descendant());

}


void MainWindow::on_triid2_4_clicked()
{
qDebug() << "Button clicked";
ui->tableView_6->setModel(article.afficher_tri_date_creation_ascendant());

}


void MainWindow::on_triid1_10_clicked()
{
qDebug() << "Button clicked";
ui->tableView_6->setModel(article.afficher_tri_type_descendant());

}


void MainWindow::on_triid2_5_clicked()
{
qDebug() << "Button clicked";
ui->tableView_6->setModel(article.afficher_tri_type_ascendant());

}



void MainWindow::on_triid1_11_clicked()
{
qDebug() << "Button clicked";
ui->tableView_6->setModel(article.afficher_tri_dimension_descendant());

}


void MainWindow::on_triid2_6_clicked()
{
qDebug() << "Button clicked";
ui->tableView_6->setModel(article.afficher_tri_dimension_ascendant());

}


void MainWindow::on_triid1_12_clicked()
{
qDebug() << "Button clicked";
ui->tableView_6->setModel(article.afficher_tri_poids_descendant());

}

void MainWindow::on_triid2_7_clicked()
{
qDebug() << "Button clicked";
ui->tableView_6->setModel(article.afficher_tri_poids_ascendant());

}





// chatbot ecouter //
void MainWindow::on_start_clicked()
{
// Créer et démarrer un QProcess pour exécuter le script Python de reconnaissance vocale
  process = new QProcess(this);
  QString scriptPath = "C:/Users/meddh/Desktop/noblePalette/noblePalette/script/article/speech_recognition1.py";
  process->start("python", QStringList() << scriptPath);

  connect(process, &QProcess::readyReadStandardOutput, this, &MainWindow::updateLineEditWithVoice);
 // connect(process, &QProcess::finished, process, &QProcess::deleteLater);
}

void MainWindow::updateLineEditWithVoice()
{
QByteArray text = process->readAllStandardOutput();
ui->descriptionInput_3->setText(QString(text).trimmed());
}

void MainWindow::on_rating_clicked()
{
bool ok;
   int rating = QInputDialog::getInt(this, tr("Donner une Note"),
                                     tr("Note:"), 5, 0, 10, 1, &ok);
   if (ok) {
       changeChatIcon(rating);
   }
}
void MainWindow::changeChatIcon(int rating) {
QMovie *movie;
  if (rating <= 5) {
      movie = new QMovie("C:/Users/meddh/Desktop/noblePalette/noblePalette/images/giphy1.gif");
  } else {
      movie = new QMovie("C:/Users/meddh/Desktop/noblePalette/noblePalette/images/tata.gif");
  }
  ui->label_product_3->setMovie(movie);
  movie->start();
}

void MainWindow::on_pub_clicked() {
QAbstractItemModel *model = ui->tableView_6->model();
QStringList imagePaths;

// Collecte uniquement les chemins des images
for (int row = 0; row < model->rowCount(); ++row) {
   QString imagePath = model->index(row, 9).data().toString();
   if (!imagePath.isEmpty() && imagePath != "0") {
       imagePaths << imagePath;
   }

}

// Chemins des fichiers et des ressources
QString inputVideoPath = "C:/Users/meddh/Desktop/noblePalette/noblePalette/script/article/pub/test.mp4";
   QString outputVideoPath = "C:/Users/meddh/Desktop/noblePalette/noblePalette/script/article/pub/output_video.mp4";
   QString scriptPath = "C:/Users/meddh/Desktop/noblePalette/noblePalette/script/article/pub/Pub.py";

// Prépare et lance le script Python
QProcess *process = new QProcess(this);
QStringList arguments;
arguments << inputVideoPath << outputVideoPath << imagePaths.join(","); // Passe uniquement les chemins des images

process->start("python", QStringList() << scriptPath << arguments);

// Débogage
process->waitForFinished(-1);  // -1 signifie attendre indéfiniment
QString scriptOutput = process->readAllStandardOutput();
QString scriptError = process->readAllStandardError();

qDebug() << "Python Output:" << scriptOutput;
qDebug() << "Python Error:" << scriptError;
}
void MainWindow::on_supprimer_32_clicked()
{
    qDebug() << "Button clicked";

       QSqlQueryModel *model = new QSqlQueryModel();
       model->setQuery("SELECT poids_article FROM ARTICLE");

       QMap<QString, int> weightCategories;
       weightCategories["0-500g"] = 0;
       weightCategories["501-1000g"] = 0;
       weightCategories["1001-1500g"] = 0;
       // Ajoutez plus de catégories si nécessaire

       for (int i = 0; i < model->rowCount(); ++i) {
           int weight = model->record(i).value("poids_article").toInt();
           if (weight <= 500) {
               weightCategories["0-500g"]++;
           } else if (weight <= 1000) {
               weightCategories["501-1000g"]++;
           } else if (weight <= 1500) {
               weightCategories["1001-1500g"]++;
           } // Ajoutez plus de conditions pour d'autres catégories
       }

    // Création du pixmap pour dessiner le pie chart
    QSize pixmapSize(581, 371);
    QPixmap pixmap(pixmapSize);
    pixmap.fill(Qt::transparent); // Fond transparent

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    // Variables pour le dessin du pie chart
    QRectF pieRect(10, 10, pixmapSize.width() - 220, pixmapSize.height() - 20);
    qreal startAngle = 0.0;

    // Dessiner chaque tranche du pie chart
    for (auto it = weightCategories.constBegin(); it != weightCategories.constEnd(); ++it) {
        qreal sweepAngle = 360.0 * it.value() / std::accumulate(weightCategories.constBegin(), weightCategories.constEnd(), 0);
        QColor sliceColor = QColor::fromHsv((std::distance(weightCategories.constBegin(), it) * 30) % 360, 100, 200); // Couleur pastel pour chaque tranche
        painter.setBrush(sliceColor); // Définir la couleur de la tranche
        painter.drawPie(pieRect, startAngle * 16, sweepAngle * 16);

        // Dessiner un carré de couleur à côté du pie chart
        QRectF colorRect(pixmapSize.width() - 200, 20 + std::distance(weightCategories.constBegin(), it) * 30, 20, 20); // Position et taille du carré de couleur
        painter.fillRect(colorRect, sliceColor);

        // Afficher la catégorie à côté du carré de couleur
        QString categoryLabel = it.key();
        QPointF categoryPos = colorRect.topRight() + QPointF(30, 15); // Position pour afficher la catégorie à côté du carré de couleur
        painter.drawText(categoryPos, categoryLabel);

        // Calcul du pourcentage
        double percentage = (static_cast<double>(it.value()) / std::accumulate(weightCategories.constBegin(), weightCategories.constEnd(), 0)) * 100;
        QString percentageText = QString::number(percentage, 'f', 1) + "%";

        // Afficher le pourcentage à côté du carré de couleur
        QPointF textPos = colorRect.topRight() + QPointF(130, 15); // Position pour afficher le texte à côté du carré de couleur
        painter.drawText(textPos, percentageText);

        startAngle += sweepAngle;
    }

    painter.end();
    ui->stackedWidgetProduct->setCurrentIndex(7);
    ui->label_statProduct->setPixmap(pixmap);


}



//################################################## vedio languedesigne ##########################################

void MainWindow::on_gerervedio_clicked()
{
QString description = ui->textEdit_description->toPlainText();

 // Création d'un nouveau processus pour exécuter le script Python
     QProcess *process = new QProcess(this);

     // Chemin vers votre script Python
     QString scriptPath = "C:/Users/meddh/Desktop/noblePalette/noblePalette/script/article/vedio1.py";

     // Lancement du script Python avec le texte comme argument
     process->start("python", QStringList() << scriptPath << description);

     // Connecter les signaux pour gérer la sortie standard et les erreurs
     connect(process, &QProcess::readyReadStandardOutput, this, [=]() {
         QString output = process->readAllStandardOutput();
         qDebug() << "Python Output:" << output;
     });

     connect(process, &QProcess::readyReadStandardError, this, [=]() {
         QString error = process->readAllStandardError();
         qDebug() << "Python Error:" << error;
     });

     // Optionnel : gérer la fin du processus
     connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
             [=](int exitCode, QProcess::ExitStatus exitStatus) {
         if (exitStatus == QProcess::CrashExit || exitCode != 0) {
             qDebug() << "Le script Python s'est terminé avec l'erreur.";
         } else {
             qDebug() << "Le script Python s'est terminé avec succès.";
         }
     });

}



void MainWindow::executePythonScript1(const QString &change)
{
    // Spécifiez le chemin du script Python
    QString scriptPath = "C:/Users/meddh/Desktop/noblePalette/noblePalette/script/article/sonB.py";

    // Créez un processus pour exécuter le script Python
    QProcess process;

    // Exécutez le script Python avec l'argument spécifié (up ou down)
    process.start("python", QStringList() << scriptPath << change);

    // Attendre que le processus se termine
    process.waitForFinished();

    // Lisez la sortie standard du processus (si nécessaire)
    qDebug() << QString(process.readAllStandardOutput());
}

void MainWindow::on_up_clicked()
{
    executePythonScript1("up");

}

void MainWindow::on_down_clicked()
{
    executePythonScript1("down");

}
bool Article::updateNbVu(int id_article, int newNbVu) {
    QSqlQuery query;
    query.prepare("UPDATE ARTICLE SET nbvu = :nbvu WHERE id_article = :id");
    query.bindValue(":nbvu", newNbVu);
    query.bindValue(":id", id_article);
    return query.exec();
}































