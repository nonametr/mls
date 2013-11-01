#include "gui_surface_settings.h"
#include "opengl_render_widget.h"
#include <qtimer.h>
#include <qevent.h>
#include <qwidget.h>
#include "settings.h"
#include "runtime.h"
#include "glsl.h"
#include <math.h>
#include "glm.hpp"
#include "glsl.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLuint GLRenderWidget::scene_shader_program = 0;

GLRenderWidget::GLRenderWidget(QWidget *parent)
:		QWidget(parent), selected_surface(NULL),
        active_button(Qt::NoButton), fps(0), frame_counter(0),
        GLContext(0), hdc(0), _fboId(0), render_rgb_texture_id(0), render_depth_texture_id(0),
 		gl_height(0), gl_width(0), fbo_render_VAO(0)
{}

GLRenderWidget::~GLRenderWidget()
{
	this->clear();
    glDeleteFramebuffers(1, &_fboId);
}

void GLRenderWidget::clear()
{
	selected_surface = NULL;
	for(map<string, MqsOpenGlSurface*>::iterator it = _surface.begin(); it != _surface.end(); ++it)
	{
		emit surfaceDel(it->first);
		it->second->deleteLater();
	}
	_surface.clear();
}

void GLRenderWidget::createGLContext(QWidget *parent)
{
	PIXELFORMATDESCRIPTOR pfd;
	int format;
	hdc = GetDC((HWND)parent->winId());

	memset(&pfd, 0, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 24;

	format = ChoosePixelFormat(hdc, &pfd);
	if (!format || !SetPixelFormat(hdc, format, &pfd))
	{
			traceerr("Setting pixel format fail (%d)\n", GetLastError());
			return;
	}

	GLContext = wglCreateContext(hdc);
	wglMakeCurrent(hdc, GLContext);

	GL_CHECK_FOR_ERRORS();

	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		traceerr("OpenGL GLEW is not initialized!");
	}

	char *version = (char*)glGetString(GL_VERSION);
	char *hw_platform = (char*)glGetString(GL_RENDERER);
	char *vendor = (char*)glGetString(GL_VENDOR);

	traceerr("Initializing [%s] OpenGL %s \r\n on %s...", vendor, version, hw_platform);
	GL_CHECK_FOR_ERRORS();
}

void GLRenderWidget::initialize(QWidget *parent)
{
	createGLContext(parent);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_TEXTURE_2D );
	//setuping opengl surface engine
    ASSERT_WITH_CODE(initShaders() == true && initSceneRenderTraget() == true, "Critical error occurred during OpenGL initialization! \r\nProgram will stop in 30 seconds or terminate it manually...", Sleep(30000);exit(1));
    ASSERT_WITH_CODE(MqsOpenGlSurface::initOpenGl(GLContext) == true, "Critical error occurred during OpenGL initialization! \r\nProgram will stop in 30 seconds or terminate it manually...", Sleep(30000);exit(1));

    setMouseTracking(true);

	//setuping timers
	QTimer *fps_timer = new QTimer(this);
	connect(fps_timer, SIGNAL(timeout()), this, SLOT(calcFPS()));
	fps_timer->start(1000);

	QTimer *render_timer = new QTimer(this);
	connect(render_timer, SIGNAL(timeout()), this, SLOT(paintGL()));
    render_timer->start(30);

	connect(this, SIGNAL(initMainScene()), parent, SLOT(initScene()));
	emit initMainScene();

	// create textures for FBO
	glGenTextures(1, &render_rgb_texture_id);
	glGenTextures(1, &render_depth_texture_id);
    glGenFramebuffers(1, &_fboId);
    glGenBuffers(2, _rgb_pbo);
    glGenBuffers(2, _yuv_y_pbo);
    glGenBuffers(2, _yuv_u_pbo);
    glGenBuffers(2, _yuv_v_pbo);

	traceerr("OpenGl render initialized successfully...");
}

void GLRenderWidget::calcFPS()
{
	fps = frame_counter;
	//traceerr("current fps = %u", fps);
	frame_counter = 0;
}

