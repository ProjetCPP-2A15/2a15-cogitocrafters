#include "evenement.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QDebug>
#include <QObject>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <qsqlerror.h>
#include <QPainter>
#include <cmath>
#include <QString>
#include <QFontMetrics>
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPainter>
#include<QLabel>
#include "controller.h"
#include"employee.h"

int evenement::getIdEvent()const
{
    return id_event ;
}
int evenement::getNbEmployee()const
{
    return nb_employee ;
}
QString evenement::getEventNoun()const
{
    return event_noun ;
}
QString evenement::getLocation()const
{
    return location ;
}
QString evenement::getDescription()const
{
    return description ;
}
QDate evenement::getStartD()const
{
    return start_d ;
}
QDate evenement::getEndD()const
{
    return end_d ;
}
QTime evenement::getStartH ()const
{
    return start_h ;
}
QTime evenement::getEndH()const
{
    return end_h ;
}
float evenement::getPriceTick()const
{
    return price_tick ;
}
//setters
void evenement::setIdEvent(int id_event)
{
     this ->id_event=id_event;
}
void evenement::setNbEmployee(int nb_employee)
{
     this ->nb_employee=nb_employee;
}
void evenement::setEventNoun(QString event_noun)
{
     this ->event_noun=event_noun;
}
void evenement::setLocation(QString location)
{
     this ->location=location;
}
void evenement::setDescription(QString description)
{
     this ->description=description;
}
void evenement::setStartD(QDate start_d)
{
     this ->start_d=start_d;
}
void evenement::setEndD(QDate end_d)
{
     this ->end_d=end_d;
}
void evenement::setStartH(QTime start_h)
{
     this ->start_h=start_h;
}
void evenement::setEndH(QTime end_h)
{
     this ->end_h=end_h;
}
void evenement::setPriceTick(float price_tick)
{
     this ->price_tick=price_tick;
}
evenement::evenement()
{
}
evenement::evenement(int id_event, int nb_employee, QString event_noun, QString location, QString description, QDate start_d, QDate end_d, QTime start_h, QTime end_h, float price_tick)
{
    this->id_event = id_event;
    this->nb_employee = nb_employee;
    this->event_noun = event_noun;
    this->location = location;
    this->description = description;
    this->start_d = start_d;
    this->end_d = end_d;
    this->start_h = start_h;
    this->end_h = end_h;
    this->price_tick = price_tick;
}
evenement::evenement(int id_event, int nb_employee, QString event_noun, QString location, QString description, QDate start_d, QDate end_d, QTime start_h, QTime end_h, float price_tick,QString RFID)
{
    this->id_event = id_event;
    this->nb_employee = nb_employee;
    this->event_noun = event_noun;
    this->location = location;
    this->description = description;
    this->start_d = start_d;
    this->end_d = end_d;
    this->start_h = start_h;
    this->end_h = end_h;
    this->price_tick = price_tick;
    this->RFID=RFID;
}
evenement::evenement(int id_event, QString imagePath)
{
    this->id_event = id_event;
    this->imagePath=imagePath;
}

