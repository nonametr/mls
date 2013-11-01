#ifndef ECODER_EXPORT_H_
#define ECODER_EXPORT_H_

#define EXTERN_DLL __declspec(dllexport)

#include "global.h"
#include "escape_call_client.h"

#define PLUGIN_NAME "custom rtmp channel"
#define CHANNEL_PLUGIN_TYPE 103

extern "C"
{
	//plugin specific
	EXTERN_DLL int getVersion();
	EXTERN_DLL int getType();
	EXTERN_DLL const char* getName();
    EXTERN_DLL const char* getImagePath();

    //channel specific
    EXTERN_DLL void initializeEscape(EscapeCallFunc escape_call);
    EXTERN_DLL void start(CHANNEL_HANDLE handle);
    EXTERN_DLL void stop(CHANNEL_HANDLE handle);
    EXTERN_DLL void broadcastFrame(CHANNEL_HANDLE handle, char *buf, unsigned int buf_len);

    EXTERN_DLL CHANNEL_HANDLE createInstance(char* channel_name);
    EXTERN_DLL void releaseInstance(CHANNEL_HANDLE obj);

    //channel configuration
    EXTERN_DLL void edit(char *channel_name);
    EXTERN_DLL void rm(char *channel_name);
    EXTERN_DLL void create(void *owner);
}

#endif /* ECODER_EXPORT_H_ */
