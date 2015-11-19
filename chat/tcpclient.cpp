#include "tcpclient.h"
#include "ui_tcpclient.h"
#include <QMessageBox>

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
    ui->progressBar->reset();
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
    if(localFile->isOpen())
    {
        localFile->close();
    }
}

void TcpClient::on_closeBtn_clicked()
{
    tcpClient->abort();
    if(localFile->isOpen())
    {
        localFile->close();
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
    QDataStream in(tcpClient);
    in.setVersion(QDataStream::Qt_5_1);
    float useTime = time.elapsed(); if (bytesReceived <= sizeof(qint64)*2) {    //说明刚开始接受数据
        if ((tcpClient->bytesAvailable()    //bytesAvailable为返回将要被读取的字节数
             >= sizeof(qint64)*2) && (fileNameSize == 0))
        {
            //接受数据总大小信息和文件名大小信息
            in>>TotalBytes>>fileNameSize;
            bytesReceived += sizeof(qint64)*2;
        }
        if((tcpClient->bytesAvailable() >= fileNameSize) && (fileNameSize != 0)){
            //开始接受文件，并建立文件
            in>>fileName;
            bytesReceived +=fileNameSize;

            if(!localFile->open(QFile::WriteOnly)){
                QMessageBox::warning(this,tr("应用程序"),tr("无法读取文件 %1:\n%2.")
                                     .arg(fileName).arg(localFile->errorString()));
                return;
            }
        } else {
            return;
        }
    }
    if (bytesReceived < TotalBytes) {
        bytesReceived += tcpClient->bytesAvailable();//返回tcpClient中字节的总数
        inBlock = tcpClient->readAll();    //返回读到的所有数据
        localFile->write(inBlock);
        inBlock.resize(0);
    }
    ui->progressBar->setMaximum(TotalBytes);
    ui->progressBar->setValue(bytesReceived);

    double speed = bytesReceived / useTime;
    ui->tcpClientStatusLabel->setText(tr("已接收 %1MB (%2MB/s) "
                                         "\n共%3MB 已用时:%4秒\n估计剩余时间：%5秒")
                                      .arg(bytesReceived / (1024*1024))
                                      .arg(speed*1000/(1024*1024),0,'f',2)
                                      .arg(TotalBytes / (1024 * 1024))
                                      .arg(useTime/1000,0,'f',0)
                                      .arg(TotalBytes/speed/1000 - useTime/1000,0,'f',0));

    if(bytesReceived == TotalBytes)
    {
        localFile->close();
        tcpClient->close();
        ui->tcpClientStatusLabel->setText(tr("接收文件 %1 完毕")
                                          .arg(fileName));
    }
}

void TcpClient::displayError(QAbstractSocket::SocketError)
{

}
