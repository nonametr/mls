/*
 * gl_source.cpp
 *
 *  Created on: 18.02.2013
 *      Author: nonametr
 */

#include "gl_source.h"

map<string, GLSource*> GLSource::_gl_sources = map<string, GLSource*>();

void GLSource::initPBO()
{
	int height 	= src->getHeight();
	int width 	= src->getWidth();

	glGenBuffers(2, texture_PBO);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, texture_PBO[0]);
	glBufferData(GL_PIXEL_UNPACK_BUFFER, width*height*3+1, 0, GL_STREAM_DRAW);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, texture_PBO[1]);
	glBufferData(GL_PIXEL_UNPACK_BUFFER, width*height*3+1, 0, GL_STREAM_DRAW);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
}

GLSource* GLSource::startSource(ISource *p_src)
{
	GLSource* gl_source;
	map<string, GLSource*>::iterator it = _gl_sources.find(p_src->getName());
	if(it != _gl_sources.end())
	{
		gl_source = it->second;
		it->second->ref_count++;
	}
	else
	{
		gl_source = new GLSource(p_src);
		_gl_sources[p_src->getName()] = gl_source;
	}
	return gl_source;
}
void GLSource::stopSource(GLSource *gl_src)
{
	if(!--gl_src->ref_count)
	{
		delete gl_src;
	}
}
GLSource::GLSource(ISource *p_src) : src(p_src), ref_count(1)
{
	initPBO();
	connect(this, SIGNAL(readyBroadcast()), this, SLOT(onReadyBroadcast()), Qt::BlockingQueuedConnection);
	this->start();
}

GLSource::~GLSource()
{
	while(ref_count != -1)
		Sleep(5);
	this->terminate();
	glDeleteBuffers(2, texture_PBO);
	_gl_sources.erase(this->src->getName());
	this->src->stop();
	delete this->src;
}

void GLSource::run()
{
	while(ref_count)
	{
		emit readyBroadcast();
		src->queueNextFrame(PBO_ptr);
		Sleep(25);
	}
	ref_count = -1;
}

void GLSource::onReadyBroadcast()
{
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, texture_PBO[0]);
	glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
	emit broadcastOnFrameReady(texture_PBO[0]);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, texture_PBO[1]);
	PBO_ptr = (GLubyte*)glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);
	std::swap(texture_PBO[0], texture_PBO[1]);
}
