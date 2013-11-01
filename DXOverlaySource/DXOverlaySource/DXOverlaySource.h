#pragma once

#include <vector>
#include <windows.h>
#include <d3d9.h>
#include <D3dx9tex.h>
#include "global.h"
#include "ring_buffer.h"

using namespace std;

struct MonitorInfo
{
	int monitor_id;
	int height;
	int width;
};

class DXOverlaySource
{
public:
	DXOverlaySource(int device_id);
	~DXOverlaySource();
	bool start();
	bool stop();
	void queueNextFrame(unsigned char* data);
	int getBindDeviceId(){ return _device_id; }
	bool isRunning() { return _running; }
	int getHeight();
	int getWidth();

	static void initialize(CaptureCallBack cb);
	static char** getAvailableDevices();
	static int getAvailableDevicesCount();
private:
	int getMonitorHeight(unsigned int monitor_id);
	int getMonitorWidth(unsigned int monitor_id);
	int getMonitorOffsetHeight(unsigned int monitor_id);
	int getMonitorOffsetWidth(unsigned int monitor_id);
	void run();

	IDirect3DDevice9*	_d3d_device;
	IDirect3DSurface9*	_d3d_surface;
	volatile bool		_running;
	unsigned int		_dev_height;
	unsigned int		_dev_width;
	unsigned int		_device_id;

	static DWORD WINAPI runThread(LPVOID lpParam);
	static BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);
	static vector<MonitorInfo> _monitor;
	static char** _available_devices;
	static CaptureCallBack capture_cb;
};