#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include "employee.h"
#include "evenement.h"
#include "guest.h"
#include "artist.h"
#include "article.h"
#include "arduino.h"
#include "association.h"
#include "participer.h"
#include<QSqlRecord>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <QtWidgets>
#include <QPrinter>
#include <QPainter>
#include <QPieSeries>
#include <QPieSlice>
#include <QChart>
#include <QChartView>
#include <QCalendarWidget>
#include <QProcess>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QMessageBox>
#include <QApplication>
#include <QVector>
#include <QColor>
#include <QCoreApplication>
#include <QImage>
#include <QTime> // Inclure la bibliothèque pour utiliser qrand()
#include <qr.h>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPixmap>
#include <QSqlQuery>
#include <QSqlError>
#include <QTextToSpeech>
#include "controller.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Classe pour gérer la reconnaissance vocale dans un thread séparé
class SpeechRecognitionWorker : public QObject {
    Q_OBJECT
public:
    explicit SpeechRecognitionWorker(QObject *parent = nullptr) : QObject(parent) {}

public slots:
    void startRecognition() {
        // Mettez en place le processus de reconnaissance vocale
        QProcess *process = new QProcess(this);
        process->setProcessChannelMode(QProcess::MergedChannels);

        // Exécutez le code Python de reconnaissance vocale
        QString pythonCode = R"(
import speech_recognition as sr
import re
import time

# Fonction pour effectuer la reconnaissance vocale
def recognize():
    # Initialise le recognizer
    recognizer = sr.Recognizer()

    # Utilise le microphone comme source audio
    with sr.Microphone() as source:
        print("")
        recognizer.adjust_for_ambient_noise(source)


        timeout = 5  # 5seconde
        start_time = time.time()  # Heure de début
        while (time.time() - start_time) <= timeout:
            try:
                audio_data = recognizer.listen(source, timeout=2)  # Attend jusqu'à 2 secondes
                text = recognizer.recognize_google(audio_data, language='fr-FR')
                print("", text)

                # Si le texte contient "nom", imprimez-le
                match = re.search(r'nom\s*:\s*([\w\s]+)', text, re.IGNORECASE)
                if match:
                    print("Nom reconnu:", match.group(1))
                    break

            except sr.WaitTimeoutError:
                pass
            except sr.UnknownValueError:
                print("Speech Recognition could not understand audio.")
            except sr.RequestError as e:
                print(f"Could not request results from Google Speech Recognition service; {e}")
            time.sleep(2)  # Attendre 2 secondes entre chaque itération

# Appel de la fonction de reconnaissance vocale
recognize()
)";
        // Exécutez le code Python
        process->start("python", QStringList() << "-c" << pythonCode);

        // Connectez-vous pour lire la sortie de la reconnaissance vocale
        connect(process, &QProcess::readyReadStandardOutput, [=]() {
            // Lire la sortie standard du processus (résultats de la reconnaissance vocale)
            QByteArray output = process->readAllStandardOutput();

            // Traitez la sortie comme vous le souhaitez, par exemple, mettez à jour un champ QLineEdit avec le texte reconnu
            QString result = QString::fromUtf8(output);
            emit recognizedText(result.trimmed());
        });

        connect(process, &QProcess::readyReadStandardError, [=]() {
            // Gérer les erreurs de processus si nécessaire
            QByteArray error = process->readAllStandardError();
            qDebug() << "Error:" << error;
        });

        // Attendre que le processus se termine (peut être en option)
        process->waitForFinished();
    }
signals:
    void recognizedText(const QString &text);
};






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
      void verifyPasswordStrength(const QString &password);
