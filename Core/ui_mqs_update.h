/********************************************************************************
** Form generated from reading UI file 'mqs_update.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MQS_UPDATE_H
#define UI_MQS_UPDATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MqsUpdater
{
public:
    QProgressBar *progressBar;
    QLabel *label;

    void setupUi(QWidget *MqsUpdater)
    {
        if (MqsUpdater->objectName().isEmpty())
            MqsUpdater->setObjectName(QStringLiteral("MqsUpdater"));
        MqsUpdater->setWindowModality(Qt::WindowModal);
        MqsUpdater->resize(243, 77);
        QIcon icon;
        icon.addFile(QStringLiteral(":/MediaQuickSync/GoContactSyncLogo.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MqsUpdater->setWindowIcon(icon);
        progressBar = new QProgressBar(MqsUpdater);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(10, 30, 241, 41));
        progressBar->setValue(0);
        progressBar->setTextVisible(true);
        label = new QLabel(MqsUpdater);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 5, 111, 21));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setLayoutDirection(Qt::LeftToRight);

        retranslateUi(MqsUpdater);

        QMetaObject::connectSlotsByName(MqsUpdater);
    } // setupUi

    void retranslateUi(QWidget *MqsUpdater)
    {
        MqsUpdater->setWindowTitle(QApplication::translate("MqsUpdater", "MediaQuickSync Updater", 0));
        label->setText(QApplication::translate("MqsUpdater", "Updating...", 0));
    } // retranslateUi

};

namespace Ui {
    class MqsUpdater: public Ui_MqsUpdater {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MQS_UPDATE_H
