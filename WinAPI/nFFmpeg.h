#pragma once

extern "C" 
{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavfilter/avfilter.h>
#include <libavdevice/avdevice.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>
#include <libavutil/avutil.h>
#include <libavutil/imgutils.h>
}


class nFFmpeg
{
public:
	bool load_frame(string filename, int* width_out, int* height_out, unsigned char** data_out);
};

