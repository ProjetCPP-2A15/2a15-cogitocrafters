#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "artist.h"
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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonEvents_clicked();
    void on_pushButtonProduct_clicked();
    void on_pushButtonGuest_clicked();
    void on_pushButtonArtist_clicked();
    void on_pushButtonAssociation_clicked();
    void on_pushButtonSetting_clicked();

    // partie artiste
    void on_addEmpButton_clicked();
    void selectedPushButton(QPushButton *button);
    void on_searchButton_clicked();
    void deselectedPushButton(QPushButton *button);
    void on_deleteEmpButton_clicked();
    void on_updateEmpButton_clicked();
    void on_pushButton_5_clicked(); // submit fel Add
    void on_pushButton_6_clicked(); // clear fel Add
    void on_pushButton_21_clicked();
    void on_pushButton_20_clicked();
    void on_tableView_6_doubleClicked(const QModelIndex &index);
    void on_pushButton_22_clicked();
    void on_updateTableView_2_doubleClicked(const QModelIndex &index);
    void on_searchTextBox_textChanged(const QString &arg1);
    void on_trierp_clicked();
    void on_trierc_clicked();
    void on_triern_clicked();
    void on_pdf_clicked();
    void on_stat_clicked();
    void on_assistant_clicked();


    //reconnaissance
    void on_reconnaissance_clicked();
    void on_reconnaissance_7_clicked();
    void on_reconnaissance_6_clicked();
    void on_reconnaissance_5_clicked();
    void on_reconnaissance_9_clicked();
    void on_reconnaissance_4_clicked();
    void on_reconnaissance_3_clicked();
    void on_reconnaissance_2_clicked();
    void on_reconnaissance_8_clicked();







    // Slot pour mettre à jour le champ nom_2 avec le texte reconnu
    void updateNom(const QString &text);
    void updateCIN(const QString &text);
    void updatePrenom(const QString &text);
    void updateMail(const QString &text);
    void updateDescription(const QString &text);
    void updateTelephone(const QString &text);
    void updateSexe(const QString &text);
    void updateAdresse(const QString &text);
    void updateDomaine(const QString &text);






private:
    Ui::MainWindow *ui;
    Artiste a;
    QSqlTableModel *model;
    int cinn;

    // Thread et travailleur de reconnaissance vocale
    QThread *thread;
    SpeechRecognitionWorker *worker;
};

#endif // MAINWINDOW_H
