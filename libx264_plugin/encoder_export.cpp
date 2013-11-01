#include "encoder_export.h"
#include "Libx264Encoder.h"
#include "thread_core.h"

#define ENCODER_PLUGIN_TYPE 102

int type = ENCODER_PLUGIN_TYPE;
int version = 100;
char name[] = "LibX264 encoder";

__declspec(dllexport) int getVersion()
{
	return version;
}

__declspec(dllexport) int getType()
{
	return type;
}

__declspec(dllexport) const char* getName()
{
	return name;
}

__declspec(dllexport) void encodeFrame(ENCODER_HANDLE handle, unsigned char *yuv_y, unsigned char *yuv_u, unsigned char *yuv_v, int width, int height)
{
	Libx264Encoder* encoder = (Libx264Encoder*)handle;
    encoder->encodeFrame(yuv_y, yuv_u, yuv_v, width, height);
}

__declspec(dllexport) bool setup(ENCODER_HANDLE handle, ENCODER_INPUT *init_ops, CBEncoderPlugin cb)
{
	Libx264Encoder* encoder = (Libx264Encoder*)handle;
	encoder->setup(init_ops, cb);
}

__declspec(dllexport) ENCODER_HANDLE createInstance()
{
	ThreadCore *thread_core = ThreadCore::getSingletonPtr();
	if(thread_core == NULL)
	{
		new ThreadCore;
		return createInstance();
	}
	return new Libx264Encoder;
}

__declspec(dllexport) void releaseInstance(ENCODER_HANDLE obj)
{
	delete (Libx264Encoder*)obj;
}
__declspec(dllexport) const char* getIcoPath()
{
	return "./plugins/logo/[SW] FFMPEG.png";
}
