// DXOverlaySource.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "DXOverlaySource.h"
#include "global.h"
#include <stdio.h>

#pragma comment(lib, "d3dx9.lib")
typedef IDirect3D9* (__stdcall *DIRECT3DCREATE9)(unsigned int);

vector<MonitorInfo> DXOverlaySource::_monitor = vector<MonitorInfo>();
char** DXOverlaySource::_available_devices = NULL;
CaptureCallBack DXOverlaySource::capture_cb = NULL;

DWORD WINAPI DXOverlaySource::runThread(LPVOID lpParam) 
{
	DXOverlaySource* dx_overlay = (DXOverlaySource*)lpParam;
	dx_overlay->run();
	return 1;
}

BOOL CALLBACK DXOverlaySource::MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
	MonitorInfo monitor_info;
	MONITORINFO winapi_info;
	winapi_info.cbSize = sizeof(MONITORINFO);

	GetMonitorInfo(hMonitor, &winapi_info);

	monitor_info.monitor_id = _monitor.size();
	monitor_info.width		= winapi_info.rcMonitor.right - winapi_info.rcMonitor.left;
	monitor_info.height		= winapi_info.rcMonitor.bottom - winapi_info.rcMonitor.top;

	_monitor.push_back(monitor_info);

	return TRUE;
}

DXOverlaySource::DXOverlaySource(int device_id) : _device_id(device_id), _running(false), _d3d_device(NULL)
{
	ASSERT_WITH_CODE(device_id < (int)_monitor.size(), "Error! Inappropriate monitor id", return);

	_dev_width			= getMonitorWidth(device_id);
	_dev_height			= getMonitorHeight(device_id);
	int dev_offset_width	= getMonitorOffsetWidth(device_id);
	int dev_offset_height	= getMonitorOffsetHeight(device_id);

	HWND hWnd = CreateWindow("STATIC", "dummy", 0, dev_offset_width + _dev_width*0.5, 0, 1, 1, 0, 0, 0, 0);
	HMODULE hD3D9 = LoadLibrary("d3d9");
	DIRECT3DCREATE9 Direct3DCreate9 = (DIRECT3DCREATE9)GetProcAddress(hD3D9, "Direct3DCreate9");
	IDirect3D9 *d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DDISPLAYMODE d3ddm;
	d3d->GetAdapterDisplayMode(0, &d3ddm);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = d3ddm.Format;

	HRESULT res = d3d->CreateDevice(device_id, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &_d3d_device);
	if(_d3d_device == NULL)
	{
		traceerr("Failed to init. d3d device");
		return;
	}
	d3d->Release();

	_d3d_device->CreateOffscreenPlainSurface(_dev_width, _dev_height, D3DFMT_A8R8G8B8, D3DPOOL_SCRATCH, &_d3d_surface, NULL);
}

DXOverlaySource::~DXOverlaySource()
{
	_d3d_surface->Release();
	_d3d_device->Release();
}

int DXOverlaySource::getMonitorHeight(unsigned int monitor_id)
{
	ASSERT_WITH_CODE(monitor_id < _monitor.size(), "Error! Inappropriate monitor id", return -1);

	return _monitor[monitor_id].height;
}

int DXOverlaySource::getMonitorWidth(unsigned int monitor_id)
{
	ASSERT_WITH_CODE(monitor_id < _monitor.size(), "Error! Inappropriate monitor id", return -1);

	return _monitor[monitor_id].width;
}

int DXOverlaySource::getMonitorOffsetHeight(unsigned int monitor_id)
{
	ASSERT_WITH_CODE(monitor_id < _monitor.size(), "Error! Inappropriate monitor id", return -1);

	int offset_height = 0;
	for(unsigned int i = 0; i < monitor_id; ++i)
		offset_height += _monitor[i].height;
	return offset_height;
}

int DXOverlaySource::getMonitorOffsetWidth(unsigned int monitor_id)
{
	ASSERT_WITH_CODE(monitor_id < _monitor.size(), "Error! Inappropriate monitor id", return -1);

	int offset_width = 0;
	for(unsigned int i = 0; i < monitor_id; ++i)
		offset_width += _monitor[i].width;
	return offset_width;
}

char** DXOverlaySource::getAvailableDevices()
{
	return _available_devices;
}

int DXOverlaySource::getAvailableDevicesCount()
{
	return _monitor.size();
}

void DXOverlaySource::initialize(CaptureCallBack cb)
{
	capture_cb = cb;
	EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, (LPARAM)NULL);
	_available_devices = new char*[_monitor.size()];
	for(unsigned int i = 0; i < _monitor.size(); ++i)
	{
		_available_devices[i] = new char[64];
		memset(_available_devices[i], 0, 64*sizeof(char));
		_snprintf(_available_devices[i], 64, "%monitor-%u//%ux%u", _monitor[i].monitor_id, _monitor[i].width, _monitor[i].height);
	}
}

int DXOverlaySource::getHeight()
{
	return _dev_height;
}

int DXOverlaySource::getWidth()
{
	return _dev_width;
}

bool DXOverlaySource::start()
{
	return true;
}

bool DXOverlaySource::stop()
{
	return true;
}

void DXOverlaySource::queueNextFrame(unsigned char* data)
{
	D3DLOCKED_RECT lockedRect;
	if(_d3d_device->GetFrontBufferData(0, _d3d_surface) != D3D_OK)
	{
		traceerr("Error! GetFrontBufferData failed!");
		return;
	}
	_d3d_surface->LockRect(&lockedRect, NULL, D3DLOCK_NO_DIRTY_UPDATE|D3DLOCK_NOSYSLOCK|D3DLOCK_READONLY);
	for( int row = 0 ; row < _dev_height ; ++row)
	{
		for(int  col = 0; col < _dev_width; ++col)
		{
			memcpy( data + _dev_width*_dev_height*3 - (row*_dev_width*3 + (_dev_width*3 - col*3)), (BYTE*) lockedRect.pBits + row * lockedRect.Pitch + col * 4, 3 * sizeof(unsigned char));
		}
	}
	_d3d_surface->UnlockRect();
}

void DXOverlaySource::run()
{
	/*D3DLOCKED_RECT lockedRect;
	while(_running)
	{
		WaitForSingleObject(_read_semaphore, INFINITE);
		if(_d3d_device->GetFrontBufferData(0, _d3d_surface) != D3D_OK)
		{
			traceerr("Error! GetFrontBufferData failed!");
			continue;
		}
		_d3d_surface->LockRect(&lockedRect, NULL, D3DLOCK_NO_DIRTY_UPDATE|D3DLOCK_NOSYSLOCK|D3DLOCK_READONLY);
		for( int row = 0 ; row < _dev_height ; ++row)
		{
			for(int  col = 0; col < _dev_width; ++col)
			{
				memcpy( _frame_storage + ((_dev_width * _dev_height * 3 - 3) - (row * _dev_width * 3 + (_dev_width - col * 3))), (BYTE*) lockedRect.pBits + row * lockedRect.Pitch + col * 4, 3 * sizeof(unsigned char));
			}
		}
		_d3d_surface->UnlockRect();
		capture_cb(this, _frame_storage, _dev_height, _dev_width);
	}
	_running = !_running;*/
}