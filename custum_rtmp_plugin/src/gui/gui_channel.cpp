#include "gui_channel.h"
#include "settings.h"
#include "json.h"
#include <qt>
#include "escape_call_client.h"
#include "channel_export.h"

CustomRTMPConfig::CustomRTMPConfig(QWidget *parent, Qt::WindowFlags flags)
    : QDialog(parent, flags)
{
    ui.setupUi(this);

    connect(ui.pushButton_ok, SIGNAL(clicked()), this, SLOT(okClicked()));
    connect(ui.pushButton_cancel, SIGNAL(clicked()), this, SLOT(cancelClicked()));
}

CustomRTMPConfig::~CustomRTMPConfig(void)
{
}

void CustomRTMPConfig::edit(string channel_name)
{
    this->load(channel_name);
    this->exec();
}

void CustomRTMPConfig::remove(string channel_name)
{
    settings->query("DELETE FROM custom_rtmp_channel WHERE name = '%s'", channel_name.c_str());
    this->close();
}

void CustomRTMPConfig::create()
{
    updateEncoders();
    this->exec();
}

void CustomRTMPConfig::updateEncoders()
{
    map<string, EscapeEncoder> encoders = getEncoders();
    for(map<string, EscapeEncoder>::iterator it = encoders.begin(); it != encoders.end(); ++it)
    {
        ui.comboBox_encoder->addItem(it->first.c_str());
    }
}

bool CustomRTMPConfig::load(string user_defined_channel_name)
{
    old_name = user_defined_channel_name;
    QSqlRecord channel = settings->query("SELECT name, description, rtmp_url, app_link, encoder FROM custom_rtmp_channel WHERE name = '%s'", user_defined_channel_name.c_str()).record();

    updateEncoders();

    ui.lineEdit_name->setText(user_defined_channel_name.c_str());
    ui.lineEdit_description->setText(channel.value("description").toString());
    ui.lineEdit_rtmp_url->setText(channel.value("rtmp_url").toString());
    ui.lineEdit_app_link->setText(channel.value("app_link").toString());

    int index = ui.comboBox_encoder->findText(channel.value("encoder").toString(), Qt::MatchExactly);
    ui.comboBox_encoder->setCurrentIndex((index > 0)?index:0);

	return true;
}

void CustomRTMPConfig::cancelClicked()
{
	this->close();
}

void CustomRTMPConfig::okClicked()
{
	if(!old_name.empty())
        settings->query("DELETE FROM custom_rtmp_channel WHERE name = '%s'", old_name.c_str());

    QSqlQuery update_channel = settings->prepareQuery("INSERT INTO custom_rtmp_channel VALUES(:name, :description, :rtmp_url, :app_link, :encoder)");
    update_channel.bindValue(":name", 			ui.lineEdit_name->text());
    update_channel.bindValue(":description", 	ui.lineEdit_description->text());
    update_channel.bindValue(":rtmp_url", 		ui.lineEdit_rtmp_url->text());
    update_channel.bindValue(":app_link",       ui.lineEdit_app_link->text());
    update_channel.bindValue(":encoder", 		ui.comboBox_encoder->currentText());

	if(!update_channel.exec())
		traceerr("SQL error = %s, sql = %s", update_channel.lastError().text().toStdString().c_str(), update_channel.lastQuery().toStdString().c_str());

    updateChannels(ui.lineEdit_name->text().toStdString(), PLUGIN_NAME, ui.comboBox_encoder->currentText().toStdString());
    this->close();
}
