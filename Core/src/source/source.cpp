#include "source.h"

map<string, CapturePlugin*> SrcManager::_capture_plugins = map<string, CapturePlugin*>();
map<CAPTURE_HANDLE, set<CaptureDevice*> > SrcManager::_active_capture_devices = map<CAPTURE_HANDLE, set<CaptureDevice*> >();

unsigned int CaptureDevice::getDeviceId()
{
	return _bind_device_id;
}

vector<string> CaptureDevice::listDevices()
{
	vector<string> result;
	unsigned int device_count = _plugin->getDeviceCount();
	for(unsigned int i = 0; i < device_count; ++i)
		result.push_back(_plugin->getDeviceNameById(i));
	return result;
}

int CaptureDevice::getHeight()
{
	return _plugin->getHeight(capture_handle);
}

int CaptureDevice::getWidth()
{
	return _plugin->getWidth(capture_handle);
}

void CaptureDevice::queueNextFrame(unsigned char* data)
{
	_plugin->queueNextFrame(capture_handle, data);
}

void CaptureDevice::bind(uint device_id)
{
	_bind_device_id = device_id;
	capture_handle = _plugin->bindDevice(device_id);
}
//-----------IMqsSrc implementation-----------
void CaptureDevice::start()
{
	SrcManager::_active_capture_devices[capture_handle].insert(this);
	_plugin->start(capture_handle);
}

void CaptureDevice::stop()
{
	SrcManager::_active_capture_devices[capture_handle].erase(this);
	_plugin->stop(capture_handle);
}

string CaptureDevice::getName()
{
	return string(_plugin->getName()) + string("-") + string(_plugin->getDeviceNameById(_bind_device_id));
}
//------------SRC_MANAGER--------------------
void SrcManager::captureCallBack(CAPTURE_HANDLE handle, unsigned char *data, unsigned int height, unsigned int width)
{
	for(set<CaptureDevice*>::iterator it = _active_capture_devices[handle].begin(); it != _active_capture_devices[handle].end(); ++it)
	{
		ISource *source = dynamic_cast<ISource*>(reinterpret_cast<CaptureDevice*>(*it));
		Image *img = Image::initImage(data, width, height);
		source->broadcastFrame(img);
	}
}

void SrcManager::addCapturePlugin(string name, CapturePlugin* create_plugin)
{
	_capture_plugins[name] = create_plugin;
}

void SrcManager::unloadAllCapturePlugins()
{
    _capture_plugins.clear();
}

vector<string> SrcManager::getCapturePlugins()
{
	vector<string> result;
	for(map<string, CapturePlugin*>::iterator it = _capture_plugins.begin(); it != _capture_plugins.end(); ++it)
	{
		result.push_back(it->first);
	}
	return result;
}

ISource *SrcManager::createRegion()
{
  ISource *src;
  return src;
}

ICapture *SrcManager::createCapture(string name)
{
	map<string, CapturePlugin*>::iterator it = _capture_plugins.find(name);
	ASSERT_WITH_CODE(it != _capture_plugins.end(), "Error, capture not found!", return NULL);
	return new CaptureDevice(it->second);
}

