#ifndef MLS_CONFIG_H
#define MLS_CONFIG_H

#include <qwidget.h>
#include <qmenu.h>
#include <map>
#include <string.h>

#include "ui_mqs_configuration.h"
#include "global.h"

using namespace std;

class MqsConfig : public QWidget
{
	Q_OBJECT
public:

	MqsConfig(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	virtual ~MqsConfig(void);

    void activateTab(unsigned int tab_id){ ui.tabWidget->setCurrentIndex(tab_id); }
private:
	QMenu add_channel_menu;
	Ui::Config ui;
public slots:
	void onResolutionItemChanged(QListWidgetItem *item);
	void onClearAllResolutions();
	void onSellectAllResolutions();
	void onLoadDefaultResolutions();
	void onAddResolutions();
	void onRemoveResolutions();
	void onEditResolutions();

	void updateResolutions();
	void updateChannels();
	void updateEncoders();

	void onAddChannel();
	void onEditChannel();
	void onRemoveChannel();
	void onCreateChannel();

	void onAddEncoder();
	void onEditEncoder();
	void onRemoveEncoder();

	void onSelectPluginPath();
	void onSelectScreenShotPath();
	void onEditPluginPath(const QString &new_text);
	void onEditScreenShotPath(const QString &new_text);

	void onEncoderSelect(const QString &);
signals:
    void updateMain(GUIUpdate);
};

#endif
