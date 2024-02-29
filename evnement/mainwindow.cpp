#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>



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
    ui->tableView_22->setModel(a.afficher());

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

void MainWindow::on_updateAssociaton_clicked()
{
    ui->stackedWidgetAssociation->setCurrentIndex(2);

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




//-------------------------------***** partie association *****-------------------------------

void MainWindow::on_save_a_clicked()
{
    // Récupérer les valeurs des champs
    int budget = ui->budget_a->text().toInt();
    QString nom = ui->name_a->text();
    QString adresse = ui->adress_a->text();
    QString description = ui->desc_a->text();

    // Créer une nouvelle association
    Association a(budget, nom, adresse, description);

    // Ajouter l'association
    bool ajoutReussi = a.ajouter();

    if (ajoutReussi)
    {
        // Effacer les champs après l'ajout réussi
        ui->budget_a->clear();
        ui->name_a->clear();
        ui->adress_a->clear();
        ui->desc_a->clear();

        //afficher les informations dans le tableau
        ui->stackedWidgetAssociation->setCurrentIndex(0);
        ui->tableView_22->setModel(a.afficher());
        ui->tableView_23->setModel(a.afficher2());


        QMessageBox::information(this, "Ajout réussi", "Association ajoutée avec succès.");
    }
    else
    {
        QMessageBox::critical(this, "Erreur lors de l'ajout", "Erreur lors de l'ajout de l'association.");
    }
}



            void MainWindow::on_tableView_23_doubleClicked(const QModelIndex &index)
            {
                // Check if the index is valid
                if (!index.isValid()) {
                    // Handle the invalid index if necessary, e.g., show an error message
                    return;
                }

                // Define the column indices based on your table's actual structure
                const int ID_COLUMN = 0;
                const int NOM_COLUMN = 1;
                const int ADRESS_COLUMN = 2;
                const int BUDGET_COLUMN = 3;
                const int DESCRIPTION_COLUMN = 4;


                // Retrieve the artist's details from the selected row in updateview_2.
                int id = index.sibling(index.row(), ID_COLUMN).data().toInt();
                int budget = index.sibling(index.row(), BUDGET_COLUMN).data().toInt();
                QString nom = index.sibling(index.row(), NOM_COLUMN).data().toString();
                QString adress = index.sibling(index.row(), ADRESS_COLUMN).data().toString();
                QString description = index.sibling(index.row(), DESCRIPTION_COLUMN).data().toString();


                // Fill the input fields with the retrieved data.
                ui->asid->setText(QString::number(id));
                ui->asid->setReadOnly(true);
                ui->asbudget->setText(QString::number(budget));
                ui->asname->setText(nom);
                ui->asadress->setText(adress);
                ui->asdescription->setText(description);



                // Now the user can modify the data in the input fields.
            }




void MainWindow::on_asupdate_clicked()
{
    ui->stackedWidgetAssociation->setCurrentIndex(2);
    ui->tableView_23->setModel(a.afficher2());
}



void MainWindow::on_supprimer_23_clicked()
{
    ui->asname->setText("");
    ui->asadress->setText("");
    ui->asbudget->setText("");
    ui->asdescription->setText("");
}

void MainWindow::on_save_4_clicked()
{
    int id= ui->asid->text().toInt();
    ui->asid->setReadOnly(true);
    int budget= ui->asbudget->text().toInt();
    QString nom=ui->asname->text();
    QString adress=ui->asadress->text();
    QString description=ui->asdescription->text();

    bool test=a.modifier(id,budget,nom,adress,description);
    //ui->asid->clear();



    if (test)
    {
        ui->asbudget->clear();
        ui->asname->clear();
        ui->asadress->clear();
        ui->asdescription->clear();
        ui->tableView_22->setModel(a.afficher());//refresh
        ui->tableView_23->setModel(a.afficher2());//refresh
        //ui->artableView_2->setModel(a.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Modifier un artiste"),
                    QObject::tr("Association modifié.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier une Association"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}



void MainWindow::on_searchTextBox_21_textChanged(const QString &arg1)
{
    QString searchText = arg1;
    QSqlQueryModel* model = a.rechercher(searchText);

    // Remplacer le modèle précédent dans le QTableView
    if(ui->tableView_23->model())
        delete ui->tableView_23->model();
    ui->tableView_23->setModel(model);
}

void MainWindow::on_searchTextBox_18_textChanged(const QString &arg1)
{
    QString searchText = arg1;
    QSqlQueryModel* model = a.rechercher(searchText);

    // Remplacer le modèle précédent dans le QTableView
    if(ui->tableView_22->model())
        delete ui->tableView_22->model();
    ui->tableView_22->setModel(model);
}




void MainWindow::on_comboBox_4_activated(const QString &arg1)
{
    if (arg1 == "Name") {
           ui->tableView_22->setModel(a.afficher_tri_nom());
       } else if (arg1 == "Adress") {
           ui->tableView_22->setModel(a.afficher_tri_adresse());
       } else if (arg1 == "Budget") {
         ui->tableView_22->setModel(a.afficher_tri_budget());
       }
}



void MainWindow::on_tableView_22_doubleClicked(const QModelIndex &index)
{

    if (index.isValid()) {
                QVariant name = index.sibling(index.row(), 0).data();
                QVariant address = index.sibling(index.row(), 1).data();
                QVariant budget = index.sibling(index.row(), 2).data();
                QVariant description = index.sibling(index.row(), 3).data();

                ui->labelaffnameass->setText(name.toString());
                ui->labelaffbudgetass->setText(budget.toString());
                ui->labelaffaddressass->setText(address.toString());
                ui->labelaffdescriptionass->setText(description.toString());
            }

    ui->stackedWidgetAssociation->setCurrentIndex(3);

}