evenement evenement::chercher(int id_event)
{
    evenement e;  // Create an instance of the Employee class
    QString queryStr = QString("SELECT * FROM evenement WHERE id_event = %1").arg(id_event);
    QSqlQuery query;
    query.prepare(queryStr);

    if (query.exec())
    {
        if (query.next())
        {
            // Assuming your Employee class has setter methods, update them accordingly
            e.setIdEvent(query.value("id_event").toInt());
            e.setNbEmployee(query.value("nb_employee").toInt());
            e.setEventNoun(query.value("event_noun").toString());
            e.setLocation(query.value("location").toString());
            e.setDescription(query.value("description").toString());
            e.setStartD(query.value("start_d").toDate());
            e.setEndD(query.value("end_d").toDate());
            e.setStartH(query.value("start_h").toTime());
            e.setEndH(query.value("end_h").toTime());
            e.setPriceTick(query.value("price_tick").toInt());
        }
        else
        {
            // Handle the case when no records are found for the given ID
            qDebug() << "No records found for ID:" << id_event;
        }
    }
    else
    {
        // Handle the case when the query fails, e.g., log an error
        qDebug() << "Query failed:" << query.lastError().text();
    }

    return e;
}
void updateEventComboBox(QComboBox *comboBox) {
    // Clear existing items in the ComboBox
    comboBox->clear();

    // Fetch IDs from the database
    QSqlQuery query;
    query.exec("SELECT id_event FROM evenement");
    while (query.next()) {
        int id = query.value(0).toInt();
        // Add each ID to the ComboBox
        comboBox->addItem(QString::number(id));
    }
}
bool evenement::ajouterEvenement()
{
    QSqlQuery query;
    //QString res=QString::number(id_event);
    id_event = generateNewID();
    QString nb=QString::number(nb_employee);
    QString prx=QString::number(price_tick);
    query.prepare("INSERT INTO EVENEMENT (ID_EVENT, NB_EMPLOYEE ,EVENT_NOUN,LOCATION ,DESCRIPTION ,START_D ,END_D,START_H,END_H,PRICE_TICK,RFID) "
                          "VALUES (:id_event,:nb_employee ,:event_noun,:location ,:description ,:start_d ,:end_d,:start_h,:end_h,:price_tick,:RFID)");
            //query.bindValue(":id_event",res);
            query.bindValue(":id_event", id_event);
            query.bindValue(":nb_employee", nb);
            query.bindValue(":event_noun", event_noun);
            query.bindValue(":location", location);
            query.bindValue(":description", description);
            query.bindValue(":start_d", start_d);
            query.bindValue(":end_d", end_d);
            query.bindValue(":start_h", start_h);
            query.bindValue(":end_h", end_h);
            query.bindValue(":price_tick", prx);
            query.bindValue(":RFID", RFID);

            return query.exec();
}
QSqlQueryModel *evenement::afficherEvenement()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT ID_EVENT, EVENT_NOUN, LOCATION, CAST(START_D AS varchar(255)),  CAST(END_D AS varchar(255)), PRICE_TICK FROM EVENEMENT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_EVENT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("EVENT_NOUN"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("LOCATION"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("START_D"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("END_D"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("PRICE_TICK"));
    return model;
}

bool evenement::supprimerEvenement(QString event_noun)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EVENEMENT WHERE event_noun = :event_noun");
    query.bindValue(":event_noun", event_noun);
    if (!query.exec()) {
        qDebug() << "Delete failed: " ;  // Detailed error message
        return false;
    }
    return query.exec();
}
int evenement::generateNewID()
{
    QSqlQuery query;
    query.exec("SELECT MAX(id_event) FROM evenement");
    if (query.next()) {
        return query.value(0).toInt() + 1;
    } else {
        return 1;
    }
}

bool evenement::modifierEvenement()
{
    QSqlQuery query;
    query.prepare("UPDATE EVENEMENT SET nb_employee = :nb_employee, event_noun = :event_noun, location = :location, description = :description, start_d = :start_d, end_d = :end_d, start_h = :start_h, end_h = :end_h, price_tick = :price_tick WHERE id_event = :id_event");

    // Convert numeric values to strings
    QString nb = QString::number(nb_employee);
    QString prx = QString::number(price_tick);

    query.bindValue(":id_event", id_event);
    query.bindValue(":nb_employee", nb);
    query.bindValue(":event_noun", event_noun);
    query.bindValue(":location", location);
    query.bindValue(":description", description);
    query.bindValue(":start_d", start_d);
    query.bindValue(":end_d", end_d);
    query.bindValue(":start_h", start_h);
    query.bindValue(":end_h", end_h);
    query.bindValue(":price_tick", prx);

    // Execute the query and return the result
    if (!query.exec()) {
        qDebug() << "Erreur SQL:" << query.lastError().text();
        return false;
    }
    return true;
}

QSqlQueryModel *evenement::afficher_tri_id_descendant()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT ID_EVENT, EVENT_NOUN, LOCATION, CAST(START_D AS varchar(255)),  CAST(END_D AS varchar(255)), PRICE_TICK FROM EVENEMENT ORDER BY ID_EVENT DESC");
    return model;
}
QSqlQueryModel *evenement::afficher_tri_id_ascendant()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT ID_EVENT, EVENT_NOUN, LOCATION, CAST(START_D AS varchar(255)),  CAST(END_D AS varchar(255)), PRICE_TICK FROM EVENEMENT ORDER BY ID_EVENT ASC");
    return model;
}
QSqlQueryModel *evenement::afficher_tri_nom_descendant()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT ID_EVENT, EVENT_NOUN, LOCATION, CAST(START_D AS varchar(255)),  CAST(END_D AS varchar(255)), PRICE_TICK FROM EVENEMENT ORDER BY EVENT_NOUN DESC");
    return model;
}
QSqlQueryModel *evenement::afficher_tri_nom_ascendant()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT ID_EVENT, EVENT_NOUN, LOCATION, CAST(START_D AS varchar(255)),  CAST(END_D AS varchar(255)), PRICE_TICK FROM EVENEMENT ORDER BY EVENT_NOUN ASC");
    return model;
}
QSqlQueryModel *evenement::afficher_tri_location_descendant()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT ID_EVENT, EVENT_NOUN, LOCATION, CAST(START_D AS varchar(255)),  CAST(END_D AS varchar(255)), PRICE_TICK FROM EVENEMENT ORDER BY LOCATION DESC");
    return model;
}
QSqlQueryModel *evenement::afficher_tri_location_ascendant()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT ID_EVENT, EVENT_NOUN, LOCATION, CAST(START_D AS varchar(255)),  CAST(END_D AS varchar(255)), PRICE_TICK FROM EVENEMENT ORDER BY LOCATION ASC");
    return model;
}
QSqlQueryModel *evenement::afficher_tri_start_descendant()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT ID_EVENT, EVENT_NOUN, LOCATION, CAST(START_D AS varchar(255)),  CAST(END_D AS varchar(255)), PRICE_TICK FROM EVENEMENT ORDER BY START_D DESC");
    return model;
}
QSqlQueryModel *evenement::afficher_tri_start_ascendant()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT ID_EVENT, EVENT_NOUN, LOCATION, CAST(START_D AS varchar(255)),  CAST(END_D AS varchar(255)), PRICE_TICK FROM EVENEMENT ORDER BY START_D ASC");
    return model;
}
QSqlQueryModel *evenement::afficher_tri_end_descendant()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT ID_EVENT, EVENT_NOUN, LOCATION, CAST(START_D AS varchar(255)),  CAST(END_D AS varchar(255)), PRICE_TICK FROM EVENEMENT ORDER BY END_D DESC");
    return model;
}
QSqlQueryModel *evenement::afficher_tri_end_ascendant()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT ID_EVENT, EVENT_NOUN, LOCATION, CAST(START_D AS varchar(255)),  CAST(END_D AS varchar(255)), PRICE_TICK FROM EVENEMENT ORDER BY END_D ASC");
    return model;
}
QSqlQueryModel *evenement::afficher_tri_price_descendant()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT ID_EVENT, EVENT_NOUN, LOCATION, CAST(START_D AS varchar(255)),  CAST(END_D AS varchar(255)), PRICE_TICK FROM EVENEMENT ORDER BY PRICE_TICK DESC");
    return model;
}
QSqlQueryModel* evenement::afficher_tri_price_ascendant()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT ID_EVENT, EVENT_NOUN, LOCATION, CAST(START_D AS varchar(255)),  CAST(END_D AS varchar(255)), PRICE_TICK FROM EVENEMENT ORDER BY PRICE_TICK ASC");
    return model;
}
QSqlQueryModel* evenement::rechercher(QString e)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT ID_EVENT, EVENT_NOUN, LOCATION, CAST(START_D AS varchar(255)),  CAST(END_D AS varchar(255)), PRICE_TICK FROM EVENEMENT WHERE EVENT_NOUN LIKE '%" + e + "%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_EVENT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("EVENT_NOUN"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("LOCATION"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("START_D"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("END_D"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("PRICE_TICK"));
    return model;
}

void evenement::afficherPieChart(QLabel *label)
{
    // Exécution de la requête pour récupérer les données sur les saisons
    QSqlQuery query;
    query.prepare("SELECT CASE "
                     "WHEN EXTRACT(MONTH FROM start_d) IN (3, 4, 5) OR "
                     "(EXTRACT(MONTH FROM start_d) = 6 AND EXTRACT(DAY FROM start_d) <= 20) THEN 'Spring' "
                     "WHEN EXTRACT(MONTH FROM start_d) IN (6, 7, 8) OR "
                     "(EXTRACT(MONTH FROM start_d) = 9 AND EXTRACT(DAY FROM start_d) <= 22) THEN 'Summer' "
                     "WHEN EXTRACT(MONTH FROM start_d) IN (9, 10, 11) OR "
                     "(EXTRACT(MONTH FROM start_d) = 12 AND EXTRACT(DAY FROM start_d) <= 20) THEN 'Autumn' "
                     "ELSE 'Winter' "
                     "END AS season, COUNT(*) "
                     "FROM EVENEMENT "
                     "GROUP BY CASE "
                     "WHEN EXTRACT(MONTH FROM start_d) IN (3, 4, 5) OR "
                     "(EXTRACT(MONTH FROM start_d) = 6 AND EXTRACT(DAY FROM start_d) <= 20) THEN 'Spring' "
                     "WHEN EXTRACT(MONTH FROM start_d) IN (6, 7, 8) OR "
                     "(EXTRACT(MONTH FROM start_d) = 9 AND EXTRACT(DAY FROM start_d) <= 22) THEN 'Summer' "
                     "WHEN EXTRACT(MONTH FROM start_d) IN (9, 10, 11) OR "
                     "(EXTRACT(MONTH FROM start_d) = 12 AND EXTRACT(DAY FROM start_d) <= 20) THEN 'Autumn' "
                     "ELSE 'Winter' "
                     "END");

    // Vérification si la requête a échoué
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête SQL :" << query.lastError().text();
        return;
    }

    // Variables pour stocker les données récupérées
    QList<QString> seasons;
    QList<int> counts;

    // Récupération des données de la requête
    while (query.next()) {
        seasons.append(query.value(0).toString());
        counts.append(query.value(1).toInt());
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
    for (int i = 0; i < seasons.size(); ++i) {
        qreal sweepAngle = 360.0 * counts[i] / std::accumulate(counts.begin(), counts.end(), 0);
        QColor sliceColor = QColor::fromHsv((i * 30) % 360, 100, 200); // Couleur pastel pour chaque tranche
        painter.setBrush(sliceColor); // Définir la couleur de la tranche
        painter.drawPie(pieRect, startAngle * 16, sweepAngle * 16);

        // Dessiner un carré de couleur à côté du pie chart
        QRectF colorRect(pixmapSize.width() - 200, 20 + i * 30, 20, 20); // Position et taille du carré de couleur
        painter.fillRect(colorRect, sliceColor);

        // Afficher la saison à côté du carré de couleur
        QString seasonLabel = seasons[i];
        QPointF seasonPos = colorRect.topRight() + QPointF(30, 15); // Position pour afficher la saison à côté du carré de couleur
        painter.drawText(seasonPos, seasonLabel);

        // Calcul du pourcentage
        double percentage = (static_cast<double>(counts[i]) / std::accumulate(counts.begin(), counts.end(), 0)) * 100;
        QString percentageText = QString::number(percentage, 'f', 1) + "%";

        // Afficher le pourcentage à côté du carré de couleur
        QPointF textPos = colorRect.topRight() + QPointF(130, 15); // Position pour afficher le texte à côté du carré de couleur
        painter.drawText(textPos, percentageText);

        startAngle += sweepAngle;
    }

    painter.end();

    // Afficher le pixmap dans le QLabel
    label->setPixmap(pixmap);
}

