#pragma once
#include "SceneObject.h"
//#include "GLAPI.h"

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

	bool animPlaying;
	bool bPause;
	bool animDone;

public:
	bool load_frame(string filename);
	bool readFrame(); 
	void clearData();
	void initData();
	virtual void OnUpdate();
	virtual void Render();
	void RenderTest();

	void SeekTo(void);
	void SeekTo(uint pos, uint angle);
	void SeekTo(uint pos, uint angle, uint min);
	
	void loop(void);
	void loop(uint pos, uint angle);
	void loop(uint pos, uint angle, uint min, uint max);

	void pause(uint pos, uint angle, uint point);

	void playOnce(uint pos, uint angle, uint min, uint max);

	void SetEnable(void) { enable ? enable = false : enable = true; }
	void SetEnable(bool _ena) { enable = _ena; }
	
	uint GetPts() { return pts; }

	bool GetAnimPlaying() { return animPlaying; }
	void SetAnimPlaying() { animPlaying = true; }
	nFFmpeg();
};

