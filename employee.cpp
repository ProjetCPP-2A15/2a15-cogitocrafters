#include "employee.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRecord>
#include<QFile>
#include <qsqlerror.h>
#include <QCryptographicHash>
#include<QRegularExpression>
#include<QtNetwork>
#include <QSslSocket>
#include <QTcpSocket>
#include<QSsl>
#include <cstdlib>
#include <ctime>
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPainter>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QApplication>
#include <QtWidgets>
#include <QPrinter>
#include "smtp.h"

employee::employee()
{
    id=0;
    name="";
    lastname="";
    address="";
    sex="";
    dateBirth=QDate();
    mail="";
    function="";
    password="";
    //profil="";
    phoneNumber=0;
    imagePath="";

}
employee::employee(int id,QString name, QString lastname,QString address,QString sex,QString mail,QString function,QString password,QDate dateBirth,int phoneNumber,QString imagePath)
{
    this->id=id;
    this->name=name;
    this->lastname=lastname;
    this->address=address;
    this->sex=sex;
    this->dateBirth=dateBirth;
    this->mail=mail;
    this->function=function;
    this->password=password;
    //this->profil=profil;
    this->phoneNumber=phoneNumber;
    this->imagePath=imagePath;
}
employee::employee(int id,QString name, QString lastname,QString address,QString sex,QString mail,QString function,QString password,QDate dateBirth,int phoneNumber)
{
    this->id=id;
    this->name=name;
    this->lastname=lastname;
    this->address=address;
    this->sex=sex;
    this->dateBirth=dateBirth;
    this->mail=mail;
    this->function=function;
    this->password=password;
    this->phoneNumber=phoneNumber;
}

void employee::setId(int id){this ->id=id;}
void employee::setName(QString name){this->name=name;}
void employee::setLastname(QString lastname){this->lastname=lastname;}
void employee::setAddress(QString address){this->address=address;}
void employee::setSex(QString sex){this->sex=sex;}
void employee::setDateBirth(QDate dateBirth){this->dateBirth=dateBirth;}
void employee::setMail(QString mail){this->mail=mail;}
void employee::setFunction(QString function){this->function=function;}
void employee::setPassword(QString password){this->password=password;}
//void employee::setProfil(QString profil){this->profil=profil;}
void employee::setPhoneNumber(int phoneNumber){this->phoneNumber=phoneNumber;}
void employee::setImagePath(QString imagePath){this->imagePath=imagePath;}
void employee::setImageData(QByteArray imageData){this->imageData=imageData;}



bool employee::ajouterEmployee() {
    QSqlQuery query;
    QString id_string = QString::number(id);
    QString phoneNumber_string = QString::number(phoneNumber);
    QFile file(imagePath);

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Erreur: Impossible de lire l'image:" << file.errorString();
        qDebug() << imagePath;
        return false;
    }

    QByteArray imageData = file.readAll();
    file.close();
    QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);

    // Vérifier la force du mot de passe
    bool passwordIsStrong = password.contains(QRegularExpression("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d).+$"));
    if (!passwordIsStrong) {
        qDebug() << "Mot de passe faible: doit contenir au moins une minuscule, une majuscule et un chiffre.";
        return false;
    }
    // Vérifier si l'adresse e-mail est déjà utilisée
    query.prepare("SELECT id FROM employee WHERE mail = :mail");
    query.bindValue(":mail", mail);
    if (query.exec() && query.next()) {
        qDebug() << "Erreur: L'adresse e-mail est déjà utilisée.";
        return false;
    }

    query.prepare("INSERT INTO employee (id, name, lastname, address, sex, dateBirth, mail, function, password, phoneNumber, image) "
                  "VALUES (:id, :name, :lastname, :address, :sex, :dateBirth, :mail, :function, :password, :phoneNumber, :image)");
    query.bindValue(":id", id_string);
    query.bindValue(":name", name);
    query.bindValue(":lastname", lastname);
    query.bindValue(":address", address);
    query.bindValue(":sex", sex);
    query.bindValue(":dateBirth", dateBirth);
    query.bindValue(":mail", mail);
    query.bindValue(":function", function);
    query.bindValue(":password", hashedPassword.toHex()); // Stocker le hash en hexadécimal
    query.bindValue(":phoneNumber", phoneNumber_string);
    query.bindValue(":image", imageData);

    return query.exec();
}

QSqlQueryModel * employee::afficherEmployee()
{
    QSqlQueryModel* model=new  QSqlQueryModel();
          model->setQuery("SELECT cast(id as varchar(255)),name,lastname,address,function,mail FROM employee");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("name"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("lastname"));
          //model->setHeaderData(3, Qt::Horizontal, QObject::tr("phoneNumber"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("address"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("function"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("mail"));


    return model;
}
employee employee::chercher(int id_chercher)
{
    employee employee;  // Create an instance of the Employee class
    QString queryStr = QString("SELECT * FROM employee WHERE id = %1").arg(id_chercher);
    QSqlQuery query;
    query.prepare(queryStr);

    if (query.exec())
    {
        if (query.next())
        {
            // Assuming your Employee class has setter methods, update them accordingly
            employee.setId(query.value("id").toInt());
            employee.setName(query.value("name").toString());
            employee.setLastname(query.value("lastname").toString());
            employee.setAddress(query.value("address").toString());
            employee.setSex(query.value("sex").toString());
            employee.setDateBirth(query.value("dateBirth").toDate());
            employee.setMail(query.value("mail").toString());
            employee.setFunction(query.value("function").toString());
            employee.setPassword(query.value("password").toString());
            employee.setPhoneNumber(query.value("phoneNumber").toInt());
            employee.setImagePath(query.value("image").toString());  // Retrieve imagePath from the database
            QByteArray imageData = query.value("image").toByteArray();
            employee.setImageData(imageData);
        }
        else
        {
            // Handle the case when no records are found for the given ID
            qDebug() << "No records found for ID:" << id_chercher;
        }
    }
    else
    {
        // Handle the case when the query fails, e.g., log an error
        qDebug() << "Query failed:" << query.lastError().text();
    }

    return employee;
}
bool employee::suprimerEmployee(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);
          query.prepare("DELETE FROM employee WHERE id= :id");
          query.bindValue(":id", res);
          return query.exec();
}

