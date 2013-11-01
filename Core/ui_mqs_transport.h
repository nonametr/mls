/********************************************************************************
** Form generated from reading UI file 'mqs_transport.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MQS_TRANSPORT_H
#define UI_MQS_TRANSPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MqsChannel
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *HLayout_cfg_fields;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *button_ok;
    QPushButton *button_cancel;

    void setupUi(QWidget *MqsChannel)
    {
        if (MqsChannel->objectName().isEmpty())
            MqsChannel->setObjectName(QStringLiteral("MqsChannel"));
        MqsChannel->setWindowModality(Qt::ApplicationModal);
        MqsChannel->resize(434, 336);
        QIcon icon;
        icon.addFile(QStringLiteral(":/MediaQuickSync/resources/GoContactSyncLogo.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MqsChannel->setWindowIcon(icon);
        horizontalLayout = new QHBoxLayout(MqsChannel);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 4, 4, 4);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(MqsChannel);
        label->setObjectName(QStringLiteral("label"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/MediaQuickSync/resources/channel_baner.png")));

        verticalLayout->addWidget(label);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 0, -1, 0);
        HLayout_cfg_fields = new QVBoxLayout();
        HLayout_cfg_fields->setSpacing(8);
        HLayout_cfg_fields->setObjectName(QStringLiteral("HLayout_cfg_fields"));

        verticalLayout_2->addLayout(HLayout_cfg_fields);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 4, -1, -1);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        button_ok = new QPushButton(MqsChannel);
        button_ok->setObjectName(QStringLiteral("button_ok"));

        horizontalLayout_2->addWidget(button_ok);

        button_cancel = new QPushButton(MqsChannel);
        button_cancel->setObjectName(QStringLiteral("button_cancel"));

        horizontalLayout_2->addWidget(button_cancel);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalLayout_2->setStretch(0, 1);

        horizontalLayout->addLayout(verticalLayout_2);

        horizontalLayout->setStretch(1, 10);

        retranslateUi(MqsChannel);

        QMetaObject::connectSlotsByName(MqsChannel);
    } // setupUi

    void retranslateUi(QWidget *MqsChannel)
    {
        MqsChannel->setWindowTitle(QApplication::translate("MqsChannel", "Channel Properties", 0));
        label->setText(QString());
        button_ok->setText(QApplication::translate("MqsChannel", "OK", 0));
        button_cancel->setText(QApplication::translate("MqsChannel", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class MqsChannel: public Ui_MqsChannel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MQS_TRANSPORT_H
