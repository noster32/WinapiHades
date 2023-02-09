#include "Stdafx.h"
#include "FFmpeg.h"


FFmpeg::FFmpeg() : vert_shader_source(
	"aversion 150\n"
	"in vec3 vertex;\n"
	"in vec2 texCoord0;\n"
	"uniform mat4 mvpMatrix;\n"
	"out vec2 texCoord;\n"
	"void main() {\n"
	"	gl_Position = mvpMatrix = vec4(vertexx, 1.0);\n"
	"	texCoord = texCoord0;\n"
	"}\n"),
frag_shader_source(
	"#version 150\n"
	"uniform sampler2D frameTex;\n"
	"in vec2 texCoord;\n"
	"out vec4 fragColor;\n"
	"void main() {\n"
	"	fragColor = texture(frameTex, texCoord);\n"
	"}\n")
{
}

void FFmpeg::InitializeAppData(AppData* data)
{
	data->fmt_ctx = NULL;
	data->stream_idx = -1;
	data->video_stream = NULL;
	data->codec_ctx = NULL;
	data->decoder = NULL;
	data->av_frame = NULL;
	data->gl_frame = NULL;
	data->conv_ctx = NULL;
}

void FFmpeg::clearAppdata(AppData* data)
{
	if (data->av_frame) av_free(data->av_frame);
	if (data->gl_frame) av_free(data->gl_frame);
	if (data->packet) av_free(data->packet);
	if (data->codec_ctx) avcodec_close(data->codec_ctx);
	if (data->fmt_ctx) avformat_free_context(data->fmt_ctx);
	glDeleteVertexArrays(1, &data->vao);
	glDeleteBuffers(1, &data->vert_buf);
	glDeleteBuffers(1, &data->elem_buf);
	glDeleteTextures(1, &data->frame_tex);
	InitializeAppData(data);
}

bool FFmpeg::readFrame(AppData* data)
{
	do {
		if (av_read_frame(data->fmt_ctx, data->packet) < 0) {
			av_packet_free(&data->packet);
			return false;
		}

		if (data->packet->stream_index == data->stream_idx) {
			int frame_finished = 0;

			if (avcodec_receive_packet(data->codec_ctx, data->packet) < 0)	{
				av_packet_free(&data->packet);
				return false;
			}

			if (frame_finished) {
				if (!data->conv_ctx) {
					data->conv_ctx = sws_getContext(data->codec_ctx->width,
						data->codec_ctx->height, data->codec_ctx->pix_fmt,
						data->codec_ctx->width, data->codec_ctx->height, AV_PIX_FMT_RGB24,
						SWS_BICUBIC, NULL, NULL, NULL);
				}

				sws_scale(data->conv_ctx, data->av_frame->data, data->av_frame->linesize, 0, data->codec_ctx->height,
					data->gl_frame->data, data->gl_frame->linesize);

				glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, data->codec_ctx->width,
					data->codec_ctx->height, GL_RGB, GL_UNSIGNED_BYTE,
					data->gl_frame->data[0]);
			}
		}

		av_packet_free(&data->packet);
	} while (data->packet->stream_index != data->stream_idx);

	return true;
}

bool FFmpeg::buildShader(string const& shader_source, GLuint& shader, GLenum type)
{
	int size = shader_source.length();

	shader = glCreateShader(type);
	char const* c_shader_source = shader_source.c_str();
	glShaderSource(shader, 1, (GLchar const**)&c_shader_source, &size);
	glCompileShader(shader);
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		cout << "failed to compile shader" << endl;
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char* log = new char[length];
		glGetShaderInfoLog(shader, length, &length, log);
		cout << log << endl;
		delete[] log;
		return false;
	}

	return true;
}

bool FFmpeg::buildProgram(AppData* data)
{
	GLuint v_shader, f_shader;
	if (!buildShader(vert_shader_source, v_shader, GL_VERTEX_SHADER)) {
		cout << "failed to build vertex shader" << endl;
	}

	if (!buildShader(frag_shader_source, f_shader, GL_FRAGMENT_SHADER)) {
		cout << "failed to build fragment shader" << endl;
		return false;
	}

	data->program = glCreateProgram();
	glAttachShader(data->program, v_shader);
	glAttachShader(data->program, f_shader);
	glLinkProgram(data->program);
	GLint status;
	glGetProgramiv(data->program, GL_LINK_STATUS, &status);
	if (status != GL_TRUE) {
		cout << "failed to link program" << endl;
		int length;
		char* log = new char[length];
		glGetShaderInfoLog(data->program, length, &length, log);
		cout << log << endl;
		delete[] log;
		return false;
	}

	data->uniforms[MVP_MATRIX] = glGetUniformLocation(data->program, "mvpMatrix");
	data->uniforms[FRAME_TEX] = glGetUniformLocation(data->program, "frameTex");
	data->uniforms[VERTICES] = glGetUniformLocation(data->program, "vertex");
	data->uniforms[TEX_COORDS] = glGetAttribLocation(data->program, "texCoord0");

	return true;
}

