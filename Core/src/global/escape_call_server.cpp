#include "escape_call_server.h"
#include "iencoder.h"
#include "settings.h"

EscapeCallServer::EscapeCallServer()
{
}

void EscapeCallServer::escapeCallback(int escape_call_id, void** data_out, int &data_out_size)
{
    switch(escape_call_id)
    {
        case ESCAPE_GET_ENCODERS:
        {
            vector<string> encoders = EncoderManager::getSuported();
            EscapeEncoder *escape_encoders = new EscapeEncoder[encoders.size()];
            memset(escape_encoders, 0, sizeof(EscapeEncoder)*encoders.size());
            for(unsigned int i = 0; i < encoders.size(); ++i)
            {
                QString ico_path = EncoderManager::getEncoderPlugin(encoders[i])->getIcoPath();
                memcpy(escape_encoders[i].name, encoders[i].c_str(), encoders[i].length());
                memcpy(escape_encoders[i].image_path, ico_path.toStdString().c_str(), ico_path.length());
            }

            *data_out = escape_encoders;
            data_out_size = encoders.size();
        }
        break;
        case ESCAPE_GET_METRIX:
        {
            EscapeMetrix *escape_metrix = new EscapeMetrix;

            QSqlRecord fps_record           = settings->query("SELECT fps FROM fps WHERE name in (SELECT value FROM property WHERE name = 'fps')").record();
            QSqlRecord scale_record         = settings->query("SELECT scale FROM scale WHERE name in (SELECT value FROM property WHERE name = 'scale')").record();
            QSqlRecord resolution_record    = settings->query("SELECT width, height FROM resolution WHERE name in (SELECT value FROM property WHERE name = 'resolution')").record();

            escape_metrix->fps              = fps_record.value("fps").toInt();
            escape_metrix->preview_scale    = scale_record.value("scale").toInt();
            escape_metrix->height           = resolution_record.value("height").toInt();
            escape_metrix->widht            = resolution_record.value("width").toInt();

            *data_out = escape_metrix;
            data_out_size = sizeof(EscapeMetrix);
        }
        break;
        case ESCAPE_UPDATE_CHANNEL:
        {
            ASSERT_WITH_CODE(sizeof(EscapeUpdateChannel) == data_out_size, "Wrong size of input for ESCAPE_UPDATE_CHANNEL", break);
            EscapeUpdateChannel *escape_update_channel = (EscapeUpdateChannel*)*data_out;
            QSqlQuery channel_sql = settings->prepareQuery("INSERT OR REPLACE INTO channel VALUES(:name, :channel_plugin, :encoder)");
            channel_sql.bindValue(":name",	escape_update_channel->channel_name);
            channel_sql.bindValue(":channel_plugin",	escape_update_channel->plugin_name);
            channel_sql.bindValue(":encoder",	escape_update_channel->encoder_name);
            if(!channel_sql.exec())
                traceerr("SQL error = %s, sql = %s", channel_sql.lastError().text().toStdString().c_str(), channel_sql.lastQuery().toStdString().c_str());
        }
        break;

        default:
        break;
    }
}
