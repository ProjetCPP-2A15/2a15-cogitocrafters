#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,manager(new QNetworkAccessManager(this))//weather
{
    ui->setupUi(this);
 //employee
    ui->tabEmployee->setModel(emp.afficherEmployee());
    connect(ui->searchTextBox_employee, &QLineEdit::textEdited, this, &MainWindow::on_searchTextBox_employee_textEdited);
    // Dans votre constructeur ou initialisation
    //connect(ui->lineEdit_PasswordEmployee, &QLineEdit::textChanged, this, &MainWindow::verifyPasswordStrength);
    ui->tabEmployee->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tabEmployee->setSelectionMode(QAbstractItemView::ExtendedSelection);

    //event
    // connect(ui->generateAffiche, &QPushButton::clicked, this, &MainWindow::on_generateAffiche_clicked);
    ui->table_event->setModel(e.afficherEvenement());
    connect(ui->searchevent, &QLineEdit::textEdited, this, &MainWindow::on_searchevent_textEdited);
    ui->table_event->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_event->setSelectionMode(QAbstractItemView::ExtendedSelection);


    //Guest
    connect(ui->searchGuest, &QLineEdit::textEdited, this, &MainWindow::on_searchGuest_textEdited);
    ui->tableViewGuest->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewGuest->setSelectionMode(QAbstractItemView::ExtendedSelection);

    ui->tableViewParticiper->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewParticiper->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableViewParticiper_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewParticiper_2->setSelectionMode(QAbstractItemView::ExtendedSelection);



    //ui->stackedWidgetGlobal->setCurrentIndex(0);
//partie artiste et article
    ui->artableView_3->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->artableView_3->setSelectionMode(QAbstractItemView::ExtendedSelection);
 // Activez la sélection multiple

 //connect(ui->rating, &QPushButton::clicked, this, &MainWindow::on_rating_clicked);
 connect(ui->gerervedio, &QPushButton::clicked, this, &MainWindow::on_gerervedio_clicked);


 // ################pour le recherchearticle################################
 connect(ui->searchTextBox_19, &QLineEdit::textChanged, this, &MainWindow::on_searchTextBox_19_textChanged);
 // Connexion du signal currentIndexChanged du comboBoxTri à la méthode de tri appropriée
     ui->tableView_4->setSelectionBehavior(QAbstractItemView::SelectRows);
     ui->tableView_4->setSelectionMode(QAbstractItemView::ExtendedSelection);
speech = new QTextToSpeech(this);



//#################################### Arduino(IYED ET DHIA) ############################################
/*#####################################################################################################*/
        int ret=A.connect_arduino(); // lancer la connexion à arduino
        switch(ret){
        case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
            break;
        case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
           break;
        case(-1):qDebug() << "arduino is not available";
        }
         QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
         //le slot update_label suite à la reception du signal readyRead (reception des données).
         A.write_to_arduino("1"); //envoyer 1 à arduino
         count = 0;



}

MainWindow::~MainWindow()
{
    delete ui;
    delete manager;
    delete speech;
    //A.write_to_arduino("0");
}

