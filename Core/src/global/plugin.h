#ifndef PLUGIN_H_
#define PLUGIN_H_

#include <string>
#include <map>
#include <vector>
#include <windef.h>
#include <windows.h>
#include "escape_call.h"

using namespace std;

class EncoderPlugin
{
public:
	typedef void* ENCODER_INPUT;
	typedef void* ENCODER_HANDLE;
	typedef void (*CBEncoderPlugin)(ENCODER_HANDLE handle, char *encoded_data, unsigned int encoded_size);

	EncoderPlugin(HMODULE lib);
	~EncoderPlugin()
	{}

	//plugin specific
	int (*getVersion)();
	int (*getType)();
	const char* (*getName)();
	const char* (*getIcoPath)();

    //encoder specific
    void (*encodeFrame)(ENCODER_HANDLE, unsigned char *, unsigned char *, unsigned char *, int, int);
	bool (*setup)(ENCODER_HANDLE, ENCODER_INPUT, CBEncoderPlugin);
	ENCODER_HANDLE (*createInstance)();
	void (*releaseInstance)(ENCODER_HANDLE);
};

class ChannelPlugin
{
public:
    typedef void* CHANNEL_HANDLE;

    ChannelPlugin(HMODULE lib);
    ~ChannelPlugin()
    {}

    //plugin specific
    int (*getVersion)();
    int (*getType)();
    const char* (*getName)();
    const char* (*getImagePath)();

    //channel specific
    void (*initializeEscape)(EscapeCallFunc);
    void (*start)(CHANNEL_HANDLE);
    void (*stop)(CHANNEL_HANDLE);
    void (*broadcastFrame)(CHANNEL_HANDLE, char *, unsigned int);
    void (*edit)(char *);
    void (*rm)(char *);
    void (*create)(void *owner);
    CHANNEL_HANDLE (*createInstance)(char*);
    void (*releaseInstance)(CHANNEL_HANDLE obj);
};

class CapturePlugin
{
public:
	typedef void* CAPTURE_HANDLE;
    typedef void (*CaptureCallBack)(CAPTURE_HANDLE handle, unsigned char *data, unsigned int height, unsigned int width);

	CapturePlugin(HMODULE lib);
	~CapturePlugin()
	{}
	//plugin specific
	int (*getVersion)();
	int (*getType)();
	const char* (*getName)();

	//capture specific general
	char *(*getDeviceNameById)(unsigned int);
	unsigned int (*getDeviceCount)();
	void (*initialize)(CaptureCallBack);

	//capture specific actions
	bool (*start)(CAPTURE_HANDLE);
	bool (*stop)(CAPTURE_HANDLE);
	int (*getHeight)(CAPTURE_HANDLE);
	int (*getWidth)(CAPTURE_HANDLE);
	void (*queueNextFrame)(CAPTURE_HANDLE, unsigned char*);

	CAPTURE_HANDLE (*bindDevice)(unsigned int device_id);
};

class PluginManager
{
public:
    enum PLUGIN_TYPE { CAPTURE_SOURCE = 101, VIDEO_ENCODER, CHANNEL };

	static bool loadPlugin(string full_path);
	static void unloadAll();
private:
	static map<string, HMODULE> plugin;
};

#endif /* PLUGIN_H_ */
