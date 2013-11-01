#ifndef MEDIAQUICKSYNC_UPDATER_H
#define MEDIAQUICKSYNC_UPDATER_H

#include <qwidget.h>
#include "ui_mqs_update.h"
#include <qthread.h>

class MqsUpdater : public QWidget
{
	Q_OBJECT
public:
	MqsUpdater(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	virtual ~MqsUpdater(void);
	void check();
private:
	void onTimer();
	bool isLatest();
	void update();
	void restart();
	int getLatestVersion();
	int getCurrentVersion();

	Ui::MqsUpdater ui;
	QWidget *owner;
};

#endif // MEDIAQUICKSYNC_H
