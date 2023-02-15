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
	AVFrame* avFrame;
	AVFrame* glFrame;
	uint8_t* rgbbuf;

	struct SwsContext* convCtx;

	AVFrame vFrame;
	AVPacket* packet;
	int ret;

	Timer timer, t1, t2;

	bool enable;

	uint video;
	uint pBuf;
	uint width;
	uint height;
	uint pts;
	uint duration;

public:
	bool load_frame(string filename);
	bool readFrame(); 
	void clearData();
	void initData();
	virtual void OnUpdate();
	virtual void Render();

	void SeekTo(void);
	void SeekTo(uint pos, uchar angle);
	
	void loop(void);
	void loop(uint pos, uchar angle);

	void SetEnable(void) { enable ? enable = false : enable = true; }
	void SetEnable(bool _ena) { enable = _ena; }
	
	uint GetPts() { return pts; }

	nFFmpeg();
};

