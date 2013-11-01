#pragma once

#include <map>
#include "global.h"

using namespace std;
extern map<int, CAPTURE_HANDLE> _instances;//map<active device(0 if not active), device>
extern map<CAPTURE_HANDLE, int> _rinstances;//map<device, ref count>

extern char name[];
extern int type;
extern int version;

extern "C"
{
	//plugin specific
	__declspec(dllexport) int getVersion();
	__declspec(dllexport) int getType();
	__declspec(dllexport) const char* getName();

	//capture specific general
	__declspec(dllexport) char *getDeviceNameById(unsigned int device_id);
	__declspec(dllexport) char **getDeviceList();
	__declspec(dllexport) unsigned int getDeviceCount();
	__declspec(dllexport) void initialize(CaptureCallBack cb);

	//capture specific actions
	__declspec(dllexport) bool start(CAPTURE_HANDLE handle);
	__declspec(dllexport) bool stop(CAPTURE_HANDLE);
	__declspec(dllexport) int getHeight(CAPTURE_HANDLE handle);
	__declspec(dllexport) int getWidth(CAPTURE_HANDLE handle);
	__declspec(dllexport) void queueNextFrame(CAPTURE_HANDLE handle, unsigned char *data_buf);

	__declspec(dllexport) CAPTURE_HANDLE bindDevice(unsigned int device_id);
};