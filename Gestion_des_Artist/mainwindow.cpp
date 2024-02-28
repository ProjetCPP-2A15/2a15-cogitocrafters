#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "artist.h"
#include <QSqlQuery>
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

//                                            Partie Event
void MainWindow::on_pushButtonEvents_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

//                                            Partie Product
void MainWindow::on_pushButtonProduct_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

//                                            Partie Guest
void MainWindow::on_pushButtonGuest_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

//                                            Partie Artist
void MainWindow::on_pushButtonArtist_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->tableView_2->setModel(a.afficher());
}

//                                            Partie Association
void MainWindow::on_pushButtonAssociation_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

//                                            Partie Setting
void MainWindow::on_pushButtonSetting_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}







//partie artist

void MainWindow::selectedPushButton(QPushButton *button)
{
    button->setStyleSheet("QPushButton{background:#333333;border: none;border-left:6px solid #1E90FF;margin: 0px;padding: 0px;color:white;text-align: left;padding-left:24px;}");
}

void MainWindow::deselectedPushButton(QPushButton *button)
{
    button->setStyleSheet("QPushButton{ background:#1F1F1F; border: none; margin: 0px; padding: 0px; border-left:6px solid #1F1F1F; color:white; text-align: left;padding-left:24px;} QPushButton:hover{background:#333333;border: none;border-left:6px solid #333333;margin: 0px;padding: 0px;color:white;text-align: left;padding-left:24px;}");
}

void MainWindow::on_addEmpButton_clicked()
{
    selectedPushButton(ui->addEmpButton);
    deselectedPushButton(ui->deleteEmpButton);
    deselectedPushButton(ui->updateEmpButton);
    deselectedPushButton(ui->searchButton);

    ui->stackedWidgetArtist->setCurrentIndex(1);
}


void MainWindow::on_searchButton_clicked()
{


    selectedPushButton(ui->searchButton);
    deselectedPushButton(ui->deleteEmpButton);
    deselectedPushButton(ui->updateEmpButton);
    deselectedPushButton(ui->addEmpButton);
    ui->stackedWidgetArtist->setCurrentIndex(0);
    ui->tableView_2->setModel(a.afficher());
}


void MainWindow::on_updateEmpButton_clicked()
{
    selectedPushButton(ui->updateEmpButton);
    deselectedPushButton(ui->deleteEmpButton);
    deselectedPushButton(ui->searchButton);
    deselectedPushButton(ui->addEmpButton);
    ui->stackedWidgetArtist->setCurrentIndex(2);
    ui->updateTableView_2->setModel(a.affichers());
}


void MainWindow::on_deleteEmpButton_clicked()
{
    selectedPushButton(ui->deleteEmpButton);
    deselectedPushButton(ui->updateEmpButton);
    deselectedPushButton(ui->searchButton);
    deselectedPushButton(ui->addEmpButton);
    ui->stackedWidgetArtist->setCurrentIndex(3);
    ui->tableView_6->setModel(a.afficher());
}





void MainWindow::on_pushButton_5_clicked()
{
    QString cinStr = ui->cin->text();
    QString telStr = ui->telephone->text();
    QString nom = ui->nom_2->text();

    // Vérifie que les champs obligatoires ne sont pas vides
    if (cinStr.isEmpty() || telStr.isEmpty() || nom.isEmpty() || !ui->mail->text().contains("@")) {
        QMessageBox::critical(nullptr, QObject::tr("Champs obligatoires vides ou mail invalide"),
                              QObject::tr("Les champs CIN, Téléphone, Nom et Mail sont obligatoires et le mail doit contenir '@'.\n"
                                          "Veuillez remplir tous les champs obligatoires."), QMessageBox::Ok);
        return;
    }

    // Vérifie que la CIN est unique
    int cin = cinStr.toInt();
    QString cinQuery = "SELECT COUNT(*) FROM TABLE1 WHERE cin = :cin";
    QSqlQuery query;
    query.prepare(cinQuery);
    query.bindValue(":cin", cin);
    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        if (count > 0) {
            QMessageBox::critical(nullptr, QObject::tr("CIN déjà utilisé"),
                                  QObject::tr("Le numéro CIN spécifié est déjà utilisé par un autre artiste.\n"
                                              "Veuillez saisir un numéro CIN unique."), QMessageBox::Ok);
            return;
        }
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Erreur de base de données"),
                              QObject::tr("Erreur lors de la vérification du CIN.\n"
                                          "Veuillez réessayer."), QMessageBox::Ok);
        return;
    }

    // Vérifie que le téléphone est un nombre
    int tel = telStr.toInt();
    if (tel == 0) {
        QMessageBox::critical(nullptr, QObject::tr("Numéro de téléphone invalide"),
                              QObject::tr("Le numéro de téléphone doit être un nombre valide.\n"
                                          "Veuillez saisir un numéro de téléphone valide."), QMessageBox::Ok);
        return;
    }

    // Vérifier les autres champs
    if (ui->prenom->text().isEmpty() || ui->adresse->text().isEmpty() || ui->domaine->text().isEmpty() || ui->description->text().isEmpty() || ui->sexe->currentText().isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Champs obligatoires vides"),
                              QObject::tr("Les champs Prénom, Adresse, Domaine, Description et Sexe sont obligatoires.\n"
                                          "Veuillez remplir tous les champs obligatoires."), QMessageBox::Ok);
        return;
    }

    // Tous les contrôles de saisie sont valides, ajouter l'artiste
    Artiste a(cin, tel, nom, ui->prenom->text(), ui->adresse->text(), ui->mail->text(), ui->domaine->text(), ui->description->text(), ui->sexe->currentText());

    bool test = a.ajouter();
    if (test)
    {
        // Efface les champs de saisie après l'ajout réussi
        ui->cin->clear();
        ui->telephone->clear();
        ui->nom_2->clear();
        ui->prenom->clear();
        ui->adresse->clear();
        ui->mail->clear();
        ui->domaine->clear();
        ui->description->clear();
        ui->sexe->setCurrentIndex(0); // Réinitialise la sélection du sexe

        ui->stackedWidgetArtist->setCurrentIndex(0);
        ui->tableView_2->setModel(a.afficher());
        ui->tableView_6->setModel(a.afficher());
        ui->updateTableView_2->setModel(a.affichers());
        QMessageBox::information(nullptr, QObject::tr("Ajout réussi"),
                                 QObject::tr("Artiste ajouté avec succès."), QMessageBox::Ok);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Erreur lors de l'ajout"),
                              QObject::tr("Erreur lors de l'ajout de l'artiste.\n"
                                          "Veuillez réessayer."), QMessageBox::Ok);
    }
}






