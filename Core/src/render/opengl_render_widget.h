#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <qmutex.h>
#include "irender_widget.h"
#include "opengl_surface.h"
#include "ring_buffer.h"

using namespace std;

#define SELLECTED_SURFACE ""

class GLRenderWidget : public QWidget, public IMqsRenderWidget
{
	Q_OBJECT
public:
	GLRenderWidget(QWidget *parent = 0);
	virtual ~GLRenderWidget();

	void createGLContext(QWidget *parent);

	void initialize(QWidget *parent);
	virtual string createSurface(ISource *src);//returns string handle to surface
    virtual void showSurface(string surface_handle = "");
    virtual void hideSurface(string surface_handle = "");
    virtual bool isSurfaceVisible(string surface_handle = "");
	virtual void deleteSurface(string surface_handle = "");
	virtual void selectSurface(string surface_handle);
	virtual void showSurfaceSetting(string surface_handle = "");
	virtual void show();
	virtual void move(uint x, uint y);
	virtual void setSize(uint width, uint height);
	virtual void load(string scene_name);
	virtual void save();
	virtual void saveScreenShot();

    void setBG(int r, int g, int b);
	void resizeGL(int width, int height);
	void mouseReleaseEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
private:
	void clear();
    GLubyte* unmapPBO(GLuint *pbo);
    GLubyte* mapTexureToPBO(GLuint textureID, GLuint tex_component, GLuint *pbo);
    bool initShaders();
    bool initSceneRenderTraget();
    bool initFBO(int width, int height);
	void selectSurface(MqsOpenGlSurface *surface);
	bool checkLimits(float x_pos, float y_pos, float x_scale, float y_scale);
	MqsOpenGlSurface* getObjectByPoint(const QPoint &point);

	map<string, MqsOpenGlSurface*> _surface;
	MqsOpenGlSurface *selected_surface;
	Qt::MouseButton active_button;

	HDC hdc;
	HGLRC GLContext;

	GLuint fbo_render_VAO;
    GLuint _fboId;
    GLuint render_rgb_texture_id, render_depth_texture_id, render_yuv_texture_id;
    GLuint _yuv_y_pbo[2], _yuv_u_pbo[2], _yuv_v_pbo[2], _rgb_pbo[2];

	unsigned int fps, frame_counter;
	unsigned int gl_width, gl_height;
    static GLuint scene_shader_program;
protected slots:
	void paintGL();
	void calcFPS();
signals:
	void surfaceAdd(string);
	void surfaceDel(string);
	void initMainScene();
    void frameReadyAll(unsigned char *yuv_y, unsigned char *yuv_u, unsigned char *yuv_v, uint width, uint height);
	void surfaceSelected(string surface_handle);
};

#endif
