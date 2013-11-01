/*
 * glsl.h
 *
 *  Created on: 01.02.2013
 *      Author: nonametr
 */

#ifndef GLSL_H_
#define GLSL_H_

#include <string>
#include "glew.h"
#include "global.h"

using namespace std;

class GLSL
{
public:
	/**
	* Load fragment and vertex shader, compile and link them into new shader program
	*
	* @access public
	*
	* @param string vertex_shader_path - string containing path to file with source code of vertex shader
	*
	* @param string fragment_shader_path - string containing path to file with source code of fragment shader
	*
	* @return GLuint Returns an identifier of linked shader program on success, 0 on error
	*/
	static GLuint setupProgram(string vertex_shader_path, string fragment_shader_path)
	{
		GLuint shaderProgram  = glCreateProgram();
		GLuint vertexShader   = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		string frag_shader = global.readFile(fragment_shader_path);
		string vert_shader = global.readFile(vertex_shader_path);

		const char* frag_shader_str = frag_shader.c_str();
		const char* vert_shader_str = vert_shader.c_str();
		const int frag_shader_len = frag_shader.length();
		const int vert_shader_len = vert_shader.length();
		if(frag_shader_len == 0 || vert_shader_len == 0)
			return 0;

	    glShaderSource(vertexShader, 1, (const GLchar**)&vert_shader_str, (const GLint*)&vert_shader_len);
	    glCompileShader(vertexShader);
	    if(getShaderStatus(vertexShader, GL_COMPILE_STATUS) != GL_TRUE)
	       return 0;

	    glShaderSource(fragmentShader, 1, (const GLchar**)&frag_shader_str, (const GLint*)&frag_shader_len);
	    glCompileShader(fragmentShader);
	    if(getShaderStatus(fragmentShader, GL_COMPILE_STATUS) != GL_TRUE)
	       return 0;

	    glAttachShader(shaderProgram, vertexShader);
	    glAttachShader(shaderProgram, fragmentShader);

	    GL_CHECK_FOR_ERRORS();

	    glLinkProgram(shaderProgram);
	    if(getShaderProgramStatus(shaderProgram, GL_LINK_STATUS) != GL_TRUE)
			return 0;

	    GL_CHECK_FOR_ERRORS();
	    return shaderProgram;
	}
	/**
	* set program as current
	*
	* @access public
	*
	* @param GLuint shader_program_id - id of previously setup shader program
	*/
	static void useProgram(GLuint shader_program_id)
	{
		glUseProgram(shader_program_id);GL_CHECK_FOR_ERRORS();
	}
private:
	static GLint getShaderStatus(GLuint shader, GLenum param)
	{
		GLint status, length;
		GLchar buffer[1024];

		glGetShaderiv(shader, param, &status);

		if (status != GL_TRUE)
		{
				glGetShaderInfoLog(shader, 1024, &length, buffer);
				traceerr("Shader: %s\n", (const char*)buffer);
		}

		GL_CHECK_FOR_ERRORS();

		return status;
	}
	static GLint getShaderProgramStatus(GLuint program, GLenum param)
	{
		GLint status, length;
		GLchar buffer[1024];

		glGetProgramiv(program, param, &status);

		if (status != GL_TRUE)
		{
			glGetProgramInfoLog(program, 1024, &length, buffer);
			traceerr("Shader program: %s\n", (const char*)buffer);
		}

		GL_CHECK_FOR_ERRORS();

		return status;
	}
};

#endif /* GLSL_H_ */
