#ifndef MLS_SRC_H
#define MLS_SRC_H

#include <qobject.h>
#include <qthread>
#include <qmutex>

#include <string>
#include <set>

#include "global.h"
#include "smart_ptr.h"
#include "plugin.h"

typedef void* CAPTURE_HANDLE;

using namespace std;
typedef unsigned int uint;

class ISource: public QObject
{
Q_OBJECT
public:
	virtual ~ISource(void)
	{
	}
	void broadcastFrame(IplImage *data)
	{
		emit frameReady(data);
	}
	virtual void start() = 0;
	virtual void stop() = 0;
	virtual int getHeight() = 0;
	virtual int getWidth() = 0;
	virtual string getName() = 0;
	virtual void queueNextFrame(unsigned char* data) = 0;
signals:
	void frameReady(IplImage *p_rbuf);
};

class ICapture //its capture interface that we use in MLS
{
public:
	virtual ~ICapture(void)
	{}
	virtual unsigned int getDeviceId() = 0;
	virtual vector<string> listDevices() = 0;
	virtual void bind(unsigned int device_id) = 0;
};

class CaptureDevice: public ICapture, public ISource //concrete implementation of object for manage capture source
{
public:
	CaptureDevice(CapturePlugin *p_cap_plugin) :
			capture_handle(NULL), _bind_device_id(-1), _plugin(p_cap_plugin)
	{}
	virtual ~CaptureDevice()
	{
		_plugin->stop(capture_handle);
	}
//-----------ICapture implementation-----------
	virtual unsigned int getDeviceId();
	virtual vector<string> listDevices();
	virtual void bind(uint device_id);
	//-----------IMqsSrc implementation-----------
	virtual void start();
	virtual void stop();
	virtual int getHeight();
	virtual int getWidth();
	virtual void queueNextFrame(unsigned char* data);
	virtual string getName();
	string getPluginName(){ return _plugin->getName(); }
private:
	CAPTURE_HANDLE capture_handle;
	unsigned int _bind_device_id;
	CapturePlugin *_plugin;
};

class SrcManager
{
	//capture devices
public:
    static void unloadAllCapturePlugins();
	static void addCapturePlugin(string name, CapturePlugin *capture_plugin);
	static vector<string> getCapturePlugins();

	static void captureCallBack(CAPTURE_HANDLE handle, unsigned char *data,
			unsigned int height, unsigned int width);

	static ICapture *createCapture(string name);
	static ISource *createRegion();
	static map<CAPTURE_HANDLE, set<CaptureDevice*> > _active_capture_devices;
private:
	static map<string, CapturePlugin*> _capture_plugins; //map<plugin_name, ICapturePlugin*>
};

#endif
