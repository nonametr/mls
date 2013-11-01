#ifndef MLS_ENCODER_H
#define MLS_ENCODER_H

#include <qwidget.h>
#include "ui_mqs_encoder.h"
#include "global.h"
#include <string>

using namespace std;

class MqsEncoder : public QWidget
{
	Q_OBJECT
public:
	MqsEncoder(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	virtual ~MqsEncoder(void);
	void init(string global_encoder_name);
private:
	void setCombo(QComboBox *combo, QString value);
	Ui::MqsEncoder ui;
	string old_name;
public slots:
	void okClicked();
	void cancelClicked();
signals:
	void updateEncodersListView();
};

#endif
