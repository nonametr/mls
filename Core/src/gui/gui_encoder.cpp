#include "gui_encoder.h"
#include "iencoder.h"
#include <QtMultimedia/QAudioDeviceInfo.h>
#include "settings.h"

MqsEncoder::MqsEncoder(QWidget *parent, Qt::WindowFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);

	vector<string> encoders = EncoderManager::getSuported();
	for(unsigned int i = 0; i < encoders.size(); ++i)
	{
		QString ico_path = EncoderManager::getEncoderPlugin(encoders[i])->getIcoPath();
		ui.combo_encoder->addItem(QIcon(ico_path), encoders[i].c_str());
	}
	QList<QAudioDeviceInfo> capture_devices = QAudioDeviceInfo::availableDevices( QAudio::AudioInput );
	for(unsigned int i = 0; i < capture_devices.size(); ++i)
	{
        ui.combo_audio_source->addItem(capture_devices[i].deviceName());
	}
	connect(this, SIGNAL(updateEncodersListView()), parent, SLOT(updateEncoders()));
	connect(ui.button_ok, SIGNAL(clicked()), this, SLOT(okClicked()));
	connect(ui.button_cancel, SIGNAL(clicked()), this, SLOT(cancelClicked()));
}

MqsEncoder::~MqsEncoder(void)
{
}

void MqsEncoder::setCombo(QComboBox *combo, QString value)
{
	int index = combo->findText(value);
	combo->setCurrentIndex(index);
}

void MqsEncoder::init(string user_defined_encoder_name)
{
	old_name = user_defined_encoder_name;
	QSqlRecord encoder = settings->query("SELECT audio_bitrate, audio_encoder, audio_format, audio_source, "
			"video_bitrate, video_buffer, video_encoder_plugin, video_preset, "
			"video_quality FROM encoder WHERE name = '%s'", user_defined_encoder_name.c_str()).record();

	setCombo(ui.combo_preset, encoder.value("video_preset").toString());
	setCombo(ui.combo_quality, encoder.value("video_quality").toString());
	setCombo(ui.combo_buffer, encoder.value("video_buffer").toString());
	setCombo(ui.combo_bitrate, encoder.value("video_bitrate").toString());
	setCombo(ui.combo_encoder, encoder.value("video_encoder_plugin").toString());
	setCombo(ui.combo_audio_source, encoder.value("audio_source").toString());
	setCombo(ui.combo_audio_format, encoder.value("audio_format").toString());
	setCombo(ui.combo_audio_bitrate, encoder.value("audio_bitrate").toString());
	setCombo(ui.combo_audio_encoder, encoder.value("audio_encoder").toString());
	ui.line_name->setText(user_defined_encoder_name.c_str());
}

void MqsEncoder::okClicked()
{
	string user_defined_encoder_name = ui.line_name->text().toStdString();

	if(!old_name.empty())
		settings->query("DELETE FROM encoder WHERE name = '%s'", old_name.c_str());
	if(ui.line_name->text().isEmpty())
		ui.line_name->setText(ui.combo_encoder->currentText() + ui.combo_preset->currentText() + ui.combo_audio_encoder->currentText() + ui.combo_bitrate->currentText() + ui.combo_quality->currentText());
	QSqlQuery update_encoder = settings->prepareQuery("INSERT INTO encoder VALUES(:encoder_name,"
			":audio_bitrate, :audio_encoder, :audio_format, :audio_source, "
			":video_bitrate, :video_buffer, :video_encoder_plugin, :video_preset, "
			":video_quality)");
	update_encoder.bindValue(":encoder_name",	ui.line_name->text());
	update_encoder.bindValue(":audio_bitrate", 	ui.combo_audio_bitrate->currentText().toInt());
	update_encoder.bindValue(":audio_encoder", 	ui.combo_audio_encoder->currentText());
	update_encoder.bindValue(":audio_format", 	ui.combo_audio_format->currentText().toInt());
	update_encoder.bindValue(":audio_source", 	ui.combo_audio_source->currentText());
	update_encoder.bindValue(":video_bitrate", 	ui.combo_bitrate->currentText().toInt());
	update_encoder.bindValue(":video_buffer", 	ui.combo_buffer->currentText().toInt());
	update_encoder.bindValue(":video_encoder_plugin", 	ui.combo_encoder->currentText());
	update_encoder.bindValue(":video_preset", 	ui.combo_preset->currentText());
	update_encoder.bindValue(":video_quality", 	ui.combo_quality->currentText().toInt());
	if(!update_encoder.exec())
		traceerr("SQL error = %s, sql = %s", update_encoder.lastError().text().toStdString().c_str(), update_encoder.lastQuery().toStdString().c_str());

	emit updateEncodersListView();
	this->close();
}

void MqsEncoder::cancelClicked()
{
	this->close();
}
