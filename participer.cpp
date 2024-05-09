#include "participer.h"
#include<QDebug>
#include <QFile>
#include "mainwindow.h"
#include "ui_mainwindow.h"


Participer::Participer(int g,int e)
{
    idGuest = g;
    idEvent = e;
}
QSqlQueryModel* Participer::idGuests(int id_event) {
    QSqlQueryModel *model = new QSqlQueryModel();

    // Création de la requête SQL avec une clause WHERE pour filtrer par l'ID de l'événement
    QString query = QString("SELECT idguest FROM PARTICIPER WHERE idevent = %1").arg(id_event);

    // Exécution de la requête SQL et configuration du modèle avec les résultats
    model->setQuery(query);

    return model;
}

void Participer::precenceGuest(int id_event, int id_guest) {
    // Création de la requête SQL pour mettre à jour la présence
    QString query = QString("UPDATE PARTICIPER SET presence = 1 WHERE idevent = %1 AND idguest = %2")
                        .arg(id_event)
                        .arg(id_guest);

    // Exécution de la requête SQL
    QSqlQuery sqlQuery;
    if (!sqlQuery.exec(query)) {
        qDebug() << "Erreur lors de l'exécution de la requête :" << sqlQuery.lastError().text();
    } else {
        qDebug() << "Mise à jour de la présence réussie.";
    }
}

QSqlQueryModel* Participer::getGuestsInfo(int idevent) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT CAST(GUEST.CIN AS varchar(255)), GUEST.name, CAST(GUEST.phone AS varchar(255)) "
                  "FROM PARTICIPER "
                  "INNER JOIN GUEST ON PARTICIPER.IDGUEST = GUEST.CIN "
                  "WHERE PARTICIPER.IDEVENT = :idevent");
    query.bindValue(":idevent", idevent);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
        delete model;
        return nullptr;
    }

    model->setQuery(query);
    return model;
}

bool Participer::supprimerp(int cin)
{
    QSqlQuery query;
    query.prepare("DELETE FROM PARTICIPER WHERE IDGUEST = :cin");
    query.bindValue(":cin", cin);

    if (!query.exec()) {
        qDebug() << "Erreur SQL:" << query.lastError().text(); // Utiliser qDebug() au lieu de QDebug()
        return false;
    }
    return true; // Retourner true si l'ajout a réussi
}

QSqlQueryModel* Participer::getAllGuestsInfo(int idevent) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT CAST(GUEST.CIN AS varchar(255)), GUEST.name, GUEST.age, GUEST.gender, GUEST.address, CAST(GUEST.phone AS varchar(255)), GUEST.email "
                  "FROM GUEST "
                  "WHERE GUEST.CIN NOT IN (SELECT PARTICIPER.IDGUEST FROM PARTICIPER WHERE PARTICIPER.IDEVENT = :idevent) AND (GUEST.CIN>1)");
    query.bindValue(":idevent", idevent);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
        delete model;
        return nullptr;
    }

    model->setQuery(query);
    return model;
}
bool Participer::ajouterp()
{
    Connection connection;


    QSqlQuery query;
    query.prepare("INSERT INTO Participer (idguest, idevent) VALUES (:idguest, :idevent)");

    query.bindValue(":idguest", this->idGuest);
    query.bindValue(":idevent", this->idEvent);

    if (!query.exec()) {
        qDebug() << "Erreur d'exécution de la requête SQL:" << query.lastError().text();
        return false;
    }

    return true; // Retourner true si l'ajout a réussi
}

//mainwindow participer


void MainWindow::on_go_to_participer_clicked()
{
    ui->tableViewParticiper->setModel(p.getGuestsInfo(ui->idEventParticiper->text().toInt()));
    ui->stackedWidgetEvent->setCurrentIndex(6);
}


void MainWindow::on_supprimeParSelectionParticiper_clicked()
{
    QModelIndexList selectedRows = ui->tableViewParticiper->selectionModel()->selectedRows();
    // Parcourez les indices des lignes sélectionnées et supprimez-les une par une
    for (const QModelIndex &index : selectedRows) {
        // Obtenez la valeur dans la première colonne (colonnes sont 0-indexées)
        int valueToDelete = ui->tableViewParticiper->model()->data(index.sibling(index.row(), 0)).toInt();
        // Utilisez cette valeur pour appeler votre fonction de suppression
        p.supprimerp(valueToDelete);
    }

    // Rafraîchissez le modèle de votre table view après la suppression
    ui->tableViewParticiper->setModel(p.getGuestsInfo(ui->idEventParticiper->text().toInt()));
}


void MainWindow::on_go_to_participer_2_clicked()
{
    ui->tableViewParticiper_2->setModel(p.getAllGuestsInfo(ui->idEventParticiper->text().toInt()));
    ui->stackedWidgetEvent->setCurrentIndex(7);

}
void MainWindow::on_go_to_participer_3_clicked()
{
    QModelIndexList selectedRows = ui->tableViewParticiper_2->selectionModel()->selectedRows();
    // Parcourez les indices des lignes sélectionnées et supprimez-les une par une
    for (const QModelIndex &index : selectedRows) {
        // Obtenez la valeur dans la première colonne (colonnes sont 0-indexées)
        int valueIdGuest = ui->tableViewParticiper_2->model()->data(index.sibling(index.row(), 0)).toInt();
        Participer p(valueIdGuest , ui->idEventParticiper->text().toInt());
        // Utilisez cette valeur pour appeler votre fonction de suppression
        p.ajouterp();
    }

    // Rafraîchissez le modèle de votre table view après la suppression
    ui->tableViewParticiper->setModel(p.getGuestsInfo(ui->idEventParticiper->text().toInt()));
    ui->stackedWidgetEvent->setCurrentIndex(6);

}
