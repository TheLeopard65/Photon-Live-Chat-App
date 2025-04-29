#include "clienthandlerthread.h"
#include <openssl/aes.h>
#include <openssl/rand.h>

QByteArray ClientHandlerThread::decryptMessage(const QByteArray &encryptedMessage, const QString &key) {
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
ClientHandlerThread::ClientHandlerThread(qintptr handle, QObject *parent) : QThread(parent) { this->id = handle; }
void ClientHandlerThread::run(){
    socket = new CustomTcpSocket();
    if(!socket->setSocketDescriptor(id)) {
        emit error(socket->error());
        exit(1);
    }
    qDebug() << "[#] Client #" << id << " has connected";
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(this, SIGNAL(messageToSocket(QByteArray)), socket, SLOT(on_messageToSocket(QByteArray)));
    exec();
}
void ClientHandlerThread::readyRead(){
    QByteArray data = socket->readAll();
    if(!nicknameReceived) {
        nickname = QString::fromStdString(data.toStdString());
        nicknameReceived = true;
    } else emit messageFromClient(id, data);
}
void ClientHandlerThread::disconnected(){
    socket->deleteLater();
    qDebug() << "[#] Client #" << id << " has disconnected";
    emit finished(id);
    exit(0);
}
QHostAddress ClientHandlerThread::getPeerAddress(){ return socket->peerAddress(); }
void ClientHandlerThread::on_messageToAll(QByteArray data){ emit messageToSocket(data); }
QString ClientHandlerThread::getNickname(){ return nickname; }
void ClientHandlerThread::setNickname(QString newName){ nickname = newName; }
