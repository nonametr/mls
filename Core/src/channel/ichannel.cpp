#include "ichannel.h"
#include "rtmp_channel.h"
#include "local_recording.h"
#include "iencoder.h"
#include "gui_main.h"

#include "settings.h"

map<string, ChannelPlugin*> ChannelManager::_registered_channel_types = map<string, ChannelPlugin*>();
map<string, IChannel*> ChannelManager::_active_channels = map<string, IChannel*>();

bool ChannelManager::edit(string user_defined_channel_name)
{
    getPluginByChannelName(user_defined_channel_name)->edit((char*)user_defined_channel_name.c_str());
    return true;
}

bool ChannelManager::remove(string user_defined_channel_name)
{
    return true;
}

bool ChannelManager::create(string channel_type, QWidget *owner)
{
    getPlugin(channel_type)->create(owner);
    return true;
}

void ChannelManager::unloadAll()
{

}

bool ChannelManager::addPlugin(string channel_type_name, ChannelPlugin *channel_plugin)
{
    map<string, ChannelPlugin*>::iterator it = _registered_channel_types.find(channel_type_name);
    if(it != _registered_channel_types.end())//this name already reserved by other channel?
        return false;

    _registered_channel_types[channel_type_name] = channel_plugin;
    return true;
}

vector<string> ChannelManager::getSuportedPlugins()
{
    vector<string> result;
    for(map<string, ChannelPlugin*>::iterator it = _registered_channel_types.begin(); it != _registered_channel_types.end(); ++it)
    {
        result.push_back(it->first);
    }
    return result;
}

ChannelPlugin *ChannelManager::getPluginByChannelName(string channel_name)
{
    QSqlRecord channel_rec = settings->query("SELECT channel_plugin FROM channel WHERE name = '%s'", channel_name.c_str()).record();
    string channel_type = channel_rec.value("channel_plugin").toString().toStdString();
    return getPlugin(channel_type);
}

ChannelPlugin *ChannelManager::getPlugin(string channel_type)
{
    return _registered_channel_types[channel_type];
}

Channel::Channel(string user_defined_channel_name, ChannelPlugin *channel_plugin)
{

}

Channel::~Channel()
{

}

void Channel::start()
{

}

void Channel::stop()
{

}

void Channel::onFrameReady(char *buf, unsigned int buf_len)
{

}