bool employee::modifierEmployee()
{
    QSqlQuery query;
          query.prepare("UPDATE EMPLOYEE SET id=:id,name= :name, lastname= :lastname, address= :address, sex= :sex, mail= :mail,function= :function ,phoneNumber= :phoneNumber,dateBirth=:dateBirth where id =:id");
          query.bindValue(":id",id);
          query.bindValue(":name", name);
          query.bindValue(":lastname", lastname);
          query.bindValue(":address", address);
          query.bindValue(":sex", sex);
          query.bindValue(":dateBirth", dateBirth);
          query.bindValue(":mail", mail);
          query.bindValue(":function", function);
         // query.bindValue(":password", password);
          //query.bindValue(":profil", profilByteArray);
          //query.bindValue(":profil", profil);
          query.bindValue(":phoneNumber", phoneNumber);
           return query.exec();
}
bool employee::modifierImage(QString imagePath)
{
    // Lire l'image depuis le fichier
    QFile file(imagePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Erreur: Impossible de lire l'image:" << file.errorString();
        qDebug() << imagePath;
        return false;
    }
    QByteArray image = file.readAll();
    file.close();
    QSqlQuery query;
          query.prepare("UPDATE EMPLOYEE SET id=:id,name= :name, lastname= :lastname, address= :address, sex= :sex, mail= :mail,function= :function ,phoneNumber= :phoneNumber,password=:password,dateBirth=:dateBirth,IMAGE=:image where id =:id");
          query.bindValue(":id",id);
          query.bindValue(":name", name);
          query.bindValue(":lastname", lastname);
          query.bindValue(":address", address);
          query.bindValue(":sex", sex);
          query.bindValue(":dateBirth", dateBirth);
          query.bindValue(":mail", mail);
          query.bindValue(":function", function);
          query.bindValue(":password", password);
          //query.bindValue(":profil", profilByteArray);
          //query.bindValue(":profil", profil);
          query.bindValue(":phoneNumber", phoneNumber);
          query.bindValue(":image", image);

           return query.exec();
}


int employee::chercherMailId(QString mail)
{
    // Prepare the query to check the login credentials
    QSqlQuery query;
    query.prepare("SELECT id FROM employee WHERE mail = :mail ");
    query.bindValue(":mail", mail);
    if (query.exec()) {
        // If the query returns a single row, return the phone number as an integer
        if (query.next()) {
            // Récupérez le numéro de téléphone à partir de la colonne correspondante et convertissez-le en entier
            return query.value(0).toInt();
        }
    }
    // Si la requête échoue ou ne renvoie pas de résultat, retournez une valeur par défaut, par exemple -1
    return -1; // ou toute autre valeur par défaut que vous souhaitez utiliser
}



