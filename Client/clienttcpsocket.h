#ifndef CLIENTTCPSOCKET_H
#define CLIENTTCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QString>
#include <QByteArray>

class ClientTcpSocket : public QObject{
    Q_OBJECT
public:
    explicit ClientTcpSocket(QObject *parent = nullptr);
    void doConnect(QString host, quint16 port);
    static QByteArray encryptMessage(const QString &message, const QString &key);
    static QByteArray decryptMessage(const QByteArray &encryptedMessage, const QString &key);
public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
private:
    QTcpSocket *socket;
signals:
	void clientReady(qintptr id);
};

#endif // CLIENTTCPSOCKET_H