GLubyte* GLRenderWidget::mapTexureToPBO(GLuint textureID, GLuint tex_component, GLuint *pbo)
{
    glBindTexture(GL_TEXTURE_2D, textureID);
    glBindBuffer(GL_PIXEL_PACK_BUFFER, pbo[0]);
    glGetTexImage(GL_TEXTURE_2D, 0, tex_component, GL_UNSIGNED_BYTE, NULL);
    glBindBuffer(GL_PIXEL_PACK_BUFFER, pbo[1]);
    GLubyte* ptr = (GLubyte*)glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);
    glBindTexture(GL_TEXTURE_2D, 0);
    return ptr;
}

GLubyte* GLRenderWidget::unmapPBO(GLuint *pbo)
{
    glBindBuffer(GL_PIXEL_PACK_BUFFER, pbo[1]);
    glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
    glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
    std::swap(pbo[0], pbo[1]);
}

void GLRenderWidget::paintGL()
{
    //render to FBO texture
    glBindFramebuffer(GL_FRAMEBUFFER, _fboId);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, render_rgb_texture_id, 0);
	glViewport(0, 0, gl_width, gl_height);
    glClear(GL_COLOR_BUFFER_BIT);

    //rendering to texture
	for(map<string, MqsOpenGlSurface*>::iterator it = _surface.begin(); it != _surface.end(); ++it)
	{
        it->second->render();
	}

    GLSL::useProgram(scene_shader_program);

    //converting resulted rgb texure to yuv via gpgpu
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, render_yuv_texture_id, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(fbo_render_VAO);
    glBindTexture(GL_TEXTURE_2D, render_rgb_texture_id);
    glUniform1i(glGetUniformLocation(scene_shader_program, "render_type"), 1);//yuv render
    glDrawArrays(GL_QUADS, 0, 4);

    //fetching yuv componets
    GLubyte* yuv_y = mapTexureToPBO(render_yuv_texture_id, GL_RED, _yuv_y_pbo);
    GLubyte* yuv_u = mapTexureToPBO(render_yuv_texture_id, GL_GREEN, _yuv_u_pbo);
    GLubyte* yuv_v = mapTexureToPBO(render_yuv_texture_id, GL_BLUE, _yuv_v_pbo);

    //broadcast rendered data to external channel
    emit frameReadyAll((unsigned char*)yuv_y, (unsigned char*)yuv_u, (unsigned char*)yuv_v, gl_width, gl_height);

    //unmap yuv data
    unmapPBO(_yuv_y_pbo);
    unmapPBO(_yuv_u_pbo);
    unmapPBO(_yuv_v_pbo);

    if(is_visible)
	{
        //render to preview viewport
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, width(), height());
        glClear(GL_COLOR_BUFFER_BIT);
        glBindTexture(GL_TEXTURE_2D, render_rgb_texture_id);
        glBindVertexArray(fbo_render_VAO);
        glUniform1i(glGetUniformLocation(scene_shader_program, "render_type"), 0);//normal render
        glDrawArrays(GL_QUADS, 0, 4);
	}
    else
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    SwapBuffers(hdc);
    MqsOpenGlSurface::activateShader();
    ++frame_counter;GL_CHECK_FOR_ERRORS();
}

string GLRenderWidget::createSurface(ISource *src)
{
    string surface_handle;
    static uint uniq_id = 0;
    static float next_x_pos = 0.0f;
    static float next_y_pos = 0.0f;

    do
    {
    	surface_handle = this->getName() + string("-") + global.intToString(++uniq_id);
    }while(_surface.find(surface_handle) != _surface.end());
    emit surfaceAdd(surface_handle);

    MqsOpenGlSurface *new_surface = new MqsOpenGlSurface(surface_handle, src);
    new_surface->xPos() = next_x_pos += 0.02f;
    new_surface->yPos() = next_y_pos += 0.02f;
    _surface[surface_handle] = new_surface;
    new_surface->save(this->getName());

    return surface_handle;
}

bool GLRenderWidget::isSurfaceVisible(string surface_handle)
{
    if(surface_handle.empty())
    {
        ASSERT_WITH_CODE(selected_surface, "Can't get status of unknown surface!", return false);
        surface_handle = selected_surface->getHandle();
    }
    map<string, MqsOpenGlSurface*>::iterator it = _surface.find(surface_handle);
    ASSERT_WITH_CODE(it != _surface.end(), "Can't get status of unknown surface!", return false);

    return it->second->isVisible();
}

