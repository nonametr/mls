/********************************************************************************
** Form generated from reading UI file 'mqs_login.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MQS_LOGIN_H
#define UI_MQS_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MqsLogin
{
public:
    QLabel *label;
    QPushButton *login_button;
    QLineEdit *lineEdit;
    QLineEdit *password_text;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *RegisterAccount;
    QLabel *RecoverPassword;
    QCheckBox *is_remeber_me;
    QCheckBox *is_log_me_in_auto;
    QLabel *label_11;
    QLabel *label_12;
    QPushButton *close_button;

    void setupUi(QWidget *MqsLogin)
    {
        if (MqsLogin->objectName().isEmpty())
            MqsLogin->setObjectName(QStringLiteral("MqsLogin"));
        MqsLogin->setWindowModality(Qt::NonModal);
        MqsLogin->setEnabled(true);
        MqsLogin->resize(280, 395);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MqsLogin->sizePolicy().hasHeightForWidth());
        MqsLogin->setSizePolicy(sizePolicy);
        MqsLogin->setMinimumSize(QSize(280, 395));
        MqsLogin->setMaximumSize(QSize(280, 395));
        MqsLogin->setBaseSize(QSize(280, 395));
        MqsLogin->setContextMenuPolicy(Qt::NoContextMenu);
        QIcon icon;
        icon.addFile(QStringLiteral(":/MediaQuickSync/GoContactSyncLogo.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MqsLogin->setWindowIcon(icon);
        MqsLogin->setWindowOpacity(1);
        MqsLogin->setAutoFillBackground(false);
        label = new QLabel(MqsLogin);
        label->setObjectName(QStringLiteral("label"));
        label->setEnabled(true);
        label->setGeometry(QRect(-20, -20, 301, 431));
        label->setPixmap(QPixmap(QString::fromUtf8(":/MediaQuickSync/resources/login.jpg")));
        login_button = new QPushButton(MqsLogin);
        login_button->setObjectName(QStringLiteral("login_button"));
        login_button->setEnabled(true);
        login_button->setGeometry(QRect(40, 240, 201, 41));
        login_button->setStyleSheet(QStringLiteral("background-color: rgba( 255, 255, 255, 0% );"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/MediaQuickSync/resources/login-button.png"), QSize(), QIcon::Normal, QIcon::Off);
        login_button->setIcon(icon1);
        login_button->setIconSize(QSize(160, 40));
        login_button->setCheckable(false);
        login_button->setChecked(false);
        login_button->setAutoRepeat(false);
        login_button->setAutoExclusive(false);
        login_button->setAutoRepeatDelay(100);
        login_button->setAutoRepeatInterval(100);
        login_button->setDefault(false);
        login_button->setFlat(false);
        lineEdit = new QLineEdit(MqsLogin);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(40, 130, 200, 20));
        password_text = new QLineEdit(MqsLogin);
        password_text->setObjectName(QStringLiteral("password_text"));
        password_text->setGeometry(QRect(40, 190, 201, 20));
        label_2 = new QLabel(MqsLogin);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 350, 61, 16));
        label_3 = new QLabel(MqsLogin);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 350, 151, 31));
        label_4 = new QLabel(MqsLogin);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(190, 360, 301, 21));
        label_5 = new QLabel(MqsLogin);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(40, 110, 41, 20));
        label_6 = new QLabel(MqsLogin);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(40, 170, 61, 20));
        RegisterAccount = new QLabel(MqsLogin);
        RegisterAccount->setObjectName(QStringLiteral("RegisterAccount"));
        RegisterAccount->setGeometry(QRect(110, 150, 131, 20));
        RecoverPassword = new QLabel(MqsLogin);
        RecoverPassword->setObjectName(QStringLiteral("RecoverPassword"));
        RecoverPassword->setGeometry(QRect(130, 210, 111, 20));
        is_remeber_me = new QCheckBox(MqsLogin);
        is_remeber_me->setObjectName(QStringLiteral("is_remeber_me"));
        is_remeber_me->setGeometry(QRect(40, 280, 91, 16));
        is_remeber_me->setStyleSheet(QStringLiteral("QCheckBox { color: gray }"));
        is_log_me_in_auto = new QCheckBox(MqsLogin);
        is_log_me_in_auto->setObjectName(QStringLiteral("is_log_me_in_auto"));
        is_log_me_in_auto->setEnabled(true);
        is_log_me_in_auto->setGeometry(QRect(40, 300, 131, 18));
        is_log_me_in_auto->setContextMenuPolicy(Qt::NoContextMenu);
        is_log_me_in_auto->setStyleSheet(QStringLiteral("QCheckBox { color: gray }"));
        is_log_me_in_auto->setCheckable(true);
        is_log_me_in_auto->setChecked(false);
        is_log_me_in_auto->setTristate(false);
        label_11 = new QLabel(MqsLogin);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(60, 320, 111, 16));
        label_11->setStyleSheet(QStringLiteral(""));
        label_12 = new QLabel(MqsLogin);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(40, 320, 16, 21));
        label_12->setPixmap(QPixmap(QString::fromUtf8(":/MediaQuickSync/combobox-arrow-down-2x.png")));
        close_button = new QPushButton(MqsLogin);
        close_button->setObjectName(QStringLiteral("close_button"));
        close_button->setEnabled(true);
        close_button->setGeometry(QRect(230, 10, 51, 41));
        close_button->setAutoFillBackground(false);
        close_button->setStyleSheet(QStringLiteral("background-color: rgba( 255, 255, 255, 0% );"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/MediaQuickSync/power_off_black.png"), QSize(), QIcon::Normal, QIcon::Off);
        close_button->setIcon(icon2);
        close_button->setIconSize(QSize(32, 32));
        close_button->setCheckable(false);
        close_button->setChecked(false);
        close_button->setAutoRepeat(false);
        close_button->setFlat(true);

        retranslateUi(MqsLogin);
        QObject::connect(close_button, SIGNAL(clicked()), MqsLogin, SLOT(close()));

        QMetaObject::connectSlotsByName(MqsLogin);
    } // setupUi

    void retranslateUi(QWidget *MqsLogin)
    {
        MqsLogin->setWindowTitle(QApplication::translate("MqsLogin", "MediaQuickSync", 0));
#ifndef QT_NO_TOOLTIP
        MqsLogin->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label->setText(QString());
        login_button->setText(QString());
        lineEdit->setText(QApplication::translate("MqsLogin", "guest", 0));
        label_2->setText(QApplication::translate("MqsLogin", "<html><head/><body><p><span style=\" font-style:italic; color:#aa0000;\">Version </span><span style=\" font-weight:600; color:#aa0000;\">1.0</span></p></body></html>", 0));
        label_3->setText(QApplication::translate("MqsLogin", "<html><head/><body><p><span style=\" font-size:7pt; font-style:italic; color:#b1b1b1;\">MediaQuickSync </span><img src=\":/MediaQuickSync/GoContactSyncLogo.ico\" width=\"16\" height=\"16\"/><span style=\" font-size:7pt; font-style:italic; color:#b1b1b1;\">v1.0.123.111</span></p></body></html>", 0));
        label_4->setText(QApplication::translate("MqsLogin", "<html><head/><body><p><span style=\" font-size:7pt; font-style:italic; color:#b1b1b1;\">Copyright \302\251 2012</span></p></body></html>", 0));
        label_5->setText(QApplication::translate("MqsLogin", "<html><head/><body><p><span style=\" font-size:9pt; color:#e8e8e8;\">Email:</span></p></body></html>", 0));
        label_6->setText(QApplication::translate("MqsLogin", "<html><head/><body><p><span style=\" font-size:9pt; color:#e8e8e8;\">Password:</span></p></body></html>", 0));
        RegisterAccount->setText(QApplication::translate("MqsLogin", "<html><head/><body><p><span style=\" font-size:9pt; color:#c6c6c6;\"><a href= \"google.com\"  style=\" font-size:9pt; color:#cfc6cf;\">Register new account?</a></span></p></body></html>", 0));
        RecoverPassword->setText(QApplication::translate("MqsLogin", "<html><head/><body><p><span style=\" font-size:9pt; color:#c6c6c6;\"><a href= \"google.com\"  style=\" font-size:9pt; color:#cfc6cf;\">Recover password?</a></span></p></body></html>", 0));
        is_remeber_me->setText(QApplication::translate("MqsLogin", "Remember me", 0));
        is_log_me_in_auto->setText(QApplication::translate("MqsLogin", "Log me in automatically", 0));
        label_11->setText(QApplication::translate("MqsLogin", "<html><head/><body><p><span style=\" color:gray;\">English[United States]</span></p></body></html>", 0));
        label_12->setText(QString());
        close_button->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MqsLogin: public Ui_MqsLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MQS_LOGIN_H
