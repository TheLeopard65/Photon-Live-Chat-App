#include <QCoreApplication>
#include "chatserver.h"

int main(int argc, char *argv[]){
    QCoreApplication app(argc, argv);
    ChatServer Photon_Server;
    Photon_Server.start();
    return app.exec();
}