void FFmpeg::drawFrame(AppData* data)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, data->frame_tex);
	glBindVertexArray(data->vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
	glBindVertexArray(0);
	SwapBuffers();
}

int FFmpeg::runFFmpeg(string filename)
{
	//파일 이름 넣기

	avdevice_register_all();
	avformat_network_init();

	AppData data;
	InitializeAppData(&data);
										//argv 파일 이름
	if (avformat_open_input(&data.fmt_ctx, filename.c_str(), NULL, NULL) < 0) {
		std::cout << "failed to open input" << std::endl;
		clearAppdata(&data);
		return -1;
	}

	if (avformat_find_stream_info(data.fmt_ctx, NULL) < 0) {
		std::cout << "failed to get stream info" << std::endl;
		clearAppdata(&data);
		return -1;
	}

	av_dump_format(data.fmt_ctx, 0, filename.c_str(), 0);

	for (unsigned int i = 0; i < data.fmt_ctx->nb_streams; ++i)
	{
		if (data.fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			data.stream_idx = i;
			break;
		}
	}

	if (data.stream_idx == -1)
	{
		std::cout << "failed to find video stream" << std::endl;
		clearAppdata(&data);
		return -1;
	}

	data.video_stream = data.fmt_ctx->streams[data.stream_idx];
	data.codec_ctx = data.video_stream->codecpar;

	data.decoder = avcodec_find_decoder(data.codec_ctx->codec_id);
	if (data.decoder == NULL)
	{
		std::cout << "failed to find decoder" << std::endl;
		clearAppdata(&data);
		return -1;
	}
	
	// 디코더
	if (avcodec_open2(data.codec_ctx, data.decoder, NULL) < 0)
	{
		std::cout << "failed to open codec" << std::endl;
		clearAppdata(&data);
		return -1;
	}

	// 프레임 할당
	data.av_frame = av_frame_alloc();
	data.gl_frame = av_frame_alloc();
	int size = av_image_get_buffer_size(AV_PIX_FMT_RGB24, data.codec_ctx->width ,data.codec_ctx->height, 2);
	uint8_t* internal_buffer = (uint8_t*)av_malloc(size * sizeof(uint8_t));
	av_image_fill_arrays(data.av_frame->data, data.av_frame->linesize, internal_buffer, AV_PIX_FMT_RGB24, data.codec_ctx->width, data.codec_ctx->height, 2);
	data.packet = (AVPacket*)av_malloc(sizeof(AVPacket));

	//if (!glfwInit()) {
	//	std::cout << "glfw failed to init" << std::endl;
	//	glfwTerminate();
	//	clearAppdata(&data);
	//	return -1;
	//}

	//float aspect = (float)data.codec_ctx->width / (float)data.codec_ctx->height;
	//int adj_width = aspect * 300;
	//int adj_height = 300;
	//glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	//glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
	//glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//if (!glfwOpenWindow(adj_width, adj_height, 0, 0, 0, 0, 0, 0, GLFW_WINDOW)) {
	//	std::cout << "failed to open window" << std::endl;
	//	glfwTerminate();
	//	clearAppdata(&data);
	//	return -1;
	//}

	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glEnable(GL_TEXTURE_2D);

	// 쉐이더 init
	if (!buildProgram(&data)) {
		std::cout << "failed to initialize shaders" << std::endl;
		glfwTerminate();
		clearAppdata(&data);
		return -1;
	}
	glUseProgram(data.program);

	// 렌더 
	glGenVertexArrays(1, &data.vao);
	glBindVertexArray(data.vao);

	glGenBuffers(1, &data.vert_buf);
	glBindBuffer(GL_ARRAY_BUFFER, data.vert_buf);
	float quad[20] = {
		-1.0f,  1.0f, 0.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 1.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 0.0f
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
	glVertexAttribPointer(data.attribs[VERTICES], 3, GL_FLOAT, GL_FALSE, 20,
		BUFFER_OFFSET(0));
	glEnableVertexAttribArray(data.attribs[VERTICES]);
	glVertexAttribPointer(data.attribs[TEX_COORDS], 2, GL_FLOAT, GL_FALSE, 20,
		BUFFER_OFFSET(12));
	glEnableVertexAttribArray(data.attribs[TEX_COORDS]);
	glGenBuffers(1, &data.elem_buf);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data.elem_buf);
	unsigned char elem[6] = {
		0, 1, 2,
		0, 2, 3
	};
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elem), elem, GL_STATIC_DRAW);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &data.frame_tex);
	glBindTexture(GL_TEXTURE_2D, data.frame_tex);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, data.codec_ctx->width, data.codec_ctx->height,
		0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glUniform1i(data.uniforms[FRAME_TEX], 0);

	//glMaterialivglOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(data.uniforms[MVP_MATRIX], 1, GL_FALSE, glm::value_ptr(mvp));

	bool running = true;

	// 실행
	while (readFrame(&data) && running) {
		//running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
		drawFrame(&data);
	}

	avformat_close_input(&data.fmt_ctx);

	// 초기화
	glfwTerminate();
	clearAppdata(&data);
}

