#ifndef SMTP_H
#define SMTP_H

#include <QObject>
#include <QTcpSocket>
#include <QTextStream>

class Smtp : public QObject
{
    Q_OBJECT
public:
    explicit Smtp(const QString &user, const QString &pass, const QString &host, int port, int timeout, QObject *parent = nullptr);
    void sendMail(const QString &from, const QString &to, const QString &subject, const QString &body);

signals:

public slots:
    void connected();
    void disconnected();
    void errorReceived(QAbstractSocket::SocketError socketError);
    void stateChanged(QAbstractSocket::SocketState socketState);
    void readyRead();

private:
    QString user;
    QString pass;
    QString host;
    int port;
    int timeout;
    enum States { Init, HandShake, Auth, User, Pass, Mail, Rcpt, Data, Body, Quit, Close } state;
    QString message;
    QString response;
    QString from;
    QString rcpt;
    QTcpSocket *socket;
    QTextStream *t;
};

#endif // SMTP_H
