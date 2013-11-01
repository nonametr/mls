#ifndef ESCAPE_CALL_CLIENT_H
#define ESCAPE_CALL_CLIENT_H

#include <map>
#include <string>
#include <string.h>
#include "escape_call.h"

using namespace std;

extern EscapeCallFunc escape_call;
static void initEscape(EscapeCallFunc v_escape_call){ escape_call = v_escape_call; }

map<string, EscapeEncoder> getEncoders();
void updateChannels(string channel_name, string plugin_name, string encoder_name);

#endif // ESCAPE_CALL_CLIENT_H
