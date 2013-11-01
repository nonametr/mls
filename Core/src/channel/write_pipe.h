#pragma once

#include "global.h"
#include <Windows.h>
#include <qthread>

class WritePipe : public QThread//only for windows. TODO: Add impl. for linux and factory creation
{
public:
	WritePipe(string name);
	bool send(char *p_data, unsigned int len);
	void stop();
	~WritePipe();
protected:
	WritePipe() : data_ptr(NULL), data_len(0), running(false), _pipe(NULL)
	{};
private:
	void run();
	void setup_pipe();

	char *data_ptr;
	unsigned int data_len;

	bool running;

	HANDLE _pipe;
	string _pipe_name;
};
