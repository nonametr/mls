#include "escape_call_client.h"

EscapeCallFunc escape_call = NULL;

map<string, EscapeEncoder> getEncoders()
{
    map<string, EscapeEncoder> result;
    int encoders_count;
    EscapeEncoder *escape_encoders;

    escape_call(ESCAPE_GET_ENCODERS, (void**)&escape_encoders, encoders_count);

    for(int i = 0; i < encoders_count; ++i)
    {
        result[escape_encoders[i].name] = escape_encoders[i];
    }
    delete []escape_encoders;
    return result;
}

void updateChannels(string channel_name, string plugin_name, string encoder_name)
{
    int escape_size = sizeof(EscapeUpdateChannel);
    EscapeUpdateChannel *escape_update_channel = new EscapeUpdateChannel;
    memset(escape_update_channel, 0, sizeof(EscapeUpdateChannel));
    memcpy(escape_update_channel->channel_name, channel_name.c_str(), channel_name.length());
    memcpy(escape_update_channel->encoder_name, encoder_name.c_str(), encoder_name.length());
    memcpy(escape_update_channel->plugin_name, plugin_name.c_str(), plugin_name.length());
    escape_call(ESCAPE_UPDATE_CHANNEL, (void**)&escape_update_channel, escape_size);
}