QSqlQueryModel * employee::afficher_tri(const QString &critere)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QString query = "SELECT cast(id as varchar(255)),name,lastname,address,function,mail FROM EMPLOYEE ORDER BY ";

    if(critere == "CIN") {
        query += "cast(id as varchar(255))";
    } else if(critere == "Address") {
        query += "Address";
    } else if(critere == "Name") {
        query += "NAME";
    }

    model->setQuery(query);
    return model;
}
QSqlQueryModel* employee::rechercher(QString e)
{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("SELECT cast(id as varchar(255)),name,lastname,address,function,mail FROM employee WHERE NAME LIKE '%" + e + "%'");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("lastname"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("address"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("function"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("mail"));

    return model;
}
bool employee::login(QString mail, QString password)
{
    // Prepare the query to check the login credentials
    QSqlQuery query;
    QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);

            // Vérifier la force du mot de passe
     //bool passwordIsStrong = password.contains(QRegularExpression("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d).+$"));

    query.prepare("SELECT * FROM employee WHERE mail = :mail AND password = :password");
    query.bindValue(":mail", mail);
    query.bindValue(":password", hashedPassword.toHex()); // Stocker le hash en hexadécimal
    if (query.exec()) {
        // If the query returns a single row, the email and password are for the same employee
        if (query.next()) {
            return true;
        }
    }
    return false;
}
QSqlQueryModel* employee::afficher_tri_id_descendant()
{
    QSqlQueryModel* model = new QSqlQueryModel();
       model->setQuery("SELECT cast(id as varchar(255)),name,lastname,address,function,mail FROM employee ORDER BY id DESC");
       return model;
}
QSqlQueryModel* employee::afficher_tri_name_descendant()
{
    QSqlQueryModel* model = new QSqlQueryModel();
       model->setQuery("SELECT cast(id as varchar(255)),name,lastname,address,function,mail FROM employee ORDER BY name DESC");
       return model;
}
QSqlQueryModel* employee::afficher_tri_lastname_descendant()
{
    QSqlQueryModel* model = new QSqlQueryModel();
       model->setQuery("SELECT cast(id as varchar(255)),name,lastname,address,function,mail FROM employee ORDER BY name DESC");
       return model;
}
QSqlQueryModel* employee::afficher_tri_address_descendant()
{
    QSqlQueryModel* model = new QSqlQueryModel();
       model->setQuery("SELECT cast(id as varchar(255)),name,lastname,address,function,mail FROM employee ORDER BY address DESC");
       return model;
}
QSqlQueryModel* employee::afficher_tri_function_descendant()
{
    QSqlQueryModel* model = new QSqlQueryModel();
       model->setQuery("SELECT cast(id as varchar(255)),name,lastname,address,function,mail FROM employee ORDER BY function DESC");
       return model;
}
QSqlQueryModel* employee::afficher_tri_mail_descendant()
{
    QSqlQueryModel* model = new QSqlQueryModel();
       model->setQuery("SELECT cast(id as varchar(255)),name,lastname,address,function,mail FROM employee ORDER BY mail DESC");
       return model;
}
QSqlQueryModel* employee::afficher_tri_id_aescendant()
{
    QSqlQueryModel* model = new QSqlQueryModel();
       model->setQuery("SELECT cast(id as varchar(255)),name,lastname,address,function,mail FROM employee ORDER BY id ASC");
       return model;
}
QSqlQueryModel* employee::afficher_tri_name_aescendant()
{
    QSqlQueryModel* model = new QSqlQueryModel();
       model->setQuery("SELECT cast(id as varchar(255)),name,lastname,address,function,mail FROM employee ORDER BY name ASC");
       return model;
}
QSqlQueryModel* employee::afficher_tri_lastname_aescendant()
{
    QSqlQueryModel* model = new QSqlQueryModel();
       model->setQuery("SELECT cast(id as varchar(255)),name,lastname,address,function,mail FROM employee ORDER BY name ASC");
       return model;
}
QSqlQueryModel* employee::afficher_tri_address_aescendant()
{
    QSqlQueryModel* model = new QSqlQueryModel();
       model->setQuery("SELECT cast(id as varchar(255)),name,lastname,address,function,mail FROM employee ORDER BY address ASC");
       return model;
}
QSqlQueryModel* employee::afficher_tri_function_aescendant()
{
    QSqlQueryModel* model = new QSqlQueryModel();
       model->setQuery("SELECT cast(id as varchar(255)),name,lastname,address,function,mail FROM employee ORDER BY function ASC");
       return model;
}
QSqlQueryModel* employee::afficher_tri_mail_aescendant()
{
    QSqlQueryModel* model = new QSqlQueryModel();
       model->setQuery("SELECT cast(id as varchar(255)),name,lastname,address,function,mail FROM employee ORDER BY mail ASC");
       return model;
}

int employee::sendEmail(const QString &to, const QString &subject, const QString &body)
{
    QString smtpServer = "smtp.gmail.com"; // Remplacez ceci par votre serveur SMTP
    int port = 587; // Le port SMTP utilisé (587 est généralement pour TLS)

    QString from = "farahhassen96@gmail.com"; // Votre adresse e-mail
    QString username = "farahhassen96@gmail.com"; // Votre nom d'utilisateur SMTP
    QString password = "bvpz rmqt ubvf ydrg"; // Votre mot de passe SMTP
    int entier = genererEntierQuatreChiffres();
    // Création du socket TCP
    QSslSocket socket;
    socket.connectToHost(smtpServer, port);

    if (!socket.waitForConnected()) {
        qDebug() << "Erreur de connexion au serveur SMTP:" << socket.errorString();
        //return;
    }

    if (!socket.waitForReadyRead()) {
        qDebug() << "Erreur lors de la lecture du message d'accueil du serveur SMTP:" << socket.errorString();
        //return;
    }

    // Envoyer les commandes SMTP
    QTextStream stream(&socket);

    // Lecture de la réponse initiale du serveur SMTP
    QString response = socket.readAll();
    qDebug() << "Réponse initiale du serveur SMTP:" << response;

    // Étape EHLO
    stream << "EHLO localhost\r\n";
    stream.flush(); // Envoyer les données en attente
    if (!socket.waitForReadyRead()) {
        qDebug() << "Erreur lors de l'envoi de la commande EHLO:" << socket.errorString();
        //return;
    }

    response = socket.readAll();
    qDebug() << "Réponse EHLO:" << response;
    // After EHLO command
    stream << "STARTTLS\r\n";
    stream.flush(); // Send pending data
    if (!socket.waitForReadyRead()) {
        qDebug() << "Error sending STARTTLS command:" << socket.errorString();
        //return;
    }

    response = socket.readAll();
    qDebug() << "Response to STARTTLS:" << response;

    // Start SSL/TLS encryption
    socket.startClientEncryption();
    if (!socket.waitForEncrypted()) {
        qDebug() << "Error starting SSL/TLS encryption:" << socket.errorString();
        //return;
    }

    // Étape d'authentification
    QByteArray login = QByteArray().append(username).toBase64();
    QByteArray passwordHash = QByteArray().append(password).toBase64();

    stream << "AUTH LOGIN\r\n";
    stream.flush(); // Envoyer les données en attente
    if (!socket.waitForReadyRead()) {
        qDebug() << "Erreur lors de l'envoi de la commande AUTH LOGIN:" << socket.errorString();
        //return;
    }

    response = socket.readAll();
    qDebug() << "Réponse AUTH LOGIN:" << response;

    stream << login + "\r\n";
    stream.flush(); // Envoyer les données en attente
    if (!socket.waitForReadyRead()) {
        qDebug() << "Erreur lors de l'envoi du nom d'utilisateur encodé:" << socket.errorString();
        //return;
    }

    response = socket.readAll();
    qDebug() << "Réponse nom d'utilisateur:" << response;

    stream << passwordHash + "\r\n";
    stream.flush(); // Envoyer les données en attente
    if (!socket.waitForReadyRead()) {
        qDebug() << "Erreur lors de l'envoi du mot de passe encodé:" << socket.errorString();
        //return;
    }

    response = socket.readAll();
    qDebug() << "Réponse mot de passe:" << response;

    // Envoyer l'e-mail
    stream << "MAIL FROM:<" + from + ">\r\n";
    stream.flush(); // Envoyer les données en attente
    if (!socket.waitForReadyRead()) {
        qDebug() << "Erreur lors de l'envoi de l'expéditeur:" << socket.errorString();
        //return;
    }

    response = socket.readAll();
    qDebug() << "Réponse expéditeur:" << response;

    stream << "RCPT TO:<" + to + ">\r\n";
    stream.flush(); // Envoyer les données en attente
    if (!socket.waitForReadyRead()) {
        qDebug() << "Erreur lors de l'envoi du destinataire:" << socket.errorString();
        //return;
    }

    response = socket.readAll();
    qDebug() << "Réponse destinataire:" << response;

    stream << "DATA\r\n";
    stream.flush(); // Envoyer les données en attente
    if (!socket.waitForReadyRead()) {
        qDebug() << "Erreur lors de l'envoi de la commande DATA:" << socket.errorString();
        //return;
    }

    response = socket.readAll();
    qDebug() << "Réponse DATA:" << response;

    stream << "Subject: " + subject + "\r\n";
    stream << "\r\n";
    stream << body + "\r\n";
    stream << "" + QString::number(entier) + "\r\n"; // Incorporer l'entier dans le corps du message
    stream << ".\r\n";
    stream.flush();

    if (!socket.waitForReadyRead()) {
        qDebug() << "Erreur lors de l'envoi du corps du message:" << socket.errorString();
        //return;
    }

    response = socket.readAll();
    qDebug() << "Réponse d'envoi de message:" << response;

    // Quitter la session SMTP
    stream << "QUIT\r\n";
    stream.flush(); // Envoyer les données en attente
    if (!socket.waitForDisconnected()) {
        qDebug() << "Erreur lors de l'envoi de la commande QUIT:" << socket.errorString();
        //return;
    }

    qDebug() << "E-mail envoyé avec succès!";
    return entier;
}


int employee::genererEntierQuatreChiffres() {
    srand(time(nullptr));

        // Génération de 4 chiffres aléatoires
        int chiffre1 = rand() % 10;
        int chiffre2 = rand() % 10;
        int chiffre3 = rand() % 10;
        int chiffre4 = rand() % 10;

        // Création de l'entier composé de ces 4 chiffres
        int entier = chiffre1 * 1000 + chiffre2 * 100 + chiffre3 * 10 + chiffre4;

        return entier;
}
bool employee::chercherMail(QString mail)
{
    // Prepare the query to check the login credentials
    QSqlQuery query;
    query.prepare("SELECT * FROM employee WHERE mail = :mail ");
    query.bindValue(":mail", mail);
    if (query.exec()) {
        // If the query returns a single row, the email and password are for the same employee
        if (query.next()) {
            return true;
        }
    }
    return false;
}
int employee::chercherMailPhoneNumber(QString mail)
{
    // Prepare the query to check the login credentials
    QSqlQuery query;
    query.prepare("SELECT phoneNumber FROM employee WHERE mail = :mail ");
    query.bindValue(":mail", mail);
    if (query.exec()) {
        // If the query returns a single row, return the phone number as an integer
        if (query.next()) {
            // Récupérez le numéro de téléphone à partir de la colonne correspondante et convertissez-le en entier
            return query.value(0).toInt();
        }
    }
    // Si la requête échoue ou ne renvoie pas de résultat, retournez une valeur par défaut, par exemple -1
    return -1; // ou toute autre valeur par défaut que vous souhaitez utiliser
}


bool employee::SaveNewPassword(QString password,QString mail)
{
    QSqlQuery query;
    QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);

            // Vérifier la force du mot de passe
      bool passwordIsStrong = password.contains(QRegularExpression("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d).+$"));

            if (!passwordIsStrong)
            {
                qDebug() << "Mot de passe faible: doit contenir au moins une minuscule, une majuscule et un chiffre.";
                return false;
            }
          query.prepare("UPDATE EMPLOYEE SET password=:password where mail =:mail");
          query.bindValue(":mail", mail);
          query.bindValue(":password", hashedPassword.toHex()); // Stocker le hash en hexadécimal
          return query.exec();
}
QString employee::chercherFunction(QString mail)
{
    QSqlQuery query;
    query.prepare("SELECT function FROM employee WHERE mail = :mail ");
    query.bindValue(":mail", mail);

    QString function;

    if (query.exec() && query.next()) {
        function = query.value(0).toString(); // Récupération de la valeur de la colonne 'function'
    } else {
        // Gérer les erreurs ou les cas où aucun enregistrement n'est trouvé
        qDebug() << "Erreur lors de la recherche de la fonction pour l'e-mail" << mail << ":" << query.lastError().text();
    }

    return function;
}
void employee::sendSMS(const QString& accountSid, const QString& authToken, const QString& fromNumber, QString toNumber, QString message) {
    QNetworkAccessManager manager;
    QNetworkRequest request(QUrl("https://api.twilio.com/2010-04-01/Accounts/" + accountSid + "/Messages.json"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QString credentials = accountSid + ":" + authToken;
    QByteArray data;
    QUrlQuery params;
    params.addQueryItem("From", fromNumber);
    params.addQueryItem("To", toNumber);
    params.addQueryItem("Body", message);
    data.append(params.toString());

    request.setRawHeader("Authorization", "Basic " + credentials.toUtf8().toBase64());


     QNetworkReply* reply = manager.post(request, data);
     QEventLoop loop;
     QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
     loop.exec();
     qDebug() << "SMS";
     reply->deleteLater();
}

#include <QPainter>
#include <cmath>
#include <QString>
#include <QFontMetrics>

void employee::afficherPieChart(QLabel *label)
{
    // Exécution de la requête pour récupérer les données sur le sexe
    QSqlQuery query;
    query.prepare("SELECT sex, COUNT(*) FROM employee GROUP BY sex");

    // Vérification si la requête a échoué
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête SQL :" << query.lastError().text();
        return;
    }

    // Variables pour stocker les données récupérées
    QList<QString> sexes;
    QList<int> counts;

    // Récupération des données de la requête
    while (query.next()) {
        sexes.append(query.value(0).toString());
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
    for (int i = 0; i < sexes.size(); ++i) {
        qreal sweepAngle = 360.0 * counts[i] / std::accumulate(counts.begin(), counts.end(), 0);
        QColor sliceColor = QColor::fromHsv(80, 100 * (i + 1) / sexes.size(), 200); // Dégradé de vert à jaune pastel
        painter.setBrush(sliceColor); // Définir la couleur de la tranche
        painter.drawPie(pieRect, startAngle * 16, sweepAngle * 16);

        // Dessiner un carré de couleur à côté du pie chart
        QRectF colorRect(pixmapSize.width() - 200, 20 + i * 30, 20, 20); // Position et taille du carré de couleur
        painter.fillRect(colorRect, sliceColor);

        // Afficher le sexe à côté du carré de couleur
        QString sexLabel = sexes[i];
        QPointF sexPos = colorRect.topRight() + QPointF(30, 15); // Position pour afficher le sexe à côté du carré de couleur
        painter.drawText(sexPos, sexLabel);

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


void MainWindow::on_statEmployee_clicked()
{
    ui->stackedWidgetEmployee->setCurrentIndex(4);
    emp.afficherPieChart(ui->label_statEmployee);
}

void MainWindow::on_supprimer_Employee_2_clicked()
{
    QModelIndexList selectedRows = ui->tabEmployee->selectionModel()->selectedRows();

          // Parcourez les indices des lignes sélectionnées et supprimez-les une par une
          for (const QModelIndex &index : selectedRows) {
              // Obtenez la valeur dans la première colonne (colonnes sont 0-indexées)
              int valueToDelete = ui->tabEmployee->model()->data(index.sibling(index.row(), 0)).toInt();
              // Utilisez cette valeur pour appeler votre fonction de suppression
              emp.suprimerEmployee(valueToDelete);
          }
          // Rafraîchissez le modèle de votre table view après la suppression
          ui->tabEmployee->setModel(emp.afficherEmployee());
}
void MainWindow::on_pushButton_upCin_clicked()
{
    ui->tabEmployee->setModel(emp.afficher_tri_id_aescendant());

}

void MainWindow::on_pushButton_downCin_clicked()
{
    ui->tabEmployee->setModel(emp.afficher_tri_id_descendant());
}

void MainWindow::on_pushButton_upName_clicked()
{
    ui->tabEmployee->setModel(emp.afficher_tri_name_aescendant());
}

void MainWindow::on_pushButton_downName_clicked()
{
    ui->tabEmployee->setModel(emp.afficher_tri_name_descendant());
}

void MainWindow::on_pushButton_upLastname_clicked()
{
    ui->tabEmployee->setModel(emp.afficher_tri_lastname_aescendant());
}

void MainWindow::on_pushButton_downLastname_clicked()
{
    ui->tabEmployee->setModel(emp.afficher_tri_lastname_descendant());
}

void MainWindow::on_pushButton_upAddress_clicked()
{
    ui->tabEmployee->setModel(emp.afficher_tri_address_aescendant());

}

void MainWindow::on_pushButton_downAddress_clicked()
{
    ui->tabEmployee->setModel(emp.afficher_tri_address_descendant());

}

void MainWindow::on_pushButton_upFunction_clicked()
{
    ui->tabEmployee->setModel(emp.afficher_tri_function_aescendant());
}

void MainWindow::on_pushButton_downFunction_clicked()
{
    ui->tabEmployee->setModel(emp.afficher_tri_function_descendant());

}

void MainWindow::on_pushButton_upMail_clicked()
{
    ui->tabEmployee->setModel(emp.afficher_tri_mail_aescendant());


}

void MainWindow::on_pushButton_downMail_clicked()
{
    ui->tabEmployee->setModel(emp.afficher_tri_mail_descendant());
}

void MainWindow::on_save_AddEmployee_clicked()
{
    int id=ui->lineEdit_IdEmployee->text().toUInt();
    QString name=ui->lineEdit_NameEmployee->text();
    QString lastname=ui->lineEdit_LastameEmployee->text();
    QString address=ui->lineEdit_AddressEmployee->text();
    QString sex=ui->comboBox_AddEmployee->currentText();
    QDate dateBirth = QDate::fromString(ui->lineEdit_DateBirthEmployee->text(), "dd/MM/yyyy");
    QString mail=ui->lineEdit_MailEmployee->text();
    QString function=ui->comboBox_AddFunctionEmployee->currentText();
    QString password=ui->lineEdit_PasswordEmployee->text();
    int phoneNumber=ui->lineEdit_PhoneNumberEmployee->text().toUInt();

    QRegularExpression emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    QRegExp cinRegex("\\d{8}"); // Expression régulière pour un CIN de 8 chiffres

    employee e(id,name,lastname,address,sex,mail,function,password,dateBirth,phoneNumber,emp.getImagePath());
    //e.sendSMS("AC2cf360180aba7634f559ba2de80d9ec7","8775944acd6baa8deeeb4651354e3dd7","+17606702645","+21629703391","helloooooo");
   //e.recupererJoursFeriesTunisiens(QDate::currentDate().year());

    if (name.isEmpty() || lastname.isEmpty() || address.isEmpty() ||dateBirth.isNull() || sex.isEmpty() || mail.isEmpty() || function.isEmpty()||password.isEmpty())
            {
                QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                      QObject::tr(" Tous les champs sont obligatoires."),
                                      QMessageBox::Cancel);
                return;
            }
        if (dateBirth> QDate(1960, 1, 1) and dateBirth> QDate(2000, 1, 1)) {
                QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                      QObject::tr("date of birth should be between 1960 and 2000 ."),
                                      QMessageBox::Cancel);
                return; }
        if (!emailRegex.match(mail).hasMatch()) {
                QMessageBox::critical(this, "Erreur", "Veuillez saisir une adresse email valide.");
                return;
            }
        if (!cinRegex.exactMatch(ui->lineEdit_IdEmployee->text())) {
               QMessageBox::critical(this, "Erreur", "Veuillez saisir un CIN valide (8 chiffres).");
               return;
           }
        if (!cinRegex.exactMatch(ui->lineEdit_PhoneNumberEmployee->text())) {
               QMessageBox::critical(this, "Erreur", "Veuillez saisir un phoneNumber valide (8 chiffres).");
               return;
           }


    bool test=e.ajouterEmployee();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("Ajout effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->lineEdit_IdEmployee->clear();
        ui->lineEdit_NameEmployee->clear();
        ui->lineEdit_LastameEmployee->clear();
        ui->lineEdit_AddressEmployee->clear();
        //ui->lineEdit_DateBirthEmployee->clear();
        ui->lineEdit_MailEmployee->clear();
       // ui->comboBox_AddFunctionEmployee->clear();
        ui->lineEdit_PasswordEmployee->clear();
        ui->lineEdit_PhoneNumberEmployee->clear();
        ui->label_downPasswordAdd->clear();
        ui->pushButton_AddImageEmployee->setStyleSheet(""); // Supprime le styleSheet et l'image personnalisée
        ui->stackedWidgetEmployee->setCurrentIndex(1);
    }
    else
     {

        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("Ajout non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ui->tabEmployee->setModel(emp.afficherEmployee());

}

void MainWindow::on_tabEmployee_clicked(const QModelIndex &index)
{

    if (index.isValid())
       {
               int row = index.row();
               ui->stackedWidgetEmployee->setCurrentIndex(2);
               int id_chercher = ui->tabEmployee->model()->index(row, 0).data().toInt();
               employee e = emp.chercher(id_chercher);
               ui->lineEdit_AffCIN->setText(QString::number(id_chercher));
               ui->lineEdit_AffName->setText(e.getName());
               ui->lineEdit_AffLastname->setText(e.getLastname());
               ui->lineEdit_AffSex->setText(e.getSex());
               ui->lineEdit_AffMail->setText(e.getMail());
               ui->lineEdit_AffAddress->setText(e.getAddress());

               ui->lineEdit_AffPhoneNumber->setText(QString::number(e.getPhoneNumber()));
               QString encryptedPassword = QString(e.getPassword().length(), '*');

               ui->lineEdit_AffFunction->setText(e.getFunction());
               ui->lineEdit_AffPassword->setText(encryptedPassword);
               ui->lineEdit_AffDateBirth->setText(e.getDateBirth().toString("dd/MM/yyyy"));

               QPixmap pixmap;
               pixmap.loadFromData(e.getImageData());
               if (!pixmap.isNull()) {
                   // Redimensionner l'image pour s'adapter à la taille de la QLabel
                   pixmap = pixmap.scaled(ui->label_AffImageEmployee->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                   ui->label_AffImageEmployee->setPixmap(pixmap);
               } else {
                   qDebug() << "Erreur: Impossible de charger l'image depuis les données ByteArray.";
                 }
           }


}

void MainWindow::on_supprimer_Employee_clicked()
{
    int id=ui->lineEdit_AffCIN->text().toInt();
    bool test=emp.suprimerEmployee(id);
    QMessageBox msgBox;
    if(test){
        QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("Suppression effectuée \n"
                                                                        "Clicke Cancel to exite"),
                                 QMessageBox::Cancel);
        ui->label_AffImageEmployee->clear();
        ui->tabEmployee->setModel(emp.afficherEmployee());
        ui->stackedWidgetEmployee->setCurrentIndex(1);

    }
    else{ QMessageBox::critical(nullptr , QObject::tr("Not Ok "),QObject::tr("Suppression non effectuée\n"
                                                                              "Click Cancel to exit ."),
                                 QMessageBox::Cancel);
    }
}

void MainWindow::on_pdfEmployee_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save PDF", ui->lineEdit_AffCIN->text(), "*.pdf");

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QPainter painter;
    painter.begin(&printer);

    // Définir les couleurs
    QColor titleColor(50, 50, 150); // Bleu foncé
    QColor infoColor(100, 100, 100); // Gris foncé
    QColor borderColor(0, 0, 0); // Noir

    // Configuration de la police
    QFont titleFont("Arial", 16, QFont::Bold);
    QFont infoFont("Arial", 12);

    // Définir le pinceau pour le cadre
    QPen borderPen(borderColor);
    borderPen.setWidth(2);
    painter.setPen(borderPen);

    // Dessiner le cadre pour la feuille
    painter.drawRect(50, 50, printer.width() - 100, printer.height() - 100);

    // Définir le pinceau pour le titre
    painter.setPen(titleColor);
    painter.setFont(titleFont);

    // Dessiner le titre
    painter.drawText(100, 80, "Employee's Information");

    // Dessiner les informations supplémentaires
    QStringList additionalInfo;
    additionalInfo << "CIN: " + ui->lineEdit_AffCIN->text();
    additionalInfo << "Name: " + ui->lineEdit_AffName->text();
    additionalInfo << "Lastname: " + ui->lineEdit_AffLastname->text();
    additionalInfo << "Date of Birth: " + ui->lineEdit_AffDateBirth->text();
    additionalInfo << "Address: " + ui->lineEdit_AffAddress->text();
    additionalInfo << "Phone Number: " + ui->lineEdit_AffPhoneNumber->text();
    additionalInfo << "Function: " + ui->lineEdit_AffFunction->text();
    additionalInfo << "Email: " + ui->lineEdit_AffMail->text();

    // Définir le pinceau pour les informations supplémentaires
    painter.setPen(infoColor);
    painter.setFont(infoFont);

    // Définir les marges et l'espacement
    int xOffset = 100;
    int yOffset = 140;
    int spacing = 20;

    // Dessiner les informations supplémentaires
    foreach(const QString &info, additionalInfo) {
        painter.drawText(xOffset, yOffset, info);
        yOffset += spacing;
    }

    painter.end();
    ui->label_AffImageEmployee->clear();
    ui->tabEmployee->setModel(emp.afficherEmployee());
    ui->stackedWidgetEmployee->setCurrentIndex(1);
}

void MainWindow::on_updateEmployee_clicked()
{
    int id=ui->lineEdit_AffCIN->text().toUInt();

      QString name=ui->lineEdit_AffName->text();
      QString lastname=ui->lineEdit_AffLastname->text();
      QString address=ui->lineEdit_AffAddress->text();
      QString sex=ui->lineEdit_AffSex->text();
      QString mail=ui->lineEdit_AffMail->text();
      QString function=ui->lineEdit_AffFunction->text();
      QString password=ui->lineEdit_AffPassword->text();
      QDate dateBirth=QDate::fromString(ui->lineEdit_AffDateBirth->text(), "dd/MM/yyyy");;
      int phoneNumber=ui->lineEdit_AffPhoneNumber->text().toUInt();

      ui->lineEdit_UpDateIdEmployee->setText(QString::number(id));
      ui->lineEdit_UpDateNameEmployee->setText(name);
      ui->lineEdit_UpDateLastnameEmployee->setText(lastname);
      ui->comboBox_UpDateEmployee->setCurrentText(sex);
      ui->lineEdit_UpDateMailEmployee->setText(mail);
      ui->lineEdit_UpDateAddressEmployee->setText(address);
      ui->lineEdit_UpDatePhoneNumberEmployee->setText(QString::number(phoneNumber));
      ui->comboBox_UpDateFunctionEmployee->setCurrentText(function);
      ui->lineEdit_UpDatePasswordEmployee->setText(password);
      ui->dateEdit_UpDateEmployee->setDate(dateBirth);

      ui->stackedWidgetEmployee->setCurrentIndex(0);
}

void MainWindow::on_save_updateEmployee_clicked()
{
    int id=ui->lineEdit_UpDateIdEmployee->text().toUInt();
    QString name=ui->lineEdit_UpDateNameEmployee->text();
    QString lastname=ui->lineEdit_UpDateLastnameEmployee->text();
    QString address=ui->lineEdit_UpDateAddressEmployee->text();
    QString sex=ui->comboBox_UpDateEmployee->currentText();
    QString mail=ui->lineEdit_UpDateMailEmployee->text();
    QString function=ui->comboBox_UpDateFunctionEmployee->currentText();
    QString password=ui->lineEdit_UpDatePasswordEmployee->text();
    QDate dateBirth=QDate::fromString(ui->dateEdit_UpDateEmployee->text(), "dd/MM/yyyy");;
    int phoneNumber=ui->lineEdit_UpDatePhoneNumberEmployee->text().toUInt();
    QRegularExpression emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    QRegExp cinRegex("\\d{8}"); // Expression régulière pour un CIN de 8 chiffres

    if (name.isEmpty() || lastname.isEmpty() || address.isEmpty() ||dateBirth.isNull() || sex.isEmpty() || mail.isEmpty() || function.isEmpty()||password.isEmpty())
            {
                QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                      QObject::tr(" Tous les champs sont obligatoires."),
                                      QMessageBox::Cancel);
                return;
            }
        if (dateBirth> QDate(1960, 1, 1) and dateBirth> QDate(2000, 1, 1)) {
                QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                      QObject::tr("date of birth should be between 1960 and 2000 ."),
                                      QMessageBox::Cancel);
                return; }
        if (!emailRegex.match(mail).hasMatch()) {
                QMessageBox::critical(this, "Erreur", "Veuillez saisir une adresse email valide.");
                return;
            }
        /*if (!cinRegex.exactMatch(ui->lineEdit_IdEmployee->text())) {
               QMessageBox::critical(this, "Erreur", "Veuillez saisir un CIN valide (8 chiffres).");
               return;
           }*/
        if (!cinRegex.exactMatch(ui->lineEdit_UpDatePhoneNumberEmployee->text())) {
               QMessageBox::critical(this, "Erreur", "Veuillez saisir un phoneNumber valide (8 chiffres).");
               return;
           }
    employee e(id,name,lastname,address,sex,mail,function,password,dateBirth,phoneNumber);
    bool test=e.modifierEmployee();
    if(test){
        QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("Modification effectuée\n"
                                                                        "Clicke Cancel to exite"),QMessageBox::Cancel);

        ui->tabEmployee->setModel(emp.afficherEmployee());


    }else{ QMessageBox::critical(nullptr , QObject::tr("Not Ok "),QObject::tr("Modification échouée.\n"
                                                                              "Click Cancel to exit."),
                                 QMessageBox::Cancel);

    }
    ui->tabEmployee->setModel(emp.afficherEmployee());
    ui->stackedWidgetEmployee->setCurrentIndex(1);
}

