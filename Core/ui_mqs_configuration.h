/********************************************************************************
** Form generated from reading UI file 'mqs_configuration.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MQS_CONFIGURATION_H
#define UI_MQS_CONFIGURATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Config
{
public:
    QHBoxLayout *horizontalLayout_5;
    QTabWidget *tabWidget;
    QWidget *channels;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *button_add_channel;
    QPushButton *button_edit_channel;
    QPushButton *button_remove_channel;
    QSpacerItem *verticalSpacer;
    QListWidget *list_channel;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QWidget *encoders;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *button_add_encoder;
    QPushButton *button_edit_encoder;
    QPushButton *button_remove_encoder;
    QLabel *label_logo_img;
    QSpacerItem *verticalSpacer_2;
    QListWidget *list_encoders;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_3;
    QWidget *Resolutions;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_6;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_2;
    QListWidget *list_resolutions;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *button_sellectall_resolutions;
    QPushButton *button_clearall_resolutions;
    QPushButton *button_loaddefaults_resolutions;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *button_add_resolutions;
    QPushButton *button_edit_resolutions;
    QPushButton *button_remove_resolutions;
    QWidget *general;
    QFormLayout *formLayout_2;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *line_plugin_path;
    QToolButton *select_plugins_dir;
    QLabel *label_9;
    QHBoxLayout *horizontalLayout_10;
    QLineEdit *line_screen_shot_path;
    QToolButton *select_screenshot_dir;

    void setupUi(QWidget *Config)
    {
        if (Config->objectName().isEmpty())
            Config->setObjectName(QStringLiteral("Config"));
        Config->setWindowModality(Qt::ApplicationModal);
        Config->resize(628, 451);
        QIcon icon;
        icon.addFile(QStringLiteral(":/MediaQuickSync/resources/GoContactSyncLogo.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Config->setWindowIcon(icon);
        horizontalLayout_5 = new QHBoxLayout(Config);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        tabWidget = new QTabWidget(Config);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        channels = new QWidget();
        channels->setObjectName(QStringLiteral("channels"));
        gridLayout = new QGridLayout(channels);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        button_add_channel = new QPushButton(channels);
        button_add_channel->setObjectName(QStringLiteral("button_add_channel"));

        verticalLayout->addWidget(button_add_channel);

        button_edit_channel = new QPushButton(channels);
        button_edit_channel->setObjectName(QStringLiteral("button_edit_channel"));

        verticalLayout->addWidget(button_edit_channel);

        button_remove_channel = new QPushButton(channels);
        button_remove_channel->setObjectName(QStringLiteral("button_remove_channel"));

        verticalLayout->addWidget(button_remove_channel);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout->addLayout(verticalLayout, 2, 1, 1, 1);

        list_channel = new QListWidget(channels);
        list_channel->setObjectName(QStringLiteral("list_channel"));
        list_channel->setProperty("showDropIndicator", QVariant(true));
        list_channel->setDragEnabled(true);
        list_channel->setDragDropOverwriteMode(false);
        list_channel->setDragDropMode(QAbstractItemView::DragDrop);
        list_channel->setDefaultDropAction(Qt::MoveAction);

        gridLayout->addWidget(list_channel, 2, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(15);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(channels);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/MediaQuickSync/resources/1353017205_xine.png")));

        horizontalLayout_2->addWidget(label_2);

        label = new QLabel(channels);
        label->setObjectName(QStringLiteral("label"));
        label->setLineWidth(1);
        label->setTextFormat(Qt::AutoText);
        label->setScaledContents(false);
        label->setOpenExternalLinks(true);
        label->setTextInteractionFlags(Qt::LinksAccessibleByKeyboard|Qt::LinksAccessibleByMouse);

        horizontalLayout_2->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 2);

        tabWidget->addTab(channels, QString());
        encoders = new QWidget();
        encoders->setObjectName(QStringLiteral("encoders"));
        gridLayout_2 = new QGridLayout(encoders);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        button_add_encoder = new QPushButton(encoders);
        button_add_encoder->setObjectName(QStringLiteral("button_add_encoder"));

        verticalLayout_2->addWidget(button_add_encoder);

        button_edit_encoder = new QPushButton(encoders);
        button_edit_encoder->setObjectName(QStringLiteral("button_edit_encoder"));

        verticalLayout_2->addWidget(button_edit_encoder);

        button_remove_encoder = new QPushButton(encoders);
        button_remove_encoder->setObjectName(QStringLiteral("button_remove_encoder"));

        verticalLayout_2->addWidget(button_remove_encoder);

        label_logo_img = new QLabel(encoders);
        label_logo_img->setObjectName(QStringLiteral("label_logo_img"));
        label_logo_img->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_logo_img);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        gridLayout_2->addLayout(verticalLayout_2, 3, 2, 1, 1);

        list_encoders = new QListWidget(encoders);
        list_encoders->setObjectName(QStringLiteral("list_encoders"));
        list_encoders->setDragEnabled(true);
        list_encoders->setDragDropMode(QAbstractItemView::DragDrop);
        list_encoders->setDefaultDropAction(Qt::MoveAction);

        gridLayout_2->addWidget(list_encoders, 3, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(15);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_4 = new QLabel(encoders);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/MediaQuickSync/resources/1353018877_kmencoder.png")));

        horizontalLayout->addWidget(label_4);

        label_3 = new QLabel(encoders);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setOpenExternalLinks(true);
        label_3->setTextInteractionFlags(Qt::LinksAccessibleByKeyboard|Qt::LinksAccessibleByMouse);

        horizontalLayout->addWidget(label_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        gridLayout_2->addLayout(horizontalLayout, 0, 1, 1, 2);

        tabWidget->addTab(encoders, QString());
        Resolutions = new QWidget();
        Resolutions->setObjectName(QStringLiteral("Resolutions"));
        verticalLayout_3 = new QVBoxLayout(Resolutions);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(15);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_6 = new QLabel(Resolutions);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setPixmap(QPixmap(QString::fromUtf8(":/logo/resolution_config.png")));

        horizontalLayout_3->addWidget(label_6);

        label_5 = new QLabel(Resolutions);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setOpenExternalLinks(true);
        label_5->setTextInteractionFlags(Qt::LinksAccessibleByKeyboard|Qt::LinksAccessibleByMouse);

        horizontalLayout_3->addWidget(label_5);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_3);

        list_resolutions = new QListWidget(Resolutions);
        list_resolutions->setObjectName(QStringLiteral("list_resolutions"));

        verticalLayout_3->addWidget(list_resolutions);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        button_sellectall_resolutions = new QPushButton(Resolutions);
        button_sellectall_resolutions->setObjectName(QStringLiteral("button_sellectall_resolutions"));

        horizontalLayout_4->addWidget(button_sellectall_resolutions);

        button_clearall_resolutions = new QPushButton(Resolutions);
        button_clearall_resolutions->setObjectName(QStringLiteral("button_clearall_resolutions"));

        horizontalLayout_4->addWidget(button_clearall_resolutions);

        button_loaddefaults_resolutions = new QPushButton(Resolutions);
        button_loaddefaults_resolutions->setObjectName(QStringLiteral("button_loaddefaults_resolutions"));

        horizontalLayout_4->addWidget(button_loaddefaults_resolutions);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        button_add_resolutions = new QPushButton(Resolutions);
        button_add_resolutions->setObjectName(QStringLiteral("button_add_resolutions"));

        horizontalLayout_4->addWidget(button_add_resolutions);

        button_edit_resolutions = new QPushButton(Resolutions);
        button_edit_resolutions->setObjectName(QStringLiteral("button_edit_resolutions"));

        horizontalLayout_4->addWidget(button_edit_resolutions);

        button_remove_resolutions = new QPushButton(Resolutions);
        button_remove_resolutions->setObjectName(QStringLiteral("button_remove_resolutions"));

        horizontalLayout_4->addWidget(button_remove_resolutions);


        verticalLayout_3->addLayout(horizontalLayout_4);

        tabWidget->addTab(Resolutions, QString());
        general = new QWidget();
        general->setObjectName(QStringLiteral("general"));
        formLayout_2 = new QFormLayout(general);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label_7 = new QLabel(general);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        line_plugin_path = new QLineEdit(general);
        line_plugin_path->setObjectName(QStringLiteral("line_plugin_path"));

        horizontalLayout_6->addWidget(line_plugin_path);

        select_plugins_dir = new QToolButton(general);
        select_plugins_dir->setObjectName(QStringLiteral("select_plugins_dir"));

        horizontalLayout_6->addWidget(select_plugins_dir);


        formLayout_2->setLayout(0, QFormLayout::FieldRole, horizontalLayout_6);

        label_9 = new QLabel(general);
        label_9->setObjectName(QStringLiteral("label_9"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        line_screen_shot_path = new QLineEdit(general);
        line_screen_shot_path->setObjectName(QStringLiteral("line_screen_shot_path"));

        horizontalLayout_10->addWidget(line_screen_shot_path);

        select_screenshot_dir = new QToolButton(general);
        select_screenshot_dir->setObjectName(QStringLiteral("select_screenshot_dir"));

        horizontalLayout_10->addWidget(select_screenshot_dir);


        formLayout_2->setLayout(1, QFormLayout::FieldRole, horizontalLayout_10);

        tabWidget->addTab(general, QString());

        horizontalLayout_5->addWidget(tabWidget);


        retranslateUi(Config);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(Config);
    } // setupUi

    void retranslateUi(QWidget *Config)
    {
        Config->setWindowTitle(QApplication::translate("Config", "MediaQuickSync - Configuration", 0));
        button_add_channel->setText(QApplication::translate("Config", "Add", 0));
        button_edit_channel->setText(QApplication::translate("Config", "Edit", 0));
        button_remove_channel->setText(QApplication::translate("Config", "Remove", 0));
        label_2->setText(QString());
        label->setText(QApplication::translate("Config", "<html><head/><body><p>If you have a membership with <a href=\"http://www.own3d.tv\"><span style=\" text-decoration: underline; color:#0000ff;\">own3d.tv</span></a>, <a href=\"http://www.ustream.tv\"><span style=\" text-decoration: underline; color:#0000ff;\">ustream.tv</span></a>, <a href=\"http://www.justin.tv\"><span style=\" text-decoration: underline; color:#0000ff;\">justin.tv</span></a>,<a href=\"http://www.twitch.tv\"><span style=\" text-decoration: underline; color:#0000ff;\">twitch.tv </span></a>or another <br/>online service, you can add one or more channels for each service which supports open streaming<br/>via <a href=\"http://ru.wikipedia.org/wiki/RTMP\"><span style=\" text-decoration: underline; color:#0000ff;\">RTMP</span></a> or <a href=\"http://en.wikipedia.org/wiki/Real_Time_Messaging_Protocol\"><span style=\" text-decoration: underline; color:#0000ff;\">RTMPT</span></a>. Also local recordings, p2p broadcasts(as plugin) and third party plugin<br/>extensions can be added\\edited here. <a href="
                        "\"http://en.wikipedia.org/wiki/Streaming_media\"><span style=\" font-weight:600; text-decoration: underline; color:#0000ff;\">Click here to learn more...</span></a></p></body></html>", 0));
        tabWidget->setTabText(tabWidget->indexOf(channels), QApplication::translate("Config", "Channels", 0));
        button_add_encoder->setText(QApplication::translate("Config", "Add", 0));
        button_edit_encoder->setText(QApplication::translate("Config", "Edit", 0));
        button_remove_encoder->setText(QApplication::translate("Config", "Remove", 0));
        label_logo_img->setText(QString());
        label_4->setText(QString());
        label_3->setText(QApplication::translate("Config", "<html><head/><body><p>There is a complex balance between the <a href=\"http://en.wikipedia.org/wiki/Video_codec\"><span style=\" text-decoration: underline; color:#0000ff;\">video quality</span></a>, <a href=\"http://en.wikipedia.org/wiki/Bit_rate\"><span style=\" text-decoration: underline; color:#0000ff;\">bit rate</span></a>, the complexity of the encoding <br/>algorithms, robustness to data losses and errors, end-to-end delay, and a number of other factors.<br/>You can add one or more configurations for suported encoders and switch quickly <br/>between them in your broadcasts. <a href=\"http://en.wikipedia.org/wiki/Encoder\"><span style=\" font-weight:600; text-decoration: underline; color:#0000ff;\">Click here to learn more...</span></a></p></body></html>", 0));
        tabWidget->setTabText(tabWidget->indexOf(encoders), QApplication::translate("Config", "Encoders", 0));
        label_6->setText(QString());
        label_5->setText(QApplication::translate("Config", "<html><head/><body><p>The <span style=\" font-weight:600;\">display resolution</span> is the number of distinct <a href=\"http://en.wikipedia.org/wiki/Pixel\"><span style=\" text-decoration: underline; color:#0000ff;\">pixels</span></a> in each dimension that can be displayed.<br/>It is quoted as <span style=\" font-weight:600;\">width \303\227 height</span>, with the units in pixels.<br/>Select the <a href=\"http://en.wikipedia.org/wiki/Display_resolution\"><span style=\" text-decoration: underline; color:#0000ff;\">resolutions</span></a> you want to appear on the Broadcaster's View =&gt; Resolution menu.</p></body></html>", 0));
        button_sellectall_resolutions->setText(QApplication::translate("Config", "Sellect All", 0));
        button_clearall_resolutions->setText(QApplication::translate("Config", "Clear All", 0));
        button_loaddefaults_resolutions->setText(QApplication::translate("Config", "Load Defaults", 0));
        button_add_resolutions->setText(QApplication::translate("Config", "Add", 0));
        button_edit_resolutions->setText(QApplication::translate("Config", "Edit", 0));
        button_remove_resolutions->setText(QApplication::translate("Config", "Remove", 0));
        tabWidget->setTabText(tabWidget->indexOf(Resolutions), QApplication::translate("Config", "Resolutions", 0));
        label_7->setText(QApplication::translate("Config", "Plugins path:", 0));
        line_plugin_path->setText(QApplication::translate("Config", "./plugins", 0));
        select_plugins_dir->setText(QApplication::translate("Config", "...", 0));
        label_9->setText(QApplication::translate("Config", "Screen shot path:", 0));
        select_screenshot_dir->setText(QApplication::translate("Config", "...", 0));
        tabWidget->setTabText(tabWidget->indexOf(general), QApplication::translate("Config", "General", 0));
    } // retranslateUi

};

namespace Ui {
    class Config: public Ui_Config {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MQS_CONFIGURATION_H
