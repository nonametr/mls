#pragma once

#include <time.h>
#include <stdio.h>

#define MAX_HANDLES_PER_DEVICE 16
#define MAX_DEVICE_NAME 255
#define CAPTURE_PLUGIN_TYPE 101

typedef void* CAPTURE_HANDLE;
typedef void* MLS_HANDLE;
typedef void (*CaptureCallBack)(CAPTURE_HANDLE handle, unsigned char *data, unsigned int height, unsigned int width);

#define traceerr( S, ... ) \
{ \
char __BUF__[32736]; \
sprintf_s( __BUF__, sizeof(__BUF__)-1, \
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

#define ASSERT_WITH_CODE(cond, msg, code) \
	if(!(cond)) \
{ \
	traceerr(msg); \
	code; \
}