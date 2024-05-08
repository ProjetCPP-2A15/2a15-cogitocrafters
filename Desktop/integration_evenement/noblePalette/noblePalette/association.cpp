#include "association.h"
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


Association::Association(int budget,QString nom,QString adresse,QString description,QString type)
{
   // this->id=id;
    this->budget=budget;
    this->nom=nom;
    this->adresse=adresse;
    this->description=description;
    this->type=type;
}



bool Association::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO ASSOCIATION (budget,nom, adress, description, type) "
                  "VALUES (:budget, :nom, :adress, :description, :type)");
    query.bindValue(":budget", budget);
    query.bindValue(":nom", nom);
    query.bindValue(":adress", adresse);
    query.bindValue(":description", description);
    query.bindValue(":type", type);
    return query.exec();

}


QSqlQueryModel * Association::afficher()
{
    QSqlQueryModel * model = new QSqlQueryModel();

    // Corrected SQL query with proper column selection
    model->setQuery("SELECT nom, adress, budget, description, type FROM ASSOCIATION");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ADRESS"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("BUDGET"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TYPE"));

    return model;
}



QSqlQueryModel * Association::afficher2()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from ASSOCIATION");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("ADRESS"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("BUDGET"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("DESCRIPTION"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("TYPE"));

    return model;
}








bool Association::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM ASSOCIATION WHERE ID = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Delete failed: " ;  // Detailed error message
        return false;
    }
    return true;
}


QSqlQueryModel* Association::rechercher(QString A)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ASSOCIATION WHERE NOM LIKE '%" + A + "%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ADRESS"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("BUDGET"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("TYPE"));


    return model;
}


bool Association::modifier(int id,int budget,QString nom,QString adresse,QString description)
{
    QSqlQuery query;
    query.prepare("UPDATE ASSOCIATION set ID=:id, NOM=:nom, ADRESS=:adress,BUDGET=:budget,DESCRIPTION=:description WHERE ID= :id");
    query.bindValue(":id",id);
    query.bindValue(":nom",nom);
    query.bindValue(":adress",adresse);
    query.bindValue(":budget",budget);
    query.bindValue(":description",description);

    if (!query.exec()) {
        qDebug() << "Delete failed: " ;  // Detailed error message
        return false;
    }
    return true;
}

QSqlQueryModel* Association::afficher_tri_budget() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ASSOCIATION ORDER BY BUDGET");
    return model;
}

QSqlQueryModel* Association::afficher_tri_nom() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ASSOCIATION ORDER BY NOM");
    return model;
}

QSqlQueryModel* Association::afficher_tri_adresse() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ASSOCIATION ORDER BY ADRESS");
    return model;
}



//-------------------------------***** partie association *****-------------------------------





