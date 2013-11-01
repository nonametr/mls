#include "icap.h"

unsigned int MlsCapture::getDeviceId()
{
	return _bind_device_id;
}
vector<string> MlsCapture::listDevices()
{
	vector<string> result;
	unsigned int device_count = _plugin->getDeviceCount();
	char **device_list = _plugin->getDeviceList();
	for(unsigned int i = 0; i < device_count; ++i)
		result.push_back(device_list[i]);
	return result;
}
void MlsCapture::bind(uint device_id)
{
	_bind_device_id = device_id;
}
//-----------IMqsSrc implementation-----------
void MlsCapture::start()
{
	ASSERT_WITH_CODE(running == false, "Can't start device. Already running", return);

	running = true;
	_plugin->start((CAPTURE_HANDLE)this, _bind_device_id, &SrcManager::captureCallBack);
}
void MlsCapture::stop()
{
	running = false;
	_plugin->stop(_bind_device_id);
}
string MlsCapture::getName()
{
	return string(_plugin->getPluginName()) + string("-") + string(_plugin->getName(_bind_device_id));
}
