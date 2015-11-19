#include "tcpclient.h"
#include "ui_tcpclient.h"

TcpClient::TcpClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TcpClient)
{
    ui->setupUi(this);
    setFixedSize(350,150);

    tcpClient = new QTcpSocket(this);
    tcpPort =6666;
    connect(tcpClient,SIGNAL(readyRead()),this,SLOT(readMessage()));
    connect(tcpClient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));

}

TcpClient::~TcpClient()
{
    delete ui;
}

void TcpClient::setHostAddress(QHostAddress address)
{
    hostAddress = address;
    newConnect();
}

void TcpClient::setFileName(QString fileName)
{
    localFile = new QFile(fileName);
}

void TcpClient::on_cancelBtn_clicked()
{
    tcpClient->abort();
    if(localFile.isOpen())
    {
        localFile.close();
    }
}

void TcpClient::on_closeBtn_clicked()
{
    tcpClient->abort();
    if(localFile.isOpen())
    {
        localFile.close();
    }
    close();
}

void TcpClient::newConnect()
{
    tcpClient->abort();
    tcpClient->connectToHost(hostAddress,tcpPort);
    time.start();
}

void TcpClient::readMessage()
{

}

void TcpClient::displayError(QAbstractSocket::SocketError)
{

}
