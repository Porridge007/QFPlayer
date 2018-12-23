#include "QFFFmpeg.h"
#include <iostream>

#pragma comment(lib,"avformat.lib") //工具类
#pragma comment(lib,"avutil.lib")	//文件格式
#pragma comment(lib,"avcodec.lib")  //编码
#pragma comment(lib,"swscale.lib")
#pragma  comment(lib,"swresample.lib")

 double r2d(AVRational r)
 {
 	return r.num == 0 || r.den == 0 ? 0. : (double)r.num / (double)r.den;
 }

int QFFFmpeg::Open(const  char *path)
{
	Close();
	mutex.lock();
	int re = avformat_open_input(&ic, path, nullptr, nullptr);
	if (re)
	{
		mutex.unlock();
		char buf[1024] = { 0 };
		av_strerror(re, errorbuf, sizeof(buf));
		std::cout << "open failed:" << errorbuf << std::endl;
		return 0;
	}
	totalMs = ((ic->duration / AV_TIME_BASE)*1000);
	
	for (int i = 0; i < ic->nb_streams; i++)
	{
		AVCodecContext *enc = ic->streams[i]->codec;
		if (enc->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			videoStream = i;
			//r.num == 0 || r.den == 0 ? 0. : (double)r.num / (double)r.den;
			fps = r2d(ic->streams[i]->avg_frame_rate);
// 			fps = ic->streams[i]->avg_frame_rate.num == 0 || ic->streams[i]->avg_frame_rate.den ==0? 0.
// 				: (double)ic->streams[i]->avg_frame_rate.num / (double)ic->streams[i]->avg_frame_rate.den;
			AVCodec *codec = avcodec_find_decoder(enc->codec_id);
			if (!codec)
			{
				mutex.unlock();
				std::cout << "video code not find";
				return 0;
			}
			int err = avcodec_open2(enc, codec, nullptr);
			if (err)
			{
				mutex.unlock();
				char buf[1024] = { 0 };
				av_strerror(err, buf, sizeof(buf));
				std::cout << buf << std::endl;
				return 0;
			}
			std::cout << "open codec success!";
		}
		else if (enc->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			audioStream = i;
			AVCodec *codec = avcodec_find_decoder(enc->codec_id);
			if (avcodec_open2(enc, codec, nullptr) < 0)
			{
				mutex.unlock();
				return false;
			}
			this->sampleRate = enc->sample_rate;
			this->channel = enc->channels;
			switch (enc->sample_fmt)
			{
			case AV_SAMPLE_FMT_S16:
				this->sampleSize = 16;
				break;
			case AV_SAMPLE_FMT_S32:
				this->sampleSize = 32;
				break;
			default:
				break;
			}
		}
	}
	mutex.unlock();
	return totalMs;
}
void QFFFmpeg::Close()
{
	mutex.lock();
	if (ic) avformat_close_input(&ic);
	if (yuv) av_frame_free(&yuv);
	if (cCtx)
	{
		sws_freeContext(cCtx);
		cCtx = nullptr;
	}
	if (aCtx)
	{
		swr_free(&aCtx);
	}
	mutex.unlock();
}
std::string QFFFmpeg::GetError()
{
	mutex.lock();
	std::string re = this->errorbuf;
	mutex.unlock();
	return re;
}

AVPacket QFFFmpeg::Read()
{
	AVPacket pkt;
	memset(&pkt, 0, sizeof(AVPacket));
	mutex.lock();
	if (!ic)
	{
		mutex.unlock();
		return pkt;
	}
	int err = av_read_frame(ic,&pkt);
	if (err)
	{
		av_strerror(err, errorbuf, sizeof(errorbuf));
	}
	mutex.unlock();
	return pkt;
}

int QFFFmpeg::GetPts(const AVPacket *pkt)
{
	mutex.lock();
	if (!ic)
	{
		mutex.unlock();
		return -1;
	}
	int pts = (pkt->pts*r2d(ic->streams[pkt->stream_index]->time_base) )* 1000;
	mutex.unlock();
	return pts;
}

