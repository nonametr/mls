#ifndef RTMP_CHANNEL_H
#define RTMP_CHANNEL_H
/*
#include "ichannel.h"
#include <string>
#include "write_pipe.h"
#include <qprocess.h>
#include "rtmp_proxy.h"

using namespace std;

class RTMPChannel : public IChannel
{
	Q_OBJECT
public:
	static IChannel	*create();
	vector<string> getConfigFields();

	virtual void start();
	virtual void stop();
	virtual bool setup(map<string, string> ops);

	virtual ~RTMPChannel(void){}
private:
	QProcess *_ffmpeg;
	RtmpProxy *_proxy;
	WritePipe *_write_pipe;
	string _uniq_channel_id;
	string _ffmpeg_exec_str;
    RTMPChannel(void) : _ffmpeg(NULL), _write_pipe(NULL), _proxy(NULL) {}
public slots:
	void onFFmpegSay();
	void onFinishFFMPEG(int ecode);
	void onFrameReady(char *buf, unsigned int buf_len);
};
*/
#endif
