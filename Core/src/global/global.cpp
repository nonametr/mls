#include "global.h"
#include "value.h"
#include <time.h>
#include "json.h"

Global global;
unsigned int gl_last_error_code;

void Global::loadDefaultFps()
{
	_fps.push_back("10 fps");
	_fps.push_back("15 fps");
	_fps.push_back("25 fps");
	_fps.push_back("30 fps");
	_fps.push_back("50 fps");
	_fps.push_back("60 fps");
}
void Global::loadDefaultScale()
{
	_scale.push_back("10%");
	_scale.push_back("20%");
	_scale.push_back("30%");
	_scale.push_back("40%");
	_scale.push_back("50%");
	_scale.push_back("60%");
	_scale.push_back("70%");
	_scale.push_back("80%");
	_scale.push_back("90%");
	_scale.push_back("100%");
}
void Global::loadDefaultResolutions()
{
	_resolutions.clear();
	_resolutions.push_back(Resolution("176x144-QCIF(11:9)", false));
	_resolutions.push_back(Resolution("180x144-PAL D-1(video)(5:4)", false));
	_resolutions.push_back(Resolution("240x180-PAL(video)(4:3)", false));
	_resolutions.push_back(Resolution("240x192-PAL D-1(video)(5:4)", false));
	_resolutions.push_back(Resolution("256x188-70mm IMAX(cine)(64:47)", false));
	_resolutions.push_back(Resolution("256x256-6cmx6cm(2 1/4\" x 2 1/4)(slide)(11:9)", false));
	_resolutions.push_back(Resolution("320x180-NTSC HDTV(16:9)", true));
	_resolutions.push_back(Resolution("320x200-(8:5)", false));
	_resolutions.push_back(Resolution("320x240-(4:3)", false));
	_resolutions.push_back(Resolution("320x400-(4:5)", false));
	_resolutions.push_back(Resolution("320x480-(2:3)", false));
	_resolutions.push_back(Resolution("352x288-CIF(11:9)", false));
	_resolutions.push_back(Resolution("360x200-(9:5)", false));
	_resolutions.push_back(Resolution("360x240-NTSC DV(video)50%, VistaVision, 35mm(24mmx36mm)(slide)(3:2)", false));
	_resolutions.push_back(Resolution("360x288-PAL D-1(video) 50% (5:4)", false));
	_resolutions.push_back(Resolution("360x400-(9:10)", false));
	_resolutions.push_back(Resolution("360x480-(3:4)", false));
	_resolutions.push_back(Resolution("360x200-(8:5)", false));
	_resolutions.push_back(Resolution("400x300-(4:3)", true));
	_resolutions.push_back(Resolution("440x200-700mm Panavision(cine)(11:5)", false));
	_resolutions.push_back(Resolution("480x360-PAL(video)(4:3)", false));
	_resolutions.push_back(Resolution("480x384-PAL D-1(video)(5:4)", false));
	_resolutions.push_back(Resolution("512x384-4\"x5\" or 8\"x10\"(slide) (4:3)", false));
	_resolutions.push_back(Resolution("640x360-(16:9)", true));
	_resolutions.push_back(Resolution("640x400-(8:5)", false));
	_resolutions.push_back(Resolution("640x480-(4:3)", true));
	_resolutions.push_back(Resolution("720x480-NTSC DV(video)(3:2)", false));
	_resolutions.push_back(Resolution("720x576-PAL D-1(video)(5:4)", false));
	_resolutions.push_back(Resolution("768x432-(16:9)", false));
	_resolutions.push_back(Resolution("768x576-PAL(video)(4:3)", false));
	_resolutions.push_back(Resolution("800x600-(4:3)", true));
	_resolutions.push_back(Resolution("854x480-WVGA(427:240)", false));
	_resolutions.push_back(Resolution("960x600-(8:5)", false));
	_resolutions.push_back(Resolution("1024x436-35mm Anamorphic(2.35:1)", false));
	_resolutions.push_back(Resolution("1088x612-(16:9)", false));
	_resolutions.push_back(Resolution("1120x640-35mm(cine)(7:4)", false));
	_resolutions.push_back(Resolution("1280x720-HDTV(video)(16:9)",  true));
	_resolutions.push_back(Resolution("1280:800-WXGA(16:10)", true));
	_resolutions.push_back(Resolution("1280x960-SXGA-(UVGA)(4:3)", true));
	_resolutions.push_back(Resolution("1366x768-HD(16:9)", true));
	_resolutions.push_back(Resolution("1440x900-WXGA+(16:10)", true));
	_resolutions.push_back(Resolution("1600x900-HD+(16:9)", true));
	_resolutions.push_back(Resolution("1600x1200-UXGA(4:3)", true));
	_resolutions.push_back(Resolution("1680x1050-WSXGA+(16:10)", true));
	_resolutions.push_back(Resolution("1920x1080-FullHD(16:9)", true));
	_resolutions.push_back(Resolution("1920x1200-WUXGA(16:10)", false));
	_resolutions.push_back(Resolution("2560x1440-WQHD(16:9)", false));
	_resolutions.push_back(Resolution("2560x1600-WQXGA(16:10)", false));
}
Global::Global(void)
{
	_config["resolution"] = "640x480-(4:3)";
	_config["fps"] = "25 fps";
	_config["scale"] = "100%";
	_config["os_type"] = "windows";
	_config["capture_method"] ="DirectShow";
	_config["prefered_encoder"] = "AMD";

	loadDefaultResolutions();
	loadDefaultFps();
	loadDefaultScale();
}
Global::~Global(void)
{
}
map<string, map<string, map<string, Value> > > &Global::getScenes()
{ 
	return _scenes; 
}
void Global::saveScenes()
{
	JSONObject j_scenes;
	for(map<string, map<string, map<string, Value> > >::iterator it_scene = _scenes.begin(); it_scene != _scenes.end(); ++it_scene)
	{
		JSONObject j_sources;
		for(map<string, map<string, Value> >::iterator it_source = it_scene->second.begin(); it_source != it_scene->second.end(); ++it_source)
		{
			JSONObject j_source_settings;
			for(map<string, Value>::iterator it_source_settings = it_source->second.begin(); it_source_settings != it_source->second.end(); ++it_source_settings)
			{
				j_source_settings[it_source_settings->first] = new JSONValue(it_source_settings->second.toDouble());
			}
			j_sources[it_source->first] = new JSONValue(j_source_settings);
		}
		j_scenes[it_scene->first] = new JSONValue(j_sources);
	}
	string j_scenes_str = JSONValue(j_scenes).stringify();
	global.writeFile("./config/scenes.cfg", j_scenes_str);
}
void Global::loadScenes()
{
	string sz_scenes = global.readFile("./config/scenes.cfg");
	JSONValue *j_val = JSON::parse(sz_scenes.c_str());
	ASSERT_WITH_CODE(j_val != NULL, "Config file corrupted!...", return);
	JSONObject j_scenes_obj = j_val->asObject();

	_scenes.clear();
	for(JSONObject::iterator it_scene = j_scenes_obj.begin(); it_scene != j_scenes_obj.end(); ++it_scene)
	{
		map<string, map<string, Value> > sources;
		JSONObject j_sources_obj = it_scene->second->asObject();
		for(JSONObject::iterator it_sources = j_sources_obj.begin(); it_sources != j_sources_obj.end(); ++it_sources)
		{
			map<string, Value> source_settings;
			JSONObject j_source_settings_obj = it_sources->second->asObject();
			for(JSONObject::iterator it_source_settings = j_source_settings_obj.begin(); it_source_settings != j_source_settings_obj.end(); ++it_source_settings)
			{
				Value vec(it_source_settings->second->asNumber());
				source_settings[it_source_settings->first] = vec;
			}
			sources[it_sources->first] = source_settings;
		}
		_scenes[it_scene->first] = sources;
	}
	delete j_val;
}
bool Global::isFileExist(string file_name)
{
	FILE * pFile;
	pFile = fopen ( file_name.c_str() , "rt+" ); 
	if(pFile == NULL)
		return false;
	fclose(pFile);
	return true;
}
void Global::writeFile(string file_name, string data)
{
	FILE * pFile;
	pFile = fopen ( file_name.c_str() , "wt+" );
	ASSERT_WITH_CODE(pFile != NULL, "Error! Can't write file!", return);
	fwrite (data.c_str() , 1 , sizeof(char)*data.length() , pFile );
	fclose (pFile);
}
string Global::readFile(string file_name)
{
	FILE * pFile;
	long int file_size;
	char * buffer;
	string result;

	pFile = fopen ( file_name.c_str() , "rt+" );
	ASSERT_WITH_CODE(pFile != NULL, "Configuration read error", return "");
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	file_size = ftell (pFile);
	rewind (pFile);
	// allocate memory to contain the whole file:
	buffer = (char*) calloc (sizeof(char), file_size);
	// copy the file into the buffer:
	fread (buffer, 1, file_size, pFile);
	/* the whole file is now loaded in the memory buffer. */
	result = string(buffer, file_size);

	fclose (pFile);
	free (buffer);

	return result;
}
vector<string> Global::strSplit ( const string &src, const string &sep )
{
	int end_pos = 0;
	int begin_pos = 0;
	vector<string> result;

	while( (end_pos = src.find(sep, begin_pos)) != string::npos )
	{
		result.push_back(src.substr(begin_pos, end_pos - begin_pos));
		begin_pos = end_pos + sep.length();
	}
	result.push_back(src.substr(begin_pos));
	return result;
}
JSONValue* Global::serializeCfgMap(map<string, map<string, string> > &cfg_map)
{
	JSONObject j_gl_obj;
	for(map<string, map<string, string> >::iterator it_gl = cfg_map.begin(); it_gl != cfg_map.end(); ++it_gl)
	{
		JSONObject j_obj;
		for(map<string, string>::iterator it = it_gl->second.begin(); it != it_gl->second.end(); ++it)
		{
			j_obj[it->first] = new JSONValue(it->second);
		}
		j_gl_obj[it_gl->first] = new JSONValue(j_obj);
	}
	return new JSONValue(j_gl_obj);
}
map<string, map<string, string> > Global::deserializeCfgMap(JSONValue *j_val)
{
	map<string, map<string, string> > result;
	JSONObject j_json_obj = j_val->asObject();

	for(JSONObject::iterator it_gl = j_json_obj.begin(); it_gl != j_json_obj.end(); ++it_gl)
	{
		JSONObject j_obj = it_gl->second->asObject();
		for(JSONObject::iterator it = j_obj.begin(); it != j_obj.end(); ++it)
		{
			result[it_gl->first][it->first] = it->second->getString();
		}
	}
	return result;
}
JSONValue Global::serialize()
{
	string json_result;
	JSONObject json;
	json["encoders"] = serializeCfgMap(_encoders);
	json["channels"] = serializeCfgMap(_channels);

	JSONObject j_obj_config;
	for(map<string, string>::iterator it = _config.begin(); it != _config.end(); ++it)
	{
		j_obj_config[it->first] = new JSONValue(it->second);
	}
	json["config"] = new JSONValue(j_obj_config);
	return JSONValue(json);
}
bool Global::deserialize(JSONValue &j_json_val)
{
	JSONObject j_json_obj = j_json_val.asObject();

	_encoders = deserializeCfgMap(j_json_obj["encoders"]);
	_channels = deserializeCfgMap(j_json_obj["channels"]);

	JSONObject j_obj_config = j_json_obj["config"]->asObject();
	for(JSONObject::iterator it = j_obj_config.begin(); it != j_obj_config.end(); ++it)
	{
		_config[it->first] = it->second->getString();
	}
	return true;
}