void MainWindow::on_searchTextBox_employee_textEdited(const QString &arg1)
{
    QSqlQueryModel* model = emp.rechercher(arg1);
        ui->tabEmployee->setModel(model);
}

void MainWindow::on_pushButton_AddImageEmployee_clicked()
{
    QString imagePath2 = QFileDialog::getOpenFileName(nullptr, "Sélectionner une image", "", "Images (*.png *.jpg *.jpeg *.bmp *.gif)");
    QPixmap pixmap(imagePath2);

    // Définir l'image comme fond du bouton et styliser le cadre
    ui->pushButton_AddImageEmployee->setStyleSheet(
                             "border-image: url("+imagePath2+");"
                             "border-width: 2px;"
                             "border-style: solid;"
                             "border-radius:15px;"
                             "border-color: #000000;" // Couleur du cadre
                             "text-align: center;"    // Aligner le texte au centre du bouton (en dehors de l'image)
                             "color: transparent;"
                             );
     emp.setImagePath(imagePath2);
}

void MainWindow::on_pushButton_UpDateImageEmployee_clicked()
{
    QString imagePath2 = QFileDialog::getOpenFileName(nullptr, "Sélectionner une image", "", "Images (*.png *.jpg *.jpeg *.bmp *.gif)");
           QPixmap pixmap(imagePath2);

           // Définir l'image comme fond du bouton et styliser le cadre
           ui->label_AffImageEmployee->setPixmap(pixmap);
            emp.setImagePath(imagePath2);
            int id_chercher=ui->lineEdit_AffCIN->text().toUInt();
            employee e = emp.chercher(id_chercher);
            bool test=e.modifierImage(imagePath2);
            if(test){
                QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("Modification effectuée\n"
                                                                                "Clicke Cancel to exite"),QMessageBox::Cancel);

                ui->tabEmployee->setModel(emp.afficherEmployee());


            }else{ QMessageBox::critical(nullptr , QObject::tr("Not Ok "),QObject::tr("Modification échouée.\n"
                                                                                      "Click Cancel to exit."),
                                         QMessageBox::Cancel);

            }    ui->tabEmployee->setModel(emp.afficherEmployee());

}

