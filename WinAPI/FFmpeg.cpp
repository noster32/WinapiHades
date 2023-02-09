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

void FFmpeg::InitalizeAppData(AppData* data)
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
	InitalizeAppData(data);
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

			if (avcodec_receive_packet(data->codec_ctx, data->av_frame) < 0)	{
				av_packet_free(&data->packet);
				return false;
			}

			if (frame_finished) {
				if (!data->conv_ctx) {
					data->conv_ctx = sws_getContext(data->codec_ctx->width,
						data->codec_ctx->height, data->codec_ctx->pix_fmt,
						data->codec_ctx->width, data->codec_ctx->height, AV_PIX_FMT_RGB24,
						SWS_BICUBIC, NULL, NULL, NULLL);
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
	return false;
}

bool FFmpeg::buildProgram(AppData* data)
{
	return false;
}

void FFmpeg::drawFrame(AppData* data)
{
}

