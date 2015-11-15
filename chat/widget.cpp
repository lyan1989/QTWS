#include "widget.h"
#include "ui_widget.h"
#include <QHostInfo>
#include <QMessageBox>
#include <QDataStream>
#include <QDateTime>
#include <QProcess>
#include <QNetworkInterface>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //调整用户登录信息框中table为自适应大小
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //设置窗口标题
    setWindowTitle(tr("局域网聊天室"));

    udpSocket = new QUdpSocket(this); //创建一个QUdpSocket对象
    port = 45454;
    udpSocket->bind(port,QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(processPendingDatagrams()));
    sendMessage(ParticapantOn); //打开软件就向外发送上线消息

    /*
    //test environment
    QStringList env = QProcess::systemEnvironment();
    foreach(QString str,env){
        qDebug() << str;

    }
    */
}

Widget::~Widget()
{
    delete ui;
}

void Widget::sendMessage(MessageType type)
{
    QByteArray data; //字节数组
    QDataStream out(&data,QIODevice::WriteOnly);
    QString localHostName = QHostInfo::localHostName();
    QString address = getIp(); //调用getip函数
    out << type << getUserName() << localHostName;

    switch(type)
    {
        case Message:
            if(ui->messageTextEdit->toPlainText()=="")
            {
                QMessageBox::warning(0,tr("警告"),tr("发送内容不能为空"),QMessageBox::Ok);
                return;
            }
            out << address << getMessage();
        break;
    case ParticapantOn:
        out << address;
        break;
    case ParticapantOff:
        break;
    case FileName:
        break;
    case Refuse:
        break;
    }
    udpSocket->writeDatagram(data,QHostAddress::Broadcast,port);
}

void Widget::processPendingDatagrams()
{
    //hasPendingDatagrams返回true时表示至少有一个数据报在等待被读取
    while(udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        //pendingDatagramSize为返回第一个在等待读取报文的size,resize函数是把datagram的size归一化到参数size的大小一样
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(),datagram.size());
        QDataStream in(&datagram,QIODevice::ReadOnly);
        int messageType;
        in >> messageType;
        QString userName,localHostName,ipAddress,message;
        QString time= QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"); //将当前的时间转换为括号中的格式


        switch(messageType)
        {

        case Message:
                //in>>后面如果为QString,则表示读取一个直到出现'\0'的字符串
                in >> userName >> localHostName >> ipAddress >> message;
                ui->messageBrowser->setTextColor(Qt::blue);
                ui->messageBrowser->setCurrentFont(QFont("Times New Roman",10
                                                         ));
                //输出格式为主机名加时间
                ui->messageBrowser->append("["+localHostName+"]"+time);
                ui->messageBrowser->append(message);//消息输出
            break;

        case ParticapantOn:
            in >> userName>>localHostName>>ipAddress;
            doParticapantON(userName,localHostName,ipAddress);
            break;
        case ParticapantOff:
            in >> userName >> localHostName;
            doparticapantOFF(userName,localHostName,time);
            break;
        case FileName:
            break;
        case Refuse:
            break;

        }
    }
}

void Widget::doParticapantON(QString userName, QString localHost, QString ipAddr)
{
    //findItems表示找到与内容localHostName匹配的item，其匹配是基于遍体的匹配模式
    bool isEmpty = ui->tableWidget->findItems(localHost,Qt::MatchExactly).isEmpty();
    if(isEmpty){//没有找到相应的主机
        //新建3个小的ITEM，分别是user,host,ip
        QTableWidgetItem *user = new QTableWidgetItem(userName);
        QTableWidgetItem *host = new QTableWidgetItem(localHost);
        QTableWidgetItem *ip = new QTableWidgetItem(ipAddr);

        ui->tableWidget->insertRow(0);
        ui->tableWidget->setItem(0,0,user);
        ui->tableWidget->setItem(0,1,host);
        ui->tableWidget->setItem(0,2,ip);
        ui->messageBrowser->setTextColor(Qt::gray);
        ui->messageBrowser->setCurrentFont(QFont("Times New Roman",10));
        //arg为返回后面文本的第一个副本,1%表示输出的内容按照第一个.arg后面的输出
        ui->messageBrowser->append(tr("%1 在线!").arg(userName));
        ui->userNumLabel->setText(tr("在线人数：%1").arg(ui->tableWidget->rowCount()));

        //sendMessage(ParticapantOn);
    }
}

void Widget::doparticapantOFF(QString userName, QString localHost, QString time)
{
    int rowNum = ui->tableWidget->findItems(localHost,Qt::MatchExactly).first()->row();
    ui->tableWidget->removeRow(rowNum);
    ui->messageBrowser->setTextColor(Qt::gray);
    ui->messageBrowser->setCurrentFont(QFont("Times New Roman",10));
    ui->messageBrowser->append(tr("%1 于 %2 离开！").arg(userName).arg(time));
    ui->userNumLabel->setText(tr("在线人数: %1").arg(ui->tableWidget->rowCount()));
}

//获取本地Ip地址
QString Widget::getIp()
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list) {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
            return address.toString();
    }
    return 0;
}


//获取用户名
QString Widget::getUserName()
{
    QStringList envVariables;
    envVariables << "USERNAME.*" << "USER.*" << "USERDOMAIN.*"
                 <<"HOSTNAME.*" << "DOMAINNAME.*";
    QStringList env = QProcess::systemEnvironment();
    foreach(QString str,envVariables){
        int index = env.indexOf(QRegExp(str));
        if(index!=-1){
            QStringList stringList = env.at(index).split('=');
            if(stringList.size()==2){
                return stringList.at(1);
                break;
            }
        }
    }
    return "unknown";
}

QString Widget::getMessage()
{
    QString msg = ui->messageTextEdit->toHtml();//转化成html语言进行发送
    ui->messageTextEdit->clear();
    ui->messageTextEdit->setFocus();//重新设置光标输入点
    return msg;
}



void Widget::on_pushButton_clicked()
{
    sendMessage(Message);
}
