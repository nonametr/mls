#include "gui_channel.h"
/*
#include "ichannel.h"
#include "settings.h"
#include "json.h"
#include "iencoder.h"
#include <Qt>

MqsChannel::MqsChannel(QWidget *parent, Qt::WindowFlags flags)
	: QWidget(parent, flags), user_channel_name(NULL), combo_encoders(NULL)
{
	ui.setupUi(this);

	connect(this, SIGNAL(updateChannelListView()), parent, SLOT(updateChannels()));
	connect(ui.button_ok, SIGNAL(clicked()), this, SLOT(okClicked()));
	connect(ui.button_cancel, SIGNAL(clicked()), this, SLOT(cancelClicked()));	
}

MqsChannel::~MqsChannel(void)
{
}

QLineEdit *MqsChannel::createInputField(string field_name)
{
    QHBoxLayout *hbox = new QHBoxLayout();
	QLabel *label = new QLabel(field_name.c_str(), this);
	QLineEdit *line_edit = new QLineEdit("", this);
	hbox->addWidget(label, 3);
	hbox->addWidget(line_edit, 7);
	ui.HLayout_cfg_fields->addItem(hbox);
	return line_edit;
}

bool MqsChannel::setPluginName(string channel_plugin_name)
{
	channel_plugin = channel_plugin_name;
	IChannel *channel = IChannel::create(channel_plugin_name);
	if(channel == NULL)
		return false;
	vector<string> cfg_fields  = channel->getConfigFields();

	fields["Name:"] = createInputField("Name:");//first field always channel identification
	fields["Description:"] = createInputField("Description:");//first field always channel identification
	for(unsigned int i = 0; i < cfg_fields.size(); ++i)
	{
		fields[cfg_fields[i]] = createInputField(cfg_fields[i]);
	}

	QHBoxLayout *hbox = new QHBoxLayout();
	QLabel *label = new QLabel("Encoder:", this);
	combo_encoders = new QComboBox(this);

	QSqlQuery encoder_result = settings->query("SELECT name, video_encoder_plugin FROM encoder");
	do
	{
		QSqlRecord encoder = encoder_result.record();
        if(!encoder.count())
            continue;
		EncoderPlugin * encoder_plugin = EncoderManager::getEncoderPlugin(encoder.value("video_encoder_plugin").toString().toStdString());
        QString ico_path = encoder_plugin->getIcoPath();
        combo_encoders->addItem(QIcon(ico_path), encoder.value("name").toString());
	}while(encoder_result.next());
	hbox->addWidget(label, 3);
	hbox->addWidget(combo_encoders, 7);
	ui.HLayout_cfg_fields->addItem(hbox);

	ui.HLayout_cfg_fields->addItem(new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding ));
	return true;
}

bool MqsChannel::load(string user_defined_channel_name)
{
    old_name = user_defined_channel_name;
	QSqlRecord channel = settings->query("SELECT description, settings, channel_plugin, encoder FROM channel WHERE name = '%s'", user_defined_channel_name.c_str()).record();
	
	setPluginName(channel.value("channel_plugin").toString().toStdString());
	combo_encoders->setCurrentIndex(combo_encoders->findText(channel.value("encoder").toString()));
	fields["Description:"]->setText(channel.value("description").toString());
	fields.find("Name:")->second->setText(user_defined_channel_name.c_str());
	JSONObject channel_settings = JSON::parse(channel.value("settings").toString().toStdString().c_str())->asObject();
	for(map<string, QLineEdit*>::iterator it = fields.begin();it != fields.end(); ++it)
	{
		JSONObject::iterator it_value = channel_settings.find(it->first);
		if(it_value == channel_settings.end())
			continue;
		it->second->setText(it_value->second->getString().c_str());
    }
	return true;
}

void MqsChannel::cancelClicked()
{
	this->close();
}

void MqsChannel::okClicked()
{
	JSONObject settings_field;
	for(map<string, QLineEdit*>::iterator it = fields.begin();it != fields.end(); ++it)
	{
		if(it->first == "Name:" || it->first == "Description:")
			continue;
		settings_field[it->first] = new JSONValue(it->second->text().toStdString());
	}
	if(!old_name.empty())
		settings->query("DELETE FROM channel WHERE name = '%s'", old_name.c_str());
	QSqlQuery update_channel = settings->prepareQuery("INSERT INTO channel VALUES(:name, :description, :settings, :channel_plugin, :encoder)");
	update_channel.bindValue(":name", 			fields["Name:"]->text());
	update_channel.bindValue(":description", 	fields["Description:"]->text());
	update_channel.bindValue(":settings", 		JSONValue(settings_field).stringify().c_str());
	update_channel.bindValue(":channel_plugin", channel_plugin.c_str());
	update_channel.bindValue(":encoder", 		combo_encoders->currentText());
	if(!update_channel.exec())
		traceerr("SQL error = %s, sql = %s", update_channel.lastError().text().toStdString().c_str(), update_channel.lastQuery().toStdString().c_str());

	emit updateChannelListView();
	this->close();
}
*/
