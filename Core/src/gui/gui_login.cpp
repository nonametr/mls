#include <QMessageBox>
#include <windows.h>
#include <qevent.h>
#include <QDesktopServices>
#include <qurl.h>
#include <QtNetwork\qlocalsocket.h>
#include "gui_updater.h"
#include "gui_login.h"
#include "gui_main.h"

MqsLogin::MqsLogin(QWidget *parent, Qt::WindowFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
	ui.password_text->setEchoMode(QLineEdit::Password);

	QObject::connect(ui.RecoverPassword, SIGNAL(linkActivated(const QString&)),
                      this, SLOT(clickRecoverPassword(const QString&)));
	QObject::connect(ui.RegisterAccount, SIGNAL(linkActivated(const QString&)),
                      this, SLOT(clickRegisterAccount(const QString&)));
	QObject::connect(ui.login_button, SIGNAL(pressed()),
						this, SLOT(clickLogin()));

	//version check
	MqsUpdater *upd = new MqsUpdater(this);
	upd->check();
	delete upd;
}

void MqsLogin::mousePressEvent(QMouseEvent* event)
{
    event->accept(); // do not propagate
    if (isWindow())
        offset = event->globalPos() - pos();
    else
        offset = event->pos();
}
void MqsLogin::mouseReleaseEvent(QMouseEvent* event)
{
    event->accept(); // do not propagate
    offset = QPoint();
}
void MqsLogin::mouseMoveEvent(QMouseEvent* event)
{
    event->accept(); // do not propagate
    if (isWindow())
        move(event->globalPos() - offset);
    else
        move(mapToParent(event->pos() - offset));
}

MqsLogin::~MqsLogin(void)
{
}

void MqsLogin::clickRecoverPassword(const QString& link)
{
	QDesktopServices::openUrl(QUrl("http://www.mediaquicksync.com/recover_password.php", QUrl::TolerantMode));
}
void MqsLogin::clickRegisterAccount(const QString& link)
{
	QDesktopServices::openUrl(QUrl("http://www.mediaquicksync.com/register.php", QUrl::TolerantMode));
}
void MqsLogin::clickLogin()
{
	MlsMain *w = new MlsMain;
	w->setWindowFlags(Qt::FramelessWindowHint);
	//w->setAttribute(Qt::WA_TranslucentBackground);
	//w->setAttribute(Qt::WA_NoSystemBackground);

	w->show();
	this->close();
}
