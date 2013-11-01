#include "plugin.h"
#include "global.h"
#include "source.h"
#include "iencoder.h"
#include "source.h"
#include "escape_call_server.h"

map<string, HMODULE> PluginManager::plugin = map<string, HMODULE>();

bool PluginManager::loadPlugin(string full_path)
{
	typedef int (*GetVersion)();
	typedef int (*GetType)();
	typedef char* (*GetName)();

    HMODULE lib = LoadLibrary(full_path.c_str());
    traceerr("loading library = %s", full_path.c_str());
	ASSERT_WITH_CODE(lib != NULL, "Can't load plugin... skipping...", return false);
	GetVersion getVersion	 = (GetVersion)GetProcAddress(lib, "getVersion");
	GetType getType	 		= (GetType)GetProcAddress(lib, "getType");
	GetName getName 		= (GetName)GetProcAddress(lib, "getName");
	ASSERT_WITH_CODE(
			getVersion != NULL &&
			getName != NULL &&
			getType != NULL,
			"Wrong plugin format... skipping...", FreeLibrary(lib);
			return false);

	switch(getType())
	{
	case CAPTURE_SOURCE:
		traceerr("Loading %s plugin %s, v. %u", "source(camera) capture", getName(), getVersion());
		SrcManager::addCapturePlugin(getName(), new CapturePlugin(lib));
		plugin[full_path] = lib;
	break;
	case VIDEO_ENCODER:
	{
		traceerr("Loading %s plugin %s, v. %u", "video encoder", getName(), getVersion());
		EncoderManager::addEncoderPlugin(getName(), new EncoderPlugin(lib));
		plugin[full_path] = lib;
	}
        break;
    case CHANNEL:
    {
        traceerr("Loading %s plugin %s, v. %u", "broadcasting transport channel", getName(), getVersion());
        ChannelManager::addPlugin(getName(), new ChannelPlugin(lib));
        plugin[full_path] = lib;
    }
		break;
	default:
		traceerr("Skipping unsupported plugin type...");
		break;
	}
	return true;
}

void PluginManager::unloadAll()
{
    SrcManager::unloadAllCapturePlugins();
    EncoderManager::unloadAllEncoderPlugins();
	for(map<string, HMODULE>::iterator it = plugin.begin(); it != plugin.end(); ++it)
	{
		FreeLibrary(it->second);
	}
}

EncoderPlugin::EncoderPlugin(HMODULE lib)
{
	getVersion 		= (int (*)())GetProcAddress(lib, "getVersion");
	getType 		= (int (*)())GetProcAddress(lib, "getType");
	getName 		= (const char* (*)())GetProcAddress(lib, "getName");
	getIcoPath		= (const char* (*)())GetProcAddress(lib, "getIcoPath");
    encodeFrame 	= (void (*)(ENCODER_HANDLE, unsigned char *, unsigned char *, unsigned char *, int, int))GetProcAddress(lib, "encodeFrame");
	setup 			= (bool (*)(ENCODER_HANDLE, ENCODER_INPUT, CBEncoderPlugin))GetProcAddress(lib, "setup");
	createInstance 	= (ENCODER_HANDLE (*)())GetProcAddress(lib, "createInstance");
	releaseInstance = (void (*)(ENCODER_HANDLE))GetProcAddress(lib, "releaseInstance");

    ASSERT_WITH_CODE(getVersion && getType && getName && getIcoPath && encodeFrame && setup && createInstance && releaseInstance,
                     "Error! Failed to load encoder plugin! Program can't start!", exit(1));
}

ChannelPlugin::ChannelPlugin(HMODULE lib)
{
    getVersion 		= (int (*)())GetProcAddress(lib, "getVersion");
    getType 		= (int (*)())GetProcAddress(lib, "getType");
    getName 		= (const char* (*)())GetProcAddress(lib, "getName");
    getImagePath	= (const char* (*)())GetProcAddress(lib, "getImagePath");
    initializeEscape= (void (*)(EscapeCallFunc))GetProcAddress(lib, "initializeEscape");
    start           = (void (*)(CHANNEL_HANDLE))GetProcAddress(lib, "start");
    stop            = (void (*)(CHANNEL_HANDLE))GetProcAddress(lib, "stop");
    broadcastFrame  = (void (*)(CHANNEL_HANDLE, char *, unsigned int))GetProcAddress(lib, "broadcastFrame");
    edit            = (void (*)(char *))GetProcAddress(lib, "edit");
    rm          = (void (*)(char *))GetProcAddress(lib, "rm");
    create          = (void (*)(void *))GetProcAddress(lib, "create");
    createInstance 	= (CHANNEL_HANDLE (*)(char*))GetProcAddress(lib, "createInstance");
    releaseInstance = (void (*)(CHANNEL_HANDLE))GetProcAddress(lib, "releaseInstance");

    ASSERT_WITH_CODE(getVersion && getType && getName && getImagePath && initializeEscape && start && stop && broadcastFrame && broadcastFrame && edit && rm && create && createInstance && releaseInstance,
                     "Error! Failed to load channel plugin! Program can't start!", exit(1));

    initializeEscape(EscapeCallServer::escapeCallback);
}

CapturePlugin::CapturePlugin(HMODULE lib)
{
	getVersion 		= (int (*)())GetProcAddress(lib, "getVersion");
	getType 		= (int (*)()) GetProcAddress(lib, "getType");
	getName 		= (const char* (*)())GetProcAddress(lib, "getName");
	getDeviceNameById = (char *(*)(unsigned int))GetProcAddress(lib, "getDeviceNameById");
	getDeviceCount 	= (unsigned int (*)())GetProcAddress(lib, "getDeviceCount");
	initialize 		= (void (*)(CaptureCallBack))GetProcAddress(lib, "initialize");
	start 			= (bool (*)(CAPTURE_HANDLE))GetProcAddress(lib, "start");
	stop 			= (bool (*)(CAPTURE_HANDLE))GetProcAddress(lib, "stop");
	getHeight 		= (int (*)(CAPTURE_HANDLE))GetProcAddress(lib, "getHeight");
	getWidth		= (int (*)(CAPTURE_HANDLE))GetProcAddress(lib, "getWidth");
	queueNextFrame 	= (void (*)(CAPTURE_HANDLE, unsigned char*))GetProcAddress(lib, "queueNextFrame");
	bindDevice 		= (CAPTURE_HANDLE (*)(unsigned int))GetProcAddress(lib, "bindDevice");
	initialize(&SrcManager::captureCallBack);

    ASSERT_WITH_CODE(getVersion && getType && getName && getDeviceNameById && getDeviceCount && initialize && start && stop && getHeight && getWidth && queueNextFrame && bindDevice,
                     "Error! Failed to load capture plugin! Program can't start!", exit(1));
}

