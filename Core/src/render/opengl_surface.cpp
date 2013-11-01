#include "opengl_surface.h"

#include <qfile.h>
#include <algorithm>
#include "glsl.h"
#include "glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLuint MqsOpenGlSurface::tex_id = 0;
GLuint MqsOpenGlSurface::surface_shader_program = 0;
GLuint MqsOpenGlSurface::surface_mesh_VAO = 0;
GLuint MqsOpenGlSurface::surface_hit_test_mesh_VAO = 0;
GLuint MqsOpenGlSurface::texture_VBO = 0;
GLuint MqsOpenGlSurface::surface_mesh_VBO = 0;

MqsOpenGlSurface::MqsOpenGlSurface(string v_surface_handle, ISource *p_src) : IMqsSurface(v_surface_handle, p_src),
		selected(false), current_PBO_id(0)
{
	px_height 	= src->getHeight();
	px_width 	= src->getWidth();

	glBindTexture(GL_TEXTURE_2D, tex_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, px_width, px_height, 0, GL_BGR, GL_UNSIGNED_BYTE, NULL);
	gl_src = GLSource::startSource(src);
	connect(gl_src, SIGNAL(broadcastOnFrameReady(GLuint)), this, SLOT(onFrameReady(GLuint)));
}

MqsOpenGlSurface::~MqsOpenGlSurface(void)
{
	GLSource::stopSource(gl_src);
}

void MqsOpenGlSurface::onFrameReady(GLuint PBO_id)
{
	current_PBO_id = PBO_id;
}

bool MqsOpenGlSurface::initShaders()
{
    surface_shader_program = GLSL::setupProgram("surface_vertex.glsl", "surface_fragment.glsl");
    ASSERT_WITH_CODE(surface_shader_program != 0, "Failed to initialize surface shader program", return false);
    GLSL::useProgram(surface_shader_program);
	return true;
}

bool MqsOpenGlSurface::initTextures()
{
	//initializing texture VBO
	GLint texCordsLocation;
	float texture_cords[2 *4] =
	{
			//u:	v:
			0.0, 	0.0,
			1.0, 	0.0,
			1.0, 	1.0,
			0.0, 	1.0,
	};

	glBindVertexArray(surface_mesh_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, texture_VBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), texture_cords, GL_STATIC_DRAW);
    texCordsLocation = glGetAttribLocation(surface_shader_program, "tex_cords");
	ASSERT_WITH_CODE(texCordsLocation != -1, "Error! Can't set shader attribute.", return false);
	glVertexAttribPointer(texCordsLocation, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
	glEnableVertexAttribArray(texCordsLocation);

	glBindVertexArray(surface_hit_test_mesh_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, texture_VBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), texture_cords, GL_STATIC_DRAW);
    texCordsLocation = glGetAttribLocation(surface_shader_program, "tex_cords");
	ASSERT_WITH_CODE(texCordsLocation != -1, "Error! Can't set shader attribute.", return false);
	glVertexAttribPointer(texCordsLocation, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
	glEnableVertexAttribArray(texCordsLocation);

	glGenTextures(1, &tex_id);//should be 1 for all surfaces static
	glBindTexture(GL_TEXTURE_2D, tex_id);//should be 1 for all surfaces static
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glActiveTexture(GL_TEXTURE0);//GL_TEXTURE0 -> gfx texture unit #0

	//initializing GLSL texture sampler
	GLint textureLocation;
    textureLocation = glGetUniformLocation(surface_shader_program, "colorTexture");
	ASSERT_WITH_CODE(textureLocation != -1, "Error! Can't setup texture location in shader", return false);
	glUniform1i(textureLocation, 0);

	return true;
}

