#pragma once

#include "video_capture_ds.h"
#include "global.h"

class DSCapture
{
	enum CAPTURE_STATE { UNBINDED, BINDED, RUNING };
public:
	DSCapture();
	DSCapture(int device_id);
	virtual ~DSCapture(void);
	void DSCallback(unsigned char* data, int len, int bpp);
	bool bind(unsigned int device_id);
	bool start();
	bool stop();
	void queueNextFrame(unsigned char *data_buf);
	int getHeight(){ return vcap->getHeight(); }
	int getWidth(){ return vcap->getWidth(); }

	static char *getDeviceNameById(unsigned int device_id);
	static char **getDeviceList();
	static unsigned int getDeviceCount();
	static void initialize(CaptureCallBack cb);

	static char** dev_list;
	static int dev_count;
	static CaptureCallBack external_cb;
private:
	CAPTURE_STATE state;
	int active_device_id;
	unsigned char *current_frame_ptr;
	unsigned char *extern_data_ptr;
	unsigned int width;
	unsigned int height;
	HANDLE _read_mutex;
	VideoCapture *vcap;
};