void GLRenderWidget::hideSurface(string surface_handle)
{
	if(surface_handle.empty())
	{
        ASSERT_WITH_CODE(selected_surface, "Can't hide unknown surface!", return);
		surface_handle = selected_surface->getHandle();
	}
	map<string, MqsOpenGlSurface*>::iterator it = _surface.find(surface_handle);
    ASSERT_WITH_CODE(it != _surface.end(), "Can't hide unknown surface!", return);

    it->second->setVisible(false);
}

void GLRenderWidget::showSurface(string surface_handle)
{
    if(surface_handle.empty())
    {
        ASSERT_WITH_CODE(selected_surface, "Can't show unknown surface!", return);
        surface_handle = selected_surface->getHandle();
    }
    map<string, MqsOpenGlSurface*>::iterator it = _surface.find(surface_handle);
    ASSERT_WITH_CODE(it != _surface.end(), "Can't show unknown surface!", return);

    it->second->setVisible(true);
}

void GLRenderWidget::deleteSurface(string surface_handle) 
{
	if(surface_handle.empty())
	{
		ASSERT_WITH_CODE(selected_surface, "Can't delete unknown surface!", return);
		surface_handle = selected_surface->getHandle();
		selected_surface = NULL; 
	}
	map<string, MqsOpenGlSurface*>::iterator it = _surface.find(surface_handle);
	ASSERT_WITH_CODE(it != _surface.end(), "Can't delete unknown surface!", return);

    it->second->deleteLater();
	_surface.erase(it);
}

void GLRenderWidget::selectSurface(string surface_handle)
{
	map<string, MqsOpenGlSurface*>::iterator it = _surface.find(surface_handle);
	if(it != _surface.end())
		selectSurface(it->second);
	else
		selectSurface(NULL);
}

void GLRenderWidget::selectSurface(MqsOpenGlSurface *surface)
{
	string selected_surface_handle;
	if(selected_surface != NULL)
	{
		selected_surface->deselect();
	}
	if(surface != NULL)
	{
		surface->select();
		selected_surface = surface;
		selected_surface_handle = surface->getHandle();
	}
	emit surfaceSelected(selected_surface_handle);
}

void GLRenderWidget::showSurfaceSetting(string surface_handle)
{
	IMqsSurface *control_surface = selected_surface;
	if(!surface_handle.empty())
	{
		map<string, MqsOpenGlSurface*>::iterator it = _surface.find(surface_handle);
		ASSERT_WITH_CODE(it != _surface.end(), "Can't show settings for unknown surface!", return);
		control_surface = it->second;
	}
	MqsSurfaceSettings *settings = new MqsSurfaceSettings(this);
	settings->setAttribute(Qt::WA_DeleteOnClose, true);
	settings->setControlSurface(control_surface);
	settings->show();
}

void GLRenderWidget::show()
{
	QWidget::show();
}

void GLRenderWidget::move(uint x, uint y)
{
	QWidget::move(x, y);
}

void GLRenderWidget::setSize(uint width, uint height)
{
    traceerr("Stream resolution changed to %ux%u", width, height);
    traceerr("View resolution changed to %ux%u", (unsigned int)(width*scale), (unsigned int)(height*scale));

    this->resize(width*scale, height*scale);
    this->resizeGL(width, height);
}

bool GLRenderWidget::initShaders()
{
    scene_shader_program = GLSL::setupProgram("scene_vertex.glsl", "scene_fragment.glsl");
    ASSERT_WITH_CODE(scene_shader_program != 0, "Failed to initialize surface shader program", return false);
    return true;
}

