#ifndef MLS_CAPTURE_H
#define MLS_CAPTURE_H
/*
#include "source.h"
#include "global.h"
#include "smart_ptr.h"
#include <QThread>
#include <QMutex>

class ICapture//its capture interface that we use in MLS
{
public:
  virtual ~ICapture(void){}
  virtual unsigned int getDeviceId() = 0;
  virtual vector<string> listDevices() = 0;
  virtual void bind(unsigned int device_id) = 0;
};

class ICapturePlugin//its capture interface that external library should implement for us
{
public:
  typedef void (*CBCapturePlugin)(CAPTURE_HANDLE handle, unsigned char *data, unsigned int height, unsigned int width);

  virtual char *getName(unsigned int device_id) = 0;
  virtual char *getPluginName() = 0;
  virtual char **getDeviceList() = 0;
  virtual unsigned int getDeviceCount() = 0;
  virtual bool start(CAPTURE_HANDLE handle, unsigned int device_id, CBCapturePlugin cb) = 0;
  virtual bool stop(unsigned int device_id) = 0;
};

class MlsCapture : public ICapture, public IMqsSrc
{
public:
  MlsCapture(ICapturePlugin *p_cap_plugin) : running(false), _bind_device_id(-1), _plugin(p_cap_plugin){}
  virtual ~MlsCapture(){}
//-----------ICapture implementation-----------
  virtual unsigned int getDeviceId();
  virtual vector<string> listDevices();
  virtual void bind(uint device_id);
  //-----------IMqsSrc implementation-----------
  virtual void start();
  virtual void stop();
  virtual string getName();
private:

  bool running;
  unsigned int _bind_device_id;
  ICapturePlugin *_plugin;
};
*/
#endif
