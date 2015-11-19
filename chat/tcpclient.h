#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QDialog>
#include <QTcpSocket>
#include <QFile>
#include <QTime>
namespace Ui {
class TcpClient;
}

class TcpClient : public QDialog
{
    Q_OBJECT

public:
    explicit TcpClient(QWidget *parent = 0);
    ~TcpClient();

    void setHostAddress(QHostAddress address);
    void setFileName(QString fileName);

private slots:
    void on_cancelBtn_clicked();

    void on_closeBtn_clicked();
    void newConnect();
    void readMessage();
    void displayError(QAbstractSocket::SocketError);


private:
    Ui::TcpClient *ui;

    QTcpSocket *tcpClient;
    quint16 tcpPort;
    QFile localFile;
    QTime time;
};

#endif // TCPCLIENT_H
