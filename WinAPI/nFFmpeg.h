#pragma once
#include "SceneObject.h"

class nFFmpeg : public SceneObject
{
private:
	AVFormatContext* fmtCtx;
	int vidx;
	AVStream* vStream;
	AVCodecParameters* vPara;
	const AVCodec* vCodec;
	AVCodecContext* vCtx;
	SwsContext* swsCtx;
	AVFrame RGBFrame;
	AVFrame* avFrame;
	AVFrame* glFrame;
	uint8_t* rgbbuf;

	struct SwsContext* convCtx;

	AVFrame vFrame;
	AVPacket* packet;
	int ret;

	Timer timer, t1, t2;

public:
	uint video;
	uint pBuf;
	uint width;
	uint height;
	

	bool load_frame(string filename);
	bool readFrame(); 
	void clearData();
	void initData();
	virtual void OnUpdate();
	virtual void Render();

	nFFmpeg();
};