private slots:
      void on_AddEmployee_2_clicked();

      void on_pushButtonEmployee_clicked();

      void on_statEmployee_clicked();

      void on_supprimer_Employee_2_clicked();
      void on_pushButton_upCin_clicked();

        void on_pushButton_downCin_clicked();

        void on_pushButton_upName_clicked();

        void on_pushButton_downName_clicked();

        void on_pushButton_upLastname_clicked();

        void on_pushButton_downLastname_clicked();

        void on_pushButton_upAddress_clicked();

        void on_pushButton_downAddress_clicked();

        void on_pushButton_upFunction_clicked();

        void on_pushButton_downFunction_clicked();

        void on_pushButton_upMail_clicked();

        void on_pushButton_downMail_clicked();

        void on_save_AddEmployee_clicked();


        void on_tabEmployee_clicked(const QModelIndex &index);

        void on_supprimer_Employee_clicked();

        void on_pdfEmployee_clicked();

        void on_updateEmployee_clicked();

        void on_save_updateEmployee_clicked();

        void on_searchTextBox_employee_textEdited(const QString &arg1);

        void on_pushButton_AddImageEmployee_clicked();

        void on_pushButton_UpDateImageEmployee_clicked();

        void on_pushButtonLogin_clicked();

        void on_pushButton_forgetPassword_clicked();
        void on_Valider_button_clicked();

        void on_pushButton_ValidNewPassword_clicked();

        void on_checkBox_passwordLogin_stateChanged();

        void on_checkBox_Newpassword_stateChanged();

        void on_checkBox_Confirmpassword_stateChanged();

        void on_checkBox_passwordSave_stateChanged();

        void on_logout_clicked();

        void on_clearEmployee_clicked();
        //event
       /* void on_pushButtonEvents_clicked();
        void on_tableView_14_clicked(const QModelIndex &index);

            void on_searchevent_textEdited(const QString &arg1);

            void on_ajouterArt_19_clicked();

            void on_up_id_clicked();

            void on_down_id_clicked();



            void on_up_noun_clicked();

            void on_down_noun_clicked();

            void on_up_location_clicked();

            void on_down_location_clicked();

            void on_up_start_clicked();

            void on_down_start_clicked();

            void on_up_end_clicked();

            void on_down_end_clicked();

            void on_up_price_clicked();

            void on_down_price_clicked();
            void calendarWidget();
            QVector<evenement> getEventsFromDatabase() ;
            void clearEventHighlights();
            void on_stat_clicked();
            void highlightEventPeriod(const QDate &startDate, const QDate &endDate);
            void on_calendarWidget_clicked(const QDate &date);
            void executePythonScript(const QString &query);
            void on_add_cal_clicked();
            void on_supprimer_event_2_clicked();
            QColor generateRandomColor();
            void on_stat_2_clicked();
            void getWeatherData(const QString& location);
            void on_generateAffiche_clicked();

            void on_weathergenerate_clicked();*/


        void on_pushButtonEvents_clicked();

        void on_add_event_clicked();

        void on_table_event_clicked(const QModelIndex &index);

        void clearEventFields();

        void clearEventdetailFields();

        void on_clear_clicked();

        void calendarWidget();

        QVector<evenement> getEventsFromDatabase() ;

        void clearEventHighlights();

        void on_up_id_clicked();

        void on_down_id_clicked();

        void on_up_noun_clicked();

        void on_down_noun_clicked();

        void on_up_location_clicked();

        void on_down_location_clicked();

        void on_up_start_clicked();

        void on_down_start_clicked();

        void on_up_end_clicked();

        void on_down_end_clicked();

        void on_up_price_clicked();

        void on_down_price_clicked();

        void on_tout_supprimer_clicked();

        void highlightEventPeriod(const QDate &startDate, const QDate &endDate);

        void on_add_cal_clicked();

        void on_supprimer_event_cal_clicked();

        void on_generateAffiche_clicked();

        void executePythonScript(const QString &query);

        QColor generateRandomColor();

        void getWeatherData(const QString& location);

        void on_weathergenerate_clicked();

        void on_updateEvent_clicked();

        void on_pdfevent_clicked();

        void on_supprimer_event_clicked();

        void on_list_clicked();

        void on_saveup_clicked();


        void on_calendar_event_clicked();

        void on_calendarWidget_clicked(const QDate &date);

        void on_stat_clicked();

        void on_add_event_2_clicked();

        void on_searchevent_textEdited(const QString &arg1);

        void on_pushButtonGuest_clicked();

        void on_tableViewGuest_doubleClicked(const QModelIndex &index);

        void on_go_to_addGuest_clicked();

        void on_supprimer_Guest_clicked();

        void on_go_to_updateGuest_clicked();

        void on_go_to_affSimple_from_addGuest_clicked();

        void on_go_to_addSimple_from_update_clicked();

        void on_searchGuest_textEdited(const QString &arg1);

        void on_go_to_listGuest_from_addGuest_clicked();

        void on_go_to_list_from_affSimple_clicked();

        void on_go_to_listGuest_from_updateGuest_clicked();

        void on_pdfGuest_clicked();

        void on_rechercheCinCart_clicked();

        void on_addImageGuest_clicked();

        void on_updateImage_clicked();

        void on_supprimer_GuestSelect_clicked();

        void on_statEmotion_clicked();

        void on_tri_Ccin_clicked();

        void on_tri_Dcin_clicked();

        void on_tri_Cname_clicked();

        void on_tri_Dname_clicked();

        void on_tri_Cage_clicked();

        void on_tri_Dage_clicked();

        void on_tri_Cgender_clicked();

        void on_tri_Dgender_clicked();

        void on_tri_Caddress_clicked();

        void on_tri_Daddress_clicked();

        void on_tri_Cphone_clicked();

        void on_tri_Dphone_clicked();

        void on_tri_Cemail_clicked();

        void on_tri_Demail_clicked();

        void on_surv_Guest_clicked();





        //partie article
        void on_save_5_clicked();
        void on_pushButtonProduct_clicked();
        void on_listtoaddpro_clicked();

                void on_pushButton_14_clicked();

                    void on_ajouterArt_clicked();
                    void on_lireai_clicked();

                    void on_tableView_17_doubleClicked(const QModelIndex &index);

                    void on_updateEmployee_5_clicked();

                    void on_tableView_6_doubleClicked(const QModelIndex &index);

                    void on_envoyer_clicked();

                    void on_chatbot_clicked();

                    void on_supprimer_25_clicked();

                    void on_searchTextBox_19_textChanged(const QString &arg1);


                    void on_pushButton_2_clicked();

                    void on_supprimer_26_clicked();



                    void on_triid1_clicked();

                    void on_triid2_clicked();

                    void on_triname1_clicked();

                    void on_triname2_clicked();

                    void on_tridomaine1_clicked();

                    void on_tridomaine2_clicked();

                    void on_suppgen_clicked();

                    void on_tableView_4_doubleClicked(const QModelIndex &index);

                    void on_del_all_clicked();

                    void on_supprimer_4_clicked();

                    void on_supprimer_24_clicked();

                    void on_liste_clicked();

                    void on_triid1_9_clicked();

                    void on_triid2_4_clicked();

                    void on_triid1_10_clicked();

                    void on_triid2_5_clicked();

                    void on_triid1_11_clicked();

                    void on_triid2_6_clicked();

                    void on_triid1_12_clicked();

                    void on_triid2_7_clicked();

                    void on_start_clicked();

                    void on_rating_clicked();

                    void on_pub_clicked();

                    void on_supprimer_32_clicked();

                    void on_gerervedio_clicked();







                    //partie artist
                    void on_ararriere_clicked();
                       void on_ararriere_2_clicked();
                       void on_ararriere_7_clicked();
                       void on_ararriere_3_clicked();
                       void on_aradd_clicked();
                       void on_arupdate_clicked();
                       void on_arsupp_clicked();
                       void on_arajouter_clicked();
                       void on_arclear_clicked();
                       void on_artableView_2_doubleClicked(const QModelIndex &index);
                       void on_arupdate_2_clicked();
                       void on_arclear_2_clicked();
                       void on_ardelete_clicked();
                       void on_arsearchTextBox_textChanged(const QString &arg1);



                        void on_artableView_3_doubleClicked(const QModelIndex &index);
                        void on_arstat_clicked();
                        void on_arpdf_clicked();
                        void on_arassistant_clicked();




                        //reconnaissance
                        void on_reconnaissance_clicked();
                        void on_reconnaissance_2_clicked();
                        void on_reconnaissance_3_clicked();
                        void on_reconnaissance_4_clicked();
                        void on_reconnaissance_5_clicked();
                        void on_reconnaissance_6_clicked();
                        void on_reconnaissance_7_clicked();
                        void on_reconnaissance_8_clicked();







                        // Slot pour mettre à jour les champs avec le texte reconnu
                        void updateNom(const QString &text);
                        void updateCIN(const QString &text);
                        void updatePrenom(const QString &text);
                        void updateMail(const QString &text);
                        void updateDescription(const QString &text);
                        void updateTelephone(const QString &text);
                        //void updateSexe(const QString &text);
                        void updateAdresse(const QString &text);
                        void updateDomaine(const QString &text);





                        //--------scann par camera ---
                        void on_scann_clicked();
                        void on_scann_2_clicked();
                        void on_scann_3_clicked();
                        void on_scann_4_clicked();
                        void on_scann_5_clicked();
                        void on_scann_6_clicked();
                        void on_scann_7_clicked();
                        void on_scann_8_clicked();

                        // ------- mail--------


                        void on_artableView_doubleClicked(const QModelIndex &index);

                        void on_arpdf_3_clicked();

                        void on_arpicture_clicked();

                        void on_arpicture_2_clicked();



                        void on_checkBox_stateChanged(int arg1);





                    //------ TRIE------
                        void on_desc_1_clicked();
                        void on_asc_1_clicked();
                        void on_desc_2_clicked();
                        void on_asc_2_clicked();
                        void on_desc_3_clicked();
                        void on_asc_3_clicked();
                        void on_desc_4_clicked();
                        void on_asc_4_clicked();
                        void on_desc_5_clicked();
                        void on_asc_5_clicked();
                        void on_desc_6_clicked();
                        void on_asc_6_clicked();
                        void on_desc_7_clicked();
                        void on_asc_7_clicked();











                        void on_pushButtonArtist_clicked();





                //association
                        void on_save_a_clicked();


                        void on_tableView_23_doubleClicked(const QModelIndex &index);


                        void on_asupdate_clicked();

                        void on_supprimer_23_clicked();

                        void on_save_4_clicked();

                        void on_searchTextBox_21_textChanged(const QString &arg1);

                        void on_searchTextBox_18_textChanged(const QString &arg1);


                        void on_comboBox_4_activated(const QString &arg1);

                        void on_tableView_22_doubleClicked(const QModelIndex &index);

                        void on_assupprimer_clicked();

                        //void on_supprimer_31_clicked();

                        void on_asPDF_clicked();

                        void on_comboBox_10_currentIndexChanged(int index);


                        void on_listtoaddass_clicked();


                        void on_supprimer_36_clicked();




                        void on_pushButtonAssociation_clicked();

                        void on_go_to_participer_clicked();


                        void on_supprimeParSelectionParticiper_clicked();

                        void on_go_to_participer_2_clicked();

                        void on_updateEmployee_3_clicked();
