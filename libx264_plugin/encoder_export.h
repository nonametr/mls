#ifndef ECODER_EXPORT_H_
#define ECODER_EXPORT_H_

typedef void* ENCODER_HANDLE;
typedef void (*CBEncoderPlugin)(ENCODER_HANDLE handle, char *encoded_data, unsigned int encoded_size);
#define EXTERN_DLL __declspec(dllexport)

#include "global.h"

extern "C"
{
	//plugin specific
	EXTERN_DLL int getVersion();
	EXTERN_DLL int getType();
	EXTERN_DLL const char* getName();
	EXTERN_DLL const char* getIcoPath();

	//encoder specific general
    EXTERN_DLL void encodeFrame(ENCODER_HANDLE handle, unsigned char *yuv_y, unsigned char *yuv_u, unsigned char *yuv_v, int width, int height);
	EXTERN_DLL bool setup(ENCODER_HANDLE handle, ENCODER_INPUT *init_ops, CBEncoderPlugin cb);
	EXTERN_DLL ENCODER_HANDLE createInstance();
	EXTERN_DLL void releaseInstance(ENCODER_HANDLE obj);
}

#endif /* ECODER_EXPORT_H_ */
