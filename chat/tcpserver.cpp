#include "tcpserver.h"
#include "ui_tcpserver.h"
#include <QMessageBox>

TcpServer::TcpServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TcpServer)
{
    ui->setupUi(this);
    setFixedSize(380,180);
    tcpPort = 6666;
    tcpServer = new QTcpServer(this);
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(sendMessage()));
    initServer();
}

TcpServer::~TcpServer()
{
    delete ui;
}

void TcpServer::initServer()
{
    payloadSize = 64*1024;
    totalBytes = 0;
    bytesToWrite = 0;
    bytesWritten = 0;

    ui->serverStatusLabel->setText(tr("Chose which file need to be sent."));
    ui->progressBar->reset();
    ui->sendFileButton->setEnabled(false);
    ui->openFileButton->setEnabled(true);

    tcpServer->close();
}

void TcpServer::sendMessage()
{
    ui->sendFileButton->setEnabled(false);
    clientConnection = tcpServer->nextPendingConnection(); //achieve a tcp connection
    connect(clientConnection,SIGNAL(bytesWritten(qint64)),this,SLOT(updateClientProgress(qint64)));

    ui->serverStatusLabel->setText(tr("start sending files...."));
    qDebug() << theFileName;
    localFile  = new QFile(theFileName);
    if(!localFile->isOpen())
    {
        QMessageBox::warning(this,tr("program"),tr("can not read the file %1:\n%2")
                             .arg(fileName).arg(localFile->errorString())); //the file error information
        return;
    }
    totalBytes = localFile->size();
    //SET the output streaming attributes
    QDataStream sendout(&outBlock,QIODevice::WriteOnly);
    sendout.setVersion(QDataStream::Qt_5_1);
    time.start();
    sendout <<qint64(0) << qint64(0) << fileName;
    //the file information size plus file size;
    totalBytes += outBlock.size();
    //return to the origin of the outBlock
    sendout.device()->seek(0);
    //send the size information
    sendout << totalBytes << qint64(outBlock.size()-sizeof(qint64)*2);
    bytesToWrite = totalBytes - clientConnection->write(outBlock);
    outBlock.resize(0);
}

//chose the file which need to be sent
void TcpServer::on_openFileButton_clicked()
{
    theFileName = QFileDialog::getOpenFileName(0);
    if(!theFileName.isEmpty())
    {
        fileName = theFileName.right(theFileName.size()-theFileName.lastIndexOf('/')-1);
        ui->serverStatusLabel->setText(tr("send file %1").arg(fileName));
        ui->openFileButton->setEnabled(false);
        ui->sendFileButton->setEnabled(true);

    }
}
//send the file
void TcpServer::on_sendFileButton_clicked()
{
    //tcp server listen the port 6666
    if(!tcpServer->listen(QHostAddress::Any,6666))
    {
        qDebug() << tcpServer->errorString();
        close();
        return;
    }

    ui->serverStatusLabel->setText(tr("wait receiving..."));
    emit sendFileName(fileName);
}

void TcpServer::on_closeButton_clicked()
{
    if(tcpServer->isListening())
    {
        //when tcp server is listening prot 666, close
        tcpServer->close();
        //if(localFile->isOpen())
         //   localFile->close();
        qDebug() << "close the tcp server.";
    }
    close();//close the tcpserver ui
}
//update the progress bar
void TcpServer::updateClientProgress(qint64 bytes)
{
    qApp->processEvents();
    bytesWritten += (int)bytes;
    if(bytesToWrite >0)
    {
        outBlock = localFile->read(qMin(bytesToWrite,payloadSize));
        bytesToWrite -= (int)clientConnection->write(outBlock);
        outBlock.resize(0); //clean the buffer

    }
    else
        localFile->close();

    ui->progressBar->setMaximum(totalBytes);
    ui->progressBar->setValue(bytesWritten);

    float usetime = time.elapsed();
    double speed = bytesWritten / usetime;
    ui->serverStatusLabel->setText(tr("Send %1MB (%2MB/s)\n total %3MB time:%4s\n last time:%5s")
                                   .arg(bytesWritten/(1024*1024)).arg(speed*1000/(1024*1024),0,'f',2)
                                   .arg(totalBytes/(1024*1024)).arg(usetime/1000,0,'f',0)
                                   .arg(totalBytes/speed/1000-usetime/1000,0,'f',0));

    if(bytesWritten == totalBytes)
    {
        localFile->close();
        tcpServer->close();
        ui->serverStatusLabel->setText(tr("The %1 has been transformed successly").arg(fileName));

    }

}
