#ifndef MLS_ICHANNEL_H
#define MLS_ICHANNEL_H

#include <qobject.h>
#include <string>
#include "json.h"
#include "ichannel.h"
#include "irender_widget.h"
#include "plugin.h"

class MlsMain;
using namespace std;

typedef void* PLUGIN_CHANNEL_HANDLE;

class IChannel : public QObject
{
	Q_OBJECT
public:
	virtual void start() = 0;
    virtual void stop() = 0;
    virtual void configure() = 0;
public slots:
	virtual void onFrameReady(char *buf, unsigned int buf_len) = 0;
};

class Channel : public IChannel
{
    Q_OBJECT
public:
    Channel(string user_defined_channel_name, ChannelPlugin *channel_plugin);
    virtual ~Channel();

    virtual void start();
    virtual void stop();
public slots:
    virtual void onFrameReady(char *buf, unsigned int buf_len);
private:
    ChannelPlugin *_plugin;
    PLUGIN_CHANNEL_HANDLE _handle;
};

class ChannelManager
{
public:
    static void unloadAll();
    static bool addPlugin(string channel_type_name, ChannelPlugin *channel_plugin);

    static bool edit(string user_defined_channel_name);
    static bool remove(string user_defined_channel_name);
    static bool create(string channel_type, QWidget *owner);

    static void startBroadcast(string channel_name, MlsMain *broadcast_source){}
    static void stopBroadcast(string channel_name){}
    static vector<string> getSuportedPlugins();
    static ChannelPlugin *getPluginByChannelName(string channel_name);
    static ChannelPlugin *getPlugin(string channel_type);
private:
    static map<string, ChannelPlugin *> _registered_channel_types;
    static map<string, IChannel*> _active_channels;
};

#endif
