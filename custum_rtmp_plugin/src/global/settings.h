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

#include <qstringlist.h>
#include <qvariant.h>

using namespace std;

class Settings;
extern Settings *settings;

#define CUSTOM_RTMP_CHANNEL_TABLE_CREATE_V1  	"CREATE TABLE \"custom_rtmp_channel\" (name TEXT PRIMARY KEY, description TEXT, rtmp_url TEXT, app_link TEXT, encoder TEXT)"
#define CHECK_CUSTOM_RTMP_CHANNEL_TABLE_INTEGRITY_V1	"SELECT count(*) AS is_correct FROM sqlite_master WHERE name = 'custom_rtmp_channel' 	AND sql LIKE '" CUSTOM_RTMP_CHANNEL_TABLE_CREATE_V1 "'"

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