bool GLRenderWidget::initSceneRenderTraget()
{
    GLSL::useProgram(scene_shader_program);
	//initializing texture VBO
	GLint texCordsLocation;
	const unsigned int fbo_render_mesh_vertex_count = 4;
	const unsigned int fbo_render_mesh_vertex_dim = 6;//3 for xyz and 3 for rgb

	float texture_cords[2 *4] =
	{
			//u:	v:
			0.0, 	0.0,
			1.0, 	0.0,
			1.0, 	1.0,
			0.0, 	1.0,
	};
	float fbo_render_mesh[fbo_render_mesh_vertex_count * fbo_render_mesh_vertex_dim] =
	{
			//		x:		y:		z:		r:		g:		b:
			/*1*/ 	0.0f, 	0.0f, 	0.0f, 	0.0f, 	0.0f, 	0.0f,
			/*2*/	1.0f, 	0.0f, 	0.0f, 	0.0f, 	0.0f, 	0.0f,
			/*3*/	1.0f, 	1.0f, 	0.0f,  	0.0f, 	0.0f, 	0.0f,
			/*4*/	0.0f, 	1.0f, 	0.0f,	0.0f, 	0.0f,  	0.0f,
	};
	GLuint fbo_render_texture_coords_VBO, fbo_render_mesh_VBO;
	glGenVertexArrays(1, &fbo_render_VAO);
	glBindVertexArray(fbo_render_VAO);
	glGenBuffers(1, &fbo_render_texture_coords_VBO);
	glGenBuffers(1, &fbo_render_mesh_VBO);

	glBindBuffer(GL_ARRAY_BUFFER, fbo_render_mesh_VBO);
	glBufferData(GL_ARRAY_BUFFER, fbo_render_mesh_vertex_count * fbo_render_mesh_vertex_dim * sizeof(float), fbo_render_mesh, GL_STATIC_DRAW);

	GLint positionLocation, colorLocation;
	const int vertexOffsetPosition 	= 0;
	const int vertexOffsetColor    	= 3 * sizeof(float);

    positionLocation = glGetAttribLocation(scene_shader_program, "vertex_position");
    ASSERT_WITH_CODE(positionLocation != -1, "Error! Can't set shader attribute.", return false);
	glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, fbo_render_mesh_vertex_dim*sizeof(float), (const GLvoid*)vertexOffsetPosition);
	glEnableVertexAttribArray(positionLocation);

    colorLocation = glGetAttribLocation(scene_shader_program, "vertex_color");
    ASSERT_WITH_CODE(colorLocation != -1, "Error! Can't set shader attribute.", return false);
	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, fbo_render_mesh_vertex_dim*sizeof(float), (const GLvoid*)vertexOffsetColor);
	glEnableVertexAttribArray(colorLocation);

	glBindBuffer(GL_ARRAY_BUFFER, fbo_render_texture_coords_VBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), texture_cords, GL_STATIC_DRAW);
    texCordsLocation = glGetAttribLocation(scene_shader_program, "tex_cords");
    ASSERT_WITH_CODE(texCordsLocation != -1, "Error! Can't set shader attribute to render FBO.", return false);
	glVertexAttribPointer(texCordsLocation, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
    glEnableVertexAttribArray(texCordsLocation);
    return true;
}

bool GLRenderWidget::initFBO(int width, int height)
{
	GLenum fboStatus;

    glBindTexture(GL_TEXTURE_2D, render_yuv_texture_id);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, render_rgb_texture_id);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, render_depth_texture_id);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, _fboId);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, render_rgb_texture_id, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,  GL_TEXTURE_2D, render_depth_texture_id, 0);

	fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
	{
        traceerr("Error initializing OpenGL FBO. glCheckFramebufferStatus error 0x%X\n", fboStatus);
        return false;
	}
	GL_CHECK_FOR_ERRORS();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return true;
}

void GLRenderWidget::setBG(int r, int g, int b)
{
    glClearColor(r*0.0039f, g*0.0039f, b*0.0039f, 0.0);
    traceerr("Changing background color to r:%u; g:%u; b:%u;", r, g, b);
}

