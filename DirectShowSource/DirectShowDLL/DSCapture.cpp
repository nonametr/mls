#include "DSCapture.h"

char**	DSCapture::dev_list		= NULL;
int		DSCapture::dev_count	= 0;
CaptureCallBack DSCapture::external_cb = NULL;

void DSCapture::DSCallback(unsigned char* data, int len, int bpp)
{
	current_frame_ptr = data;
	DWORD result = WaitForSingleObject(_read_mutex, 0);
	if(result == WAIT_TIMEOUT)
	{
		return;
	}
	memcpy(extern_data_ptr, current_frame_ptr, height*width*3);
	external_cb(this, extern_data_ptr, height, width);
}

void DSCapture::queueNextFrame(unsigned char *data_buf)
{
	extern_data_ptr = data_buf;
	ReleaseMutex(_read_mutex);
}

DSCapture::DSCapture(int device_id) : state(BINDED), active_device_id(device_id)
{}

DSCapture::DSCapture() : state(UNBINDED), active_device_id(-1)
{}

DSCapture::~DSCapture(void)
{}

void DSCapture::initialize(CaptureCallBack cb)
{
	DSCapture temp;
	VideoCapture* vc = new VideoCapture(new CallbackHandler<DSCapture>(&temp, &DSCapture::DSCallback));
	ASSERT_WITH_CODE(vc != NULL, "Can't create direct show object", return);
	
	VideoDevice* devices = vc->GetDevices();
	dev_count = vc->NumDevices();
	dev_list = new char*[dev_count];
	for(int i = 0; i < dev_count; ++i)
	{
		const char *friendly_name	= devices[i].GetFriendlyName();
		dev_list[i] = (char*) malloc(MAX_DEVICE_NAME * sizeof(char));
		memset(dev_list[i], 0, MAX_DEVICE_NAME);
		memcpy(dev_list[i], friendly_name, strlen(friendly_name));
	}
	external_cb = cb;
	delete vc;
}

char *DSCapture::getDeviceNameById(unsigned int device_id)
{
	ASSERT_WITH_CODE((device_id < dev_count), "Error! Can't get name for this capture device", return NULL);
	return dev_list[device_id];
}

char **DSCapture::getDeviceList()
{
	return dev_list;
}

unsigned int DSCapture::getDeviceCount()
{
	return dev_count;
}

bool DSCapture::bind(unsigned int device_id)
{
	if(state != UNBINDED)
		return false;
	if(active_device_id > dev_count || device_id < 0)
	{
		return false;
	}
	state = BINDED;
	active_device_id = device_id;
	return true;
}

bool DSCapture::start()
{
	if(state != BINDED)
		return false;

	_read_mutex	= CreateMutex(NULL,	FALSE, NULL);
	vcap	= new VideoCapture(new CallbackHandler<DSCapture>(this, &DSCapture::DSCallback));
	vcap->Select(&(vcap->GetDevices()[active_device_id]));
	height	= vcap->getHeight();
	width	= vcap->getWidth();
	vcap->Start();
	state = RUNING;
	return true;
}

bool DSCapture::stop()
{
	if(state != RUNING)
		return false;
	CloseHandle(_read_mutex);
	vcap->Stop();
	delete vcap;
	state = BINDED;
	return true;
}