//#pragma once
//#define BUFFER_OFFSET(i) ((char *)NULL + (i))
//
//enum {
//	VERTICES = 0,
//	TEX_COORDS
//};
//
//enum {
//	MVP_MATRIX = 0,
//	FRAME_TEX
//};
//
//typedef struct {
//	AVFormatContext* fmt_ctx;
//	int stream_idx;
//	AVStream* video_stream;
//	AVCodecContext* codec_ctx;
//	AVCodec* decoder;
//	AVPacket* packet;
//	AVFrame* av_frame;
//	AVFrame* gl_frame;
//	struct SwsContext* conv_ctx;
//	GLuint vao;
//	GLuint vert_buf;
//	GLuint elem_buf;
//	GLuint frame_tex;
//	GLuint program;
//	GLuint attribs[2];
//	GLuint uniforms[2];
//} AppData;
//
//							
//class FFmpeg
//{
//private:
//	AppData _appdata;
//public:
//	string const vert_shader_source;
//	string const frag_shader_source;
//	void InitializeAppData(AppData* data);
//	void clearAppdata(AppData* data);
//	bool readFrame(AppData* data);
//	bool buildShader(string const& shader_source, GLuint& shader, GLenum type);
//	bool buildProgram(AppData* data);
//	void drawFrame(AppData* data);
//	int runFFmpeg(string filename);
//
//	AppData GetAppData() { return _appdata; }
//	FFmpeg(); 
//};
//
//