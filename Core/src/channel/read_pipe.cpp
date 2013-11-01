#include "read_pipe.h"

void ReadPipe::setup_pipe()
{
	_pipe = CreateNamedPipeA(
		_pipe_name.c_str(), // name of the pipe
		PIPE_ACCESS_INBOUND, // 1-way pipe
		PIPE_TYPE_BYTE, // read data as a byte stream
		1, // only allow 1 instance of this pipe
		0, // no outbound buffer
		0, // no inbound buffer
		5000, // use default wait time
		NULL // use default security attributes
		);
	if (_pipe == NULL || _pipe == INVALID_HANDLE_VALUE) 
	{
		traceerr("Failed to create inbound pipe instance.");
		return;
	}
	bool result = ConnectNamedPipe(_pipe, NULL);
	if (!result)
	{
		traceerr( "Failed to make connection on named pipe.");
		CloseHandle(_pipe); // close the pipe
		return;
	}
	running = true;
}
void ReadPipe::run()
{
	DWORD numBytesRead = 0;
	setup_pipe();
	while(running)
	{
		char *data = *_rb_frame->next();
		// This call blocks until a client process reads all the data
		bool result = ReadFile(
			_pipe,
			data, // the data from the pipe will be put here
			READ_PIPE_BUFFER_SIZE, // number of bytes allocated
			&numBytesRead, // this will store number of bytes actually read
			NULL // not using overlapped IO
			);
		if (!result) 
		{
			traceerr("Failed to read data. Pipe connection lost. Trying to reinitialize reading pipe!");
			CloseHandle(_pipe);
			running = false;
			setup_pipe();
		}

		emit onPipeReadyRead(data, numBytesRead);
		Sleep(25);
	}
}
ReadPipe::~ReadPipe()
{ 
	running = false;
	while(running) Sleep(1);
	for(uint i = 0; i < _rb_frame->getSize(); ++i)
	{
		free(*_rb_frame->next());
	}
	delete _rb_frame;
	CloseHandle(_pipe); 
}
ReadPipe::ReadPipe(string name) : running(true)
{
	_rb_frame = new RingBuffer<char*>(9);//9x buffering
	for(uint i = 0; i < _rb_frame->getSize(); ++i)
	{
		char **frame = _rb_frame->next();
		*frame = (char*) malloc(sizeof(char)*READ_PIPE_BUFFER_SIZE);
	}
	_pipe_name = "\\\\.\\pipe\\" + name;
	this->start();
}
