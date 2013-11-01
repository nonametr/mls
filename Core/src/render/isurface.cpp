#include "isurface.h"
#include "settings.h"

IMqsSurface::IMqsSurface(string v_surface_handle, ISource *p_src) : src(p_src), surface_handle(v_surface_handle), visible(true)
{
	param_f["x_pos"] = 0.0f;
	param_f["y_pos"] = 0.0f;
	param_f["x_scale"] = 0.4f;
	param_f["y_scale"] = 0.4f;
	param_f["x_angle"] = 0.0f;
	param_f["y_angle"] = 0.0f;
	param_f["z_angle"] = 0.0f;
	param_f["left_cut"] = 0.0f;
	param_f["right_cut"] = 0.0f;
	param_f["top_cut"] = 0.0f;
	param_f["bottom_cut"] = 0.0f;
	param_b["keep_aspect"] = 0.0f;
	param_f["red"] = 1.0f;
	param_f["green"] = 1.0f;
	param_f["blue"] = 1.0f;
	param_f["alfa"] = 1.0f;
	param_f["contrast"] = 0.9f;
	param_f["brightness"] = 0.1f;
	param_f["red_chroma"] = 0.0f;
	param_f["green_chroma"] = 0.0f;
	param_f["blue_chroma"] = 0.0f;
	param_f["red_tolerance_chroma"] = 0.0f;
	param_f["green_tolerance_chroma"] = 0.0f;
	param_f["blue_tolerance_chroma"] = 0.0f;
	param_b["chroma_enabled"] = false;
}
void IMqsSurface::save(string owner)
{
	CaptureDevice* cap_dev = dynamic_cast<CaptureDevice*>(src);
	QSqlQuery surface_sql = settings->prepareQuery("INSERT OR REPLACE INTO surface VALUES("
			":name,:x_pos,:y_pos,:x_scale,:y_scale,:x_angle,:y_angle,:z_angle,"
			":left_cut,:right_cut,:top_cut,:bottom_cut,:keep_aspect,:red,"
			":green,:blue,:alfa,:contrast,:brightness,:red_chroma,:green_chroma,"
			":blue_chroma,:red_tolerance_chroma,:blue_tolerance_chroma,:green_tolerance_chroma,"
			":chroma_enabled,:capture_name,:capture_device_id,:scene)");

	surface_sql.bindValue(":name", 				surface_handle.c_str());
	surface_sql.bindValue(":capture_name", 		cap_dev->getPluginName().c_str());
	surface_sql.bindValue(":capture_device_id", cap_dev->getDeviceId());
	surface_sql.bindValue(":scene", 			owner.c_str());

	for(auto it = param_f.begin(); it != param_f.end(); ++it)
	{
		string param_name = it->first;
		string bind_val = ":" + param_name;
		surface_sql.bindValue(bind_val.c_str(), it->second);
	}
	for(auto it = param_b.begin(); it != param_b.end(); ++it)
	{
		string param_name = it->first;
		string bind_val = ":" + param_name;
		surface_sql.bindValue(bind_val.c_str(), it->second);
	}

	surface_sql.exec();
}
void IMqsSurface::load(string surface_name)
{
	QSqlRecord surface_f = settings->query("SELECT x_pos,y_pos,x_scale,y_scale,x_angle,y_angle,z_angle,"
			"left_cut,right_cut,top_cut,bottom_cut,red,"
			"green,blue,alfa,contrast,brightness,red_chroma,green_chroma,"
			"blue_chroma,red_tolerance_chroma,blue_tolerance_chroma,green_tolerance_chroma "
			"FROM surface WHERE name = '%s'", surface_name.c_str()).record();

	QSqlRecord surface_b = settings->query("SELECT keep_aspect, chroma_enabled FROM surface WHERE name = '%s'", surface_name.c_str()).record();
	ASSERT_WITH_CODE(!surface_f.isEmpty() && !surface_b.isEmpty(), "Error! Surface loading failed", return);

	for(unsigned int i = 0; i < surface_f.count(); ++i)
	{
		param_f[surface_f.field(i).name().toStdString()] = surface_f.value(i).toFloat();
	}
	for(unsigned int i = 0; i < surface_b.count(); ++i)
	{
		param_f[surface_b.field(i).name().toStdString()] = surface_b.value(i).toBool();
	}
}