void MainWindow::on_pushButton_6_clicked()
{
    ui->cin->setText("");
    ui->nom_2->setText("");
    ui->prenom->setText("");
    ui->telephone->setText("");
    ui->adresse->setText("");
    ui->mail->setText("");
    ui->domaine->setText("");
    ui->description->setText("");
}



void MainWindow::on_updateTableView_2_doubleClicked(const QModelIndex &index)
{
    // Check if the index is valid
    if (!index.isValid()) {
        // Handle the invalid index if necessary, e.g., show an error message
        return;
    }

    // Define the column indices based on your table's actual structure
    const int CIN_COLUMN = 0;
    const int NOM_COLUMN = 1;
    const int PRENOM_COLUMN = 2;
    const int TEL_COLUMN = 3;
    const int ADRESSE_COLUMN = 4;
    const int MAIL_COLUMN = 5;
    const int DOMAINE_COLUMN = 6;
    const int DESCRIPTION_COLUMN = 7;
    const int SEXE_COLUMN = 8;

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

    // Fill the input fields with the retrieved data.
    ui->cin_2->setText(QString::number(cin));
    ui->nom_3->setText(nom);
    ui->prenom_2->setText(prenom);
    ui->telephone_2->setText(QString::number(tel));
    ui->adresse_2->setText(adresse);
    ui->mail_2->setText(mail);
    ui->domaine_2->setText(domaine);
    ui->description_2->setText(description);

    // Assuming sexe_2 is a QComboBox that has "Male" and "Female" as items
    int sexeIndex = -1; // Default to -1 if not found
    if (sexe == "Male") {
        sexeIndex = 0;
    } else if (sexe == "Female") {
        sexeIndex = 1;
    }
    ui->sexe_2->setCurrentIndex(sexeIndex);

    // Now the user can modify the data in the input fields.
}