void MainWindow::update_label()
{
    //A.write_to_arduino(dataw); //envoyer 1 à arduino

    data = A.read_from_arduino();
    ui->label_3->setText(data);
    // int dist = data.toInt();
    if (!data.trimmed().isEmpty() && data.trimmed() != "0") {
        if (data.trimmed().toInt() <= 10 && !safe) {
            safe = true;
            int nbrvue=article.getNbVuById(202)+1;
            article.modifierNbVu(202,nbrvue);
        }
        if (data.trimmed().toInt() > 10) {
            safe = false;
        }
    }
    if(data.trimmed().toInt()<=5)
        ui->label_5->setText("Danger");
    else if(data.trimmed().toInt()<=10)
        ui->label_5->setText("Personne p");
    else
        ui->label_5->setText("Libre");
   // qDebug() << data.trimmed();
   // qDebug() << safe;
    ui->nbvu->setText(QString::number(article.getNbVuById(202)));

    //if(count==10){
    int nbrvue = article.getNbVuById(202);

    // Convertir nbrvue en une chaîne de caractères
    QString str_nbrvue = QString::number(nbrvue);

    // Envoyer le caractère 'N' à Arduino pour indiquer le début de l'envoi des chiffres
    A.write_to_arduino("N");

    // Envoyer chaque chiffre un par un à Arduino
    for (int i = 0; i < str_nbrvue.length(); i++) {
      A.write_to_arduino(QString(str_nbrvue.at(i)).toStdString().c_str());
      qDebug()<< QString(str_nbrvue.at(i)).toStdString().c_str();
    }

    // Envoyer le caractère 'B' à Arduino pour indiquer la fin de l'envoi des chiffres
    A.write_to_arduino("B");
    //count=0;
    //}else{count++;
    //qDebug()<< count;
   // }


}
void MainWindow::selectButton(QPushButton *button) {
    button->setStyleSheet("background: #8BD086;box-shadow: 0px 4px 4px rgba(0, 0, 0, 0.25);border: none;font-family: 'Athiti';font-style: normal;font-weight: 700;font-size: 20px;line-height: 32px;text-align: center;color: #2A501F;border-radius:15px;border-bottom:3px solid #669B37;");
}

// Fonction pour désélectionner un bouton
void MainWindow::deselectButton(QPushButton *button) {
    button->setStyleSheet("QPushButton {background: #A9E4A4;border: none;font-family: 'Athiti';font-style: normal;font-weight: 700;font-size: 20px;line-height: 32px;text-align: center;color: #2A501F;border-radius:15px;border-bottom:3px solid #669B37;}QPushButton:hover {background: #8BD086;box-shadow: 0px 4px 4px rgba(0, 0, 0, 0.25);}");
}

void MainWindow::on_pushButtonEmployee_clicked()
{
    ui->StackedWidget->setCurrentIndex(0);
    ui->stackedWidgetEmployee->setCurrentIndex(1);
    ui->tabEmployee->setModel(emp.afficherEmployee());
    deselectButton(ui->pushButtonEvents);
    deselectButton(ui->pushButtonProduct);
    deselectButton(ui->pushButtonGuest);
    deselectButton(ui->pushButtonArtist);
    deselectButton(ui->pushButtonAssociation);
    deselectButton(ui->pushButtonSetting);
    selectButton(ui->pushButtonEmployee);

}

void MainWindow::on_AddEmployee_2_clicked()
{
    ui->stackedWidgetEmployee->setCurrentIndex(3);

}

void MainWindow::on_pushButtonEvents_clicked()
{
    ui->StackedWidget->setCurrentIndex(1);
        ui->stackedWidgetEvent->setCurrentIndex(2);
        ui->table_event->setModel(e.afficherEvenement());
        selectButton(ui->pushButtonEvents);
        deselectButton(ui->pushButtonProduct);
        deselectButton(ui->pushButtonGuest);
        deselectButton(ui->pushButtonArtist);
        deselectButton(ui->pushButtonAssociation);
        deselectButton(ui->pushButtonSetting);
        ui->weather->clear();
        ui->weatherIcon->clear();
}










void MainWindow::on_pushButtonArtist_clicked()
{
    ui->StackedWidget->setCurrentIndex(3);
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




void MainWindow::on_pushButtonAssociation_clicked()
{
    ui->StackedWidget->setCurrentIndex(5);
    ui->stackedWidgetAssociation->setCurrentIndex(0);

    deselectButton(ui->pushButtonEvents);
    deselectButton(ui->pushButtonProduct);
    deselectButton(ui->pushButtonGuest);
    deselectButton(ui->pushButtonArtist);
    selectButton(ui->pushButtonAssociation);
    deselectButton(ui->pushButtonSetting);
    ui->tableView_22->setModel(as.afficher());
}





void MainWindow::on_updateEmployee_3_clicked()
{
    Article article;
        ui->stackedWidgetProduct->setCurrentIndex(3);
        ui->tableView_17->setModel(article.afficher());
}


