#ifndef MLS_CHANNEL_H
#define MLS_CHANNEL_H
/*
#include <qwidget.h>
#include <QLineEdit>
#include <QComboBox>
#include "ui_mqs_transport.h"
#include <vector>

using namespace std;

class MqsChannel : public QWidget
{
	Q_OBJECT
public:
	MqsChannel(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	virtual ~MqsChannel(void);
	bool setPluginName(string v_channel_type);
	bool load(string global_channel_name);
private:
	Ui::MqsChannel ui;

	map<string, QLineEdit*> fields;
	QComboBox *combo_encoders;

	string old_name;
	QLineEdit *user_channel_name;
	string channel_plugin;

	QLineEdit *createInputField(string field_name);
public slots:
	void okClicked();
	void cancelClicked();
signals:
	void updateChannelListView();
};
*/
#endif
