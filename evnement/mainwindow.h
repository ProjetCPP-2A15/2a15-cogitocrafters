#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QTableView>
#include <QLineEdit>
#include <QMessageBox>

#include "guest.h"

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

    void on_ajouterArt_7_clicked();

    void on_ajouterArt_4_clicked();

    void on_ajouterArt_8_clicked();

    void on_ajouterArt_9_clicked();

    void on_save_clicked();

    void on_updateEmployee_clicked();

    void on_addEmployee_clicked();

    void on_save_2_clicked();



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

    void on_updateEmployee_4_clicked();

    void on_updateEmployee_2_clicked();

    void on_save_5_clicked();

    void on_save_7_clicked();

    void on_save_6_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_supprimer_Guest_clicked();

    void on_searchGuest_textEdited(const QString &text);

    void on_comboBoxSortGuest_activated(const QString &text);

    void on_ajouterArt_21_clicked();

    void on_ajouterArt_18_clicked();

    void on_ajouterArt_22_clicked();

    void on_supprimer_18_clicked();

    void on_supprimer_34_clicked();
    
private:
    Ui::MainWindow *ui;
    Guest g;
};
#endif // MAINWINDOW_H
