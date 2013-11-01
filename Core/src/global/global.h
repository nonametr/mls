#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>
#include <map>
#include <QIcon>
#include <time.h>
#include "json.h"
#include <stdio.h>
#include <string.h>

using namespace std;

typedef enum _GUIUpdateType
{
    BROADCASTS = 0,
    RESOLUTIONS,
    CONFIG,
    SCENES,
    WINDOW_SIZE,
    FPS,
    SCALE,
    PLUGINS,
    TRANSLATIONS,
    ALL,
    UPDATE_MAX
} GUIUpdate;

#if defined (_WIN32) || defined(_WIN64)
//#define strncasecmp _strnicmp
//#define isnan _isnan
//#define isinf _finite
//#define snprintf sprintf_s
#endif

extern unsigned int gl_last_error_code;
#define GL_CHECK_FOR_ERRORS() gl_last_error_code = (unsigned int)glGetError( ); if(gl_last_error_code != GL_NO_ERROR) { traceerr("OpenGl error #%u occupied", gl_last_error_code); }

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
#define tracelog( LVL, S, ... )\
{ \
if( 10 >= LVL ) \
{ \
char __BUF__[32736]; \
snprintf( __BUF__, sizeof(__BUF__)-1, \
"%s:%d [%s] " S, __FILE__, \
__LINE__, \
__FUNCTION__, \
## __VA_ARGS__ ); \
printf("%s, error: %s\n", __BUF__, strerror(errno));\
errno = 0;\
} \
}

#define ASSERT_WITH_CODE(cond, msg, code) \
	if(!(cond)) \
{ \
	traceerr(msg); \
	code; \
}
typedef unsigned int uint;

class Value;

typedef struct _Resolution
{
	_Resolution(string name, bool v_checked) :
			visible_name(name), is_checked(v_checked)
	{
	}
	string visible_name;
	bool is_checked;
} Resolution;

typedef struct _Image
{
    static void initImage(_Image *img, int w, int h)
    {
        img->width = w;
        img->height = h;
        img->imageSize = w * h * 3;
        img->imageData = new unsigned char[img->imageSize + 4];
    }
    static _Image* initImage(unsigned char *data, int w, int h)
    {
        _Image *img = new _Image;
        img->width = w;
        img->height = h;
        img->imageSize = w * h * 3;
        img->imageData = data;
        return img;
    }
    _Image() :
            width(0), height(0), imageSize(0), imageData(NULL)
    {
    }
    ~_Image()
    {
        if (imageData == NULL)
            delete[] imageData;
    }
    int width; /* Image width in pixels. */
    int height; /* Image height in pixels. */

    int imageSize;
    unsigned char *imageData; /* Pointer to aligned image data.         */
} Image;

typedef Image IplImage;

class Global
{
public:
	Global(void);
	~Global(void);

	void logError(string err_log_path, const char *str);
	void logTrace(string err_log_path, const char *str);
	void intToString(char * buf, int num);
	string intToString(int num);
	string int64ToString(long long int num);
	string floatToString(float num);
	uint strToInt(const char *str);
	string doubleToString(double num);
	vector<string> strSplit(const string &src, const string &sep);
	string readFile(string file_name);
	void writeFile(string file_name, string data);
	bool isFileExist(string file_name);
	string getVal(string key);
	void saveScenes();
	void loadScenes();

	map<string, map<string, string> > &getEncoders()
	{
		return _encoders;
	}
	map<string, map<string, string> > &getChannels()
	{
		return _channels;
	}
	map<string, map<string, map<string, Value> > > &getScenes();
	vector<Resolution> &getResolutions()
	{
		return _resolutions;
	}
	vector<string> &getFps()
	{
		return _fps;
	}
	vector<string> &getScale()
	{
		return _scale;
	}
	map<string, string> &getConfig()
	{
		return _config;
	}
	void loadDefaultResolutions();
	void loadDefaultFps();
	void loadDefaultScale();
	JSONValue serialize();
	bool deserialize(JSONValue &);
private:
	JSONValue* serializeCfgMap(map<string, map<string, string> > &cfg_map);
	map<string, map<string, string> > deserializeCfgMap(JSONValue *j_val);
	map<string, map<string, string> > _encoders; //map<encoder name, metadata>
	map<string, map<string, string> > _channels; //map<transport name, metadata>
	map<string, map<string, map<string, Value> > > _scenes; //map<scene_name, map<source_name, source_data> >
	map<string, string> _config;
	vector<Resolution> _resolutions; //map<resolution string, is_enabled>
	vector<string> _fps;
	vector<string> _scale;
};

extern Global global;

#endif
