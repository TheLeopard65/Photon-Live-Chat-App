#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    MainWindow Photon_Client;
    Photon_Client.setWindowTitle("PHOTON APP");
    Photon_Client.show();
    return app.exec();
}
