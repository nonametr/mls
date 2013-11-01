#ifndef MLS_LOGIN_H
#define MLS_LOGIN_H

#include <qwidget.h>
#include "ui_mqs_login.h"

class MqsLogin : public QWidget
{
	Q_OBJECT
public:
	MqsLogin(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	virtual ~MqsLogin(void);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
private:
	QPoint offset;
	Ui::MqsLogin ui;
public slots:
	void clickRecoverPassword(const QString& link);
	void clickRegisterAccount(const QString& link);
	void clickLogin();
};

#endif
