#include "gui_config.h"
#include "gui_channel.h"
#include "gui_encoder.h"
#include "ichannel.h"
#include <QMessageBox>
#include <QList>
#include <qfiledialog.h>
#include "settings.h"

MqsConfig::MqsConfig(QWidget *parent, Qt::WindowFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);

	updateEncoders();
	updateChannels();
	updateResolutions();
    vector<string> suported_channels = ChannelManager::getSuportedPlugins();
	for(unsigned int i = 0; i < suported_channels.size(); ++i)
	{
		QAction* act = new QAction(suported_channels[i].c_str(), 0);
		add_channel_menu.addAction(act);
		connect(act, SIGNAL(triggered()), this, SLOT(onCreateChannel()));
	}

    QSqlRecord plugin_path_rec = settings->query("SELECT value as plugin_path FROM property WHERE name = 'plugin_path'").record();
    QSqlRecord screen_shot_path_rec = settings->query("SELECT value as screen_shot_path FROM property WHERE name = 'screen_shot_path'").record();
    ui.line_plugin_path->setText(plugin_path_rec.value("plugin_path").toString());
    ui.line_screen_shot_path->setText(screen_shot_path_rec.value("screen_shot_path").toString());

    QObject::connect(this, SIGNAL(updateMain(GUIUpdate)), parent, SLOT(updateMain(GUIUpdate)));

	QObject::connect(ui.button_add_channel, SIGNAL(clicked()), this, SLOT(onAddChannel()));
	QObject::connect(ui.button_edit_channel, SIGNAL(clicked()), this, SLOT(onEditChannel()));
	QObject::connect(ui.button_remove_channel, SIGNAL(clicked()), this, SLOT(onRemoveChannel()));

	QObject::connect(ui.button_add_encoder, SIGNAL(clicked()), this, SLOT(onAddEncoder()));
	QObject::connect(ui.button_edit_encoder, SIGNAL(clicked()), this, SLOT(onEditEncoder()));
	QObject::connect(ui.button_remove_encoder, SIGNAL(clicked()), this, SLOT(onRemoveEncoder()));

	QObject::connect(ui.list_resolutions, SIGNAL(itemChanged(QListWidgetItem *)), this, SLOT(onResolutionItemChanged(QListWidgetItem *)));
	QObject::connect(ui.button_clearall_resolutions, SIGNAL(clicked()), this, SLOT(onClearAllResolutions()));
	QObject::connect(ui.button_sellectall_resolutions, SIGNAL(clicked()), this, SLOT(onSellectAllResolutions()));
	QObject::connect(ui.button_loaddefaults_resolutions, SIGNAL(clicked()), this, SLOT(onLoadDefaultResolutions()));
	QObject::connect(ui.button_add_resolutions, SIGNAL(clicked()), this, SLOT(onAddResolutions()));
	QObject::connect(ui.button_remove_resolutions, SIGNAL(clicked()), this, SLOT(onRemoveResolutions()));
	QObject::connect(ui.button_edit_resolutions, SIGNAL(clicked()), this, SLOT(onEditResolutions()));
	QObject::connect(ui.line_screen_shot_path, SIGNAL(textChanged(const QString &)), this, SLOT(onEditScreenShotPath(const QString &)));
	QObject::connect(ui.line_plugin_path, SIGNAL(textChanged(const QString &)), this, SLOT(onEditPluginPath(const QString &)));
	QObject::connect(ui.select_plugins_dir, SIGNAL(clicked()), this, SLOT(onSelectPluginPath()));
	QObject::connect(ui.select_screenshot_dir, SIGNAL(clicked()), this, SLOT(onSelectScreenShotPath()));

	QObject::connect(ui.list_encoders, SIGNAL(currentTextChanged(const QString &)), this, SLOT(onEncoderSelect(const QString &)));
}
MqsConfig::~MqsConfig(void)
{
}
void MqsConfig::onSelectPluginPath()
{
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
												 global.getVal("plugin_path").c_str(),
	                                             QFileDialog::ShowDirsOnly
	                                             | QFileDialog::DontResolveSymlinks);
	if(!dir.isEmpty())
		ui.line_plugin_path->setText(dir);
}
void MqsConfig::onSelectScreenShotPath()
{
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
												 global.getVal("screen_shot_path").c_str(),
	                                             QFileDialog::ShowDirsOnly
	                                             | QFileDialog::DontResolveSymlinks);
	if(!dir.isEmpty())
		ui.line_screen_shot_path->setText(dir);
}
void MqsConfig::onEditScreenShotPath(const QString &new_text)
{
	global.getConfig()["screen_shot_path"] = new_text.toStdString();
    settings->query("UPDATE property SET value = '%s' WHERE name = 'screen_shot_path'", new_text.toStdString().c_str());
}
void  MqsConfig::onEditPluginPath(const QString &new_text)
{
	global.getConfig()["plugin_path"] = new_text.toStdString();
    settings->query("UPDATE property SET value = '%s' WHERE name = 'plugin_path'", new_text.toStdString().c_str());
}
void MqsConfig::updateResolutions()
{
	ui.list_resolutions->clear();
	QSqlQuery result = settings->query(GET_RESOLUTION, GET_ALL);
	do
	{
		QSqlRecord resolution = result.record();

		QListWidgetItem *widgetitem_resolution = new QListWidgetItem(ui.list_resolutions);
		widgetitem_resolution->setText(resolution.value("name").toString());
		if(resolution.value("enabled").toBool())
			widgetitem_resolution->setCheckState(Qt::Checked);
		else
			widgetitem_resolution->setCheckState(Qt::Unchecked);
		ui.list_resolutions->addItem(widgetitem_resolution);
	}while(result.next());
    emit updateMain(GUIUpdate::RESOLUTIONS);
}
void MqsConfig::onResolutionItemChanged(QListWidgetItem *resolution_item)
{
	unsigned int enabled = resolution_item->checkState() == Qt::Unchecked ? 0:1;
	QSqlRecord current_resolution = settings->query("SELECT value FROM property WHERE name = 'resolution'").record();
	ASSERT_WITH_CODE(current_resolution.value("value").toString() != resolution_item->text(), "Error! This resolution currently in use! Can't disable it!",  resolution_item->setCheckState(Qt::Checked); return);

	settings->query("UPDATE resolution SET enabled = %u WHERE name = '%s'", enabled, resolution_item->text().toStdString().c_str());
    emit updateMain(GUIUpdate::RESOLUTIONS);
}
void MqsConfig::onClearAllResolutions()
{
	settings->query(DISABLE_ALL_RESOLUTIONS);
	updateResolutions();
}
void MqsConfig::onSellectAllResolutions()
{
	settings->query(ENABLE_ALL_RESOLUTIONS);
	updateResolutions();
}
void MqsConfig::onLoadDefaultResolutions()
{
	settings->query(RESET_TO_DEFULT_RESOLUTIONS);
	updateResolutions();
}
void MqsConfig::onAddResolutions()
{
}
void MqsConfig::onRemoveResolutions()
{

}
void MqsConfig::onEditResolutions()
{

}
void MqsConfig::onEncoderSelect(const QString & encoder)
{
	int encoder_type_size = encoder.toStdString().find(" - ") == string::npos ? encoder.length() : encoder.toStdString().find(" - ");
	string icon_name = "./resources/logo/" + string(encoder.toStdString().c_str(), encoder_type_size) + ".png";

	ui.label_logo_img->setPixmap(QPixmap(global.strSplit(encoder.toStdString(), " - ")[0].c_str()));
}
void MqsConfig::updateEncoders()
{
	ui.list_encoders->clear();
	QSqlQuery encoder_result = settings->query("SELECT name FROM encoder");
	do
	{
		QSqlRecord encoder = encoder_result.record();
		ui.list_encoders->addItem(new QListWidgetItem(QIcon(), encoder.value("name").toString()));
	}while(encoder_result.next());
    emit updateMain(GUIUpdate::BROADCASTS);
}
void MqsConfig::updateChannels()
{
	ui.list_channel->clear();
	QSqlQuery channel_result = settings->query("SELECT name FROM channel");
	do
	{
		QSqlRecord channel = channel_result.record();
		ui.list_channel->addItem(channel.value("name").toString());
	}while(channel_result.next());
    emit updateMain(GUIUpdate::BROADCASTS);
}
void MqsConfig::onAddChannel()
{
	add_channel_menu.exec(ui.button_add_channel->pos() + this->pos());
}
void MqsConfig::onRemoveChannel()
{
	string user_defined_channel_name;
	QList<QListWidgetItem*> selected_channels = ui.list_channel->selectedItems();
    if(!selected_channels.size())
        return;

	user_defined_channel_name = selected_channels.at(0)->text().toStdString();

	if(QMessageBox::question(this,"Confirmation","Are you really want to delete channel?",QMessageBox::Yes,QMessageBox::No) ==	QMessageBox::No)
		return;

	settings->query("DELETE FROM channel WHERE name = '%s'", user_defined_channel_name.c_str());
	updateChannels();
}
void MqsConfig::onCreateChannel()
{
	string channel_plugin_name = ((QAction*)sender())->text().toStdString();

    ChannelManager::create(channel_plugin_name, this);
    updateChannels();
}
void MqsConfig::onEditChannel()
{
	string user_defined_channel_name;
	QList<QListWidgetItem*> selected_channels = ui.list_channel->selectedItems();

    if(!selected_channels.size())
        return;

	user_defined_channel_name = selected_channels.at(0)->text().toStdString();

    ChannelManager::edit(user_defined_channel_name);
}
void MqsConfig::onAddEncoder()
{
	MqsEncoder *encoder_config = new MqsEncoder(this, Qt::Dialog);
	encoder_config->setAttribute(Qt::WA_DeleteOnClose, true);
	encoder_config->show();
}
void MqsConfig::onEditEncoder()
{
	string global_encoder_name;
	QList<QListWidgetItem*> selected_encoders = ui.list_encoders->selectedItems();

    if(!selected_encoders.size())
        return;

    global_encoder_name = selected_encoders.at(0)->text().toStdString();

    MqsEncoder *encoder_config = new MqsEncoder(this, Qt::Dialog);
	encoder_config->setAttribute(Qt::WA_DeleteOnClose, true);
	encoder_config->init(global_encoder_name);
    encoder_config->show();
}
void MqsConfig::onRemoveEncoder()
{
	string user_defined_encoder_name;
	QList<QListWidgetItem*> selected_encoders = ui.list_encoders->selectedItems();
	user_defined_encoder_name = selected_encoders.at(0)->text().toStdString();

	if(user_defined_encoder_name.empty())
		return;

	if(QMessageBox::question(this,"Confirmation","Are you really want to delete channel?",QMessageBox::Yes,QMessageBox::No) ==	QMessageBox::No)
		return;

	QString affected_channels("");
	QSqlQuery affected_channels_result = settings->query("SELECT name FROM channel WHERE encoder='%s'", user_defined_encoder_name.c_str());
	do
	{
		QSqlRecord affected_channel = affected_channels_result.record();
		affected_channels += affected_channel.value("name").toString();
	}while(affected_channels_result.next());
	if(!affected_channels.isEmpty())
	{
		QString question("Next linked channels: " + affected_channels + " will be deleted too. Continue?");

		if(QMessageBox::question(this,"Channel dependencies found", question, QMessageBox::Yes,QMessageBox::No) ==	QMessageBox::No)
			return;
	}
	settings->query("DELETE FROM channel WHERE encoder='%s'", user_defined_encoder_name.c_str());
	settings->query("DELETE FROM encoder WHERE name = '%s'", user_defined_encoder_name.c_str());
	updateEncoders();
	updateChannels();
}