// **************************************************** arduino yassine w iheb ******************************************************
                        void on_verifier_clicked();


private:

        //guest
        Guest g;
        Participer p;
        QString imagePath;
        Artiste a;
        int cinn;
        QThread *thread;
        SpeechRecognitionWorker *worker;
        QPixmap imagePixmap;
        QString selectedImagePath; // Déclaration de selectedImagePath comme membre privé de la classe
        QString selectedImagePathu; // Définir une variable globale pour stocker le chemin de l'image sélectionnée update

        //
    Ui::MainWindow *ui;
    //arduino
    QByteArray data; // variable contenant les données reçues

    Arduino A; // objet temporaire



    QDialog *dialog;
        QLabel *label_1;
        QLineEdit *lineEdit ;
        int *code;
        int *failedAttempts;
        QString mail;
        employee emp;
        int id;
        Association as;

        //event
        evenement e;
        QNetworkAccessManager *manager;
        QProcess *process;
        QStringList artistCINs; // Liste pour stocker les CINs d'artistes

        //article
        void  executePythonScript(const QString &scriptPath, const QStringList &arguments);
        void executePythonChatBot(const QString &userText);
        void handlePythonError();
        void chargerCINsArtistes();
        void handleChatBotResponse();
        Article article;
        QSqlQueryModel *model; // Model for your QTableView
        QTextToSpeech *speech;

        int idA;

        void setCenter(QVariant, QVariant);
        void addMarker(QVariant lat, QVariant lng);


        //void fetchArtistCINs();
            void updateArtistComboBox();

            void updateLineEditWithVoice();

    void changeChatIcon(int rating);
    void eventCheckLoop();
       void checkEventStatus();
       // Déclarations des fonctions
};
#endif // MAINWINDOW_H
