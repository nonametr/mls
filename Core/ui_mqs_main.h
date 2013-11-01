/********************************************************************************
** Form generated from reading UI file 'mqs_main.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MQS_MAIN_H
#define UI_MQS_MAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MediaQuickSyncClass
{
public:
    QAction *actionAbout;
    QAction *actionCheck_for_updates;
    QAction *actionNews;
    QAction *actionRead_forum;
    QAction *actionForum;
    QAction *actionTwiter;
    QAction *actionAdd_delay;
    QAction *actionMy_recordings;
    QAction *actionExit;
    QAction *actionAdd_Camera;
    QAction *actionAdd_media_file;
    QAction *actionAdd_screen_region;
    QAction *actionAdd_game;
    QAction *actionLoad_configuration;
    QAction *actionSave_configuration;
    QAction *actionNew_configuration;
    QAction *actionTranslations;
    QAction *actionAdd;
    QAction *actionEdit_encoder;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *File;
    QPushButton *View;
    QPushButton *Broadcast;
    QPushButton *Tools;
    QPushButton *Help;
    QSpacerItem *horizontalSpacer_2;
    QLabel *render_space;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label_6;
    QListWidget *list_sources;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_3;
    QListWidget *list_scenes;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *exit_button;
    QLabel *label;

    void setupUi(QMainWindow *MediaQuickSyncClass)
    {
        if (MediaQuickSyncClass->objectName().isEmpty())
            MediaQuickSyncClass->setObjectName(QStringLiteral("MediaQuickSyncClass"));
        MediaQuickSyncClass->resize(969, 665);
        QIcon icon;
        icon.addFile(QStringLiteral(":/MediaQuickSync/resources/GoContactSyncLogo.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MediaQuickSyncClass->setWindowIcon(icon);
        MediaQuickSyncClass->setStyleSheet(QLatin1String("QMainWindow{\n"
"background: black;\n"
"}"));
        MediaQuickSyncClass->setAnimated(true);
        MediaQuickSyncClass->setDocumentMode(false);
        actionAbout = new QAction(MediaQuickSyncClass);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionCheck_for_updates = new QAction(MediaQuickSyncClass);
        actionCheck_for_updates->setObjectName(QStringLiteral("actionCheck_for_updates"));
        actionNews = new QAction(MediaQuickSyncClass);
        actionNews->setObjectName(QStringLiteral("actionNews"));
        actionRead_forum = new QAction(MediaQuickSyncClass);
        actionRead_forum->setObjectName(QStringLiteral("actionRead_forum"));
        actionForum = new QAction(MediaQuickSyncClass);
        actionForum->setObjectName(QStringLiteral("actionForum"));
        actionTwiter = new QAction(MediaQuickSyncClass);
        actionTwiter->setObjectName(QStringLiteral("actionTwiter"));
        actionAdd_delay = new QAction(MediaQuickSyncClass);
        actionAdd_delay->setObjectName(QStringLiteral("actionAdd_delay"));
        actionMy_recordings = new QAction(MediaQuickSyncClass);
        actionMy_recordings->setObjectName(QStringLiteral("actionMy_recordings"));
        actionExit = new QAction(MediaQuickSyncClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionAdd_Camera = new QAction(MediaQuickSyncClass);
        actionAdd_Camera->setObjectName(QStringLiteral("actionAdd_Camera"));
        actionAdd_media_file = new QAction(MediaQuickSyncClass);
        actionAdd_media_file->setObjectName(QStringLiteral("actionAdd_media_file"));
        actionAdd_screen_region = new QAction(MediaQuickSyncClass);
        actionAdd_screen_region->setObjectName(QStringLiteral("actionAdd_screen_region"));
        actionAdd_game = new QAction(MediaQuickSyncClass);
        actionAdd_game->setObjectName(QStringLiteral("actionAdd_game"));
        actionLoad_configuration = new QAction(MediaQuickSyncClass);
        actionLoad_configuration->setObjectName(QStringLiteral("actionLoad_configuration"));
        actionSave_configuration = new QAction(MediaQuickSyncClass);
        actionSave_configuration->setObjectName(QStringLiteral("actionSave_configuration"));
        actionNew_configuration = new QAction(MediaQuickSyncClass);
        actionNew_configuration->setObjectName(QStringLiteral("actionNew_configuration"));
        actionTranslations = new QAction(MediaQuickSyncClass);
        actionTranslations->setObjectName(QStringLiteral("actionTranslations"));
        actionAdd = new QAction(MediaQuickSyncClass);
        actionAdd->setObjectName(QStringLiteral("actionAdd"));
        actionEdit_encoder = new QAction(MediaQuickSyncClass);
        actionEdit_encoder->setObjectName(QStringLiteral("actionEdit_encoder"));
        centralWidget = new QWidget(MediaQuickSyncClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setLayoutDirection(Qt::LeftToRight);
        centralWidget->setAutoFillBackground(false);
        centralWidget->setStyleSheet(QLatin1String("QWidget {\n"
"background: #222222;\n"
"border: 2px solid #222222;\n"
"border-radius: 20px;\n"
"}\n"
"QPushButton{\n"
"background-color: rgba( 255, 255, 255, 0% );\n"
"color: white;\n"
"}\n"
"QPushButton:hover{\n"
"background-color: rgb(53, 120, 191, 150);;\n"
"}\n"
"QListWidget{\n"
"font-size: 14px;\n"
"background: rgb(240, 240, 250);\n"
"border: 8px solid #222222;\n"
"border-radius: 20px;\n"
"}\n"
"QListWidget::item:selected{\n"
"background-color: transparent;\n"
"border: 0px;\n"
"}\n"
"QLabel{\n"
"color: white;\n"
"}\n"
"QMenuBar{\n"
"background: black;\n"
"color: white;\n"
"border-radius: 10px;\n"
"border: 10px solid black;\n"
"}\n"
"QMenu {\n"
"border: 1px solid gray;\n"
"border-radius: 10px;\n"
"background: #bbbbbb;\n"
"}\n"
"\n"
"QMenu::item {\n"
"padding: 2px 20px 2px 20px;\n"
"border: 1px solid transparent; \n"
"spacing: 20px;\n"
"}\n"
"\n"
"\n"
"QMenu::item:selected {\n"
"border-color: darkblue;\n"
"background: rgb(53, 120, 191, 150);\n"
"color:white;\n"
"}\n"
"\n"
"QMenu::separator {\n"
"height: 2px;"
                        "\n"
"margin: 2px 5px 2px 4px;\n"
"}\n"
"\n"
"QMenu::indicator {\n"
"width: 20px;\n"
"height: 13px;\n"
"}"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 4, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_5->setContentsMargins(0, -1, -1, -1);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_3->setContentsMargins(-1, 10, -1, -1);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(20);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(10, -1, -1, -1);
        File = new QPushButton(centralWidget);
        File->setObjectName(QStringLiteral("File"));
        QFont font;
        font.setPointSize(10);
        font.setBold(false);
        font.setWeight(50);
        File->setFont(font);
        File->setStyleSheet(QStringLiteral(""));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/MediaQuickSync/resources/MediaQuickSync.ico"), QSize(), QIcon::Normal, QIcon::Off);
        File->setIcon(icon1);

        horizontalLayout->addWidget(File);

        View = new QPushButton(centralWidget);
        View->setObjectName(QStringLiteral("View"));
        QFont font1;
        font1.setPointSize(10);
        View->setFont(font1);

        horizontalLayout->addWidget(View);

        Broadcast = new QPushButton(centralWidget);
        Broadcast->setObjectName(QStringLiteral("Broadcast"));
        Broadcast->setFont(font1);
        Broadcast->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(Broadcast);

        Tools = new QPushButton(centralWidget);
        Tools->setObjectName(QStringLiteral("Tools"));
        Tools->setFont(font1);
        Tools->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(Tools);

        Help = new QPushButton(centralWidget);
        Help->setObjectName(QStringLiteral("Help"));
        Help->setFont(font1);
        Help->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(Help);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout);

        render_space = new QLabel(centralWidget);
        render_space->setObjectName(QStringLiteral("render_space"));

        verticalLayout_3->addWidget(render_space);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        horizontalLayout_18->setContentsMargins(0, -1, -1, -1);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setStyleSheet(QStringLiteral(""));

        horizontalLayout_18->addWidget(label_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_18->addWidget(label_6);


        verticalLayout_5->addLayout(horizontalLayout_18);

        list_sources = new QListWidget(centralWidget);
        list_sources->setObjectName(QStringLiteral("list_sources"));
        list_sources->setMinimumSize(QSize(0, 120));
        list_sources->setStyleSheet(QStringLiteral("background: rgb(150, 150, 150);"));

        verticalLayout_5->addWidget(list_sources);


        horizontalLayout_7->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        horizontalLayout_14->setContentsMargins(0, -1, -1, -1);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setStyleSheet(QStringLiteral(""));

        horizontalLayout_14->addWidget(label_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_3);


        verticalLayout_6->addLayout(horizontalLayout_14);

        list_scenes = new QListWidget(centralWidget);
        list_scenes->setObjectName(QStringLiteral("list_scenes"));
        list_scenes->setMinimumSize(QSize(0, 120));
        list_scenes->setStyleSheet(QStringLiteral("background: rgb(150, 150, 150);"));

        verticalLayout_6->addWidget(list_scenes);


        horizontalLayout_7->addLayout(verticalLayout_6);

        horizontalLayout_7->setStretch(0, 8);
        horizontalLayout_7->setStretch(1, 4);

        verticalLayout_3->addLayout(horizontalLayout_7);

        verticalLayout_3->setStretch(1, 100);
        verticalLayout_3->setStretch(2, 1);

        horizontalLayout_5->addLayout(verticalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(0, 4, 4, 5);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        exit_button = new QPushButton(centralWidget);
        exit_button->setObjectName(QStringLiteral("exit_button"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/MediaQuickSync/resources/power_off_black.png"), QSize(), QIcon::Normal, QIcon::Off);
        exit_button->setIcon(icon2);
        exit_button->setIconSize(QSize(32, 32));

        horizontalLayout_2->addWidget(exit_button);


        verticalLayout->addLayout(horizontalLayout_2);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QStringLiteral("background: rgb(150, 150, 150);"));
        label->setFrameShape(QFrame::NoFrame);
        label->setPixmap(QPixmap(QString::fromUtf8(":/MediaQuickSync/resources/mqs.png")));
        label->setScaledContents(false);
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout->addWidget(label);

        verticalLayout->setStretch(1, 10);

        horizontalLayout_5->addLayout(verticalLayout);

        horizontalLayout_5->setStretch(0, 100);
        horizontalLayout_5->setStretch(1, 1);

        gridLayout->addLayout(horizontalLayout_5, 0, 0, 1, 1);

        MediaQuickSyncClass->setCentralWidget(centralWidget);

        retranslateUi(MediaQuickSyncClass);
        QObject::connect(exit_button, SIGNAL(clicked()), MediaQuickSyncClass, SLOT(close()));

        QMetaObject::connectSlotsByName(MediaQuickSyncClass);
    } // setupUi

    void retranslateUi(QMainWindow *MediaQuickSyncClass)
    {
        MediaQuickSyncClass->setWindowTitle(QApplication::translate("MediaQuickSyncClass", "MediaQuickSync", 0));
        actionAbout->setText(QApplication::translate("MediaQuickSyncClass", "About", 0));
        actionCheck_for_updates->setText(QApplication::translate("MediaQuickSyncClass", "Check for updates...", 0));
        actionNews->setText(QApplication::translate("MediaQuickSyncClass", "Latest news...", 0));
        actionRead_forum->setText(QApplication::translate("MediaQuickSyncClass", "Contents", 0));
        actionForum->setText(QApplication::translate("MediaQuickSyncClass", "Forum...", 0));
        actionTwiter->setText(QApplication::translate("MediaQuickSyncClass", "Support", 0));
        actionAdd_delay->setText(QApplication::translate("MediaQuickSyncClass", "Activate delay...", 0));
        actionMy_recordings->setText(QApplication::translate("MediaQuickSyncClass", "My recordings...", 0));
        actionExit->setText(QApplication::translate("MediaQuickSyncClass", "Exit", 0));
        actionAdd_Camera->setText(QApplication::translate("MediaQuickSyncClass", "Add camera", 0));
        actionAdd_media_file->setText(QApplication::translate("MediaQuickSyncClass", "Add media file", 0));
        actionAdd_screen_region->setText(QApplication::translate("MediaQuickSyncClass", "Add screen region", 0));
        actionAdd_game->setText(QApplication::translate("MediaQuickSyncClass", "Add game", 0));
        actionLoad_configuration->setText(QApplication::translate("MediaQuickSyncClass", "Load", 0));
        actionSave_configuration->setText(QApplication::translate("MediaQuickSyncClass", "Save", 0));
        actionNew_configuration->setText(QApplication::translate("MediaQuickSyncClass", "New", 0));
        actionTranslations->setText(QApplication::translate("MediaQuickSyncClass", "Translations", 0));
        actionAdd->setText(QApplication::translate("MediaQuickSyncClass", "Edit...", 0));
        actionEdit_encoder->setText(QApplication::translate("MediaQuickSyncClass", "Edit...", 0));
        File->setText(QApplication::translate("MediaQuickSyncClass", " File", 0));
        View->setText(QApplication::translate("MediaQuickSyncClass", "View", 0));
        Broadcast->setText(QApplication::translate("MediaQuickSyncClass", "Broadcast", 0));
        Tools->setText(QApplication::translate("MediaQuickSyncClass", "Tools", 0));
        Help->setText(QApplication::translate("MediaQuickSyncClass", "About", 0));
        render_space->setText(QString());
        label_2->setText(QApplication::translate("MediaQuickSyncClass", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">Sources:</span></p></body></html>", 0));
        label_6->setText(QApplication::translate("MediaQuickSyncClass", "<html><head/><body><p><span style=\" font-size:10pt;\">HW acceleration: </span><span style=\" font-size:10pt; color:#d8a988;\">Intel Quick Sync</span></p></body></html>", 0));
        label_3->setText(QApplication::translate("MediaQuickSyncClass", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600;\">Scenes:</span></p></body></html>", 0));
        exit_button->setText(QString());
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MediaQuickSyncClass: public Ui_MediaQuickSyncClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MQS_MAIN_H
