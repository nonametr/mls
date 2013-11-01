#ifndef LIBX264ENCODER_H_
#define LIBX264ENCODER_H_

#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <time.h>
#include "global.h"
#include "thread.h"
#include "ring_buffer.h"

extern "C" {
#include "./x264/x264.h"
}

typedef void* ENCODER_HANDLE;
typedef void (*CBEncoderPlugin)(ENCODER_HANDLE handle, char *encoded_data, unsigned int encoded_size);
#define EXTERN_DLL __declspec(dllexport)

class Libx264Encoder : public Thread
{
public:
	Libx264Encoder();
	virtual ~Libx264Encoder();

    virtual void run();
    virtual void onShutdown();///it should be almost atomic. no general mutex locks

	bool setup(ENCODER_INPUT *init_ops, CBEncoderPlugin cb);
    void encodeFrame(unsigned char *yuv_y, unsigned char *yuv_u, unsigned char *yuv_v, int width, int height);
private:
	volatile bool _running;
	CBEncoderPlugin broadcastEncodedFrame;
	x264_t* encoder;
	RingBuffer<char*> _rb_for_broadcast;
	RingBuffer<x264_picture_t> *_rb_for_encode;
	x264_picture_t pic_in, pic_out;
};

#endif /* LIBX264ENCODER_H_ */
