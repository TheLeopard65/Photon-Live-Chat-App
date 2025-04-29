#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("PHOTON LIVE CHAT APP");
    w.show();
    return a.exec();
}
