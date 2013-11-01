#ifndef MLS_OPENGL_SURFACE
#define MLS_OPENGL_SURFACE

#include "isurface.h"
#include "glew.h"
#include <qtimer.h>
#include <qobject.h>
#include "gl_source.h"

using namespace std;

class MqsOpenGlSurface : public QObject, public IMqsSurface
{
	Q_OBJECT
	friend class GLRenderWidget;
public:
    enum AREA_TYPE { UNKNOWN = 0, MIN = 49, LEFT_BORDER = 50, RIGHT_BORDER, BOTTOM_BORDER, TOP_BORDER, BODY, MAX };
	MqsOpenGlSurface(string v_surface_handle, ISource *p_src);
	virtual ~MqsOpenGlSurface(void);
	virtual void render();
	void render_lite();
	static bool initOpenGl(HGLRC p_context);
    static void activateShader();
	AREA_TYPE getHitAreaType(unsigned int x, unsigned int y);
	void morph(int from_wx, int from_wy, int to_wx, int to_wy, AREA_TYPE hit_type);
	void select();
	void deselect();
	bool isSelected(){ return selected; }
	virtual void updateClipping();
public slots:
	virtual void onFrameReady(GLuint PBO_id);
private:
	void winToSurface(int from_wx, int from_wy, int to_wx, int to_wy, double *dx, double *dy);
	bool checkLimits(float x_pos, float y_pos, float x_scale, float y_scale);

	static bool initVBOs();
	static bool initTextures();
	static bool initShaders();
	static GLuint tex_id;
    static GLuint surface_shader_program;
	static GLuint surface_hit_test_mesh_VAO, surface_mesh_VAO;
	static GLuint texture_VBO, surface_mesh_VBO;

	bool selected;
	int px_width;
	int px_height;
	GLuint current_PBO_id;
	GLSource *gl_src;
};

#endif