void GLRenderWidget::resizeGL(int width, int height)
{
    initFBO(width, height);

    gl_width = width;
    gl_height = height;

    glBindBuffer(GL_PIXEL_PACK_BUFFER, _yuv_y_pbo[0]);
    glBufferData(GL_PIXEL_PACK_BUFFER, width*height+1, 0, GL_STREAM_READ);
    glBindBuffer(GL_PIXEL_PACK_BUFFER, _yuv_y_pbo[1]);
    glBufferData(GL_PIXEL_PACK_BUFFER, width*height+1, 0, GL_STREAM_READ);
    glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
    glBindBuffer(GL_PIXEL_PACK_BUFFER, _yuv_u_pbo[0]);
    glBufferData(GL_PIXEL_PACK_BUFFER, width*height+1, 0, GL_STREAM_READ);
    glBindBuffer(GL_PIXEL_PACK_BUFFER, _yuv_u_pbo[1]);
    glBufferData(GL_PIXEL_PACK_BUFFER, width*height+1, 0, GL_STREAM_READ);
    glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
    glBindBuffer(GL_PIXEL_PACK_BUFFER, _yuv_v_pbo[0]);
    glBufferData(GL_PIXEL_PACK_BUFFER, width*height+1, 0, GL_STREAM_READ);
    glBindBuffer(GL_PIXEL_PACK_BUFFER, _yuv_v_pbo[1]);
    glBufferData(GL_PIXEL_PACK_BUFFER, width*height+1, 0, GL_STREAM_READ);
    glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
    glBindBuffer(GL_PIXEL_PACK_BUFFER, _rgb_pbo[0]);
    glBufferData(GL_PIXEL_PACK_BUFFER, width*height*3+1, 0, GL_STREAM_READ);
    glBindBuffer(GL_PIXEL_PACK_BUFFER, _rgb_pbo[1]);
    glBufferData(GL_PIXEL_PACK_BUFFER, width*height*3+1, 0, GL_STREAM_READ);
    glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);

	//projection matrix setup
    glm::mat4 projectionMatrix = glm::ortho(0.0f, +1.0f, 0.0f, +1.0f, -10.0f, +10.0f);
    GLSL::useProgram(MqsOpenGlSurface::surface_shader_program);
    glUniformMatrix4fv(glGetUniformLocation(MqsOpenGlSurface::surface_shader_program, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    GLSL::useProgram(scene_shader_program);
    glUniformMatrix4fv(glGetUniformLocation(scene_shader_program, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix)); 
    glm::mat4 modelViewMatrix = glm::mat4(1.0f);
    glUniformMatrix4fv(glGetUniformLocation(scene_shader_program, "modelViewMatrix"), 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
}

MqsOpenGlSurface* GLRenderWidget::getObjectByPoint(const QPoint &point)
{
	for(map<string, MqsOpenGlSurface*>::reverse_iterator it = _surface.rbegin(); it != _surface.rend(); ++it)
	{
		if(it->second->getHitAreaType(point.x(), this->height() - point.y()))
			return it->second;
	}
	return NULL;
}

int old_wx = 0, old_wy = 0;
MqsOpenGlSurface::AREA_TYPE selected_hit_point;

void GLRenderWidget::mouseMoveEvent(QMouseEvent *event)
{
	if(selected_surface != NULL)
	{
		if(active_button != Qt::LeftButton)///if moving on some surface, selected but no mouse button clicked
		{
			MqsOpenGlSurface::AREA_TYPE dyn_hit_point = selected_surface->getHitAreaType(event->pos().x(), this->height() - event->pos().y());
			switch(dyn_hit_point)
			{
			case MqsOpenGlSurface::RIGHT_BORDER:
			case MqsOpenGlSurface::LEFT_BORDER:
				if(Qt::SizeHorCursor != cursor().shape())
					setCursor(Qt::SizeHorCursor);
				break;
			case MqsOpenGlSurface::TOP_BORDER:
			case MqsOpenGlSurface::BOTTOM_BORDER:
				if(Qt::SizeVerCursor != cursor().shape())
					setCursor(Qt::SizeVerCursor);
				break;
			case MqsOpenGlSurface::BODY:
				if(Qt::CrossCursor != cursor().shape())
				setCursor(Qt::CrossCursor);
				break;
			default:
				if(Qt::ArrowCursor != cursor().shape())
					setCursor(Qt::ArrowCursor);
				break;
			};
		}
		else///if moving with pressed mouse button on selected object
		{
			if(old_wx && old_wy)
			{
				selected_surface->morph(old_wx, old_wy, event->pos().x(), event->pos().y(), selected_hit_point);
			}
			old_wx = event->pos().x();
			old_wy = event->pos().y();
		}
	}
}

void GLRenderWidget::mouseReleaseEvent(QMouseEvent *event)
{
	setCursor(Qt::ArrowCursor);
	old_wx = 0;
	old_wy = 0;
	active_button = Qt::NoButton;
}

void GLRenderWidget::mousePressEvent(QMouseEvent * event) 
{
	active_button = event->button();
	selectSurface(NULL);
	selected_surface = getObjectByPoint(event->pos());
	if(selected_surface != NULL)
	{
		if(active_button == Qt::RightButton)
		{
			MqsSurfaceSettings *settings = new MqsSurfaceSettings(this);
			settings->setAttribute(Qt::WA_DeleteOnClose, true);
			settings->setControlSurface(selected_surface);
			settings->show();
		}
		if(active_button == Qt::LeftButton)
		{
			selected_hit_point = selected_surface->getHitAreaType(event->pos().x(), this->height() - event->pos().y());
		}
	}
	selectSurface(selected_surface);
}

void GLRenderWidget::load(string scene_name)
{
    QSqlRecord scene_bg = settings->query("SELECT background_r as R, background_g as G, background_b as B FROM scene WHERE name = '%s'", scene_name.c_str()).record();
    if(!scene_bg.isEmpty())
    {
        setBG(scene_bg.value("R").toInt(), scene_bg.value("G").toInt(), scene_bg.value("B").toInt());
    }
    else
    {
        setBG(0, 0, 0);
    }

	QSqlRecord scene_test = settings->query("SELECT count(*) as is_exist FROM scene WHERE name = '%s' and enabled = 1", scene_name.c_str()).record();
	ASSERT_WITH_CODE(scene_test.value("is_exist").toBool(), "Error! Requested scene not found!", return);

	this->setName(scene_name);
	settings->query("UPDATE scene SET active = 0;UPDATE scene SET active = 1 WHERE name = '%s'", scene_name.c_str());

	QSqlRecord surface_test = settings->query("SELECT count(*) as is_exist FROM surface WHERE scene = '%s'", scene_name.c_str()).record();
	if(!surface_test.value("is_exist").toBool())
		return;

	QSqlQuery surfaces = settings->query("SELECT name, capture_name, capture_device_id FROM surface WHERE scene = '%s'", scene_name.c_str());
	do
	{
		QSqlRecord surface = surfaces.record();
        ICapture* capture = SrcManager::createCapture(surface.value("capture_name").toString().toStdString());
        ASSERT_WITH_CODE(capture != NULL, "Failed to load surface. Unknown target plugin requested.", continue);
        capture->bind(surface.value("capture_device_id").toUInt());
        ISource *source = dynamic_cast<ISource*>(capture);

        string surface_name = surface.value("name").toString().toStdString();
		MqsOpenGlSurface *new_surface = new MqsOpenGlSurface(surface_name, source);
		new_surface->load(surface_name);
		emit surfaceAdd(surface_name);
		_surface[surface_name] = new_surface;
	}while(surfaces.next());
}

void GLRenderWidget::save()
{
	for(map<string, MqsOpenGlSurface*>::iterator it = _surface.begin(); it != _surface.end(); ++it)
	{
		it->second->save(this->getName());
	}
	this->clear();
}

void GLRenderWidget::saveScreenShot()
{
    QSqlRecord screen_path = settings->query("SELECT value FROM property WHERE name = 'screen_shot_path'").record();
    ASSERT_WITH_CODE(screen_path.isEmpty() == false, "Screenshot path not configured. Please configure it before use!", return);

    glBindBuffer(GL_PIXEL_PACK_BUFFER, _rgb_pbo[0]);
    glBindTexture(GL_TEXTURE_2D, render_rgb_texture_id);
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    const GLubyte* ptr = (GLubyte*)glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);

    QImage image_to_save = QImage((const unsigned char*)ptr, gl_width, gl_height, QImage::Format_RGB888 ).mirrored();
    char file_name[256] = {"\0"};
    snprintf(file_name, 256, "%s/mls_screen_%u.jpg", screen_path.value("value").toString().toStdString().c_str(), (unsigned int)time(NULL));
    traceerr("ScreenShot saved to %s", file_name);
    image_to_save.save(file_name, "JPG", 100);

    glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
    glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
}
