#include "Libx264Encoder.h"
#include "rgb2yuv.h"
#include "thread_core.h"

Libx264Encoder::Libx264Encoder() : broadcastEncodedFrame(NULL), encoder(NULL), _rb_for_encode(NULL)
{
	_rb_for_encode = new RingBuffer<x264_picture_t>(16);
	_rb_for_broadcast.resize(128);
}

Libx264Encoder::~Libx264Encoder()
{
    _running = false;
    while (!_running)
    {
        Sleep(10);
    }
	if(encoder)
	{
		for(uint i = 0; i < _rb_for_encode->getSize(); ++i)
		{
			x264_picture_clean(_rb_for_encode->next());
		}
		x264_encoder_close(encoder);
	}
}

void Libx264Encoder::run()
{
	static int cnt = 0;
	int i_nals;
	x264_nal_t *nals;
	x264_picture_t pic_encoded;

    while (_running)
    {
    	x264_picture_t *pic_to_encode = _rb_for_encode->read();
    	if(pic_to_encode == NULL)
    	{
    		Sleep(3);
    		continue;
    	}
    	pic_to_encode->i_pts = cnt;
    	pic_to_encode->i_type = X264_TYPE_AUTO;
        x264_nal_t* nals;
        int i_nals;
        int frame_size = x264_encoder_encode(encoder, &nals, &i_nals, pic_to_encode, &pic_out);
        if (frame_size >= 0)
        {
        	++cnt;
        	char** nals_data = _rb_for_broadcast.getNextWritePtr();
    		delete [](*nals_data);
    		*nals_data = new char[frame_size+2];
    		memcpy(*nals_data, nals[0].p_payload, frame_size);
    		_rb_for_broadcast.write();
        	broadcastEncodedFrame(this, (char*)*nals_data, frame_size);
        }
    }
    _running = !_running;
}

void Libx264Encoder::onShutdown()
{
    _running = false;
    while (!_running)
    {
        Sleep(10);
    }
}

void x264_log(void *param, int i_level, const char *psz, va_list argptr)
{
	//printf(psz, argptr);
}

bool Libx264Encoder::setup(ENCODER_INPUT *init_ops, CBEncoderPlugin cb)
{
	x264_param_t param;

	x264_param_default(&param);
	x264_param_default_preset(&param, x264_preset_names[init_ops->preset], "zerolatency");
	x264_param_apply_profile(&param, x264_profile_names[init_ops->quality]);
	param.i_width 	= init_ops->width;
	param.i_height 	= init_ops->height;
    param.b_vfr_input = 1;
	param.i_fps_num = 25;
	param.i_fps_den = 1;
	//Rate control:
	//param.i_nal_hrd         	= X264_NAL_HRD_CBR;
	param.rc.i_rc_method 		= X264_RC_ABR;//using average bit rate
	param.rc.f_rf_constant  	= 0.0f;
	param.vui.b_fullrange 		= 0;

	param.rc.i_bitrate 			= init_ops->bitrate;
	param.rc.i_vbv_max_bitrate 	= init_ops->bitrate*1.2;
	param.rc.i_vbv_buffer_size 	= init_ops->buffer_size;
	param.i_threads = ThreadCore::getSingletonPtr()->getNumCpus();
	//For streaming:
	//param.i_timebase_num = 1;
    //param.i_timebase_den = 1000;

	param.b_repeat_headers = 1;
	//param.b_annexb = 1;
	broadcastEncodedFrame = cb;
	//param.pf_log  = x264_log;
	//param.i_log_level = X264_LOG_INFO;

	encoder = x264_encoder_open(&param);

	x264_picture_alloc(&pic_in, X264_CSP_I420, init_ops->width, init_ops->height);

	for(uint i = 0; i < _rb_for_broadcast.getSize(); ++i)
	{
		char **nals_data = _rb_for_broadcast.next();
		*nals_data = new char[16];
		*nals_data = NULL;
	}
	for(uint i = 0; i < _rb_for_encode->getSize(); ++i)
	{
		x264_picture_alloc(_rb_for_encode->next(), X264_CSP_I420, init_ops->width, init_ops->height);
	}
	ThreadCore::getSingletonPtr()->startThread(this);

	return true;
}
void Libx264Encoder::encodeFrame(unsigned char *yuv_y, unsigned char *yuv_u, unsigned char *yuv_v, int width, int height)
{
	x264_picture_t *pic_to_convert = _rb_for_encode->getNextWritePtr();
    memcpy(pic_to_convert->img.plane[0], yuv_y, width*height);
    memcpy(pic_to_convert->img.plane[1], yuv_u, width*height);
    memcpy(pic_to_convert->img.plane[2], yuv_v, width*height);
	_rb_for_encode->write();
}