void MainWindow::on_pushButton_21_clicked()
{
    int cin= ui->cin_2->text().toInt();
    int tel=ui->telephone_2->text().toInt();
    QString nom=ui->nom_3->text();
    QString prenom=ui->prenom_2->text();
    QString adresse=ui->adresse_2->text();
    QString mail=ui->mail_2->text();
    QString domaine=ui->domaine_2->text();
    QString description=ui->description_2->text();
    QString sexe=ui->sexe_2->currentText();

    bool test=a.modifier(cin,tel,nom,prenom,adresse,mail,domaine,description,sexe);
    ui->cin_2->clear();
    ui->telephone_2->clear();
    ui->nom_3->clear();
    ui->prenom_2->clear();
    ui->adresse_2->clear();
    ui->mail_2->clear();
    ui->domaine_2->clear();
    ui->description_2->clear();
    ui->sexe_2->setCurrentIndex(0); // Réinitialise la sélection du sexe
    ui->tableView_2->setModel(a.afficher());
    ui->tableView_6->setModel(a.afficher());
    ui->updateTableView_2->setModel(a.affichers());
    if (test)
    {
        ui->tableView_2->setModel(a.afficher());//refresh
        ui->tableView_6->setModel(a.afficher());//refresh
        ui->updateTableView_2->setModel(a.affichers());//refresh
        QMessageBox::information(nullptr, QObject::tr("Modifier un artiste"),
                    QObject::tr("Artiste modifié.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier un Artiste"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_20_clicked()
{
    ui->cin_2->setText("");
    ui->nom_3->setText("");
    ui->prenom_2->setText("");
    ui->telephone_2->setText("");
    ui->adresse_2->setText("");
    ui->mail_2->setText("");
    ui->domaine_2->setText("");
    ui->description_2->setText("");
}



void MainWindow::on_tableView_6_doubleClicked(const QModelIndex &index) {
    int row = index.row();
    cinn = ui->tableView_6->model()->index(row, 0).data().toInt(); // Store the CIN in the member variable
    qDebug() << "CIN selected: " << cinn; // Debug message to confirm CIN is selected
}




void MainWindow::on_pushButton_22_clicked() {
    qDebug() << "Attempting to delete artist with CIN: " << cinn; // Debug message before deletion
    bool suppressionReussie = a.supprimer(cinn);
    if (suppressionReussie) {
        // Refresh the table view
        // Assuming a.afficher() returns a model that can be used to refresh the view
        ui->tableView_6->setModel(a.afficher());

        QMessageBox::information(this, "Success", "Artist deleted successfully.");
    } else {
        QMessageBox::critical(this, "Error", "Failed to delete artist.");
    }
}


void MainWindow::on_searchTextBox_textChanged(const QString &arg1)
{
    QString searchText = arg1;
    QSqlQueryModel* model = a.rechercher(searchText);

    // Remplacer le modèle précédent dans le QTableView
    if(ui->tableView_2->model())
        delete ui->tableView_2->model();
    ui->tableView_2->setModel(model);
}



void MainWindow::on_triern_clicked()
{
ui->tableView_2->setModel(a.afficher_tri_nom());
}



void MainWindow::on_trierp_clicked()
{
ui->tableView_2->setModel(a.afficher_tri_prenom());
}



void MainWindow::on_trierc_clicked()
{
ui->tableView_2->setModel(a.afficher_tri_cin());
}



void MainWindow::on_stat_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT sexe FROM TABLE1");

    int countMale = 0;
    int countFemale = 0;
    int countOther = 0;

    for (int i = 0; i < model->rowCount(); ++i) {
        QString sexe = model->record(i).value("sexe").toString();
        if (sexe == "Male") {
            ++countMale;
        } else if (sexe == "Female") {
            ++countFemale;
        } else {
            ++countOther;
        }
    }

    int total = countMale + countFemale + countOther;

    QPieSeries *series = new QPieSeries();
    if (countMale != 0)
        series->append("Male", countMale);
    if (countFemale != 0)
        series->append("Female", countFemale);
    if (countOther != 0)
        series->append("Other", countOther);

    for (QPieSlice *slice : series->slices()) {
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





void MainWindow::on_pdf_clicked()
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
    ui->nom_2->setText(text);
}

void MainWindow::on_reconnaissance_clicked()
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
    ui->cin->setText(cleanedText);
}



void MainWindow::on_reconnaissance_7_clicked()
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
    ui->prenom->setText(text);
}


void MainWindow::on_reconnaissance_6_clicked()
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
    ui->mail->setText(text);
}


void MainWindow::on_reconnaissance_5_clicked()
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
    ui->description->setText(text);
}


void MainWindow::on_reconnaissance_9_clicked()
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
    ui->telephone->setText(text);
}


void MainWindow::on_reconnaissance_4_clicked()
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
    ui->adresse->setText(text);
}


void MainWindow::on_reconnaissance_2_clicked()
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
    ui->domaine->setText(text);
}


void MainWindow::on_reconnaissance_8_clicked()
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




//********************************assistant vocale *************************
void MainWindow::on_assistant_clicked()
{
    // Créer un objet de processus pour exécuter le script Python
    QProcess *process = new QProcess(this);

    // Définir le chemin vers le script Python
    QString pythonScriptPath = "C:/Users/DELL/OneDrive/Bureau/import openai.py";

    // Exécuter le script Python en tant que processus
    process->start("python", QStringList() << pythonScriptPath);

    // Connecter les signaux de processus pour récupérer les sorties de processus
    connect(process, &QProcess::readyReadStandardOutput, [=]() {
        // Lire la sortie standard du processus (résultats de la reconnaissance vocale)
        QByteArray output = process->readAllStandardOutput();

        // Traiter les résultats de la reconnaissance vocale
        QString result = QString::fromUtf8(output);


    });

    connect(process, &QProcess::readyReadStandardError, [=]() {
        // Gérer les erreurs de processus si nécessaire
        QByteArray error = process->readAllStandardError();
        qDebug() << "Error:" << error;
    });

    // Attendre que le processus se termine (peut être en option)
    process->waitForFinished();
}




























