/********************************************************************************
** Form generated from reading UI file 'tcpserver.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCPSERVER_H
#define UI_TCPSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TcpServer
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *serverStatusLabel;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QProgressBar *progressBar;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *openFileButton;
    QPushButton *sendFileButton;
    QPushButton *closeButton;

    void setupUi(QDialog *TcpServer)
    {
        if (TcpServer->objectName().isEmpty())
            TcpServer->setObjectName(QStringLiteral("TcpServer"));
        TcpServer->resize(400, 300);
        verticalLayout = new QVBoxLayout(TcpServer);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        serverStatusLabel = new QLabel(TcpServer);
        serverStatusLabel->setObjectName(QStringLiteral("serverStatusLabel"));
        QFont font;
        font.setPointSize(17);
        font.setBold(true);
        font.setWeight(75);
        serverStatusLabel->setFont(font);
        serverStatusLabel->setLayoutDirection(Qt::LeftToRight);
        serverStatusLabel->setScaledContents(false);
        serverStatusLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(serverStatusLabel);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        progressBar = new QProgressBar(TcpServer);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy);
        progressBar->setMinimumSize(QSize(0, 30));
        progressBar->setValue(0);
        progressBar->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(progressBar);

        label_2 = new QLabel(TcpServer);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setMinimumSize(QSize(50, 0));
        QFont font1;
        font1.setPointSize(15);
        font1.setBold(true);
        font1.setWeight(75);
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        openFileButton = new QPushButton(TcpServer);
        openFileButton->setObjectName(QStringLiteral("openFileButton"));

        horizontalLayout->addWidget(openFileButton);

        sendFileButton = new QPushButton(TcpServer);
        sendFileButton->setObjectName(QStringLiteral("sendFileButton"));

        horizontalLayout->addWidget(sendFileButton);

        closeButton = new QPushButton(TcpServer);
        closeButton->setObjectName(QStringLiteral("closeButton"));

        horizontalLayout->addWidget(closeButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(TcpServer);

        QMetaObject::connectSlotsByName(TcpServer);
    } // setupUi

    void retranslateUi(QDialog *TcpServer)
    {
        TcpServer->setWindowTitle(QApplication::translate("TcpServer", "Dialog", 0));
        serverStatusLabel->setText(QApplication::translate("TcpServer", "TextLabel", 0));
        label_2->setText(QApplication::translate("TcpServer", "0%", 0));
        openFileButton->setText(QApplication::translate("TcpServer", "OPEN", 0));
        sendFileButton->setText(QApplication::translate("TcpServer", "SEND", 0));
        closeButton->setText(QApplication::translate("TcpServer", "CLOSE", 0));
    } // retranslateUi

};

namespace Ui {
    class TcpServer: public Ui_TcpServer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPSERVER_H