void MainWindow::on_pushButtonLogin_clicked()
{
    QString mail=ui->lineEdit_LoginEmail->text();
      QString password=ui->lineEdit_LoginPassword->text();
      bool test=emp.login(mail,password);
      int phone=emp.chercherMailPhoneNumber(mail);
      QString phoneString = "+216" + QString::number(phone); // Concaténer le préfixe téléphonique avec le

     // qDebug() << "failedAttempts" << *failedAttempts;

      if(test)
      {
          QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("login effectuée\n"
                                                                          "Clicke Cancel to exite"),QMessageBox::Cancel);
          qDebug() << "function"<<emp.chercherFunction(mail);
          ui->stackedWidgetGlobal->setCurrentIndex(2);
          id = emp.chercherMailId(mail);
          if(emp.chercherFunction(mail)=="Directeur")
          {
              ui->AddEmployee_2->show();
              ui->supprimer_Employee_2->show();
              ui->pushButton_UpDateImageEmployee->show();
              ui->updateEmployee->show();
              ui->supprimer_Employee->show();
              ui->statEmployee->show();

              ui->statEmployee->setGeometry(740, 500, 61, 61);
              ui->pdfEmployee->setGeometry(710,380,41,51);

              ui->calendar_event->setGeometry(700,520,61,61);
              ui->stat->setGeometry(630,520,61,61);
              ui->pdfevent_2->setGeometry(740,400,41,51);
              ui->pdfevent->setGeometry(740,400,41,51);

              ui->supprimer_32->setGeometry(750,500,61,61);
              ui->supprimer_26->setGeometry(720,410,41,41);

              ui->statEmotion->setGeometry(750,500,61,61);
              ui->pdfGuest->setGeometry(710,390,41,51);

              ui->supprimer_36->setGeometry(660,500,61,61);

              ui->add_event_2->show();
              ui->tout_supprimer->show();
              ui->add_cal->show();
              ui->supprimer_event_cal->show();
              ui->supprimer_event->show();
              ui->updateEvent->show();
              ui->generateAffiche->show();
              ui->weathergenerate->show();
              ui->go_to_participer->show();

              ui->supprimer_GuestSelect->show();
              ui->surv_Guest->show();
              ui->rechercheCinCart->show();
              ui->go_to_addGuest->show();
             ui->go_to_updateGuest->show();
              ui->supprimer_Guest->show();
             ui->go_to_list_from_affSimple->show();

                            ui->listtoaddpro->show();
                            ui->suppgen->show();
                            ui->pub->show();
                            ui->chatbot->show();
                            ui->pushButton_2->show();
                            ui->updateEmployee_5->show();
                            ui->updateEmployee_3->show();
                            ui->supprimer_25->show();

                            ui->listtoaddass->show();
                            ui->asupdate->show();

                            ui->aradd->show();
                            ui->arsupp->show();
                            ui->arupdate->show();
                            ui->arassistant->show();
                            ui->arsupp_2->show();
                            ui->ararriere_7->show();

          }
          else if(emp.chercherFunction(mail)=="RH")
          {

              ui->AddEmployee_2->show();
              ui->supprimer_Employee_2->show();
              ui->pushButton_UpDateImageEmployee->show();
              ui->updateEmployee->show();
              ui->supprimer_Employee->show();

              ui->calendar_event->setGeometry(770,520,61,61);
              ui->stat->setGeometry(700,520,61,61);
              ui->pdfevent_2->setGeometry(790,400,41,51);
              ui->pdfevent->setGeometry(790,400,41,51);

              ui->supprimer_32->setGeometry(820,500,61,61);
              ui->supprimer_26->setGeometry(790,410,41,41);

              ui->statEmotion->setGeometry(820,500,61,61);
              ui->pdfGuest->setGeometry(770,390,41,51);

              ui->supprimer_36->setGeometry(730,500,61,61);
              ui->add_event_2->hide();
              ui->tout_supprimer->hide();
              ui->add_cal->hide();
              ui->supprimer_event_cal->hide();
              ui->supprimer_event->hide();
              ui->updateEvent->hide();
              ui->generateAffiche->hide();
              ui->weathergenerate->hide();
              ui->go_to_participer->hide();

              ui->supprimer_GuestSelect->hide();
              ui->surv_Guest->hide();
              ui->rechercheCinCart->hide();
              ui->go_to_addGuest->hide();
              ui->go_to_updateGuest->hide();
              ui->supprimer_Guest->hide();
              ui->go_to_list_from_affSimple->hide();

              ui->listtoaddpro->hide();
              ui->suppgen->hide();
              ui->pub->hide();
              ui->chatbot->hide();
              ui->pushButton_2->hide();
              ui->updateEmployee_5->hide();
              ui->updateEmployee_3->hide();
              ui->supprimer_25->hide();

              ui->listtoaddass->hide();
              ui->asupdate->hide();

              ui->aradd->hide();
              ui->arsupp->hide();
              ui->arupdate->hide();
              ui->arassistant->hide();
              ui->arsupp_2->hide();
              ui->ararriere_7->hide();
          }
           else//agent
          {
              ui->statEmployee->setGeometry(820, 500, 61, 61);
              ui->pdfEmployee->setGeometry(770,390,41,51);

              ui->AddEmployee_2->hide();
              ui->supprimer_Employee_2->hide();
              ui->pushButton_UpDateImageEmployee->hide();
              ui->updateEmployee->hide();
              ui->supprimer_Employee->hide();

              ui->add_event_2->show();
              ui->tout_supprimer->show();
              ui->add_cal->show();
              ui->supprimer_event_cal->show();
              ui->supprimer_event->show();
              ui->updateEvent->show();
              ui->generateAffiche->show();
              ui->weathergenerate->show();
              ui->go_to_participer->show();

              ui->supprimer_GuestSelect->show();
              ui->surv_Guest->show();
              ui->rechercheCinCart->show();
              ui->go_to_addGuest->show();
             ui->go_to_updateGuest->show();
              ui->supprimer_Guest->show();
             ui->go_to_list_from_affSimple->show();

             ui->listtoaddpro->show();
             ui->suppgen->show();
             ui->pub->show();
             ui->chatbot->show();
             ui->pushButton_2->show();
             ui->updateEmployee_5->show();
             ui->updateEmployee_3->show();
             ui->supprimer_25->show();

                            ui->listtoaddass->show();
                            ui->asupdate->show();

                            ui->aradd->show();
                            ui->arsupp->show();
                            ui->arupdate->show();
                            ui->arassistant->show();
                            ui->arsupp_2->show();
                            ui->ararriere_7->show();
          }

          ui->tabEmployee->setModel(emp.afficherEmployee());


      }else
      {
         ( *failedAttempts)++;

          if ((*failedAttempts) >= 3)
          {
                     // Appel à la fonction d'envoi de SMS d'authentification
                     emp.sendSMS("ACdf31eab647192d5151ae462faf792c8e","3b0c0a3119c3c24a66aa311e693dfce8","+18056331567",phoneString,"Someone is trying to access to your account");
                    //*failedAttempts = 0; // Réinitialise le compteur après envoi du SMS
          }
          QMessageBox::critical(nullptr , QObject::tr("Not Ok "),QObject::tr("login échouée.\n"
                                                                                "Click Cancel to exit."),
                                   QMessageBox::Cancel);


      }
      ui->tabEmployee->setModel(emp.afficherEmployee());

}

