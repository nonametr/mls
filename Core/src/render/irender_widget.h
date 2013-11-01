#ifndef MLS_MLS_RENDER_WIDGET_H
#define MLS_MLS_RENDER_WIDGET_H

#include "isurface.h"

class Value;

class IMqsRenderWidget
{
public:
	IMqsRenderWidget() : scale(1.0f), name(""), is_visible(true)
	{}
    virtual ~IMqsRenderWidget(){}
	virtual void initialize(QWidget *parent) = 0;
	virtual string createSurface(ISource *src) = 0;
	virtual void deleteSurface(string surface_handle = "") = 0;
	virtual void selectSurface(string surface_handle) = 0;
	virtual void showSurfaceSetting(string surface_handle = "") = 0;
	virtual void show() = 0;
	virtual void move(uint x, uint y) = 0;
	virtual void setSize(uint width, uint height) = 0;
	virtual void load(string scene_name) = 0;
	virtual void save() = 0;
	virtual void saveScreenShot() = 0;
    virtual void setPreviewVisible(bool visible){ is_visible = visible; }
    string &getName(){ return name; }
	void setName(string new_name) { name = new_name; }
	void setScale(unsigned int view_scale){ scale = view_scale * 0.01f; }
protected:
	bool is_visible;
	float scale;
	string name;
};

#endif
