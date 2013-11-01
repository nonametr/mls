#include "source_export.h"
#include "DSCapture.h"

map<int, CAPTURE_HANDLE> _instances;
map<CAPTURE_HANDLE, int> _rinstances;

char name[] = "Add camera...";
int type	= CAPTURE_PLUGIN_TYPE;
int version = 100;

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

__declspec(dllexport) char *getDeviceNameById(unsigned int device_id)
{ 
	return DSCapture::getDeviceNameById(device_id);
}

__declspec(dllexport) char **getDeviceList()
{
	return DSCapture::getDeviceList();
}

__declspec(dllexport) unsigned int getDeviceCount()
{
	return DSCapture::getDeviceCount();
}

__declspec(dllexport) bool start(CAPTURE_HANDLE handle)
{
	map<CAPTURE_HANDLE, int>::iterator it = _rinstances.find(handle);
	ASSERT_WITH_CODE(_rinstances.find(handle) != _rinstances.end(), "Error! Invalid capture handle!", return NULL);
	it->second++;
	return ((DSCapture*)it->first)->start();
}

__declspec(dllexport) bool stop(CAPTURE_HANDLE handle)
{
	map<CAPTURE_HANDLE, int>::iterator it = _rinstances.find(handle);
	ASSERT_WITH_CODE(it != _rinstances.end(), "Error! Invalid capture handle!", return false);
	if(--(it->second))
		return true;
	DSCapture *ds_cap = (DSCapture*)handle;
	if(ds_cap->stop() == true)//if return true then nobody else using this device and we can delete it, elseway we should not call delete
	{
		_rinstances.erase(it);
		_instances.erase(it->second);
		delete (DSCapture *)handle;
	}
	return true;
}

__declspec(dllexport) int getHeight(CAPTURE_HANDLE handle)
{
	DSCapture* ds_cap = (DSCapture*)handle;

	return ds_cap->getHeight();
}

__declspec(dllexport) int getWidth(CAPTURE_HANDLE handle)
{
	DSCapture* ds_cap = (DSCapture*)handle;

	return ds_cap->getWidth();
}

__declspec(dllexport) void queueNextFrame(CAPTURE_HANDLE handle, unsigned char *data_buf)
{
	DSCapture* ds_cap = (DSCapture*)handle;

	ds_cap->queueNextFrame(data_buf);
}

__declspec(dllexport) CAPTURE_HANDLE bindDevice(unsigned int device_id)
{
	map<int, CAPTURE_HANDLE>::iterator it = _instances.find(device_id);
	if(it != _instances.end())
	{
		return it->second;
	}
	DSCapture *ds_cap = new DSCapture;
	ds_cap->bind(device_id);
	_rinstances[ds_cap] = 0;
	_instances[device_id] = ds_cap;
	return ds_cap;
}

__declspec(dllexport) void initialize(CaptureCallBack cb)
{
	DSCapture::initialize(cb);
}