bool evenement::ajouterImage(int id)
{
    QSqlQuery query;
    QString id_event = QString::number(id);
    QFile file(imagePath);
    if(!file.open(QIODevice::ReadOnly)) {
                qDebug() << "Erreur: Impossible de lire l'image:" << file.errorString();
                qDebug() << imagePath;
                return false;
       }
       QByteArray imageData = file.readAll();
            file.close();
    query.prepare("UPDATE EVENEMENT SET affiche = :affiche WHERE id_event = :id_event");
    query.bindValue(":id_event", id_event);
    query.bindValue(":affiche", imageData);

    if(query.exec()) {
        qDebug() << "Image ajoutée avec succès pour l'événement ID :" << id_event;
        return true;
    } else {
        qDebug() << "Erreur lors de l'ajout de l'image pour l'événement ID :" << id_event << query.lastError().text();
        return false;
    }
}
int evenement::rechercherRFID(QString rfid)
{
    QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM evenement WHERE RFID = ?");
        query.addBindValue(rfid);

        if (query.exec() && query.next())
        {
            return query.value(0).toInt();
        }
        else
        {
            qDebug() << "Query failed:" << query.lastError().text();
            return 0;
        }
}
//*********************************************************************Mainwindow*******************************************************************//
void MainWindow::on_pushButtonGuest_clicked()
{

    ui->StackedWidget->setCurrentIndex(2);
    ui->stackedWidgetGuest->setCurrentIndex(0);
    ui->tableViewGuest->setModel(g.afficher());
    deselectButton(ui->pushButtonEvents);
    deselectButton(ui->pushButtonProduct);
    selectButton(ui->pushButtonGuest);
    deselectButton(ui->pushButtonArtist);
    deselectButton(ui->pushButtonAssociation);
    //deselectButton(ui->pushButtonSetting);
    ui->addCinGuest->clear();
    ui->addNameGuest->clear();
    ui->addAgeGuest->clear();
    ui->addAddressGuest->clear();
    ui->addEmailGuest->clear();
    ui->addPhoneGuest->clear();
    updateEventComboBox(ui->id_events);

}
void MainWindow::on_add_event_clicked()
{
    int id_event =e.generateNewID();
       //int id_event = ui->id_event->text().toInt();
       QString event_noun = ui->event_noun->text();
       int nb_employee = ui->nb_employee->value();
       QString location = ui->location->text();
       QString description = ui->description->toPlainText();
       QDate start_d = QDate::fromString(ui->start_d->text(), "dd/MM/yyyy");
       QDate end_d = QDate::fromString(ui->end_d->text(), "dd/MM/yyyy");
       QTime start_h = ui->start_h->time();
       QTime end_h = ui->end_h->time();
       float price_tick = ui->price_tick->value();
       if (event_noun.isEmpty() || location.isEmpty() || description.isEmpty() || start_d.isNull() || end_d.isNull() || start_h.isNull() || end_h.isNull()||nb_employee == 0 || price_tick == 0.0)
              {
                  QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                        QObject::tr(" All fields are required."),
                                        QMessageBox::Cancel);
                  return;
              }
          if (start_d < QDate::currentDate()) {
              QMessageBox::critical(nullptr, QObject::tr("Error"),
                                    QObject::tr("Start date must be from %1 onwards.").arg(QDate::currentDate().toString("MM/dd/yyyy")),
                                    QMessageBox::Cancel);
              return;
          }


              if (end_d <= start_d) {
                  QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                        QObject::tr("End date must be after the start date."),
                                        QMessageBox::Cancel);
                  return;
              }

                  if (end_h <= start_h) {
                      QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                            QObject::tr("End time must be after the start time."),
                                            QMessageBox::Cancel);
                      return;
                  }
                  // Vérifier si la période est unique
                      QVector<evenement> events = getEventsFromDatabase();
                      foreach(const evenement &event, events)
                      {
                          if ((start_d >= event.getStartD() && start_d <= event.getEndD()) ||
                              (end_d >= event.getStartD() && end_d <= event.getEndD()) ||
                              (event.getStartD() >= start_d && event.getStartD() <= end_d) ||
                              (event.getEndD() >= start_d && event.getEndD() <= end_d))
                          {
                              QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                                    QObject::tr("The chosen period overlaps with an existing event."),
                                                    QMessageBox::Cancel);
                              return;
                          }
                      }

       evenement e(id_event, nb_employee, event_noun, location, description, start_d, end_d, start_h, end_h, price_tick,"23 CD E8 A6");
       bool test = e.ajouterEvenement();
       if (test)
       {
          // Afficher l'événement ajouté dans la vue détaillée
           ui->stackedWidgetEvent->setCurrentIndex(0);
           ui->nount->setText(event_noun);
           ui->idt->setText(QString::number(id_event));
           ui->nbt->setText(QString::number(nb_employee));
           ui->pricet->setText(QString::number(price_tick));
           ui->sht->setTime(start_h);
           ui->eht->setTime(end_h);
           ui->sdt->setDate(start_d);
           ui->edt->setDate(end_d);
           ui->locationt->setText(location);
           ui->descriptiont->setText(description);

           // Mettre à jour le modèle de la table pour refléter les modifications
           ui->table_event->setModel(e.afficherEvenement());
           // Afficher un message de succès
           QMessageBox::information(nullptr, QObject::tr("OK"),
                                    QObject::tr("the event has been added successfully.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
           updateEventComboBox(ui->id_events);

       }
       else
       {
           QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                 QObject::tr("The event could not be added.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
       }


       clearEventFields();
       calendarWidget();
}

void MainWindow::on_table_event_clicked(const QModelIndex &index)
{
    if (index.isValid())
           {
               int row = index.row();
               int id_event = ui->table_event->model()->index(row, 0).data().toInt();
               evenement ev = e.chercher(id_event);
               ui->nount->setText(ev.getEventNoun());
               ui->idt->setText(QString::number(ev.getIdEvent()));
               ui->idEventParticiper->setText(QString::number(ev.getIdEvent()));
               ui->eventnounparticiper->setText(ev.getEventNoun());
               ui->startdateparticiper->setDate(ev.getStartD());
               ui->enddateparticiper->setDate(ev.getEndD());
               ui->nbt->setText(QString::number(ev.getNbEmployee()));
               ui->pricet->setText(QString::number(ev.getPriceTick()));
               ui->sht->setTime(ev.getStartH());
               ui->eht->setTime(ev.getEndH());
               ui->sdt->setDate(ev.getStartD());
               ui->edt->setDate(ev.getEndD());
               ui->locationt->setText(ev.getLocation());
               ui->descriptiont->setText(ev.getDescription());
               ui->stackedWidgetEvent->setCurrentIndex(0);
        }
}
void MainWindow::clearEventFields()
{
    // Efface les champs du formulaire
    //ui->id_event->clear();
    ui->event_noun->clear();
    ui->nb_employee->setValue(0);
    ui->location->clear();
    ui->description->clear();
    ui->start_d->setDate(QDate::currentDate());
    ui->end_d->setDate(QDate::currentDate());
    ui->start_h->setTime(QTime(0, 0));
    ui->end_h->setTime(QTime(0, 0));
    ui->price_tick->setValue(0.0);
}
void MainWindow::clearEventdetailFields()
{
    // Efface les champs du l'affichage d'un evenement
    ui->idt->clear();
    ui->nount->clear();
    ui->nbt->clear();
    ui->pricet->clear();
    ui->sht->clear();
    ui->eht->clear();
    ui->sdt->clear();
    ui->edt->clear();
    ui->locationt->clear();
    ui->descriptiont->clear();
    ui->weather->clear();
}

void MainWindow::on_clear_clicked()
{
     clearEventFields();
}
void MainWindow::clearEventHighlights()
{

    QTextCharFormat emptyFormat;

    // Récupérer la liste des événements
    QVector<evenement> events = getEventsFromDatabase();

    // Itérer sur chaque date du calendrier
    QDate startDate = ui->calendarWidget->minimumDate();
    QDate endDate = ui->calendarWidget->maximumDate();
    for (QDate date = startDate; date <= endDate; date = date.addDays(1))
    {
        // Vérifier si la date correspond à la date de début d'un événement
        bool isStartEventDate = false;
        foreach(const evenement &event, events) {
            if (event.getStartD() == date) {
                isStartEventDate = true;
                QTextCharFormat format = ui->calendarWidget->dateTextFormat(date);
                QColor color("#8AF35D");
                format.setBackground(color);

                ui->calendarWidget->setDateTextFormat(date, format);
                break;
            }
        }

        if (!isStartEventDate) {
            ui->calendarWidget->setDateTextFormat(date, emptyFormat);
        }
    }
    ui->namecal->clear();
    ui->locationcal->clear();
    ui->pricecal->clear();
    ui->descriptioncal->clear();
    ui->datecal->clear();
    ui->starthcal->clear();
    ui->endhcal->clear();
    ui->nbcal->clear();
}

QVector<evenement> MainWindow::getEventsFromDatabase() {
    QVector<evenement> events;

    // Exécutez une requête SQL pour récupérer les événements de la base de données
    QSqlQuery query;
    if(query.exec("SELECT * FROM evenement")) {
        while(query.next()) {
            // Créez un objet evenement en utilisant les données récupérées de la base de données
            int id_event = query.value("id_event").toInt();
            int nb_employee = query.value("nb_employee").toInt();
            QString event_noun = query.value("event_noun").toString();
            QString location = query.value("location").toString();
            QString description = query.value("description").toString();
            QDate start_d = query.value("start_d").toDate();
            QDate end_d = query.value("end_d").toDate();
            QTime start_h = query.value("start_h").toTime();
            QTime end_h = query.value("end_h").toTime();
            float price_tick = query.value("price_tick").toFloat();

            evenement event(id_event, nb_employee, event_noun, location, description, start_d, end_d, start_h, end_h, price_tick);
            events.append(event);
        }
    } else {
        qDebug() << "Erreur lors de l'exécution de la requête SQL:" << query.lastError().text();
    }

    return events;
}

void MainWindow::calendarWidget() {
    // Récupérer les événements à partir de la base de données ou de toute autre source de données
    QVector<evenement> events = getEventsFromDatabase();

    // Parcourir les événements et les ajouter au calendrier
    foreach(const evenement &event, events) {
        // Créer un format de texte pour la date de début de l'événement
        QTextCharFormat format = ui->calendarWidget->dateTextFormat(event.getStartD());

        // Modifier le format de texte pour inclure des informations sur l'événement
        QString eventInfo = QString("Title: %1\nLocation: %2").arg(event.getEventNoun()).arg(event.getLocation());
        format.setToolTip(eventInfo);
        format.setBackground(Qt::green); // Définir une couleur de fond pour les dates avec des événements
        format.setForeground(QColor(128, 128, 128)); // Définir la couleur du texte en gris (ou toute autre couleur)

        // Appliquer le format de texte à la date de début de l'événement
        ui->calendarWidget->setDateTextFormat(event.getStartD(), format);
    }

    clearEventHighlights();
}
void MainWindow::highlightEventPeriod(const QDate &startDate, const QDate &endDate)
{

    QTextCharFormat format;
    QColor color("#46A91B");
    format.setBackground(color);

    for (QDate date = startDate; date <= endDate; date = date.addDays(1))
    {
        ui->calendarWidget->setDateTextFormat(date, format);
    }
}

void MainWindow::on_up_id_clicked()
{
     ui->table_event->setModel(e.afficher_tri_id_ascendant());
}

void MainWindow::on_down_id_clicked()
{
     ui->table_event->setModel(e.afficher_tri_id_descendant());
}


void MainWindow::on_up_noun_clicked()
{
     ui->table_event->setModel(e.afficher_tri_nom_ascendant());
}

void MainWindow::on_down_noun_clicked()
{
    ui->table_event->setModel(e.afficher_tri_nom_descendant());

}

void MainWindow::on_up_location_clicked()
{
    ui->table_event->setModel(e.afficher_tri_location_ascendant());
}

void MainWindow::on_down_location_clicked()
{
    ui->table_event->setModel(e.afficher_tri_location_descendant());
}

void MainWindow::on_up_start_clicked()
{
    ui->table_event->setModel(e.afficher_tri_start_ascendant());
}

void MainWindow::on_down_start_clicked()
{
    ui->table_event->setModel(e.afficher_tri_start_descendant());
}

void MainWindow::on_up_end_clicked()
{
    ui->table_event->setModel(e.afficher_tri_end_ascendant());
}

void MainWindow::on_down_end_clicked()
{
    ui->table_event->setModel(e.afficher_tri_end_descendant());
}

void MainWindow::on_up_price_clicked()
{
    ui->table_event->setModel(e.afficher_tri_price_ascendant());
}

void MainWindow::on_down_price_clicked()
{
    ui->table_event->setModel(e.afficher_tri_price_descendant());
}

void MainWindow::on_tout_supprimer_clicked()
{
    QModelIndexList selectedRows = ui->table_event->selectionModel()->selectedRows();
        // Parcourez les indices des lignes sélectionnées et supprimez-les une par une
        for (const QModelIndex &index : selectedRows) {
            // Obtenez la valeur dans la deuxième colonne (colonnes sont 1-indexées)
            QString valueToDelete = ui->table_event->model()->data(index.sibling(index.row(), 1)).toString();
            // Utilisez cette valeur pour appeler votre fonction de suppression
            e.supprimerEvenement(valueToDelete);
        }
        // Rafraîchissez le modèle de votre table view après la suppression
        ui->table_event->setModel(e.afficherEvenement());
        calendarWidget();
}
void MainWindow::on_calendar_event_clicked()
{
    ui->stackedWidgetEvent->setCurrentIndex(4);
       calendarWidget();
}

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    QVector<evenement> events = getEventsFromDatabase();
    clearEventHighlights();

    // Afficher la date sélectionnée
    ui->datecal->setText(date.toString("d MMMM yyyy"));

    // Recherche de l'événement correspondant à la date cliquée
    foreach(const evenement &event, events)
    {
        if (date >= event.getStartD() && date <= event.getEndD())
        {
            // Affichage des détails de l'événement
            ui->namecal->setText(event.getEventNoun());
            ui->locationcal->setText(event.getLocation());
            ui->pricecal->setText(QString::number(event.getPriceTick()) + " DT");
            ui->nbcal->setText(QString::number(event.getNbEmployee()) + " employee(s)");
            ui->descriptioncal->setText(event.getDescription());
            ui->starthcal->setText(event.getStartH().toString("hh:mm"));
            ui->endhcal->setText(event.getEndH().toString("hh:mm"));

            // Mise en surbrillance de la période de l'événement sur le calendrier
            highlightEventPeriod(event.getStartD(), event.getEndD());

            return;
        }
    }

    // Si aucun événement n'est trouvé pour la date cliquée, affichez un message
    QMessageBox::information(this, "No events", "No events found for this date.");
}

void MainWindow::on_add_cal_clicked()
{
    ui->stackedWidgetEvent->setCurrentIndex(3);
}

void MainWindow::on_add_cal_6_clicked()
{
     ui->stackedWidgetEvent->setCurrentIndex(2);
}

void MainWindow::on_supprimer_event_cal_clicked()
{
    QString noun=ui->namecal->text();
            bool test=e.supprimerEvenement(noun);
            QMessageBox msgBox;
            if(test){
                QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("deleted successfully \n"
                                                                                "Clicke Cancel to exite"),
                                         QMessageBox::Cancel);
                ui->table_event->setModel(e.afficherEvenement());
                //ui->stackedWidgetSetting->setCurrentIndex(1);

            }
            else
            { QMessageBox::critical(nullptr , QObject::tr("Not Ok "),QObject::tr(" not deleted successfully\n"
                                                                                      "Click Cancel to exit ."),
                                         QMessageBox::Cancel);
            }
            calendarWidget();
}

