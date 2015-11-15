#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QUdpSocket>
namespace Ui {
class Widget;
}

//枚举变量标志消息的类型:用户上线信息，聊天信息，用户下线信息,文件发送，拒绝接受文件
enum MessageType{ParticapantOn, Message, ParticapantOff, FileName, Refuse};

class Widget : public QWidget
{
    Q_OBJECT



public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void doParticapantON(QString userName, QString localHost, QString ipAddr);
    void sendMessage(MessageType type);
    void doparticapantOFF(QString userName,QString localHost,QString time);

    QString getIp();
    QString getUserName();
    QString getMessage();

private:
    Ui::Widget *ui;
    QUdpSocket *udpSocket;
    qint16 port;

private slots:
    void processPendingDatagrams();

    void on_pushButton_clicked();
};

#endif // WIDGET_H