void MainWindow::on_pushButton_forgetPassword_clicked()
{
    QRegularExpression emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
      mail=ui->lineEdit_LoginEmail->text();
      if (mail.isEmpty())
              {
                  QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                                        QObject::tr(" champ mail est vide"),
                                        QMessageBox::Cancel);
                  return;
              }
      if (!emailRegex.match(mail).hasMatch()) {
              QMessageBox::critical(this, "Erreur", "Veuillez saisir une adresse email valide.");
              return;
          }
      bool test=emp.chercherMail(mail);
      if(test)
      {
          Smtp *smtp = new Smtp("farahhassen96@gmail.com","bvpz rmqt ubvf ydrg","smtp.gmail.com");
          //connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

          code =new int(smtp->sendMail("farahhassen96@gmail.com",mail,"verification code", "Please enter the following verification code to access your account"));
         //code = new int(emp.sendEmail(mail,"verification code", "Please enter the following verification code to access your account"));
         dialog = new QDialog();
                  dialog->setWindowModality(Qt::WindowModality::NonModal);
                  dialog->setWindowTitle("validation code");
                  dialog->setFixedSize(300, 150); // Set fixed size for the dialog

                  label_1 = new QLabel(dialog);
                  label_1->setText("Enter the verification code: ");
                  label_1->setGeometry(10, 10, 150, 20);

                  lineEdit = new QLineEdit(dialog);
                  lineEdit->setToolTip("Enter the verification code ");
                  lineEdit->setGeometry(80, 40, 150, 30); // Adjust position and size

                  QPushButton *button = new QPushButton(dialog);
                  connect(button, SIGNAL(clicked()), this, SLOT(on_Valider_button_clicked()));
                  button->setText("Valider");
                  button->setGeometry(120, 80, 60, 30); // Adjust position and size

                  dialog->exec();
      }

}
void MainWindow::on_Valider_button_clicked()
{
    int code1=lineEdit->text().toUInt();
qDebug() <<"(*code)"<<(*code);
qDebug() <<"(code1"<<code1;

       if((*code) == code1)
       {
           dialog->close();
           lineEdit->clear();
           ui->stackedWidgetGlobal->setCurrentIndex(1);
       }
       else
       {
           dialog->close();
       }
}

