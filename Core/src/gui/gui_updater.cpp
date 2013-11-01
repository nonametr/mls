#include <QMessageBox>
#include <qtimer.h>
#include <windows.h>
#include "gui_updater.h"

bool MqsUpdater::isLatest()
{
	return false;
}
MqsUpdater::MqsUpdater(QWidget *parent, Qt::WindowFlags flags) : owner(parent)
{
	ui.setupUi(this);
}
MqsUpdater::~MqsUpdater(void)
{
}
void MqsUpdater::check()
{
	int q_res;
	if(isLatest() == false)
		q_res = QMessageBox::question(owner, "MediaQuickSync is out of date!", "\r\n<h3>Download latest version?</h3>", QMessageBox::Yes | QMessageBox::No);
	if(q_res == QMessageBox::Yes)
	{
		this->update();
	}
}
void MqsUpdater::update()
{
	this->show();
	int val = ui.progressBar->value();
	while(val < 100)
	{
		++val;
		ui.progressBar->setValue(val);
		QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);
	}
	restart();
}
void MqsUpdater::restart()
{
	this->close();
}