string Global::getVal(string key)
{
	map<string, string>::iterator it = _config.find(key);
	ASSERT_WITH_CODE(it != _config.end(), "Error! Global variable not exist!", return "");
	return it->second;
}
void Global::intToString ( char * buf, int num )
{
    sprintf ( buf,"%u",num );
}
string Global::intToString ( int num )
{
	char buf[64] = {"\0"};
    snprintf ( buf, 64, "%u",num );
    return buf;
}
string Global::int64ToString ( long long int num )
{
    char buf[128] = {"\0"};
    snprintf ( buf, 128, "%llu",num );
    return buf;
}
string Global::floatToString ( float num )
{
    char buf[128] = {"\0"};
    snprintf ( buf, 128, "%f",num );
    return buf;
}
uint Global::strToInt ( const char *str )
{
    uint res;
    sscanf ( str, "%u", &res );
    return res;
}
string Global::doubleToString ( double num )
{
    char buf[128];
    snprintf ( buf, 128, "%f",num );
    return buf;
}
void Global::logError ( string err_log_path, const char *str )
{
	FILE *logfile;
	if ( ( logfile = fopen ( err_log_path.c_str(), "a+" ) ) )
	{
		time_t	now;
		struct tm	*ptm;

		time ( &now );
		ptm = localtime ( &now );

		fprintf ( logfile, "%04d-%02d-%02d %02d:%02d:%02d %s\n",
			ptm->tm_year+1900, ptm->tm_mon+1, ptm->tm_mday,
			ptm->tm_hour, ptm->tm_min, ptm->tm_sec, str );
		fclose ( logfile );
	}
}

void Global::logTrace ( string trace_log_path, const char *str )
{
	FILE *logfile;
	if ( ( logfile = fopen ( trace_log_path.c_str(), "a+" ) ) )
	{
		time_t	now;
		struct tm	*ptm;

		time ( &now );
		ptm = localtime ( &now );

		fprintf ( logfile, "%04d-%02d-%02d %02d:%02d:%02d %s\n",
			ptm->tm_year+1900, ptm->tm_mon+1, ptm->tm_mday,
			ptm->tm_hour, ptm->tm_min, ptm->tm_sec, str );
		fclose ( logfile );
	}
}