void MainWindow::on_pushButton_ValidNewPassword_clicked()
{
    QString nvPassword=ui->lineEdit_NvPassword->text();
       QString confirmPassword=ui->lineEdit_cofirmPassword->text();
       if (nvPassword == confirmPassword)
       {
           bool test=emp.SaveNewPassword(nvPassword,mail);
           if(test)
           {
               QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("Modification effectuée\n"
                                                                               "Clicke Cancel to exite"),QMessageBox::Cancel);

               ui->tabEmployee->setModel(emp.afficherEmployee());
               ui->stackedWidgetGlobal->setCurrentIndex(2);

           }
           else
           {
               QMessageBox::critical(nullptr , QObject::tr("Not Ok "),QObject::tr("Modification échouée.\n"
                                                                                     "Click Cancel to exit."),
                                        QMessageBox::Cancel);

           }
        }
}

void MainWindow::on_checkBox_passwordLogin_stateChanged()
{
    if (ui->checkBox_passwordLogin->isChecked())
           {
               ui->lineEdit_LoginPassword->setEchoMode(QLineEdit::Normal);
           }
          else
           {
               ui->lineEdit_LoginPassword->setEchoMode(QLineEdit::Password);
           }
}

void MainWindow::on_checkBox_Newpassword_stateChanged()
{
    if (ui->checkBox_Newpassword->isChecked())
        {
            ui->lineEdit_NvPassword->setEchoMode(QLineEdit::Normal);
        }
       else
        {
            ui->lineEdit_NvPassword->setEchoMode(QLineEdit::Password);
        }
}