bool MqsOpenGlSurface::initVBOs()
{
	const unsigned int surface_mesh_vertex_count = 4;
	const unsigned int surface_mesh_vertex_dim = 6;//3 for xyz and 3 for rgb

	GLint positionLocation, colorLocation;
	const int vertexOffsetPosition 	= 0;
	const int vertexOffsetColor    	= 3 * sizeof(float);

	float surface_mesh[surface_mesh_vertex_count * surface_mesh_vertex_dim] =
	{
			//		x:		y:		z:		r:		g:		b:
			/*1*/ 	0.0f, 	0.0f, 	0.0f, 	-0.2f, 	-0.2f, 	-0.2f,
			/*2*/	1.0f, 	0.0f, 	0.0f, 	-0.2f, 	-0.2f, 	-0.2f,
			/*3*/	1.0f, 	1.0f, 	0.0f,  	-0.2f, 	-0.2f, 	-0.2f,
			/*4*/	0.0f, 	1.0f, 	0.0f,	-0.2f, 	-0.2f,  -0.2f,
	};
	//initializing full render surface mesh
	glGenVertexArrays(1, &surface_mesh_VAO);
	glBindVertexArray(surface_mesh_VAO);

	glGenBuffers(1, &texture_VBO);
	glGenBuffers(1, &surface_mesh_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, surface_mesh_VBO);
	glBufferData(GL_ARRAY_BUFFER, surface_mesh_vertex_count * surface_mesh_vertex_dim * sizeof(float), surface_mesh, GL_STATIC_DRAW);

    positionLocation = glGetAttribLocation(surface_shader_program, "vertex_position");
	ASSERT_WITH_CODE(positionLocation != -1, "Error! Can't set shader attribute.", return false);
	glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, surface_mesh_vertex_dim*sizeof(float), (const GLvoid*)vertexOffsetPosition);
	glEnableVertexAttribArray(positionLocation);

    colorLocation = glGetAttribLocation(surface_shader_program, "vertex_color");
	ASSERT_WITH_CODE(colorLocation != -1, "Error! Can't set shader attribute.", return false);
	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, surface_mesh_vertex_dim*sizeof(float), (const GLvoid*)vertexOffsetColor);
	glEnableVertexAttribArray(colorLocation);

	//initializing hit test(lite) render surface mesh
	const unsigned int surface_hit_mesh_vertex_count = 20;
	const unsigned int surface_hit_mesh_vertex_dim = 6;//3 for xyz and 3 for rgb
	float hit_test_mesh[surface_hit_mesh_vertex_count * surface_hit_mesh_vertex_dim] =
	{
			//		x:		y:		z:		r:		g:		b:
			/*1*/ 	0.00f, 	0.00f, 	-2.0f, 	1.0, 	0.0f, 	LEFT_BORDER*0.00392f,
			/*2*/	0.05f, 	0.00f, 	-2.0f, 	1.0, 	0.0f, 	LEFT_BORDER*0.00392f,
			/*3*/	0.05f, 	1.00f, 	-2.0f,  1.0, 	0.0f, 	LEFT_BORDER*0.00392f,
			/*4*/	0.00f, 	1.00f, 	-2.0f,	1.0f, 	0.0f,  	LEFT_BORDER*0.00392f,

			/*5*/	1.00f, 	0.00f, 	-2.0f,	1.0f, 	0.0f,  	RIGHT_BORDER*0.00392f,
			/*6*/	0.95f, 	0.00f, 	-2.0f,	1.0f, 	0.0f,  	RIGHT_BORDER*0.00392f,
			/*7*/	0.95f, 	1.00f, 	-2.0f,	1.0f, 	0.0f,  	RIGHT_BORDER*0.00392f,
			/*8*/	1.00f, 	1.00f, 	-2.0f,	1.0f, 	0.0f,  	RIGHT_BORDER*0.00392f,

			/*9*/	0.00f, 	0.0f, 	-2.0f,	1.0f, 	0.0f,  	BOTTOM_BORDER*0.00392f,
			/*10*/	1.00f, 	0.0f, 	-2.0f,	1.0f, 	0.0f,  	BOTTOM_BORDER*0.00392f,
			/*11*/	1.00f, 	0.05f, 	-2.0f,	1.0f, 	0.0f,  	BOTTOM_BORDER*0.00392f,
			/*12*/	0.00f, 	0.05f, 	-2.0f,	1.0f, 	0.0f,  	BOTTOM_BORDER*0.00392f,

			/*13*/	0.05f, 	1.00f, 	-2.0f,	1.0f, 	0.0f,  	TOP_BORDER*0.00392f,
			/*14*/	0.95f, 	1.00f, 	-2.0f,	1.0f, 	0.0f,  	TOP_BORDER*0.00392f,
			/*15*/	0.95f, 	0.95f, 	-2.0f,	1.0f, 	0.0f,  	TOP_BORDER*0.00392f,
			/*16*/	0.05f, 	0.95f, 	-2.0f,	1.0f, 	0.0f,  	TOP_BORDER*0.00392f,

            /*17*/ 	0.05f, 	0.05f, 	-2.0f, 	1.0f, 	0.0f, 	BODY*0.00392f,
            /*18*/	0.95f, 	0.05f, 	-2.0f, 	1.0f, 	0.0f, 	BODY*0.00392f,
            /*19*/	0.95f, 	0.95f, 	-2.0f,  1.0f, 	0.0f, 	BODY*0.00392f,
			/*20*/	0.05f, 	0.95f, 	-2.0f,	1.0f, 	0.0f,  	BODY*0.00392f,
	};

	GLuint surface_hit_test_mesh_VBO;

	glGenVertexArrays(1, &surface_hit_test_mesh_VAO);
	glBindVertexArray(surface_hit_test_mesh_VAO);

	glGenBuffers(1, &surface_hit_test_mesh_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, surface_hit_test_mesh_VBO);
	glBufferData(GL_ARRAY_BUFFER, surface_hit_mesh_vertex_count * surface_hit_mesh_vertex_dim * sizeof(float), hit_test_mesh, GL_STATIC_DRAW);

    positionLocation = glGetAttribLocation(surface_shader_program, "vertex_position");
	ASSERT_WITH_CODE(positionLocation != -1, "Error! Can't set shader attribute.", return false);
	glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, surface_hit_mesh_vertex_dim*sizeof(float), (const GLvoid*)vertexOffsetPosition);
	glEnableVertexAttribArray(positionLocation);

    colorLocation = glGetAttribLocation(surface_shader_program, "vertex_color");
	ASSERT_WITH_CODE(colorLocation != -1, "Error! Can't set shader attribute.", return false);
	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, surface_hit_mesh_vertex_dim*sizeof(float), (const GLvoid*)vertexOffsetColor);
	glEnableVertexAttribArray(colorLocation);
	return true;
}

