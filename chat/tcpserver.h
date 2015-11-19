#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QDialog>
#include <QTcpServer>
#include <QFileDialog>
#include <QTcpSocket>
#include <QTime>
namespace Ui {
class TcpServer;
}

class TcpServer : public QDialog
{
    Q_OBJECT

public:
    explicit TcpServer(QWidget *parent = 0);
    ~TcpServer();

    void initServer();

public slots:
    void sendMessage();
private:
    Ui::TcpServer *ui;
    quint16 tcpPort;
    QTcpServer *tcpServer;
    qint64 payloadSize; //send file max size 64*1024 every time send
    qint64 totalBytes;
    qint64 bytesWritten;
    qint64 bytesToWrite;
    QByteArray outBlock;

    QString fileName;
    QFile *localFile;
    QTcpSocket *clientConnection;
    QTime time;
    QString theFileName;
signals:
    void sendFileName(QString fileName);
private slots:
    void on_openFileButton_clicked();
    void on_sendFileButton_clicked();
    void on_closeButton_clicked();
    void updateClientProgress(qint64 bytes);
};

#endif // TCPSERVER_H