void MainWindow::on_save_a_clicked()
{
    // Récupérer les valeurs des champs
        QString budgetText = ui->budget_a->text();
        QString nom = ui->name_a->text();
        QString adresse = ui->adress_a->text();
        QString description = ui->desc_a->text();
        QString type;

        if(ui->radioButton->isChecked())
            type = "Private";
        else if(ui->radioButton_2->isChecked())
            type = "Public";

        // Vérifier si les champs sont vides
        if (budgetText.isEmpty() || nom.isEmpty() || adresse.isEmpty() || description.isEmpty()) {
            QMessageBox::warning(this, "Champs vides", "Veuillez remplir tous les champs.");
            return;
        }

        // Vérifier si le budget est valide
        bool ok;
        int budget = budgetText.toInt(&ok);
        if (!ok || budget <= 0) {
            QMessageBox::warning(this, "Budget invalide", "Veuillez entrer un budget valide (supérieur à zéro).");
            return;
        }

        // Créer une nouvelle association
        Association as(budget, nom, adresse, description,type);

        // Ajouter l'association
        bool ajoutReussi = as.ajouter();

        if (ajoutReussi)
        {
            // Effacer les champs après l'ajout réussi
            ui->budget_a->clear();
            ui->name_a->clear();
            ui->adress_a->clear();
            ui->desc_a->clear();

            // Afficher les informations dans le tableau
            ui->stackedWidgetAssociation->setCurrentIndex(0);
            ui->tableView_22->setModel(as.afficher());
            ui->tableView_23->setModel(as.afficher2());

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




            void MainWindow::on_assupprimer_3_clicked()
            {
                ui->stackedWidgetAssociation->setCurrentIndex(0);
            }

            void MainWindow::on_clear_a_2_clicked()
            {
                ui->stackedWidgetAssociation->setCurrentIndex(0);
            }

            void MainWindow::on_assupprimer_2_clicked()
            {
                ui->stackedWidgetAssociation->setCurrentIndex(0);
            }
            void MainWindow::on_listas_clicked()
            {
                 ui->stackedWidgetAssociation->setCurrentIndex(0);
            }

void MainWindow::on_asupdate_clicked()
{
    ui->stackedWidgetAssociation->setCurrentIndex(2);
    ui->tableView_23->setModel(as.afficher2());
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

    bool test=as.modifier(id,budget,nom,adress,description);
    //ui->asid->clear();



    if (test)
    {
        ui->asbudget->clear();
        ui->asname->clear();
        ui->asadress->clear();
        ui->asdescription->clear();
        ui->tableView_22->setModel(as.afficher());//refresh
        ui->tableView_23->setModel(as.afficher2());//refresh
        //ui->artableView_2->setModel(as.afficher());//refresh
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
    QSqlQueryModel* model = as.rechercher(searchText);

    // Remplacer le modèle précédent dans le QTableView
    if(ui->tableView_23->model())
        delete ui->tableView_23->model();
    ui->tableView_23->setModel(model);
}

void MainWindow::on_searchTextBox_18_textChanged(const QString &arg1)
{
    QString searchText = arg1;
    QSqlQueryModel* model = as.rechercher(searchText);

    // Remplacer le modèle précédent dans le QTableView
    if(ui->tableView_22->model())
        delete ui->tableView_22->model();
    ui->tableView_22->setModel(model);
}




void MainWindow::on_comboBox_4_activated(const QString &arg1)
{
    if (arg1 == "Name") {
           ui->tableView_22->setModel(as.afficher_tri_nom());
       } else if (arg1 == "Adress") {
           ui->tableView_22->setModel(as.afficher_tri_adresse());
       } else if (arg1 == "Budget") {
         ui->tableView_22->setModel(as.afficher_tri_budget());
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

void MainWindow::on_assupprimer_clicked()
{
    as.supprimer(ui->asid->text().toInt());
    ui->tableView_22->setModel(as.afficher());
    ui->stackedWidgetAssociation->setCurrentIndex(0);

}



void MainWindow::on_asPDF_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save PDF", "association n°", "*.pdf");

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
       painter.drawText(100, 100, "Association information");

       QStringList additionalInfo;
       additionalInfo << "NAME : " + ui->labelaffnameass->text();
       additionalInfo << "ADDRESS : " + ui->labelaffaddressass->text();
       additionalInfo << "BUDGET : " + ui->lineEdit_8->text();
       additionalInfo << "DESCRIPTION : " + ui->labelaffdescriptionass->text();


       int yOffset = 120;
       foreach(const QString &info, additionalInfo) {
           painter.drawText(120, yOffset, info);
           yOffset += 20;
       }

       painter.end();
}




void MainWindow::on_comboBox_10_currentIndexChanged(int index)
{
    // Chemin d'accès vers votre script Python
    QString pythonScriptPath = "C:/Users/Emna Nkhili/Desktop/noblePalette/noblePalette/script/devise.py";

    // Obtenir la valeur de budget de labelaffbudgetass
    QString budget = ui->labelaffbudgetass->text();
    if (!budget.isEmpty()) {
        // Déterminer le type de sortie en fonction de l'index sélectionné dans le ComboBox
        QString outputType;
        if (index > 0 && index < ui->comboBox_10->count()) {
            switch (index) {
                case 1:
                    outputType = "EUR";
                    break;
                case 2:
                    outputType = "USD";
                    break;
                default:
                    outputType = ""; // Gérer le cas par défaut si nécessaire
                    break;
            }

            // Debug: Print arguments before executing Python script
            qDebug() << "Executing Python script with arguments:";
            qDebug() << "Python Script Path:" << pythonScriptPath;
            qDebug() << "Budget:" << budget;
            qDebug() << "Output Type:" << outputType;

            // Create QProcess for Python script execution
            QProcess process(this);

            // Construct command arguments
            QStringList arguments;
            arguments << pythonScriptPath << budget << outputType; // Pass script path, budget, and outputType

            // Start the Python script
            process.start("python", arguments);

            // Create QProcess for reading standard output
            QProcess outputReader(this);

            // Connect readyReadStandardOutput signal to a slot for reading standard output
            connect(&process, &QProcess::readyReadStandardOutput, [&]() {
                // Read standard output and append it to the label text
                QByteArray output = process.readAllStandardOutput();
                QString outputStr = QString::fromUtf8(output);
                ui->devise->setText(outputStr);
            });

            // Wait for process to finish (consider timeout if needed)
            process.waitForFinished(-1);

            // Handle errors
            if (process.exitStatus() != QProcess::NormalExit) {
                QMessageBox::critical(this, "Error", "An error occurred during conversion.");
            }
        }
        else {
            ui->devise->setText("");

        }
    }
}






void MainWindow::on_supprimer_36_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT Type FROM ASSOCIATION");

    int countPrivate = 0;
    int countPublic = 0;
    int countOther = 0;

    for (int i = 0; i < model->rowCount(); ++i) {
        QString type = model->record(i).value("Type").toString();
        if (type == "Private") {
            ++countPrivate;
        } else if (type == "Public") {
            ++countPublic;
        } else {
            ++countOther;
        }
    }

    int total = countPrivate + countPublic + countOther;

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
    QStringList labels;
    QList<int> counts;
    labels << "Private" << "Public" << "Other";
    counts << countPrivate << countPublic << countOther;

    for (int i = 0; i < labels.size(); ++i) {
        qreal sweepAngle = 360.0 * counts[i] / total;
        QColor sliceColor = QColor::fromHsv((i * 30) % 360, 100, 200); // Couleur pastel pour chaque tranche
        painter.setBrush(sliceColor); // Définir la couleur de la tranche
        painter.drawPie(pieRect, startAngle * 16, sweepAngle * 16);

        // Dessiner un carré de couleur à côté du pie chart
        QRectF colorRect(pixmapSize.width() - 200, 20 + i * 30, 20, 20); // Position et taille du carré de couleur
        painter.fillRect(colorRect, sliceColor);

        // Afficher le label à côté du carré de couleur
        QString label = labels[i];
        QPointF labelPos = colorRect.topRight() + QPointF(30, 15); // Position pour afficher le label à côté du carré de couleur
        painter.drawText(labelPos, label);

        // Calcul du pourcentage
        double percentage = (static_cast<double>(counts[i]) / total) * 100;
        QString percentageText = QString::number(percentage, 'f', 1) + "%";

        // Afficher le pourcentage à côté du carré de couleur
        QPointF textPos = colorRect.topRight() + QPointF(130, 15); // Position pour afficher le texte à côté du carré de couleur
        painter.drawText(textPos, percentageText);

        startAngle += sweepAngle;
    }

    painter.end();

    // Afficher le pixmap dans le QLabel
    ui->label_statAssociation->setPixmap(pixmap);

    // Affichage du graphique dans la page 4 de stackedWidgetAssociation
    ui->stackedWidgetAssociation->setCurrentIndex(4);
}

