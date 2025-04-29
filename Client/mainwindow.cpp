#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clienttcpsocket.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->txt_allmsg->setTextColor(Qt::gray);
    ui->txt_allmsg->setReadOnly(true);
    ui->txt_allmsg->setStyleSheet("QTextEdit { background-color: #444444; color: #ffffff; }");
    setStatus("DISCONNECTED");
}
MainWindow::~MainWindow(){ delete ui; }
void MainWindow::on_btn_connect_clicked(){
    if(!isConnected) {
        setConnectInputsEnabled(false);
        ui->btn_connect->setEnabled(false);
        ui->txt_allmsg->clear();
        socket = new QTcpSocket(this);
        QString host = ui->input_server->text();
        quint16 port = defaultPort;
        connect(socket, SIGNAL(connected()), this, SLOT(on_connected()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(on_disconnected()));
        connect(socket, SIGNAL(readyRead()), this, SLOT(on_readyRead()));
        setStatus("CONNECTING...", Qt::yellow);
        socket->connectToHost(host, port);
        if(!socket->waitForConnected(1000)) {
            setStatus("some error occured", Qt::red);
            setConnectInputsEnabled(true);
            ui->btn_connect->setEnabled(true);
        }
    } else socket->disconnectFromHost();
}
void MainWindow::on_connected(){
    isConnected = true;
    setStatus("CONNECTED", Qt::green);
    setChatControlsEnabled(true);
    ui->btn_connect->setText("DISCONNECT");
    ui->btn_connect->setEnabled(true);
    socket->write(ui->input_nickname->text().toUtf8());
}
void MainWindow::on_disconnected(){
    isConnected = false;
    setStatus("DISCONNECTED");
    setChatControlsEnabled(false);
    setConnectInputsEnabled(true);
    ui->btn_connect->setText("CONNECT");
}
void MainWindow::setConnectInputsEnabled(bool val){
    ui->input_nickname->setEnabled(val);
    ui->input_server->setEnabled(val);
}
void MainWindow::on_readyRead() {
    QByteArray data = socket->readAll();
    QDataStream stream(data);
    QString nickname;
    QByteArray encryptedMessage;
    stream >> nickname >> encryptedMessage;
    if (stream.status() == QDataStream::Ok) {
        QString key = "PH070N-L1V3-CH47";
        QByteArray decrypted = ClientTcpSocket::decryptMessage(encryptedMessage, key);
        QString displayMsg = "[" + nickname + "]: " + QString::fromUtf8(decrypted);
        ui->txt_allmsg->append(displayMsg);
    } else qDebug() << "Failed to parse message from server";
}
void MainWindow::setChatControlsEnabled(bool val){
    ui->txt_tosend->setEnabled(val);
    ui->btn_send->setEnabled(val);
    if(val) ui->txt_allmsg->setStyleSheet("QTextEdit { background-color: #444444; color: #ffffff; }");
    else ui->txt_allmsg->setStyleSheet("QTextEdit { background-color: #f0f0f0; color: #ffffff; }");
}
void MainWindow::setStatus(QString status, QColor color){
    ui->lbl_status->setText(status);
    ui->lbl_status->setStyleSheet("QLabel { color: " + color.name() + "; }");
}
void MainWindow::on_btn_send_clicked(){
    QString toSend = ui->txt_tosend->toPlainText();
    QString key = "PH070N-L1V3-CH47";
    QByteArray encryptedMessage = ClientTcpSocket::encryptMessage(toSend, key);
    socket->write(encryptedMessage);
    ui->txt_tosend->clear();
}
