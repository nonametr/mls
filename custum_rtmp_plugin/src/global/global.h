#ifndef MLS_H_
#define MLS_H_

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <windows.h>
#include <time.h>

typedef unsigned int uint32;

using namespace std;

struct Option
{
    Option(string v_visible_name, string v_value) : visible_name(v_visible_name), value(v_value)
    {}
    Option(){}
    string visible_name;
    string value;
};

typedef void* CHANNEL_HANDLE;

#define traceerr( S, ... ) \
{ \
char __BUF__[32736]; \
snprintf( __BUF__, sizeof(__BUF__)-1, \
"%s:%d %u [%s] " S, __FILE__, \
__LINE__, (unsigned int)time(NULL), \
__FUNCTION__, \
## __VA_ARGS__ ); \
if(errno == 0)\
printf("%s\n", __BUF__);\
else \
printf("%s, error: %s\n", __BUF__, strerror(errno));\
errno = 0;\
}

#define ASSERT(cond) if(!(cond)) traceerr("Error! Unknown error in mlslibx264 thread core!");
#define ASSERT_WITH_CODE(cond, msg, code) \
	if(!(cond)) \
{ \
	traceerr(msg); \
	code; \
}

#endif /* MLS_H_ */