void MqsOpenGlSurface::activateShader()
{
    GLSL::useProgram(surface_shader_program);
}

bool MqsOpenGlSurface::initOpenGl(HGLRC context)
{
	ASSERT_WITH_CODE(initShaders() && initVBOs() && initTextures(), "Failed to initialize surface objects...", return false);

	//setup model view matrix
	glm::mat4 modelViewMatrix = glm::mat4();
    GLint modelViewMatrixLocation = glGetUniformLocation(surface_shader_program, "modelViewMatrix");
	ASSERT_WITH_CODE(modelViewMatrixLocation != -1, "Error! Can't setup projection matrix", return false);
	glUniformMatrix4fv(modelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));

	return true;
}

void MqsOpenGlSurface::render_lite()
{
	glClear(GL_COLOR_BUFFER_BIT);
	float x_scale = xScale() - (rightCut() + leftCut())*xScale();
	float y_scale = yScale() - (topCut() + bottomCut())*yScale();

	glBindVertexArray(surface_hit_test_mesh_VAO);
    glUniform1i(glGetUniformLocation(surface_shader_program, "lite_render"), true);//it's lite render
	glm::mat4 modelViewMatrix = glm::mat4(1.0);
	modelViewMatrix = glm::translate(modelViewMatrix, glm::vec3(xPos(), yPos(), 0.0f));
	modelViewMatrix = glm::scale(modelViewMatrix, glm::vec3(x_scale, y_scale, 0.0f));
	modelViewMatrix = glm::rotate(modelViewMatrix, xAngle(), glm::vec3(1.0f, 0.0f, 0.0f));
	modelViewMatrix = glm::rotate(modelViewMatrix, yAngle(), glm::vec3(0.0f, 1.0f, 0.0f));
	modelViewMatrix = glm::rotate(modelViewMatrix, zAngle(), glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(glGetUniformLocation(surface_shader_program, "modelViewMatrix"), 1, GL_FALSE, glm::value_ptr(modelViewMatrix));

	glDrawArrays(GL_QUADS, 0, 20);
}

void MqsOpenGlSurface::render()
{
	if(!visible)
		return;
	float x_scale = xScale() - (rightCut() + leftCut())*xScale();
	float y_scale = yScale() - (topCut() + bottomCut())*yScale();

    glBindTexture(GL_TEXTURE_2D, tex_id);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, current_PBO_id);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, px_width, px_height, GL_BGR, GL_UNSIGNED_BYTE, NULL);

	glBindVertexArray(surface_mesh_VAO);

	glm::mat4 modelViewMatrix = glm::mat4(1.0f);
	modelViewMatrix = glm::translate(modelViewMatrix, glm::vec3(xPos(), yPos(), 0.0f));
	modelViewMatrix = glm::scale(modelViewMatrix, glm::vec3(x_scale, y_scale, 0.0f));
	modelViewMatrix = glm::rotate(modelViewMatrix, xAngle(), glm::vec3(1.0f, 0.0f, 0.0f));
	modelViewMatrix = glm::rotate(modelViewMatrix, yAngle(), glm::vec3(0.0f, 1.0f, 0.0f));
	modelViewMatrix = glm::rotate(modelViewMatrix, zAngle(), glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(glGetUniformLocation(surface_shader_program, "modelViewMatrix"), 1, GL_FALSE, glm::value_ptr(modelViewMatrix));

    glUniform1i(glGetUniformLocation(surface_shader_program, "selected"), selected);
    glUniform1i(glGetUniformLocation(surface_shader_program, "lite_render"), false);//it's not lite render
    glUniform3f(glGetUniformLocation(surface_shader_program, "surface_color"), rColor(), gColor(), bColor());
    glUniform1f(glGetUniformLocation(surface_shader_program, "brightness"), brightnes());
    glUniform1f(glGetUniformLocation(surface_shader_program, "contrast"), contrast());
    glUniform3f(glGetUniformLocation(surface_shader_program, "chroma_color"), RChroma(), GChroma(), BChroma());
    glUniform3f(glGetUniformLocation(surface_shader_program, "chroma_tolerance"), RTChroma(), GTChroma(), BTChroma());
	glDrawArrays(GL_QUADS, 0, 4);
}