void MainWindow::on_generateAffiche_clicked()
{
    QString query = ui->descriptiont->text().trimmed();
    int id_event = ui->idt->text().toInt();
    executePythonScript(query);
    evenement e(id_event,"C:/Users/meddh/Desktop/noblePalette/noblePalette/script/event/image.jpg");
    e.ajouterImage(id_event);
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save PDF", ui->nount->text(),"*.pdf");

    // Vérifier si l'utilisateur a sélectionné un nom de fichier valide
    if (fileName.isEmpty()) {
        return; // Sortir de la fonction sans rien faire si aucun nom de fichier n'est sélectionné
    }

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A7);
    printer.setOutputFileName(fileName);

    QPainter painter;
    painter.begin(&printer);

       QPixmap image("C:/Users/meddh/Desktop/noblePalette/noblePalette/script/event/image.jpg");

       QSizeF paperSize = printer.pageRect(QPrinter::DevicePixel).size();
       QRectF targetRect(0, 0, paperSize.width(), paperSize.height());
       QRectF sourceRect(0, 0, image.width(), image.height());
       painter.setRenderHint(QPainter::SmoothPixmapTransform);
       painter.drawPixmap(targetRect, image, sourceRect);

       QString name = ui->nount->text();
       QFont nameFont("Trajan Pro", 25, QFont::Bold);

           // Générer une couleur aléatoire pour le titre
           QStringList titleColors = {"#D4AF37", "#A40FAF", "#013081", "#F9D598"};
           QString titleColor = titleColors.at(qrand() % titleColors.size());

           // Définir la couleur de la police du titre
           QColor nameColor(titleColor);
           painter.setFont(nameFont);
           painter.setPen(nameColor);

           QFontMetrics nameMetrics(nameFont);
           int maxWidth = 1400;
           QString elidedText = nameMetrics.elidedText(name, Qt::ElideRight, maxWidth);
           int textWidth = nameMetrics.width(elidedText);
           int xName = 800 - textWidth / 2;
           int yName = 1300;
           painter.drawText(xName, yName, elidedText);


         QString location = ui->locationt->text();
         QFont locationFont("Century Gothic", 8, QFont::Bold); // Police en gras et taille de police plus grande pour la localisation
         locationFont.setItalic(true); // Mettre en italique
         QColor locationColor= generateRandomColor();
         painter.setFont(locationFont);
         painter.setPen(locationColor); // Définir la couleur de la police
         QFontMetrics locationMetrics(locationFont);
         int xLocation = 300; // Position horizontale pour la localisation (au-dessus de l'image)
         int yLocation = 4200; // Position verticale pour la localisation (au-dessous de l'image)
         painter.drawText(xLocation, yLocation, location);

       QString startDateStr = ui->sdt->text();
       QDate startDate = QDate::fromString(startDateStr, "dd/MM/yyyy");
       QString formattedStartDate = startDate.toString("d MMMM yyyy");
       QFont startDateFont("Century Gothic", 8, QFont::Bold);
       QColor startDateColor= generateRandomColor();
       painter.setFont(startDateFont);
       painter.setPen(startDateColor);
       QFontMetrics startDateMetrics(startDateFont);
       int xStartDate = 1100;
       int yStartDate = 1500;
       painter.drawText(xStartDate, yStartDate, formattedStartDate);

       QString endDateStr = ui->edt->text();
       QDate endDate = QDate::fromString(endDateStr, "dd/MM/yyyy");
       QString formattedEndDate = endDate.toString("d MMMM yyyy");
       QFont endDateFont("Century Gothic", 8, QFont::Bold);
       QColor endDateColor= generateRandomColor();
       painter.setFont(endDateFont);
       painter.setPen(endDateColor);
       QFontMetrics endDateMetrics(endDateFont);
       int xEndDate = 1100;
       int yEndDate = 1700;
       painter.drawText(xEndDate, yEndDate, formattedEndDate);

       QTime startTime = ui->sht->time();
       QString formattedStartTime = startTime.toString("hh:mm AP");
       QFont startTimeFont("Century Gothic", 8, QFont::Bold);
       QColor startTimeColor= generateRandomColor();
       painter.setFont(startTimeFont);
       painter.setPen(startTimeColor);
       QFontMetrics startTimeMetrics(startTimeFont);
       int xStartTime = 1200;
       int yStartTime = 1900;
       painter.drawText(xStartTime, yStartTime, formattedStartTime);

       QTime endTime = ui->eht->time();
       QString formattedEndTime = endTime.toString("hh:mm AP");
       QFont endTimeFont("Century Gothic", 8, QFont::Bold);
       QColor endTimeColor= generateRandomColor();
       painter.setFont(endTimeFont);
       painter.setPen(endTimeColor);
       QFontMetrics endTimeMetrics(endTimeFont);
       int xEndTime = 1200;
       int yEndTime = 2100;
       painter.drawText(xEndTime, yEndTime, formattedEndTime);

       QString price = ui->pricet->text();
       QFont priceFont("Century Gothic", 8, QFont::Bold);
       QColor priceColor= generateRandomColor();
       painter.setFont(priceFont);
       painter.setPen(priceColor);
       QFontMetrics priceMetrics(priceFont);
       int xPrice = 300;
       int yPrice = 4500;
       painter.drawText(xPrice, yPrice, price + " DT");

       int iconSize = 150; // Taille de l'icône

       // Dessiner l'icône de localisation
       QPixmap locationIcon("C:/Users/meddh/Desktop/noblePalette/noblePalette/images/location.png");
       QPixmap scaledLocationIcon = locationIcon.scaled(iconSize, iconSize, Qt::KeepAspectRatio);
       int xLocationIcon = 100; // Position horizontale pour l'icône de localisation
       int yLocationIcon = 4100; // Position verticale pour l'icône de localisation
       painter.drawPixmap(xLocationIcon, yLocationIcon, scaledLocationIcon); // Dessiner l'icône de localisation

       // Dessiner l'icône Facebook
       QPixmap facebookIcon("C:/Users/meddh/Desktop/noblePalette/noblePalette/images/facebook.png");
       QPixmap scaledFacebookIcon = facebookIcon.scaled(iconSize, iconSize, Qt::KeepAspectRatio);
       int xFacebookIcon = 100; // Position horizontale pour l'icône Facebook
       int yFacebookIcon = 100; // Position verticale pour l'icône Facebook
       painter.drawPixmap(xFacebookIcon, yFacebookIcon, scaledFacebookIcon); // Dessiner l'icône Facebook

       // Dessiner l'icône Instagram
       QPixmap instagramIcon("C:/Users/meddh/Desktop/noblePalette/noblePalette/images/instagram.png");
       QPixmap scaledInstagramIcon = instagramIcon.scaled(iconSize, iconSize, Qt::KeepAspectRatio);
       int xInstagramIcon = 300; // Position horizontale pour l'icône Instagram
       int yInstagramIcon = 100; // Position verticale pour l'icône Instagram
       painter.drawPixmap(xInstagramIcon, yInstagramIcon, scaledInstagramIcon); // Dessiner l'icône Instagram

       // Dessiner l'icône Twitter
       QPixmap twitterIcon("C:/Users/meddh/Desktop/noblePalette/noblePalette/images/twitter.png");
       QPixmap scaledTwitterIcon = twitterIcon.scaled(iconSize, iconSize, Qt::KeepAspectRatio);
       int xTwitterIcon = 500; // Position horizontale pour l'icône Twitter
       int yTwitterIcon = 100; // Position verticale pour l'icône Twitter
       painter.drawPixmap(xTwitterIcon, yTwitterIcon, scaledTwitterIcon); // Dessiner l'icône Twitter

       // Dessiner l'icône WhatsApp
       QPixmap whatsappIcon("C:/Users/meddh/Desktop/noblePalette/noblePalette/images/whatsapp.png");
       QPixmap scaledWhatsappIcon = whatsappIcon.scaled(iconSize, iconSize, Qt::KeepAspectRatio);
       int xWhatsappIcon = 700; // Position horizontale pour l'icône WhatsApp
       int yWhatsappIcon = 100; // Position verticale pour l'icône WhatsApp
       painter.drawPixmap(xWhatsappIcon, yWhatsappIcon, scaledWhatsappIcon); // Dessiner l'icône WhatsApp

       // Dessiner l'icône ticket
       QPixmap priceIcon("C:/Users/meddh/Desktop/noblePalette/noblePalette/images/price.png");
       QPixmap scaledpriceIcon = priceIcon.scaled(iconSize, iconSize, Qt::KeepAspectRatio);
       int xpriceIcon = 100; // Position horizontale pour l'icône WhatsApp
       int ypriceIcon = 4400; // Position verticale pour l'icône WhatsApp
       painter.drawPixmap(xpriceIcon, ypriceIcon, scaledpriceIcon); // Dessiner l'icône WhatsApp


       // Générer le code QR
           QString eventIdString = QString::number(id_event);
           QString qrText = "Welcome to our event!""\n\t Event ID: " + eventIdString + " \n Description: " + query ;
           using namespace qrcodegen;
           QrCode qr = QrCode::encodeText(qrText.toUtf8().data(), QrCode::Ecc::MEDIUM);
           int scale = 20; // Facteur d'échelle pour agrandir le QR code
           int qrSize = qr.getSize() * scale; // Taille du QR code agrandi
           QImage qrImage(qrSize, qrSize, QImage::Format_RGB32);
           QRgb black = qRgb(0, 0, 0);
           QRgb white = qRgb(255, 255, 255);
           for (int y = 0; y < qrSize; ++y) {
               for (int x = 0; x < qrSize; ++x) {
                   // Mise à l'échelle de chaque module du QR code
                   int moduleX = x / scale;
                   int moduleY = y / scale;
                   qrImage.setPixel(x, y, qr.getModule(moduleX, moduleY) ? black : white);
               }
           }

           // Positionner le code QR
           QPointF qrPosition(2500, 3950); // Position du code QR dans le PDF
           QSizeF qrSizePdf(qrSize, qrSize);
           QRectF qrRect(qrPosition, qrSizePdf);
           painter.drawImage(qrRect, qrImage);


       painter.end();
}
void MainWindow::executePythonScript(const QString &query) {

    // Créer un processus pour exécuter l'interpréteur Python avec le script
    QProcess process;

    // Spécifier le chemin du script Python
    QString scriptPath = "C:/Users/meddh/Desktop/noblePalette/noblePalette/script/event/blabla.py";

    // Démarrer le processus avec le script Python et la requête comme argument
    QStringList arguments;
    arguments << query;
    process.start("python", QStringList() << scriptPath << arguments);

    // Attendre que le processus se termine
    process.waitForFinished();

    // Afficher la sortie du processus
    qDebug() << QString(process.readAllStandardOutput());
}
QColor MainWindow::generateRandomColor()
{
    // Initialiser le générateur de nombres aléatoires
    srand(time(0));

    // Générer des valeurs aléatoires pour les composants RGB
    int red = rand() % 256;
    int green = rand() % 256;
    int blue = rand() % 256;

    // Retourner une couleur avec les composants RGB générés
    return QColor(red, green, blue);
}
QMap<QString, QString> weatherIconMap = {
    {"clear sky", "C:/Users/meddh/Desktop/noblePalette/noblePalette/images/clear sky.png"},
    {"few clouds", "C:/Users/meddh/Desktop/noblePalette/noblePalette/images/few clouds.png"},
    {"scattered clouds", "C:/Users/meddh/Desktop/noblePalette/noblePalette/images/scattered clouds.png"},
    {"broken clouds", "C:/Users/meddh/Desktop/noblePalette/noblePalette/images/broken clouds.png"},
    {"shower rain", "C:/Users/meddh/Desktop/noblePalette/noblePalette/images/shower rain.png"},
    {"rain", "C:/Users/meddh/Desktop/noblePalette/noblePalette/images/rain.png"},
    {"thunderstorm", "C:/Users/meddh/Desktop/noblePalette/noblePalette/images/thunderstorm.png"},
    {"snow", "C:/Users/meddh/Desktop/noblePalette/noblePalette/images/snow.png"},
    {"mist", "C:/Users/meddh/Desktop/noblePalette/noblePalette/images/mist.png"},
    {"light rain", "C:/Users/meddh/Desktop/noblePalette/noblePalette/images/light rain.png"},
    {"overcast clouds", "C:/Users/meddh/Desktop/noblePalette/noblePalette/images/overcast clouds.png"},
    {"moderate clouds", "C:/Users/meddh/Desktop/noblePalette/noblePalette/images/moderate clouds.png"}

};

