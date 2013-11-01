#ifndef MLS_SURFACE_H
#define MLS_SURFACE_H

#include "source.h"
#include <map>
#include "value.h"

using namespace std;

class IMqsSurface
{
public:
	IMqsSurface(string v_surface_handle, ISource *p_src);
    virtual ~IMqsSurface(void){}
	inline string getHandle() { return surface_handle; }
	virtual void render() = 0;
    virtual bool isVisible() { return visible; }
    virtual void setVisible(bool v_visible){ visible = v_visible; }
	virtual void save(string owner);
	virtual void load(string surface_name);
public:
	inline float &xPos()	{ return param_f["x_pos"]; }
	inline float &yPos()	{ return param_f["y_pos"]; }
	inline float &xScale()	{ return param_f["x_scale"]; }
	inline float &yScale()	{ return param_f["y_scale"]; }
	inline float &xAngle()	{ return param_f["x_angle"]; }
	inline float &yAngle()	{ return param_f["y_angle"]; }
	inline float &zAngle()	{ return param_f["z_angle"]; }
	inline float &leftCut()	{ return param_f["left_cut"]; }
	inline float &rightCut(){ return param_f["right_cut"]; }
	inline float &topCut()	{ return param_f["top_cut"]; }
	inline float &bottomCut()	{ return param_f["bottom_cut"]; }
	inline bool &keepAspect()	{ return param_b["keep_aspect"]; }
	inline float &rColor()	{ return param_f["red"]; }
	inline float &gColor()	{ return param_f["green"]; }
	inline float &bColor()	{ return param_f["blue"]; }
	inline float &alfa()	{ return param_f["alfa"]; }
	inline float &contrast()	{ return param_f["contrast"]; }
	inline float &brightnes()	{ return param_f["brightness"]; }
	inline float &RChroma()	{ return param_f["red_chroma"]; }
	inline float &GChroma()	{ return param_f["green_chroma"]; }
	inline float &BChroma()	{ return param_f["blue_chroma"]; }
	inline float &RTChroma(){ return param_f["red_tolerance_chroma"]; }
	inline float &GTChroma(){ return param_f["green_tolerance_chroma"]; }
	inline float &BTChroma(){ return param_f["blue_tolerance_chroma"]; }
	inline bool &chromaEnabled(){ return param_b["chroma_enabled"]; }
	virtual void updateClipping() = 0;
public:
	map<string, float> param_f;
	map<string, bool> param_b;

	bool visible;
	ISource *src;
	string owner_scene_name;
	string surface_handle;
};

#endif
