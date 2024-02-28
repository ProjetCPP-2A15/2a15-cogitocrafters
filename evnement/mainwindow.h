#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"article.h"
#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QProcess>
#include <QTextToSpeech>


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

    void on_pushButton_14_clicked();


    void on_lireai_clicked();

    void on_tableView_17_doubleClicked(const QModelIndex &index);

    void on_updateEmployee_5_clicked();

    void on_tableView_6_doubleClicked(const QModelIndex &index);

    void on_envoyer_clicked();

    void on_chatbot_clicked();

    void on_supprimer_25_clicked();

    void on_comboBox_5_currentIndexChanged(int index);

    void on_searchTextBox_19_textChanged(const QString &arg1);

    void on_comboBox_5_activated(int index);

    void on_pushButton_2_clicked();

    void on_supprimer_26_clicked();

private:
    Ui::MainWindow *ui;
    QProcess *process;

    void  executePythonScript(const QString &scriptPath, const QStringList &arguments);
    void executePythonChatBot(const QString &userText);
    void handlePythonOutput();
    void handlePythonError();
    Article article;
    QSqlQueryModel *model; // Model for your QTableView

    int idA;
    QTextToSpeech *speech;






};
#endif // MAINWINDOW_H