// Fonction pour obtenir le nom du fichier d'icône associé à une description météorologique
QString getWeatherIcon(const QString& description) {
    if (weatherIconMap.contains(description)) {
        return weatherIconMap[description];
    } else {
        // Retourner un fichier d'icône par défaut si la description n'est pas trouvée dans la table de correspondance
        return ":/weather_icons/default_icon.png";
    }
}
void MainWindow::getWeatherData(const QString& location) {
    disconnect(manager, &QNetworkAccessManager::finished, nullptr, nullptr);

    QString apiKey = "937cf79a2a953daf5eace53e744b22b8";
    QString apiUrl = "http://api.openweathermap.org/data/2.5/weather?q=" + location + "&appid=" + apiKey;

    QNetworkRequest request;
    request.setUrl(QUrl(apiUrl));

    QNetworkReply *reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            QJsonDocument jsonResponse = QJsonDocument::fromJson(response);

            if (!jsonResponse.isObject()) {
                qDebug() << "Error: Invalid JSON response";
                return;
            }

            QJsonObject jsonObject = jsonResponse.object();
            QString weatherDescription;
            QString temperature;
            QString humidity;
            QString windSpeed;
            QString iconFileName = ":/weather_icons/default_icon.png"; // Icône par défaut

            if (jsonObject.contains("weather")) {
                QJsonArray weatherArray = jsonObject["weather"].toArray();
                if (!weatherArray.isEmpty()) {
                    QJsonObject weatherObject = weatherArray.at(0).toObject();
                    weatherDescription = weatherObject["description"].toString();
                }
            }

            if (jsonObject.contains("main")) {
                QJsonObject mainObject = jsonObject["main"].toObject();
                if (mainObject.contains("temp")) {
                    double tempKelvin = mainObject["temp"].toDouble();
                    temperature = QString::number(tempKelvin - 273.15, 'f', 1) + " °C";
                }
                if (mainObject.contains("humidity")) {
                    humidity = QString::number(mainObject["humidity"].toDouble()) + "%";
                }
            }

            if (jsonObject.contains("wind")) {
                QJsonObject windObject = jsonObject["wind"].toObject();
                if (windObject.contains("speed")) {
                    windSpeed = QString::number(windObject["speed"].toDouble()) + " m/s";
                }
            }

            // Charger l'icône correspondante à la description météorologique
            if (weatherIconMap.contains(weatherDescription)) {
                iconFileName = weatherIconMap[weatherDescription];
            }

            // Charger l'image de l'icône
            QPixmap weatherIcon(iconFileName);
            // Redimensionner l'image de l'icône
            weatherIcon = weatherIcon.scaledToWidth(270, Qt::SmoothTransformation); // Ajustez la largeur selon vos besoins
            // Afficher l'icône dans un QLabel
            ui->weatherIcon->setPixmap(weatherIcon);

            // Afficher les informations météorologiques
            QString weatherInfo = "Weather: " + weatherDescription + "\n"
                                 + "Temperature: " + temperature + "\n"
                                 + "Humidity: " + humidity + "\n"
                                 + "Wind Speed: " + windSpeed;

            ui->weather->setText(weatherInfo);
        } else {
            qDebug() << "Error:" << reply->errorString();
        }
        reply->deleteLater();
    });
}

