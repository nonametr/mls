#pragma once
#pragma comment(lib, "strmiids")

//#define SKIP_DXTRANS
//#define SHOW_DEBUG_RENDERER

/* If you are having the problem you can't open dxtrans.h:
* Open qedit.h and add this to the start of the file:
*
* #ifdef SKIP_DXTRANS
* #define __IDxtAlphaSetter_INTERFACE_DEFINED__
* #define __IDxtJpeg_INTERFACE_DEFINED__
* #define __IDxtKey_INTERFACE_DEFINED__
* #define __IDxtCompositor_INTERFACE_DEFINED__
* #endif
*
* Also replace the line 
* #include "dxtrans.h"
* with:
* #ifndef SKIP_DXTRANS
* #include "dxtrans.h"
* #endif
*/

#include <windows.h>
#include <dshow.h>
#include <qedit.h>

#ifndef MAXLONGLONG
#define MAXLONGLONG 0x7FFFFFFFFFFFFFFF
#endif

#ifndef MAX_DEVICES
#define MAX_DEVICES 16
#endif

#ifndef MAX_DEVICE_NAME
#define MAX_DEVICE_NAME 255
#endif

typedef struct
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
} RGB;

class VideoDevice
{
public:
	VideoDevice();
	~VideoDevice();

	const char* GetFriendlyName();

private:
	char*			friendlyname;
	WCHAR*			filtername;
	IBaseFilter*	filter;
	friend class	VideoCapture;
};

class ICallbackHandler : public ISampleGrabberCB
{
public:
	virtual ~ICallbackHandler()
	{}
	virtual void SetMediaType(AM_MEDIA_TYPE* am) = 0;
};

template <class T> class CallbackHandler : public ICallbackHandler
{
public:

	typedef void (T::*VideoCaptureCallback)(unsigned char* data, int len, int bitsperpixel);

	CallbackHandler(T *p_that, VideoCaptureCallback cb)
	{
		that = p_that;
		callback = cb;
	}

	virtual ~CallbackHandler()
	{
	}

	void SetMediaType(AM_MEDIA_TYPE* am)
	{
		if (am->subtype == MEDIASUBTYPE_RGB555) bitpixel = 16;
		else if (am->subtype == MEDIASUBTYPE_RGB24) bitpixel = 24;
		else if (am->subtype == MEDIASUBTYPE_RGB32) bitpixel = 32;
	}

	HRESULT __stdcall SampleCB(double time, IMediaSample *sample)
	{
		HRESULT hr;
		AM_MEDIA_TYPE* mt;
		unsigned char* buffer;

		hr = sample->GetPointer((BYTE**)&buffer);
		if (hr != S_OK) return S_OK;

		hr = sample->GetMediaType(&mt);
		if (hr < 0) return S_OK;
		if (hr == S_OK) SetMediaType(mt);

		(that->*callback)(buffer, sample->GetActualDataLength(), bitpixel);
		return S_OK;
	}

	HRESULT __stdcall BufferCB(double time, BYTE *buffer, long len)
	{
		return S_OK;
	}

	HRESULT __stdcall QueryInterface(const IID &iid, LPVOID *ppv)
	{
		if( iid == IID_ISampleGrabberCB || iid == IID_IUnknown )
		{
			*ppv = (void *) static_cast<ISampleGrabberCB*>( this );
			return S_OK;
		}
		return E_NOINTERFACE;
	}

	ULONG __stdcall AddRef()
	{
		return 1;
	}

	ULONG __stdcall Release()
	{
		return 2;
	}

private:
	T *that;
	int						bitpixel;
	VideoCaptureCallback	callback;

};

class VideoCapture
{
public:
	VideoCapture(ICallbackHandler *callback = NULL);
	~VideoCapture();

	VideoDevice* GetDevices();
	int  NumDevices();

	unsigned int getHeight();
	unsigned int getWidth();
	void Select(VideoDevice* dev);
	void Start();
	void Stop();

protected:
	void InitializeGraph();
	void SetSourceFilters();
	void SetSampleGrabber();
	void SetNullRenderer();
	void ConnectFilters();

private:
	IFilterGraph2*			graph;
	ICaptureGraphBuilder2*	capture;
	IMediaControl*			control;

	IBaseFilter*			nullrenderer;
	IBaseFilter*			samplegrabberfilter;
	ISampleGrabber*			samplegrabber;

	bool					playing;

	VideoDevice*			devices;
	VideoDevice*			current;

	int						num_devices;

	ICallbackHandler *callbackhandler;
};