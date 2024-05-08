#include "detecte.h"

Smtp::Smtp(const QString &user, const QString &pass, const QString &host, int port, int timeout, QObject *parent) :
    QObject(parent),
    user(user),
    pass(pass),
    host(host),
    port(port),
    timeout(timeout)
{
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorReceived(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChanged(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

void Smtp::sendMail(const QString &from, const QString &to, const QString &subject, const QString &body)
{
    message = "To: " + to + "\n";
    message.append("From: " + from + "\n");
    message.append("Subject: " + subject + "\n");
    message.append(body);
    message.replace(QString::fromLatin1("\n"), QString::fromLatin1("\r\n"));
    message.replace(QString::fromLatin1("\r\n.\r\n"), QString::fromLatin1("\r\n..\r\n"));
    this->from = from;
    rcpt = to;
    state = Init;
    socket->connectToHost(host, port);
    if (!socket->waitForConnected(timeout)) {
        qDebug() << socket->errorString();
    }
    t = new QTextStream(socket);
}

void Smtp::connected()
{
    qDebug() << "Connected ";
}

void Smtp::disconnected()
{
    qDebug() << "Disconnected";
}

void Smtp::errorReceived(QAbstractSocket::SocketError socketError)
{
    qDebug() << "Error: " << socketError;
}

void Smtp::stateChanged(QAbstractSocket::SocketState socketState)
{
    qDebug() << "State changed: " << socketState;
}

void Smtp::readyRead()
{
    qDebug() << "Ready read";
    QString responseLine;
    do {
        responseLine = socket->readLine();
        response += responseLine;
    } while (socket->canReadLine() && responseLine[3] != ' ');
    responseLine.truncate(3);
    qDebug() << "Server response code: " << responseLine;
    qDebug() << "Server response: " << response;

    if (state == Init && responseLine == "220") {
        *t << "EHLO localhost" << "\r\n";
        t->flush();
        state = HandShake;
    } else if (state == HandShake && responseLine == "250") {
        *t << "AUTH LOGIN" << "\r\n";
        t->flush();
        state = Auth;
    } else if (state == Auth && responseLine == "334") {
        *t << user.toLatin1().toBase64() << "\r\n";
        t->flush();
        state = User;
    } else if (state == User && responseLine == "334") {
        *t << pass.toLatin1().toBase64() << "\r\n";
        t->flush();
        state = Pass;
    } else if (state == Pass && responseLine == "235") {
        *t << "MAIL FROM:<" << from << ">\r\n";
        t->flush();
        state = Mail;
    } else if (state == Mail && responseLine == "250") {
        *t << "RCPT TO:<" << rcpt << ">\r\n";
        t->flush();
        state = Rcpt;
    } else if (state == Rcpt && responseLine == "250") {
        *t << "DATA\r\n";
        t->flush();
        state = Data;
    } else if (state == Data && responseLine == "354") {
        *t << message << "\r\n.\r\n";
        t->flush();
        state = Body;
    } else if (state == Body && responseLine == "250") {
        *t << "QUIT\r\n";
        t->flush();
        state = Quit;
    } else if (state == Quit && responseLine == "221") {
        socket->close();
    } else {
        qDebug() << "SMTP error: " << responseLine;
    }
    response = "";
}