void MainWindow::on_weathergenerate_clicked()
{
    QString location = ui->locationt->text(); // Récupérer la localisation depuis l'interface utilisateur
    getWeatherData(location);
}

void MainWindow::on_updateEvent_clicked()
{
    // Récupérer les valeurs des champs d'édition d'un événement
        int id_event = ui->idt->text().toInt();
        int nb_employee = ui->nbt->text().toInt();// Par exemple, récupérez l'ID de l'événement à mettre à jour
        QString event_noun = ui->nount->text();
        QString location = ui->locationt->text();
        QString description = ui->descriptiont->text();
        //QDate start_d = ui->sdt->date();
        QDate start_d=QDate::fromString(ui->sdt->text(), "dd/MM/yyyy");
        //QDate end_d = ui->edt->date();
        QDate end_d=QDate::fromString(ui->edt->text(), "dd/MM/yyyy");
        QTime start_h = ui->sht->time();
        QTime end_h = ui->eht->time();
        float price_tick = ui->pricet->text().toInt();

        // Mettre à jour les champs de l'écran de mise à jour d'un événement avec les valeurs récupérées
        ui->nbempup->setText(QString::number(nb_employee));
        ui->idup->setText(QString::number(id_event));
        ui->eventnounup->setText(event_noun);
        ui->locationup->setText(location);
        ui->descriptionup->setPlainText(description);
        ui->sdup->setDate(start_d);
        ui->edup->setDate(end_d);
        ui->shup->setTime(start_h);
        ui->ehup->setTime(end_h);
        ui->priceup->setText(QString::number(price_tick));

        // Passer à l'écran de mise à jour d'un événement
        ui->stackedWidgetEvent->setCurrentIndex(1);
}

