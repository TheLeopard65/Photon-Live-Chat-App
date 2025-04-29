#ifndef CLIENTHANDLERTHREAD_H
#define CLIENTHANDLERTHREAD_H

#include <QThread>
#include <QDebug>
#include <QTcpSocket>
#include <QHostAddress>
#include "customtcpsocket.h"

class ClientHandlerThread : public QThread{
    Q_OBJECT
public:
    static QByteArray decryptMessage(const QByteArray &encryptedMessage, const QString &key);
    explicit ClientHandlerThread(qintptr handle, QObject *parent = nullptr);
    void setNickname(QString newName);
    QHostAddress getPeerAddress();
    QString getNickname();
    void run();
signals:
	void clientReady(long long id);
    void error(QTcpSocket::SocketError error);
    void messageFromClient(long long id, QByteArray data);
    void finished(long long id);
    void messageToSocket(QByteArray data);
public slots:
    void readyRead();
    void disconnected();
    void on_messageToAll(QByteArray data);
private:
    QTcpSocket *socket;
    qintptr id;
    QString nickname;
    bool nicknameReceived = false;
};

#endif // CLIENTHANDLERTHREAD_H
