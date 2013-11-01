#include "channel_export.h"
#include <string.h>
#include <qdialog>
#include <qapplication>

#include "json.h"
#include "custom_rtmp_channel.h"
#include "gui_channel.h"
#include "settings.h"

using namespace std;


int type = CHANNEL_PLUGIN_TYPE;
int version = 100;
char name[] = PLUGIN_NAME;

__declspec(dllexport) int getVersion()
{
	return version;
}

__declspec(dllexport) int getType()
{
	return type;
}

__declspec(dllexport) const char* getName()
{
	return name;
}

__declspec(dllexport) const char* getImagePath()
{
    return "no_image";
}

//channel specific
__declspec(dllexport) void initializeEscape(EscapeCallFunc v_escape_call)
{
    Settings::load();
    initEscape(v_escape_call);
}

__declspec(dllexport) void start(CHANNEL_HANDLE handle)
{
    static_cast<CustomRtmpChannel*>(handle)->start();
}

__declspec(dllexport) void stop(CHANNEL_HANDLE handle)
{
    static_cast<CustomRtmpChannel*>(handle)->stop();
}

__declspec(dllexport) void broadcastFrame(CHANNEL_HANDLE handle, char *buf, unsigned int buf_len)
{
    static_cast<CustomRtmpChannel*>(handle)->broadcastFrame(buf, buf_len);
}

__declspec(dllexport) CHANNEL_HANDLE createInstance(char *channel_name)
{
    return new CustomRtmpChannel(channel_name);
}

__declspec(dllexport) void releaseInstance(CHANNEL_HANDLE obj)
{
    delete static_cast<CustomRtmpChannel*>(obj);
}

__declspec(dllexport) void edit(char *channel_name)
{
    CustomRTMPConfig *chennel_config = new CustomRTMPConfig(NULL, Qt::Dialog);
    chennel_config->setAttribute(Qt::WA_DeleteOnClose, true);
    chennel_config->edit(channel_name);
}

__declspec(dllexport) void rm(char *channel_name)
{
    CustomRTMPConfig *chennel_config = new CustomRTMPConfig(NULL, Qt::Dialog);
    chennel_config->setAttribute(Qt::WA_DeleteOnClose, true);
    chennel_config->remove(channel_name);
}

__declspec(dllexport) void create(void *owner)
{
    CustomRTMPConfig *channel_config = new CustomRTMPConfig((QWidget*)owner, Qt::Dialog);
    channel_config->setAttribute(Qt::WA_DeleteOnClose, true);
    channel_config->create();
}
