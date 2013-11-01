/*
 * config.h
 *
 *  Created on: 19.02.2013
 *      Author: nonametr
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include "global.h"
#include <QtSql/qsql.h>
#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlquery.h>
#include <QtSql/qsqlrecord.h>
#include <QtSql/qsqlfield.h>
#include <QtSql/qsqlerror.h>

#include <qvariant.h>

using namespace std;

class Settings;
extern Settings *settings;

#define ENCODER_TABLE_CREATE_V1  	"CREATE TABLE \"encoder\" (name TEXT PRIMARY KEY, audio_bitrate INTEGER, audio_encoder TEXT, audio_format INTEGER, audio_source TEXT, video_bitrate INTEGER, video_buffer INTEGER, video_encoder_plugin TEXT, video_preset INTEGER, video_quality INTEGER)"
#define CHANNEL_TABLE_CREATE_V1  	"CREATE TABLE \"channel\" (name TEXT PRIMARY KEY, description TEXT, settings TEXT, channel_plugin TEXT, encoder TEXT REFERENCES \"encoder\" (name) ON DELETE CASCADE ON UPDATE CASCADE)"
#define SCENE_TABLE_CREATE_V1	 	"CREATE TABLE \"scene\" (name TEXT PRIMARY KEY, enabled INTEGER, active INTEGER)"
#define SURFACE_TABLE_CREATE_V1 	"CREATE TABLE \"surface\" (name TEXT PRIMARY KEY, x_pos REAL, y_pos REAL, x_scale REAL, y_scale REAL, x_angle REAL, y_angle REAL, z_angle REAL, left_cut REAL, right_cut REAL, top_cut REAL, bottom_cut REAL, keep_aspect REAL, red REAL, green REAL, blue REAL, alfa REAL, contrast REAL, brightness REAL, red_chroma REAL, green_chroma REAL, blue_chroma REAL, red_tolerance_chroma REAL, blue_tolerance_chroma REAL, green_tolerance_chroma REAL, chroma_enabled REAL, capture_name TEXT, capture_device_id INTEGER, scene TEXT REFERENCES \"scene\" (name) ON DELETE CASCADE ON UPDATE CASCADE)"
#define PROPERTY_TABLE_CREATE_V1 	"CREATE TABLE \"property\" (name TEXT PRIMARY KEY, value TEXT)"
#define RESOLUTION_TABLE_CREATE_V1 	"CREATE TABLE \"resolution\" (name TEXT PRIMARY KEY, width INTEGER, height INTEGER, enabled INTEGER)"
#define FPS_TABLE_CREATE_V1			"CREATE TABLE \"fps\" (name TEXT PRIMARY KEY, fps INTEGER, enabled INTEGER)"
#define SCALE_TABLE_CREATE_V1 		"CREATE TABLE \"scale\" (name TEXT PRIMARY KEY, scale TEXT, enabled INTEGER)"

#define CHECK_ENCODER_TABLE_INTEGRITY_V1	"SELECT count(*) AS is_correct FROM sqlite_master WHERE name = 'encoder' 	AND sql LIKE '" ENCODER_TABLE_CREATE_V1 "'"
#define CHECK_CHANNEL_TABLE_INTEGRITY_V1	"SELECT count(*) AS is_correct FROM sqlite_master WHERE name = 'channel' 	AND sql LIKE '" CHANNEL_TABLE_CREATE_V1 "'"
#define CHECK_SCENE_TABLE_INTEGRITY_V1		"SELECT count(*) AS is_correct FROM sqlite_master WHERE name = 'scene' 		AND sql LIKE '" SCENE_TABLE_CREATE_V1 "'"
#define CHECK_SURFACE_TABLE_INTEGRITY_V1	"SELECT count(*) AS is_correct FROM sqlite_master WHERE name = 'surface' 	AND sql LIKE '" SURFACE_TABLE_CREATE_V1 "'"
#define CHECK_PROPERTY_TABLE_INTEGRITY_V1	"SELECT count(*) AS is_correct FROM sqlite_master WHERE name = 'property' 	AND sql LIKE '" PROPERTY_TABLE_CREATE_V1 "'"
#define CHECK_RESOLUTION_TABLE_INTEGRITY_V1 "SELECT count(*) AS is_correct FROM sqlite_master WHERE name = 'resolution' AND sql LIKE '" RESOLUTION_TABLE_CREATE_V1 "'"
#define CHECK_FPS_TABLE_INTEGRITY_V1 		"SELECT count(*) AS is_correct FROM sqlite_master WHERE name = 'fps' 		AND sql LIKE '" FPS_TABLE_CREATE_V1 "'"
#define CHECK_SCALE_TABLE_INTEGRITY_V1 		"SELECT count(*) AS is_correct FROM sqlite_master WHERE name = 'scale' 		AND sql LIKE '" SCALE_TABLE_CREATE_V1 "'"

#define GET_ENCODER 	"SELECT * FROM encoder WHERE name LIKE '%s'"
#define GET_CHENNEL 	"SELECT * FROM channel WHERE name LIKE '%s'"
#define GET_SCENE 		"SELECT * FROM scene WHERE name LIKE '%s'"
#define GET_SURFACE 	"SELECT * FROM surface WHERE name LIKE '%s'"
#define GET_PROPERTY	"SELECT * FROM property WHERE name LIKE '%s'"
#define GET_RESOLUTION 	"SELECT * FROM resolution WHERE name LIKE '%s'"
#define GET_FPS 		"SELECT * FROM fps WHERE name LIKE '%s'"
#define GET_SCALE 		"SELECT * FROM scale WHERE name LIKE '%s'"

#define GET_ALL "%"
#define RESET_TO_DEFULT_RESOLUTIONS "DELETE FROM resolution; INSERT INTO resolution SELECT * FROM default_resolution"
#define DISABLE_ALL_RESOLUTIONS "UPDATE resolution SET enabled = 0"
#define ENABLE_ALL_RESOLUTIONS "UPDATE resolution SET enabled = 1"

class Settings
{
public:
	Settings();
	virtual ~Settings();

    static void load()
    {
        if(settings)
            return;
        else
            settings = new Settings;
    }
	template<typename... Args>
	QSqlQuery query(string query_templ, Args... args)
	{
		char sql_buf[2048] = {"\0"};
		QSqlQuery sql_query(db);

		snprintf(sql_buf, 2048, query_templ.c_str(), args...);
		QString spliter(sql_buf);
		QStringList sql_list = spliter.split(";");

		for(unsigned int i = 0; i < sql_list.size(); ++i)
		{
			bool res = sql_query.exec(sql_list[i]);
			ASSERT_WITH_CODE(res == true, "Error! SQL query failed!", traceerr("SQL error: %s; \r\nSQL query text = %s", sql_query.lastError().text().toStdString().c_str(), sql_buf); return QSqlQuery());
		}
		sql_query.next();
		return sql_query;
	}
	QSqlQuery prepareQuery(QString sql)
	{
		QSqlQuery query(db);
		query.prepare(sql);
		return query;
	}

private:
	void checkIntegrity();
	void loadDefault();
	QSqlDatabase db;
};

#endif /* CONFIG_H_ */
