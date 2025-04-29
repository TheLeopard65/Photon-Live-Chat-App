#include "chatserver.h"

ChatServer::ChatServer(QObject *parent) : QTcpServer(parent){}
void ChatServer::start(){
    if(!this->listen(QHostAddress::Any, this->port)) qDebug() << "[#] Could not start server!";
    else qDebug() << "[#] Server ready and listening on port" << this->port;
}
void ChatServer::incomingConnection(qintptr handle){
    ClientHandlerThread *thread = new ClientHandlerThread(handle, this);
    handlers[handle] = thread;
    connect(thread, SIGNAL(finished(long long)), this, SLOT(on_threadFinished(long long)));
    connect(thread, SIGNAL(messageFromClient(long long, QByteArray)), this, SLOT(on_messageFromClient(long long, QByteArray)));
    connect(this, SIGNAL(messageToAll(QByteArray)), thread, SLOT(on_messageToAll(QByteArray)));
    thread->start();
}
void ChatServer::on_messageFromClient(long long threadId, QByteArray encryptedData) {
    QString nickname = handlers[threadId]->getNickname();
    QByteArray packet;
    QDataStream stream(&packet, QIODevice::WriteOnly);
    stream << nickname << encryptedData;
    emit messageToAll(packet);
}
void ChatServer::on_threadFinished(long long threadId){
    QString disconnectMessage = "[#] " + handlers[threadId]->getNickname() + " has left the chat!";
    handlers.remove(threadId);
    emit messageToAll(disconnectMessage.toUtf8());
}
