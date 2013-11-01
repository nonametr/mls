#include "custom_rtmp_channel.h"

void CustomRtmpChannel::onFinishFFMPEG(int ecode)
{
    traceerr("\r\n\r\nBroadcast terminated!\r\n");
    _ffmpeg->deleteLater();
}

void CustomRtmpChannel::onFFmpegSay()
{
    traceerr("%s", QString(_ffmpeg->readAllStandardOutput()).toStdString().c_str());
}

void CustomRtmpChannel::start()
{
    this->setup();
    traceerr("\r\n\r\nStarting FFMPEG instance...\r\nBroadcast will start in a few moments!\r\n");
    _ffmpeg->start(_ffmpeg_exec_str.c_str());

    if(!_ffmpeg->waitForStarted(30000))
    {
        traceerr("\r\nFailed to start FFMPEG broadcast!");
        return;
    }
    _write_pipe->start();
}

void CustomRtmpChannel::broadcastFrame(char *buf, unsigned int buf_len)
{
    _write_pipe->send(buf, buf_len);
}

void CustomRtmpChannel::stop()
{
    _write_pipe->stop();
    _ffmpeg->deleteLater();
    _proxy->deleteLater();
    _write_pipe->deleteLater();
}

bool CustomRtmpChannel::setup()
{
    char buf[2048] = {"\0"};

    ASSERT_WITH_CODE(_uniq_channel_id.empty(), "Encoder already setup!", return false);

    sprintf (buf, "%u", time(NULL));
    _uniq_channel_id = buf;

    string write_pipe_name = "wbr_" + _uniq_channel_id;
    _write_pipe = new WritePipe(write_pipe_name);

    //map<string, string> encoder_ops = global.getEncoders()[ops["encoder"]];
    //_proxy = new RtmpProxy(options["rtmp_url"].value, 1935, 5557);
    //snprintf(buf, 2048, "ffmpeg.exe -y -re -f h264 -i \\\\.\\pipe\\%s -c:v copy -an -bufsize 4000 -tune zerolatency -f flv -re rtmp://127.0.0.1:5557/%s", write_pipe_name.c_str(), options["stream_name"].value.c_str());

    //snprintf(buf, 2048, "ffmpeg.exe -re -y -f h264 -i \\\\.\\pipe\\%s -c:v copy -an -f flv -re rtmp://127.0.0.1:5557/%s", write_pipe_name.c_str(), ops["Stream Name:"].c_str());
    //snprintf(buf, 2048, "ffmpeg.exe -re -y -f h264 -i \\\\.\\pipe\\%s -c:v copy -f dshow -i audio=\"%s\" -acodec %s -ab %s -ar %s -f flv -re rtmp://127.0.0.1:5557/%s", write_pipe_name.c_str(), encoder_ops["audio_source"].c_str(), encoder_ops["audio_codec"].c_str(), encoder_ops["audio_bitrate"].c_str(), encoder_ops["audio_format"].c_str(), ops["Stream Name:"].c_str());

    traceerr("starting ffmpeg, command => %s", buf);
    _ffmpeg_exec_str = string(buf);

    _ffmpeg = new QProcess;
    _ffmpeg->setProcessChannelMode(QProcess::MergedChannels);

    connect(_ffmpeg, SIGNAL(finished(int)), this, SLOT(onFinishFFMPEG(int)));
    connect(_ffmpeg, SIGNAL(readyReadStandardOutput()), this, SLOT(onFFmpegSay()));
    connect(_ffmpeg, SIGNAL(readyReadStandardError()), this, SLOT(onFFmpegSay()));

    return true;
}
