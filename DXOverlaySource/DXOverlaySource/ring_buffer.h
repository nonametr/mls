#ifndef MLS_RING_BUFFER_H
#define MLS_RING_BUFFER_H

typedef unsigned int uint;
#define RING_BUFFER_DEFAULT_SIZE 16

///TODO: all should be thread safe
template<class T> class RingBuffer
{
public:
	RingBuffer() : _buffer(0)
	{
		resize(RING_BUFFER_DEFAULT_SIZE);
	}
	RingBuffer(uint size) : _buffer(0)
	{
		resize(size);
	}
	void resize(uint size)
	{
		if(_buffer)
			delete []_buffer;
		_max_offset = size - 1;
		_buffer = new T[size];
		_write_ptr = _read_ptr = &_buffer[0];
	}
	uint getSize()
	{
		return _max_offset;
	}
	~RingBuffer()
	{
		delete []_buffer;
	}
	//goes to next element and returns it
	T*&  next()
	{
		_read_ptr = _write_ptr;
		if(++_write_ptr >= &_buffer[_max_offset])
		{
			_write_ptr = &_buffer[0];
		}
		return _write_ptr;
	}
	T*& read()
	{
		return _read_ptr;
	}
private:
	T *_read_ptr;
	T *_write_ptr;
	T *_buffer;
	uint _max_offset;
};

#endif