void MainWindow::on_pdfevent_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save PDF", ui->idt->text(), "*.pdf");

        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFileName(fileName);

        QPainter painter;
        painter.begin(&printer);
        // Définir la taille de la page
                QRect pageRect(0, 0, printer.width(), printer.height());

                // Dessiner une bordure autour de la page
                painter.drawRect(pageRect);


        // Définir le titre de l'événement
        QString title = "Event Information";
        QFont titleFont("Arial", 16, QFont::Bold);
        painter.setFont(titleFont);

        // Calculer la largeur du titre pour le centrer horizontalement
        int titleWidth = painter.fontMetrics().width(title);
        int titleX = (printer.width() - titleWidth) / 2;
        int titleY = 100; // Position verticale du titre
        painter.drawText(titleX, titleY, title);

        // Définir les informations sur l'événement
        QStringList labels;
        labels << "ID" << "Name" << "Location" << "Description" << "Start Date" << "End Date" << "Start Hour" << "End Hour" << "Employees number" << "Price ticket";
        QStringList values;
        values << ui->idt->text() << ui->nount->text() << ui->locationt->text() << ui->descriptiont->text() << ui->sdt->text() << ui->edt->text() << ui->sht->text() << ui->eht->text() << ui->nbt->text()+ QString(" employee(s)") << ui->pricet->text()+ QString(" DT");

        // Définir la police et la taille de police pour le texte des informations
        QFont textFont("Arial", 12);
        painter.setFont(textFont);

        // Dessiner les informations sur l'événement sous forme de tableau
        int tableX = 100; // Position horizontale du début du tableau
        int tableY = titleY + 50; // Position verticale du début du tableau
        int cellWidth = 200; // Largeur de chaque cellule du tableau
        int cellHeight = 30; // Hauteur de chaque cellule du tableau

        // Calculer la hauteur totale du tableau en fonction du nombre de lignes
        int tableHeight = cellHeight * labels.size();

        // Dessiner les lignes de séparation entre les cellules pour les étiquettes
        painter.drawRect(tableX, tableY, cellWidth, tableHeight);
        for (int i = 1; i < labels.size(); ++i) {
            painter.drawLine(tableX, tableY + i * cellHeight, tableX + cellWidth, tableY + i * cellHeight);
        }

        // Dessiner chaque étiquette dans le tableau
        for (int i = 0; i < labels.size(); ++i) {
            painter.drawText(tableX + 10, tableY + i * cellHeight + 20, labels[i]);
        }

        // Dessiner les lignes de séparation entre les cellules pour les valeurs
        painter.drawRect(tableX + cellWidth, tableY, cellWidth, tableHeight);
        for (int i = 1; i < values.size(); ++i) {
            painter.drawLine(tableX + cellWidth, tableY + i * cellHeight, tableX + 2 * cellWidth, tableY + i * cellHeight);
        }

        // Dessiner chaque valeur dans le tableau
        for (int i = 0; i < values.size(); ++i) {
            painter.drawText(tableX + cellWidth + 10, tableY + i * cellHeight + 20, values[i]);
        }

        // Charger et dessiner une image
        QPixmap image("C:/Users/meddh/Desktop/noblePalette/noblePalette/images/logo app.png"); // Assurez-vous de spécifier le bon chemin vers votre image
        QSize imageSize = image.size();
        QSize targetSize(300, 300); // Taille cible minimisée de l'image
        QSize scaledSize = imageSize.scaled(targetSize, Qt::KeepAspectRatio);
        int imageX = (printer.width() - scaledSize.width()) / 2; // Calculer la position X pour centrer l'image
        int imageY = tableY + tableHeight + 50; // Position Y pour placer l'image sous le tableau
        painter.drawPixmap(imageX, imageY, scaledSize.width(), scaledSize.height(), image);

        painter.end();
}

