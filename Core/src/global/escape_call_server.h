#ifndef ESCAPE_CALL_SERVER_H
#define ESCAPE_CALL_SERVER_H

#include "escape_call.h"
#include <string>

using namespace std;

class EscapeCallServer
{
public:
    static void escapeCallback(int escape_call_id, void** data_out, int &data_out_size);
    EscapeCallServer();
};

#endif // ESCAPE_CALL_SERVER_H
