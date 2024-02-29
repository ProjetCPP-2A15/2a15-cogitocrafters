#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "evenement.h"
#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QtWidgets>
#include <QPrinter>
#include <QPainter>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void selectButton(QPushButton *button);
    void deselectButton(QPushButton *button);

private slots:
    void on_pushButtonEvents_clicked();

    void on_pushButtonProduct_clicked();

    void on_pushButtonGuest_clicked();

    void on_pushButtonArtist_clicked();

    void on_pushButtonAssociation_clicked();

    void on_pushButtonSetting_clicked();

    // partie artiste
    void on_addEmpButton_clicked();
    void on_searchButton_clicked();
    void on_deleteEmpButton_clicked();
    void on_updateEmpButton_clicked();

    //void on_pushButton_15_clicked();

    void on_pushButton_clicked();

    void on_pushButtonProduct_2_clicked();

    void on_pushButtonProduct_3_clicked();

    void on_supprimer_5_clicked();

    void on_ajouterArt_clicked();

    void on_list_clicked();

    void on_add_event_clicked();

    void on_ajouterArt_4_clicked();

    void on_ajouterArt_8_clicked();

    void on_ajouterArt_9_clicked();

    void on_save_clicked();

    void on_updateEmployee_clicked();

    void on_addEmployee_clicked();
//
    void on_save_2_clicked();

    void clearEventFields();

    void on_clear_clicked();

    void clearEventdetailFields();

    void on_updateEvent_clicked();
    void on_saveup_clicked();
    void on_pdfevent_clicked();
//

   void on_supprimer_event_clicked();

    void on_supprimer_11_clicked();

    void on_supprimer_35_clicked();

    void on_listtoaddass_clicked();

    void on_listtoaddpro_clicked();

    void on_supprimer_38_clicked();

    void on_supprimer_22_clicked();

    void on_save_3_clicked();

    void on_save_8_clicked();

    void on_ajouterArt_14_clicked();

    void on_updateEmployee_3_clicked();

    void on_updateEmployee_2_clicked();

    void on_save_5_clicked();

    void on_save_7_clicked();

    void on_save_6_clicked();

    void on_tableView_14_clicked(const QModelIndex &index);

    void on_comboBox_2_activated(const QString &arg1);

private:
    Ui::MainWindow *ui;
    evenement e;

};
#endif // MAINWINDOW_H
