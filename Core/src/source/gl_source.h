/*
 * gl_source.h
 *
 *  Created on: 18.02.2013
 *      Author: nonametr
 */

#ifndef GL_SOURCE_H_
#define GL_SOURCE_H_

#include <qthread.h>
#include "global.h"
#include <windows.h>
#include "glew.h"
#include "source.h"

class GLSource : public QThread
{
	Q_OBJECT
public:
	static GLSource* startSource(ISource *p_src);
	static void stopSource(GLSource *gl_src);
	GLSource(ISource *p_src);
	virtual ~GLSource();
	virtual void run();
signals:
	void readyBroadcast();
	void broadcastOnFrameReady(GLuint PBO_id);
public slots:
	void onReadyBroadcast();
private:
	void initPBO();
	ISource *src;
	GLuint texture_PBO[2];
	GLubyte* PBO_ptr;
	int ref_count;
	static map<string, GLSource*> _gl_sources;
};

#endif /* GL_SOURCE_H_ */