int QFFFmpeg::Decode(const AVPacket *pkt)
{
	mutex.lock();
	if (!ic)
	{
		mutex.unlock();
		return NULL;
	}
	if (!yuv)
	{
		yuv = av_frame_alloc();
	}
	if (!pcm)
	{
		pcm = av_frame_alloc();
	}
	AVFrame *frame = yuv;
	if (pkt->stream_index == audioStream)
	{
		frame = pcm;
	}
	//使用索引 解码音视频 代码是不变的
	int re = avcodec_send_packet(ic->streams[pkt->stream_index]->codec, pkt);
	if (re)
	{
		mutex.unlock();
		return NULL;
	}
	re = avcodec_receive_frame(ic->streams[pkt->stream_index]->codec, frame);
	if (re)
	{
		mutex.unlock();
		return NULL;
	}
	mutex.unlock();
	int p = frame->pts*r2d(ic->streams[pkt->stream_index]->time_base)*1000;
	if (pkt->stream_index == audioStream) this->pts = p;
	return p;
}

bool QFFFmpeg::ToRGB(char *out, int outwidth, int outheight)
{
	mutex.lock();
	if (!ic||!yuv)
	{
		mutex.unlock();
		return false;
	}
	AVCodecContext *videoCtx = ic->streams[videoStream]->codec;
	cCtx = sws_getCachedContext(cCtx, videoCtx->width,
		videoCtx->height,
		videoCtx->pix_fmt,
		outwidth, outheight,
		AV_PIX_FMT_BGRA,
		SWS_BICUBIC,
		nullptr, nullptr, nullptr);
	if (!cCtx)
	{
		std::cout << "sws_getCachedContext failed!" << std::endl;
		mutex.unlock();
		return false;
	}
	uint8_t *data[AV_NUM_DATA_POINTERS];
	data[0] = (uint8_t *)out;
	int linesize[AV_NUM_DATA_POINTERS] = { 0 };
	linesize[0] = outwidth * 4;
	//rgb转换
	int h = sws_scale(cCtx, yuv->data, yuv->linesize, 0, videoCtx->height, data, linesize);
	if (h > 0)
	{
		std::cout << "(" << h << ")";
	}
	mutex.unlock();
	return true;
}

bool QFFFmpeg::Seek(float pos)
{
	mutex.lock();
	if (!ic)
	{
		mutex.unlock();
		return false;
	}
	int64_t stamp = 0;
	stamp = pos*ic->streams[videoStream]->duration;
	int re = av_seek_frame(ic, videoStream, stamp, 
	//向后找||关键帧
		AVSEEK_FLAG_BACKWARD|AVSEEK_FLAG_FRAME);
	//解码缓冲的句柄在此 清缓冲
	avcodec_flush_buffers(ic->streams[videoStream]->codec);
	pts = stamp *r2d(ic->streams[videoStream]->time_base) * 1000;
	mutex.unlock();
	if (re > 0)
		return true;
	return false;
}

int QFFFmpeg::ToPCM(char *out)
{
	mutex.lock();
	if (!ic || !pcm||!out)
	{
		mutex.unlock();
		return 0;
	}
	AVCodecContext *ctx = ic->streams[audioStream]->codec;
	if (aCtx == nullptr)
	{
		aCtx = swr_alloc();
		swr_alloc_set_opts(aCtx, ctx->channel_layout, 
			AV_SAMPLE_FMT_S16,
			ctx->sample_rate,ctx->channels,ctx->sample_fmt,ctx->sample_rate,
			0,0);
		swr_init(aCtx);
	}
	uint8_t *data[1];
	data[0] = (uint8_t *)out;
	int len = swr_convert(aCtx, data, 10000, (const uint8_t **)pcm->data, pcm->nb_samples);
	if (len <= 0)
	{
		mutex.unlock();
		return 0;
	}
	int outsize = av_samples_get_buffer_size(nullptr, ctx->channels, 
		pcm->nb_samples, AV_SAMPLE_FMT_S16, 0);
	mutex.unlock();
	return outsize;
}

QFFFmpeg::QFFFmpeg()
{
	errorbuf[0] = '\0';
	av_register_all();
}


QFFFmpeg::~QFFFmpeg()
{
}
