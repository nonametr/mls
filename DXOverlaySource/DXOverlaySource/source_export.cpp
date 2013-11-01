#include "source_export.h"
#include "DXOverlaySource.h"

map<int, CAPTURE_HANDLE> _instances = map<int, CAPTURE_HANDLE>();//map<active device(0 if not active), device>
map<CAPTURE_HANDLE, int> _rinstances = map<CAPTURE_HANDLE, int>();//map<device, ref count>

//plugin specific
__declspec(dllexport) int getVersion()
{
	return CAPTURE_PLUGIN_VERSION;
}

__declspec(dllexport) int getType()
{
	return CAPTURE_PLUGIN_TYPE;
}

__declspec(dllexport) const char* getName()
{
	return CAPTURE_PLUGIN_NAME;
}

//capture specific general
__declspec(dllexport) char *getDeviceNameById(unsigned int device_id)
{
	ASSERT_WITH_CODE(device_id < (unsigned int)DXOverlaySource::getAvailableDevicesCount(), "Error! Inappropriate monitor id", return NULL);

	return DXOverlaySource::getAvailableDevices()[device_id];
}

__declspec(dllexport) char **getDeviceList()
{
	return DXOverlaySource::getAvailableDevices();
}

__declspec(dllexport) unsigned int getDeviceCount()
{
	return DXOverlaySource::getAvailableDevicesCount();
}

__declspec(dllexport) void initialize(CaptureCallBack cb)
{
	DXOverlaySource::initialize(cb);
}

//capture specific actions
__declspec(dllexport) bool start(CAPTURE_HANDLE handle)
{
	DXOverlaySource * dx_overlay = (DXOverlaySource*)handle;
	if(dx_overlay->isRunning())
		return true;
	dx_overlay->start();
	return true;
}

__declspec(dllexport) bool stop(CAPTURE_HANDLE handle)
{
	DXOverlaySource * dx_overlay = (DXOverlaySource*)handle;
	if(!--_rinstances[handle])
	{
		dx_overlay->stop();
		_rinstances.erase(handle);
		_instances.erase(dx_overlay->getBindDeviceId());
	}
	return true;
}

__declspec(dllexport) CAPTURE_HANDLE bindDevice(unsigned int device_id)
{
	map<int, CAPTURE_HANDLE>::iterator it = _instances.find(device_id);
	if(it != _instances.end())
	{
		_rinstances[it->second]++;
		return it->second;
	}
	DXOverlaySource *dx_overlay = new DXOverlaySource(device_id);
	_instances[device_id] = dx_overlay;
	_rinstances[dx_overlay] = 1;
	return dx_overlay;
}

__declspec(dllexport) int getHeight(CAPTURE_HANDLE handle)
{
	DXOverlaySource * dx_overlay = (DXOverlaySource*)handle;
	return dx_overlay->getHeight();
}

__declspec(dllexport) int getWidth(CAPTURE_HANDLE handle)
{
	DXOverlaySource * dx_overlay = (DXOverlaySource*)handle;
	return dx_overlay->getWidth();
}

__declspec(dllexport) void queueNextFrame(CAPTURE_HANDLE handle, unsigned char *data_buf)
{
	DXOverlaySource * dx_overlay = (DXOverlaySource*)handle;
	dx_overlay->queueNextFrame(data_buf);
}