void MqsOpenGlSurface::updateClipping()
{
	glBindVertexArray(surface_mesh_VAO);

	float texture_cords[4*2] =
	{
			//u:				v:
			leftCut(), 			bottomCut(),
			1.0f - rightCut(), 	bottomCut(),
			1.0f - rightCut(), 	1.0f - topCut(),
			leftCut(), 			1.0f - topCut()
	};

	traceerr("Updating surface clipping lc = %f, tc = %f, rc = %f, bc = %f", leftCut(), topCut(), rightCut(), bottomCut());
	glBindBuffer(GL_ARRAY_BUFFER, texture_VBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), texture_cords, GL_STATIC_DRAW);
}

MqsOpenGlSurface::AREA_TYPE MqsOpenGlSurface::getHitAreaType(unsigned int x, unsigned int y)
{
    GLubyte selected_area_type = 1;

    this->render_lite();

    glReadBuffer(GL_BACK);
    glReadPixels(x, y, 1, 1, GL_BLUE, GL_UNSIGNED_BYTE, &selected_area_type);GL_CHECK_FOR_ERRORS();

    if(selected_area_type <= AREA_TYPE::MIN || selected_area_type >= AREA_TYPE::MAX)
        return AREA_TYPE::UNKNOWN;
	return (AREA_TYPE)selected_area_type;
}

void MqsOpenGlSurface::select()
{
	selected = true;
}

void MqsOpenGlSurface::deselect()
{
	selected = false;
}

///--------------------------------------------------------------------------------------
bool MqsOpenGlSurface::checkLimits(float x_pos, float y_pos, float x_scale, float y_scale)
{
	x_scale = x_scale - (rightCut() + leftCut())*x_scale;
	y_scale = y_scale - (topCut() + bottomCut())*y_scale;
	///min scale check
	if(x_scale <= 0.1 || y_scale <= 0.1)
		return true;
	///x limits
	if(1 - x_pos < x_scale || x_pos < 0)
		return true;
	///y limits
	if(1 - y_pos < y_scale || y_pos < 0)
		return true;
	return false;
}

void MqsOpenGlSurface::winToSurface(int from_wx, int from_wy, int to_wx, int to_wy, double *dx, double *dy)
{
	double modelview[16], projection[16];
	int viewport[4];
	double dumy_z;
	double to_x, to_y;
	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );

	gluUnProject( to_wx, to_wy, 0.0f, modelview, 
		projection, viewport, dx, dy, &dumy_z );
	gluUnProject( from_wx, from_wy, 0.0f, modelview, 
		projection, viewport, &to_x, &to_y, &dumy_z );
	*dx -= to_x;
	*dy -= to_y;
}

void MqsOpenGlSurface::morph(int from_wx, int from_wy, int to_wx, int to_wy, AREA_TYPE morphing_type)
{
	double dx, dy;
	winToSurface(from_wx, from_wy, to_wx, to_wy, &dx, &dy);
	switch(morphing_type)
	{
	case MqsOpenGlSurface::LEFT_BORDER:
		if(checkLimits(xPos() + dx, yPos(), xScale() - dx, yScale()))
			break;
		xScale() -= dx;
		xPos()	+= dx;
		break;
	case MqsOpenGlSurface::RIGHT_BORDER:
		if(checkLimits(xPos(), yPos(), xScale() + dx, yScale()))
			break;
		xScale() += dx;
		break;
	case MqsOpenGlSurface::TOP_BORDER:
		if(checkLimits(xPos(), yPos(), xScale(), yScale() - dy))
			break;
		yScale() -= dy;
		break;
	case MqsOpenGlSurface::BOTTOM_BORDER:
		if(checkLimits(xPos(), yPos() - dy, xScale(), yScale() + dy))
			break;
		yScale() += dy;
		yPos() -= dy;
		break;
	default:
		if(checkLimits(xPos() + dx, yPos() - dy, xScale(), yScale()))
			break;
		xPos() += dx;
		yPos() -= dy;
		break;
	};
}
