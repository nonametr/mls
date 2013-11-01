/*
 * config.cpp
 *
 *  Created on: 19.02.2013
 *      Author: nonametr
 */

#include "settings.h"

Settings *settings = NULL;

Settings::Settings()
{
	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("mls_config.sqlite");
	ASSERT_WITH_CODE(db.open(), "Error! Can't open configuration database", return);

	checkIntegrity();
}

Settings::~Settings()
{
	db.close();
}

void Settings::checkIntegrity()
{
	map<string, string> integrity_check = {
			{"encoder", 	CHECK_ENCODER_TABLE_INTEGRITY_V1},
			{"channel", 	CHECK_CHANNEL_TABLE_INTEGRITY_V1},
			{"scene", 		CHECK_SCENE_TABLE_INTEGRITY_V1},
			{"surface", 	CHECK_SURFACE_TABLE_INTEGRITY_V1},
			{"property", 	CHECK_PROPERTY_TABLE_INTEGRITY_V1},
			{"resolution", 	CHECK_RESOLUTION_TABLE_INTEGRITY_V1},
			{"fps", 		CHECK_FPS_TABLE_INTEGRITY_V1},
			{"scale", 		CHECK_SCALE_TABLE_INTEGRITY_V1},
	};

	QSqlQuery query(db);
	for(auto it = integrity_check.begin(); it != integrity_check.end(); ++it)
	{
		query.exec(it->second.c_str());
		query.next();
		QSqlRecord result = query.record();
		ASSERT_WITH_CODE(result.field("is_correct").value().toBool(), "Configuration SQL database integrity check error!", traceerr("Table \'%s\' corrupted or not exist. Restoring default configuration!", it->first.c_str()); loadDefault(); return;);
	}
}

void Settings::loadDefault()
{

}