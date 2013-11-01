#ifndef MLS_IENCODER_H
#define MLS_IENCODER_H

#include <qobject.h>
#include <vector>
#include <string>
#include "ichannel.h"
#include "global.h"
#include "json.h"
#include "gui_main.h"
#include "plugin.h"

using namespace std;

typedef void* PLUGIN_ENCODER_INPUT;
typedef void* PLUGIN_ENCODER_HANDLE;
typedef void (*CBEncoderPlugin)(PLUGIN_ENCODER_HANDLE handle, char *encoded_data, unsigned int encoded_size);

struct ENCODER_INPUT
{
	int height;
	int width;
	int preset;
	int quality;
	int buffer_size;
	int fps;
	int bitrate;
};

class IEncoder : public QObject//its encoder interface that we use in MLS
{
	Q_OBJECT
public:
    void broadcastEncodedFrame(char *data, unsigned int data_len){ emit onFrameEncoded(data, data_len); }
	virtual bool setup(ENCODER_INPUT *init_ops) = 0;
	virtual void addChannel(IChannel *p_channel) = 0;
	virtual void delChannel(IChannel *p_channel) = 0;
	virtual void setSource(MlsMain *p_source) = 0;
	virtual const char *getIcoPath() = 0;
public slots:
	virtual void onChannelDisconnected() = 0;
    virtual void encodeFrame(unsigned char *yuv_y, unsigned char *yuv_u, unsigned char *yuv_v, uint width, uint height) = 0;
signals:
	void onFrameEncoded(char *data, unsigned int data_len);
};

class Encoder : public IEncoder
{
public:
	Encoder(string user_defined_encoder_name, EncoderPlugin* encoder_plugin);
	virtual ~Encoder();
	virtual bool setup(ENCODER_INPUT *init_ops);
	virtual void addChannel(IChannel *p_channel);
	virtual void delChannel(IChannel *p_channel);
	virtual void setSource(MlsMain *p_source);
    virtual void encodeFrame(unsigned char *yuv_y, unsigned char *yuv_u, unsigned char *yuv_v, uint width, uint height);
	virtual const char *getIcoPath();
	virtual void onChannelDisconnected();
private:
	unsigned int ref_cnt;
	string _user_defined_encoder_name;
	EncoderPlugin *_plugin;
    PLUGIN_ENCODER_HANDLE _handle;
};

class EncoderManager
{
	friend class Encoder;
public:
	static void encoderCallBack(PLUGIN_ENCODER_HANDLE handle, char *data, unsigned int data_len);

    static void unloadAllEncoderPlugins();
    static bool addEncoderPlugin(string encoder_name, EncoderPlugin *encoder_plugin);
    static vector<string> getSuported();
    static EncoderPlugin *getEncoderPlugin(string encoder_name){ return _registered_encoder_types[encoder_name]; }
	static IEncoder* create(string user_defined_encoder_name);
private:
    static map<string, EncoderPlugin *> _registered_encoder_types;
	static map<PLUGIN_ENCODER_HANDLE, IEncoder*> _active_plugins;
};

#endif

