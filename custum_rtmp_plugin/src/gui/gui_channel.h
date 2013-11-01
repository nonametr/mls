#ifndef MLS_CHANNEL_H
#define MLS_CHANNEL_H

#include <qwidget.h>
#include <QLineEdit>
#include <QComboBox>
#include <vector>

#include "../../ui_custom_rtmp_channel.h"

using namespace std;

class CustomRTMPConfig : public QDialog
{
	Q_OBJECT
public:
    CustomRTMPConfig(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    virtual ~CustomRTMPConfig(void);
    void edit(string channel_name);
    void remove(string channel_name);
    void create();
private:
    void updateEncoders();
    bool load(string channel_name);
    Ui::CustomRtmpChannel ui;

	map<string, QLineEdit*> fields;

	string old_name;
	string channel_plugin;
public slots:
	void okClicked();
	void cancelClicked();
signals:
	void updateChannelListView();
};

#endif
