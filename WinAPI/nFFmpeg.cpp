#include "Stdafx.h"
#include "nFFmpeg.h"




nFFmpeg::nFFmpeg() : enable(true), animPlaying(false), bPause(false), animDone(false), updateFrame(1000000 / 60)
					//,gl(GLAPI::GetInstance())
{
}

bool nFFmpeg::load_frame(string filename)
{
	//clearData();
	initData();
	if (avformat_open_input(&fmtCtx, filename.c_str(), NULL, NULL) < 0) {
		cout << "failed to open input" << endl;
		return false;
	}

	if (avformat_find_stream_info(fmtCtx, NULL) < 0) {
		cout << "failed to get stream info" << endl;
		return false;
	}

	cout << "Amount of streams: " << fmtCtx->nb_streams << endl;
	duration = fmtCtx->duration;
	cout << "Duration" << duration << endl;

	vidx = av_find_best_stream(fmtCtx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);

	if (vidx == -1)
	{
		cout << "failed to find video stream" << endl;
		return false;
	}

	vStream = fmtCtx->streams[vidx];
	vPara = vStream->codecpar;
	vCtx = avcodec_alloc_context3(vCodec);
	avcodec_parameters_to_context(vCtx, vPara);

	vCodec = avcodec_find_decoder(vPara->codec_id);
	if (vCodec == NULL) {
		cout << "failed to find decoder" << endl;
		return false;
	}

	if (avcodec_open2(vCtx, vCodec, NULL) < 0)
	{
		cout << "failed to open codec" << endl;
		return false;
	}

	avFrame = av_frame_alloc();
	glFrame = av_frame_alloc();
	
	int size = av_image_get_buffer_size(AV_PIX_FMT_RGBA, vCtx->width, vCtx->height, 1);
	uint8_t* internal_buffer = (uint8_t*)av_malloc(size * sizeof(uint8_t));

	av_image_fill_arrays(glFrame->data, glFrame->linesize, internal_buffer, AV_PIX_FMT_RGBA, vCtx->width, vCtx->height, 1);
	packet = av_packet_alloc();

	if (packet == NULL) {
		cout << "Allocating packet failed" << endl;
		return false;
	}

	video = gl.LoadTextureFFmpeg(glFrame->data[0], vCtx->width, vCtx->height);
	//pBuf = gl.LoadPixelBufferFFmpeg(vCtx->width, vCtx->height);

}

bool nFFmpeg::readFrame()
{
	do {
		if (av_read_frame(fmtCtx, packet) < 0) {
			av_packet_unref(packet);
			return false;
		}

		if (packet->stream_index == vidx) {
			int frame_finished = 0;

			int response;
			if (vCtx->codec_type == AVMEDIA_TYPE_VIDEO) {
				response = avcodec_send_packet(vCtx, packet);
				if (response < 0 && response != AVERROR(EAGAIN) && response != AVERROR_EOF) {

				}
				else {
					if (response >= 0)
						packet->size = 0;
					response = avcodec_receive_frame(vCtx, avFrame);
					if (response >= 0)
					{
						frame_finished = 1;
					}
				}
			}
			if (frame_finished) {
				if (!convCtx) {
					convCtx = sws_getContext(vCtx->width, vCtx->height, vCtx->pix_fmt,
											vCtx->width, vCtx->height, AV_PIX_FMT_RGBA,
											SWS_BICUBIC, NULL, NULL, NULL);
				}
					sws_scale(convCtx, avFrame->data, avFrame->linesize, 0,
						vCtx->height, glFrame->data, glFrame->linesize);
					
					glBindTexture(GL_TEXTURE_2D, video);
					glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, vCtx->width, vCtx->height, GL_RGBA, GL_UNSIGNED_BYTE, glFrame->data[0]);
			}
			
		}
		pts = avFrame->best_effort_timestamp;
		//uint tempTime = ((pts - vStream->start_time) * av_q2d(vStream->time_base) * AV_TIME_BASE);
		//cout << "pts: " << tempTime << endl;
		av_packet_unref(packet);

	} while (packet->stream_index != vidx);

	return true;
}

void nFFmpeg::clearData()
{
	if (avFrame) av_free(avFrame);
	if (glFrame) av_free(glFrame);
	if (packet) av_free(packet);
	if (vCtx) avcodec_close(vCtx);
	if (fmtCtx) avformat_free_context(fmtCtx);
}

void nFFmpeg::initData()
{
	fmtCtx = NULL;
	vidx = NULL;
	vStream = NULL;
	vCtx = NULL;
	vCodec = NULL;
	avFrame = NULL;
	glFrame = NULL;
	convCtx = NULL;
}

void nFFmpeg::OnUpdate()
{
}

