/********************************************************************************
** Form generated from reading UI file 'custom_rtmp_channel.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOM_RTMP_CHANNEL_H
#define UI_CUSTOM_RTMP_CHANNEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_CustomRtmpChannel
{
public:
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLineEdit *lineEdit_app_link;
    QLabel *label_3;
    QSpacerItem *verticalSpacer;
    QLineEdit *lineEdit_name;
    QLabel *label;
    QLineEdit *lineEdit_rtmp_url;
    QLabel *label_4;
    QLineEdit *lineEdit_description;
    QLabel *label_5;
    QPushButton *pushButton_ok;
    QPushButton *pushButton_cancel;
    QComboBox *comboBox_encoder;
    QLabel *label_6;

    void setupUi(QDialog *CustomRtmpChannel)
    {
        if (CustomRtmpChannel->objectName().isEmpty())
            CustomRtmpChannel->setObjectName(QStringLiteral("CustomRtmpChannel"));
        CustomRtmpChannel->resize(400, 300);
        gridLayout = new QGridLayout(CustomRtmpChannel);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(9, -1, -1, -1);
        label_2 = new QLabel(CustomRtmpChannel);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 1, 1, 1);

        lineEdit_app_link = new QLineEdit(CustomRtmpChannel);
        lineEdit_app_link->setObjectName(QStringLiteral("lineEdit_app_link"));

        gridLayout->addWidget(lineEdit_app_link, 3, 2, 1, 3);

        label_3 = new QLabel(CustomRtmpChannel);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 5, 3, 1, 1);

        lineEdit_name = new QLineEdit(CustomRtmpChannel);
        lineEdit_name->setObjectName(QStringLiteral("lineEdit_name"));

        gridLayout->addWidget(lineEdit_name, 0, 2, 1, 3);

        label = new QLabel(CustomRtmpChannel);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 1, 1, 1);

        lineEdit_rtmp_url = new QLineEdit(CustomRtmpChannel);
        lineEdit_rtmp_url->setObjectName(QStringLiteral("lineEdit_rtmp_url"));

        gridLayout->addWidget(lineEdit_rtmp_url, 2, 2, 1, 3);

        label_4 = new QLabel(CustomRtmpChannel);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 1, 1, 1);

        lineEdit_description = new QLineEdit(CustomRtmpChannel);
        lineEdit_description->setObjectName(QStringLiteral("lineEdit_description"));

        gridLayout->addWidget(lineEdit_description, 1, 2, 1, 3);

        label_5 = new QLabel(CustomRtmpChannel);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 0, 0, 7, 1);

        pushButton_ok = new QPushButton(CustomRtmpChannel);
        pushButton_ok->setObjectName(QStringLiteral("pushButton_ok"));

        gridLayout->addWidget(pushButton_ok, 6, 3, 1, 1);

        pushButton_cancel = new QPushButton(CustomRtmpChannel);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));

        gridLayout->addWidget(pushButton_cancel, 6, 4, 1, 1);

        comboBox_encoder = new QComboBox(CustomRtmpChannel);
        comboBox_encoder->setObjectName(QStringLiteral("comboBox_encoder"));

        gridLayout->addWidget(comboBox_encoder, 4, 2, 1, 3);

        label_6 = new QLabel(CustomRtmpChannel);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 4, 1, 1, 1);


        retranslateUi(CustomRtmpChannel);

        QMetaObject::connectSlotsByName(CustomRtmpChannel);
    } // setupUi

    void retranslateUi(QDialog *CustomRtmpChannel)
    {
        CustomRtmpChannel->setWindowTitle(QApplication::translate("CustomRtmpChannel", "Dialog", 0));
        label_2->setText(QApplication::translate("CustomRtmpChannel", "Description:", 0));
        label_3->setText(QApplication::translate("CustomRtmpChannel", "RTMP url:", 0));
        label->setText(QApplication::translate("CustomRtmpChannel", "Channel name:", 0));
        label_4->setText(QApplication::translate("CustomRtmpChannel", "App link:", 0));
        label_5->setText(QApplication::translate("CustomRtmpChannel", "CUSTOM RTMP", 0));
        pushButton_ok->setText(QApplication::translate("CustomRtmpChannel", "OK", 0));
        pushButton_cancel->setText(QApplication::translate("CustomRtmpChannel", "Cancel", 0));
        label_6->setText(QApplication::translate("CustomRtmpChannel", "Encoder:", 0));
    } // retranslateUi

};

namespace Ui {
    class CustomRtmpChannel: public Ui_CustomRtmpChannel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOM_RTMP_CHANNEL_H
