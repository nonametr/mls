#include "iencoder.h"
#include "settings.h"

map<string, EncoderPlugin*> EncoderManager::_registered_encoder_types = map<string, EncoderPlugin*>();
map<PLUGIN_ENCODER_HANDLE, IEncoder*> EncoderManager::_active_plugins = map<PLUGIN_ENCODER_HANDLE, IEncoder*>();

void EncoderManager::encoderCallBack(PLUGIN_ENCODER_HANDLE plugin, char *data, unsigned int data_len)
{
	IEncoder* encoder = _active_plugins[plugin];
	encoder->broadcastEncodedFrame(data, data_len);
}

bool EncoderManager::addEncoderPlugin(string encoder_name, EncoderPlugin* encoder_plugin)
{
    map<string, EncoderPlugin*>::iterator it = _registered_encoder_types.find(encoder_name);
    if(it != _registered_encoder_types.end())//this name already reserved by other encoder?
		return false;

    _registered_encoder_types[encoder_name] = encoder_plugin;
	return true;
}

void EncoderManager::unloadAllEncoderPlugins()
{
    _registered_encoder_types.clear();
}

vector<string> EncoderManager::getSuported()
{
	vector<string> result;
    for(map<string, EncoderPlugin*>::iterator it = _registered_encoder_types.begin(); it != _registered_encoder_types.end(); ++it)
	{
		result.push_back(it->first);
	}
	return result; 
}
//encoder factory
IEncoder* EncoderManager::create(string user_defined_encoder_name)
{
	QSqlRecord encoder_data = settings->query("SELECT audio_bitrate, audio_encoder, audio_format, audio_source, "
			"video_bitrate, video_buffer, video_encoder_plugin, video_preset, "
			"video_quality FROM encoder WHERE name = '%s'", user_defined_encoder_name.c_str()).record();

	QSqlRecord resolution_data = settings->query("SELECT width, height FROM resolution WHERE name in (SELECT value FROM property WHERE name = 'resolution')").record();

	ASSERT_WITH_CODE(!encoder_data.isEmpty() && !resolution_data.isEmpty(), "Error! Requested encoder not found!", return NULL);

	ENCODER_INPUT encoder_input;
	encoder_input.bitrate 		= encoder_data.value("video_bitrate").toInt();
	encoder_input.buffer_size 	= encoder_data.value("video_buffer").toInt();
	encoder_input.preset 		= encoder_data.value("video_preset").toInt();
	encoder_input.quality 		= encoder_data.value("video_quality").toInt();
	encoder_input.fps 			= 25;
	encoder_input.height 		= resolution_data.value("height").toInt();
	encoder_input.width 		= resolution_data.value("width").toInt();

    map<string, EncoderPlugin*>::iterator it_encoder_type = _registered_encoder_types.find(encoder_data.value("video_encoder_plugin").toString().toStdString());
    ASSERT_WITH_CODE(it_encoder_type != _registered_encoder_types.end(), "Encoder not supported", return NULL);

	EncoderPlugin* encoder_plugin = it_encoder_type->second;
	IEncoder *encoder = new Encoder(user_defined_encoder_name, encoder_plugin);
	ASSERT_WITH_CODE(encoder->setup(&encoder_input), "Error! Encoder setup failed...", delete encoder; return NULL);

	return encoder;
}

Encoder::Encoder(string user_defined_encoder_name, EncoderPlugin* encoder_plugin) :
        _user_defined_encoder_name(user_defined_encoder_name), _plugin(encoder_plugin), _handle(NULL),
		ref_cnt(0)
{
    _handle = _plugin->createInstance();
    EncoderManager::_active_plugins[_handle]	= this;
}

Encoder::~Encoder()
{
    EncoderManager::_active_plugins.erase(_handle);
    _plugin->releaseInstance(_handle);
}

bool Encoder::setup(ENCODER_INPUT *init_ops)
{
    return _plugin->setup(_handle, init_ops, &EncoderManager::encoderCallBack);
}

void Encoder::addChannel(IChannel *p_channel)
{
	connect(this, SIGNAL(onFrameEncoded(char *, unsigned int)), p_channel, SLOT(onFrameReady(char *, unsigned int)));
	connect(p_channel, SIGNAL(destroyed()), this, SLOT(onChannelDisconnected()));
	ref_cnt++;
	p_channel->start();
}

void Encoder::onChannelDisconnected()
{
	if(!--ref_cnt)
	{
		this->deleteLater();
	}
}

void Encoder::delChannel(IChannel *p_channel)
{
	disconnect(this, SIGNAL(onFrameEncoded(char *, unsigned int)), p_channel, SLOT(onFrameReady(char *, unsigned int)));
	p_channel->stop();
}

void Encoder::setSource(MlsMain *p_source)
{
    connect(p_source, SIGNAL(onFrameReady(unsigned char *, unsigned char *, unsigned char *, uint, uint)), this, SLOT(encodeFrame(unsigned char *, unsigned char *, unsigned char *, uint, uint)));
}

void Encoder::encodeFrame(unsigned char *yuv_y, unsigned char *yuv_u, unsigned char *yuv_v, uint width, uint height)
{
    _plugin->encodeFrame(_handle, yuv_y, yuv_u, yuv_v, width, height);
}

const char *Encoder::getIcoPath()
{
	return _plugin->getIcoPath();
}
