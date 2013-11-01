/********************************************************************************
** Form generated from reading UI file 'mqs_encoder.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MQS_ENCODER_H
#define UI_MQS_ENCODER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MqsEncoder
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_2;
    QLabel *label_5;
    QComboBox *combo_preset;
    QComboBox *combo_quality;
    QLabel *label_4;
    QComboBox *combo_encoder;
    QLabel *label_6;
    QComboBox *combo_buffer;
    QComboBox *combo_bitrate;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_10;
    QLineEdit *line_name;
    QGroupBox *groupBox;
    QComboBox *combo_audio_format;
    QLabel *label;
    QLabel *label_2;
    QComboBox *combo_audio_bitrate;
    QLabel *label_3;
    QComboBox *combo_audio_encoder;
    QLabel *label_9;
    QComboBox *combo_audio_source;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *button_ok;
    QPushButton *button_cancel;

    void setupUi(QWidget *MqsEncoder)
    {
        if (MqsEncoder->objectName().isEmpty())
            MqsEncoder->setObjectName(QStringLiteral("MqsEncoder"));
        MqsEncoder->setWindowModality(Qt::ApplicationModal);
        MqsEncoder->resize(469, 270);
        QIcon icon;
        icon.addFile(QStringLiteral(":/MediaQuickSync/resources/GoContactSyncLogo.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MqsEncoder->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(MqsEncoder);
        verticalLayout->setSpacing(2);
        verticalLayout->setContentsMargins(4, 4, 4, 4);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox_2 = new QGroupBox(MqsEncoder);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 76, 55, 16));
        combo_preset = new QComboBox(groupBox_2);
        combo_preset->setObjectName(QStringLiteral("combo_preset"));
        combo_preset->setGeometry(QRect(85, 45, 135, 22));
        combo_quality = new QComboBox(groupBox_2);
        combo_quality->setObjectName(QStringLiteral("combo_quality"));
        combo_quality->setGeometry(QRect(85, 75, 135, 22));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 47, 55, 16));
        combo_encoder = new QComboBox(groupBox_2);
        combo_encoder->setObjectName(QStringLiteral("combo_encoder"));
        combo_encoder->setGeometry(QRect(85, 105, 135, 22));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 105, 55, 16));
        combo_buffer = new QComboBox(groupBox_2);
        combo_buffer->setObjectName(QStringLiteral("combo_buffer"));
        combo_buffer->setGeometry(QRect(300, 45, 135, 22));
        combo_bitrate = new QComboBox(groupBox_2);
        combo_bitrate->setObjectName(QStringLiteral("combo_bitrate"));
        combo_bitrate->setGeometry(QRect(300, 75, 135, 22));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(230, 47, 55, 16));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(230, 76, 55, 16));
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(10, 20, 59, 16));
        line_name = new QLineEdit(groupBox_2);
        line_name->setObjectName(QStringLiteral("line_name"));
        line_name->setGeometry(QRect(85, 18, 347, 20));

        verticalLayout->addWidget(groupBox_2);

        groupBox = new QGroupBox(MqsEncoder);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        combo_audio_format = new QComboBox(groupBox);
        combo_audio_format->setObjectName(QStringLiteral("combo_audio_format"));
        combo_audio_format->setGeometry(QRect(305, 57, 135, 22));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(240, 60, 55, 16));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 55, 55, 16));
        combo_audio_bitrate = new QComboBox(groupBox);
        combo_audio_bitrate->setObjectName(QStringLiteral("combo_audio_bitrate"));
        combo_audio_bitrate->setGeometry(QRect(85, 55, 135, 22));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(240, 26, 55, 16));
        combo_audio_encoder = new QComboBox(groupBox);
        combo_audio_encoder->setObjectName(QStringLiteral("combo_audio_encoder"));
        combo_audio_encoder->setGeometry(QRect(305, 25, 135, 22));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 26, 55, 16));
        combo_audio_source = new QComboBox(groupBox);
        combo_audio_source->setObjectName(QStringLiteral("combo_audio_source"));
        combo_audio_source->setGeometry(QRect(85, 24, 135, 22));

        verticalLayout->addWidget(groupBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        button_ok = new QPushButton(MqsEncoder);
        button_ok->setObjectName(QStringLiteral("button_ok"));

        horizontalLayout->addWidget(button_ok);

        button_cancel = new QPushButton(MqsEncoder);
        button_cancel->setObjectName(QStringLiteral("button_cancel"));

        horizontalLayout->addWidget(button_cancel);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 10);
        verticalLayout->setStretch(1, 6);

        retranslateUi(MqsEncoder);

        QMetaObject::connectSlotsByName(MqsEncoder);
    } // setupUi

    void retranslateUi(QWidget *MqsEncoder)
    {
        MqsEncoder->setWindowTitle(QApplication::translate("MqsEncoder", "Encoder Properties", 0));
        groupBox_2->setTitle(QApplication::translate("MqsEncoder", "Video Encoding", 0));
        label_5->setText(QApplication::translate("MqsEncoder", "<html><head/><body><p><span style=\" font-size:9pt; font-weight:600;\">Quality:</span></p></body></html>", 0));
        combo_preset->clear();
        combo_preset->insertItems(0, QStringList()
         << QApplication::translate("MqsEncoder", "ultrafast", 0)
         << QApplication::translate("MqsEncoder", "superfast", 0)
         << QApplication::translate("MqsEncoder", "veryfast", 0)
         << QApplication::translate("MqsEncoder", "faster", 0)
         << QApplication::translate("MqsEncoder", "fast", 0)
         << QApplication::translate("MqsEncoder", "medium", 0)
         << QApplication::translate("MqsEncoder", "slow", 0)
         << QApplication::translate("MqsEncoder", "slower", 0)
         << QApplication::translate("MqsEncoder", "veryslow", 0)
         << QApplication::translate("MqsEncoder", "placebo", 0)
        );
        combo_quality->clear();
        combo_quality->insertItems(0, QStringList()
         << QApplication::translate("MqsEncoder", "1", 0)
         << QApplication::translate("MqsEncoder", "2", 0)
         << QApplication::translate("MqsEncoder", "3", 0)
         << QApplication::translate("MqsEncoder", "4", 0)
         << QApplication::translate("MqsEncoder", "5", 0)
         << QApplication::translate("MqsEncoder", "6", 0)
        );
        label_4->setText(QApplication::translate("MqsEncoder", "<html><head/><body><p><span style=\" font-size:9pt; font-weight:600;\">Preset:</span></p></body></html>", 0));
        label_6->setText(QApplication::translate("MqsEncoder", "<html><head/><body><p><span style=\" font-size:9pt; font-weight:600;\">Encoder:</span></p></body></html>", 0));
        combo_buffer->clear();
        combo_buffer->insertItems(0, QStringList()
         << QApplication::translate("MqsEncoder", "512", 0)
         << QApplication::translate("MqsEncoder", "1024", 0)
         << QApplication::translate("MqsEncoder", "2048", 0)
         << QApplication::translate("MqsEncoder", "4096", 0)
         << QApplication::translate("MqsEncoder", "8192", 0)
         << QApplication::translate("MqsEncoder", "12288", 0)
         << QApplication::translate("MqsEncoder", "16384", 0)
         << QApplication::translate("MqsEncoder", "24576", 0)
         << QApplication::translate("MqsEncoder", "32768", 0)
        );
        combo_bitrate->clear();
        combo_bitrate->insertItems(0, QStringList()
         << QApplication::translate("MqsEncoder", "384", 0)
         << QApplication::translate("MqsEncoder", "512", 0)
         << QApplication::translate("MqsEncoder", "768", 0)
         << QApplication::translate("MqsEncoder", "1024", 0)
         << QApplication::translate("MqsEncoder", "1536", 0)
         << QApplication::translate("MqsEncoder", "2048", 0)
         << QApplication::translate("MqsEncoder", "2560", 0)
         << QApplication::translate("MqsEncoder", "3072", 0)
         << QApplication::translate("MqsEncoder", "4096", 0)
         << QApplication::translate("MqsEncoder", "6144", 0)
         << QApplication::translate("MqsEncoder", "8192", 0)
        );
        label_7->setText(QApplication::translate("MqsEncoder", "<html><head/><body><p><span style=\" font-size:9pt; font-weight:600;\">Buffer:</span></p></body></html>", 0));
        label_8->setText(QApplication::translate("MqsEncoder", "<html><head/><body><p><span style=\" font-size:9pt; font-weight:600;\">Bitrate:</span></p></body></html>", 0));
        label_10->setText(QApplication::translate("MqsEncoder", "<html><head/><body><p><span style=\" font-size:9pt; font-weight:600;\">Name:</span></p></body></html>", 0));
        groupBox->setTitle(QApplication::translate("MqsEncoder", "Audio Encoding", 0));
        combo_audio_format->clear();
        combo_audio_format->insertItems(0, QStringList()
         << QApplication::translate("MqsEncoder", "44100", 0)
         << QApplication::translate("MqsEncoder", "22050", 0)
        );
        label->setText(QApplication::translate("MqsEncoder", "<html><head/><body><p><span style=\" font-size:9pt; font-weight:600;\">Format:</span></p></body></html>", 0));
        label_2->setText(QApplication::translate("MqsEncoder", "<html><head/><body><p><span style=\" font-size:9pt; font-weight:600;\">Bitrate:</span></p></body></html>", 0));
        combo_audio_bitrate->clear();
        combo_audio_bitrate->insertItems(0, QStringList()
         << QApplication::translate("MqsEncoder", "32", 0)
         << QApplication::translate("MqsEncoder", "56", 0)
         << QApplication::translate("MqsEncoder", "80", 0)
         << QApplication::translate("MqsEncoder", "96", 0)
         << QApplication::translate("MqsEncoder", "112", 0)
         << QApplication::translate("MqsEncoder", "128", 0)
         << QApplication::translate("MqsEncoder", "160", 0)
         << QApplication::translate("MqsEncoder", "192", 0)
         << QApplication::translate("MqsEncoder", "224", 0)
         << QApplication::translate("MqsEncoder", "256", 0)
         << QApplication::translate("MqsEncoder", "320", 0)
        );
        label_3->setText(QApplication::translate("MqsEncoder", "<html><head/><body><p><span style=\" font-size:9pt; font-weight:600;\">Encoder:</span></p></body></html>", 0));
        combo_audio_encoder->clear();
        combo_audio_encoder->insertItems(0, QStringList()
         << QApplication::translate("MqsEncoder", "mp3", 0)
         << QApplication::translate("MqsEncoder", "aac -strict 2", 0)
        );
        label_9->setText(QApplication::translate("MqsEncoder", "<html><head/><body><p><span style=\" font-size:9pt; font-weight:600;\">Source:</span></p></body></html>", 0));
        button_ok->setText(QApplication::translate("MqsEncoder", "OK", 0));
        button_cancel->setText(QApplication::translate("MqsEncoder", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class MqsEncoder: public Ui_MqsEncoder {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MQS_ENCODER_H