void MainWindow::on_checkBox_Confirmpassword_stateChanged()
{
    if (ui->checkBox_Confirmpassword->isChecked())
                 {
                     ui->lineEdit_cofirmPassword->setEchoMode(QLineEdit::Normal);
                 }
                else
                 {
                     ui->lineEdit_cofirmPassword->setEchoMode(QLineEdit::Password);
                 }
}

void MainWindow::on_checkBox_passwordSave_stateChanged()
{
    if (ui->checkBox_passwordSave->isChecked())
         {
             ui->lineEdit_PasswordEmployee->setEchoMode(QLineEdit::Normal);
         }
        else
         {
             ui->lineEdit_PasswordEmployee->setEchoMode(QLineEdit::Password);
         }
}

void MainWindow::on_logout_clicked()
{
    ui->stackedWidgetGlobal->setCurrentIndex(0);
      ui->lineEdit_LoginPassword->clear();
      ui->tabEmployee->setModel(emp.afficherEmployee());
}

void MainWindow::on_clearEmployee_clicked()
{
        ui->lineEdit_IdEmployee->clear();
        ui->lineEdit_NameEmployee->clear();
        ui->lineEdit_LastameEmployee->clear();
        ui->lineEdit_AddressEmployee->clear();
        ui->lineEdit_DateBirthEmployee->clear();
        ui->lineEdit_MailEmployee->clear();
        ui->lineEdit_PasswordEmployee->clear();
        ui->lineEdit_PhoneNumberEmployee->clear();
}
