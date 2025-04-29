#include "clienttcpsocket.h"
#include <openssl/aes.h>
#include <openssl/rand.h>

QByteArray ClientTcpSocket::encryptMessage(const QString &message, const QString &key) {
    AES_KEY encryptKey;
    unsigned char iv[AES_BLOCK_SIZE];
    RAND_bytes(iv, AES_BLOCK_SIZE);
    int padding = AES_BLOCK_SIZE - (message.size() % AES_BLOCK_SIZE);
    QByteArray paddedMsg = message.toUtf8();
    paddedMsg.append(padding, static_cast<char>(padding));
    QByteArray encrypted;
    encrypted.resize(AES_BLOCK_SIZE + paddedMsg.size());
    memcpy(encrypted.data(), iv, AES_BLOCK_SIZE);
    AES_set_encrypt_key((const unsigned char*)key.toUtf8().constData(), 128, &encryptKey);
    AES_cbc_encrypt((const unsigned char*)paddedMsg.constData(), (unsigned char*)(encrypted.data() + AES_BLOCK_SIZE), paddedMsg.size(), &encryptKey, iv, AES_ENCRYPT);
    return encrypted;
}
QByteArray ClientTcpSocket::decryptMessage(const QByteArray &encryptedMessage, const QString &key) {
    AES_KEY decryptKey;
    unsigned char iv[AES_BLOCK_SIZE];
    memcpy(iv, encryptedMessage.constData(), AES_BLOCK_SIZE);
    QByteArray ciphertext = encryptedMessage.mid(AES_BLOCK_SIZE);
    QByteArray decryptedMessage;
    decryptedMessage.resize(ciphertext.size());
    AES_set_decrypt_key((const unsigned char*)key.toUtf8().constData(), 128, &decryptKey);
    AES_cbc_encrypt((const unsigned char*)ciphertext.constData(), (unsigned char*)decryptedMessage.data(), ciphertext.size(), &decryptKey, iv, AES_DECRYPT);
    int padding = decryptedMessage.at(decryptedMessage.size() - 1);
    decryptedMessage.chop(padding);
    return decryptedMessage;
}
ClientTcpSocket::ClientTcpSocket(QObject *parent) : QObject(parent){}
void ClientTcpSocket::doConnect(QString host, quint16 port){
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    socket->connectToHost(host, port);
    if(!socket->waitForBytesWritten(5000))
        qDebug() << "ERROR: " << socket->errorString();
}

void ClientTcpSocket::connected() { qDebug() << "Connected to server."; }
void ClientTcpSocket::disconnected() { qDebug() << "Disconnected from server."; }
void ClientTcpSocket::bytesWritten(qint64 bytes) { qDebug() << bytes << "bytes written."; }
void ClientTcpSocket::readyRead() { QByteArray data = socket->readAll(); }