void nFFmpeg::Render()
{
	if (!enable) return;
	gl.PushMatrix();
	
	readFrame();
	gl.DrawVideoTexture(transformation, vCtx->width, vCtx->height, video);

	//vector<SceneObject*>& children = GetChildrenVector();
	//vector<SceneObject*>::iterator iter;
	//for (iter = children.begin(); iter != children.end(); iter++) {
	//	(*iter)->Render();
	//}

	gl.PopMatrix();	
}
void nFFmpeg::RenderTest()
{
	gl.PushMatrix();

	if (enable)
	{
		readFrame();
		gl.DrawVideoTexture(transformation, vCtx->width, vCtx->height, video);
	}

	gl.PopMatrix();
}
void nFFmpeg::SeekTo(void)
{
	if (vCtx) avcodec_flush_buffers(vCtx);
	av_seek_frame(fmtCtx, -1, vStream->start_time, AVSEEK_FLAG_FRAME);
}

void nFFmpeg::SeekTo(uint pos, uint angle)
{
	uint tempAngleVal = duration / angle;
	uint temp = pos * tempAngleVal;

	if (vCtx) avcodec_flush_buffers(vCtx);
	av_seek_frame(fmtCtx, -1, temp, AVSEEK_FLAG_FRAME);
}

void nFFmpeg::SeekTo(uint pos, uint angle, uint min)
{
	if (pos >= angle)
		pos -= 1;
	uint tempAngleVal = duration / angle;
	uint temp = pos * tempAngleVal;

	if (vCtx) avcodec_flush_buffers(vCtx);
	av_seek_frame(fmtCtx, -1, temp + min, AVSEEK_FLAG_FRAME);
}

void nFFmpeg::loop(void)
{
	uint tempTime = ((pts - vStream->start_time) * av_q2d(vStream->time_base) * AV_TIME_BASE);
	animPlaying = true;
	if (tempTime >= duration - 100000)
	{
		SeekTo();
		animPlaying = false;
	}
}

void nFFmpeg::loop(uint pos, uint angle)
{
	if (pos >= angle)
		pos -= 1;
	uint tempAngleVal = duration / angle;
	uint temp = pos * tempAngleVal;
	uint temp2 = (pos + 1) * tempAngleVal;
	uint tempTime = ((pts - vStream->start_time) * av_q2d(vStream->time_base) * AV_TIME_BASE);
	temp2 -= 100000;
	if (temp2 >= duration)
		temp2 == duration;
	
	if (tempTime > temp2)
	{
		SeekTo(pos, angle);	
	}
}

void nFFmpeg::loop(uint pos, uint angle, uint min, uint max)
{
	if (pos >= angle)
		pos -= 1;
	uint tempAngleVal = duration / angle;
	uint temp = pos * tempAngleVal;
	uint temp2 = (pos + 1) * tempAngleVal;
	uint tempTime = ((pts - vStream->start_time) * av_q2d(vStream->time_base) * AV_TIME_BASE);
	temp2 -= 100000;
	if (temp2 > duration)
		temp2 == duration;

	if (tempTime > temp + max - 100000)
	{
		SeekTo(pos, angle, min);
	}
}

void nFFmpeg::chargeLoop(uint pos, uint angle, uint min, uint max)
{
	if (pos >= angle)
		pos -= 1;
	uint tempAngleVal = duration / angle;
	uint temp = pos * tempAngleVal;
	uint temp2 = (pos + 1) * tempAngleVal;
	uint tempTime = ((pts - vStream->start_time) * av_q2d(vStream->time_base) * AV_TIME_BASE);
	temp2 -= 100000;
	if (temp2 > duration)
		temp2 == duration;

	if (tempTime > temp + max - 100000)
	{
		SeekTo(pos, angle, min);
	}
}

void nFFmpeg::pause(uint pos, uint angle, uint point)
{
	uint tempAngleVal = duration / angle;
	uint temp = pos * tempAngleVal;
	
	if (vCtx) avcodec_flush_buffers(vCtx);
	av_seek_frame(fmtCtx, -1, temp + point, AVSEEK_FLAG_ANY);
}

void nFFmpeg::playOnce(uint pos, uint angle, uint min, uint max)
{
	if(animPlaying)
	{
		if (pos >= angle)
			pos -= 1;
		uint tempAngleVal;
		if (angle == 0)
			tempAngleVal = duration;
		else
			tempAngleVal = duration / angle;
		uint temp = pos * tempAngleVal;
		uint temp2 = (pos + 1) * tempAngleVal;
		uint tempTime = ((pts - vStream->start_time) * av_q2d(vStream->time_base) * AV_TIME_BASE);
		//cout << tempTime << endl;
		temp2 -= 100000;
		if (temp2 > duration)
			temp2 == duration;

		if (tempTime >= temp + max)
		{
			animPlaying = false;
			SeekTo();
		}
	}
}
DWORD nFFmpeg::ffmpegThreadUpdateEntry()
{
	//return ffmpegThreadUpdate();
	return 0;
}

DWORD nFFmpeg::ffmpegThreadUpdate()
{
	LARGE_INTEGER begin, end;
	LARGE_INTEGER freq;
	ulong elapsed, delay;

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&begin);
	RenderTest();
	QueryPerformanceCounter(&end);
	elapsed = (end.QuadPart - begin.QuadPart) * 1000000 / freq.QuadPart;
	if (updateFrame > elapsed) {
		delay = (updateFrame - elapsed) / 1000;
		Sleep(delay);
	}

 	return 0;
}