void MainWindow::on_supprimer_event_clicked()
{
    QString noun=ui->nount->text();
            bool test=e.supprimerEvenement(noun);
            QMessageBox msgBox;
            if(test){
                clearEventFields();
                clearEventdetailFields();
                QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("deleted successfully \n"
                                                                                "Clicke Cancel to exite"),
                                         QMessageBox::Cancel);
                ui->table_event->setModel(e.afficherEvenement());
                updateEventComboBox(ui->id_events);

            }
            else{ QMessageBox::critical(nullptr , QObject::tr("Not Ok "),QObject::tr(" not deleted successfully\n"
                                                                                      "Click Cancel to exit ."),
                                         QMessageBox::Cancel);
            }
            calendarWidget();
}

void MainWindow::on_list_clicked()
{
    ui->stackedWidgetEvent->setCurrentIndex(2);
}
void MainWindow::on_add_cal_4_clicked()
{
    ui->stackedWidgetEvent->setCurrentIndex(2);
}

void MainWindow::on_add_cal_3_clicked()
{
    ui->stackedWidgetEvent->setCurrentIndex(2);
}

void MainWindow::on_add_cal_2_clicked()
{
    ui->stackedWidgetEvent->setCurrentIndex(2);
}

void MainWindow::on_add_cal_5_clicked()
{
    ui->stackedWidgetEvent->setCurrentIndex(2);
}

void MainWindow::on_saveup_clicked()
{
    // Extracting data from UI elements
        int id_event = ui->idup->text().toInt();
        int nb_employee = ui->nbempup->text().toInt();
        QString event_noun = ui->eventnounup->text();
        QString location = ui->locationup->text();
        QString description = ui->descriptionup->toPlainText();
        QDate start_d = QDate::fromString(ui->sdup->text(), "dd/MM/yyyy");
        QDate end_d = QDate::fromString(ui->edup->text(), "dd/MM/yyyy");
        QTime start_h = ui->shup->time();
        QTime end_h = ui->ehup->time();
        float price_tick = ui->priceup->text().toFloat();
        if (start_d < QDate::currentDate()) {
            QMessageBox::critical(nullptr, QObject::tr("Error"),
                                  QObject::tr("Start date must be from %1 onwards.").arg(QDate::currentDate().toString("MM/dd/yyyy")),
                                  QMessageBox::Cancel);
            return;
        }

        if (start_d < QDate::currentDate()) {
            QMessageBox::critical(nullptr, QObject::tr("Error"),
                                  QObject::tr("Start date must be from %1 onwards.").arg(QDate::currentDate().toString("MM/dd/yyyy")),
                                  QMessageBox::Cancel);
            return;
        }


            if (end_d <= start_d) {
                QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                      QObject::tr("End date must be after the start date."),
                                      QMessageBox::Cancel);
                return;
            }
            /*if (start_h < QTime(7, 0) || start_h > QTime(20, 0)) {
                    QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                          QObject::tr("Start time must be between 7AM and 8PM."),
                                          QMessageBox::Cancel);
                    return;
                }*/

                /*if (end_h < QTime(7, 0) || end_h > QTime(20, 0)) {
                    QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                          QObject::tr("End time must be between 7AM and 8PM."),
                                          QMessageBox::Cancel);
                    return;
                }
    */
                if (end_h <= start_h) {
                    QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                          QObject::tr("End time must be after the start time."),
                                          QMessageBox::Cancel);
                    return;
                }

        // Creating evenement object and updating the event in the database
        evenement e(id_event, nb_employee, event_noun, location, description, start_d, end_d, start_h, end_h, price_tick);
        bool test = e.modifierEvenement();


        if (test) {
            QMessageBox::information(nullptr, QObject::tr("OK"),
                                     QObject::tr("Updated successfully.\nClick Cancel to exit."),
                                     QMessageBox::Cancel);
            ui->table_event->setModel(e.afficherEvenement());
        } else {
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                  QObject::tr("Modification failed.\nClick Cancel to exit."),
                                  QMessageBox::Cancel);
        }

        // Changing the current index of stacked widget
        ui->stackedWidgetEvent->setCurrentIndex(2);
        calendarWidget();
}



void MainWindow::on_stat_clicked()
{
    ui->stackedWidgetEvent->setCurrentIndex(5);
    e.afficherPieChart(ui->label_statEvent);
}

void MainWindow::on_add_event_2_clicked()
{
    ui->stackedWidgetEvent->setCurrentIndex(3);
}

void MainWindow::on_searchevent_textEdited(const QString &arg1)
{
    QSqlQueryModel* model = e.rechercher(arg1);
    ui->table_event->setModel(model);
}

void MainWindow::verifyRFID() {
    QString RFID = QString::fromLatin1(A.read_from_arduino()).trimmed(); // Convertit les données en QString
    if (e.rechercherRFID(RFID) != 0) {
        qDebug() << "trouvee";
        // Vous pouvez ajouter d'autres actions ici si nécessaire
    } else {
        qDebug() << "non trouvee";
        // Vous pouvez ajouter d'autres actions ici si nécessaire
    }
}

