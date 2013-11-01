#include "write_pipe.h"
#include "runtime.h"

void WritePipe::setup_pipe()
{
	// Create a pipe to send data
	_pipe = CreateNamedPipeA(
		_pipe_name.c_str(), // name of the pipe
		PIPE_ACCESS_OUTBOUND, // 1-way pipe -- send only
		PIPE_TYPE_BYTE | PIPE_WAIT, // send data as a byte stream
		1, // only allow 1 instance of this pipe
		0, // no outbound buffer
		0, // no inbound buffer
		10, // use default wait time
		NULL // use default security attributes
		);
	if (_pipe == NULL || _pipe == INVALID_HANDLE_VALUE) 
	{
		traceerr("Failed to create outbound pipe instance.");
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

void WritePipe::stop()
{
	running = false;
	QThread::terminate();
}

void WritePipe::run()
{
	DWORD numBytesWritten = 0;
	setup_pipe();
	while(running)
	{
		if(data_ptr == NULL)
		{
			continue;
		}

		// This call blocks until a client process reads all the data
		//rdtscll(r_start);
		bool result = WriteFile(
			_pipe, // handle to our outbound pipe
			data_ptr, // data to send
			data_len, // length of data to send (bytes)
			&numBytesWritten, // will store actual amount of data sent
			NULL // not using overlapped IO
			);
		//rdtscll(r_end);

		Sleep(39);
		//data_ptr = NULL;
		if (!result)
		{
			CloseHandle(_pipe);
			if(running)
			{
				traceerr("Error! FFMPEG connection lost!");
				running = false;
				setup_pipe();
			}
		}
	}
}
bool WritePipe::send(char *p_data, unsigned int len)
{
	data_ptr = p_data;
	data_len = len;
	return running;
}
WritePipe::WritePipe(string name) : running(false), data_ptr(NULL), data_len(0), _pipe(NULL)
{
	_pipe_name = "\\\\.\\pipe\\" + name;
}
WritePipe::~WritePipe()
{
	CloseHandle(_pipe);
}
