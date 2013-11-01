#ifndef MLS_READ_PIPE_H
#define MLS_READ_PIPE_H

#include "global.h"
#include <Windows.h>
#include <qobject>
#include <qthread>
#include "ring_buffer.h"

#define  READ_PIPE_BUFFER_SIZE 2048

class ReadPipe : public QThread//only for windows. TODO: Add impl. for linux and factory creation
{
	Q_OBJECT
public:
	ReadPipe(string name);
	~ReadPipe();
private:
	void setup_pipe();
	void run();
	HANDLE _pipe;
	bool running;
	RingBuffer<char*> *_rb_frame;
	string _pipe_name;
signals:
	void onPipeReadyRead(char *p_data, unsigned int size);
};

#endif
