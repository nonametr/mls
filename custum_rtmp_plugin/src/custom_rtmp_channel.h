#ifndef CUSTOM_RTMP_CHANNEL_H
#define CUSTOM_RTMP_CHANNEL_H

#include <map>
#include <string>
#include <QObject>
#include <QProcess>

#include "rtmp_proxy.h"
#include "write_pipe.h"
#include "read_pipe.h"
#include "global.h"

using namespace std;

class CustomRtmpChannel : public QObject
{
    Q_OBJECT
public:
    CustomRtmpChannel(string v_channel_name) : channel_name(v_channel_name)
    {}
    virtual ~CustomRtmpChannel(){}

    void broadcastFrame(char *buf, unsigned int buf_len);
    void start();
    void stop();
private:
    bool setup();
    QProcess *_ffmpeg;
    RtmpProxy *_proxy;
    WritePipe *_write_pipe;
    string _uniq_channel_id;
    string _ffmpeg_exec_str;
    string channel_name;
public slots:
    void onFFmpegSay();
    void onFinishFFMPEG(int ecode);
};

#endif // CUSTOM_RTMP_CHANNEL_H
