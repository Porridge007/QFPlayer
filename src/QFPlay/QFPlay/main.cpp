#include "QFPlay.h"
#include <QtWidgets/QApplication>
#include <iostream>
#include "QFFFmpeg.h"
#include <QAudioOutput>
/*
static double r2d(AVRational r)
{
	return r.num == 0 || r.den == 0 ? 0. : (double)r.num / (double)r.den;
}*/
int main(int argc, char *argv[])
{/*
	QAudioOutput *out;
	QAudioFormat fmt;
	fmt.setSampleRate(48000);//一秒钟48000个音频
	fmt.setSampleSize(16);
	fmt.setChannelCount(2);
	fmt.setCodec("audio/pcm");
	fmt.setByteOrder(QAudioFormat::LittleEndian);
	fmt.setSampleType(QAudioFormat::UnSignedInt);
	out = new QAudioOutput(fmt);
	ad->write()
	QIODevice *ad = out->start();*/
	/*if (QFFFmpeg::Get()->Open("video.mp4"))
	{
		std::cout << "open success!" << std::endl;
	}
	else
	{
		std::cout << "open failed!"<<QFFFmpeg::Get()->GetError().c_str()<<std::endl;
		return -1;
	}
	char *rgb = new char[800 * 600 * 4];
	for (;;)
	{
		AVPacket pkt = QFFFmpeg::Get()->Read();
		if (pkt.size == 0)
			break;
		std::cout << "pts =" << pkt.pts<<std::endl;
		if (pkt.stream_index != QFFFmpeg::Get()->videoStream)
		{
			av_packet_unref(&pkt);
			continue;
		}
		AVFrame *yuv = QFFFmpeg::Get()->Decode(&pkt);
		if (yuv)
		{
			std::cout << "[D]";	
			QFFFmpeg::Get()->ToRGB(yuv, rgb,800, 600);		
		}
		av_packet_unref(&pkt);
	}*/
	
	/*
	av_register_all();
	char *path = "vedio.mp4";
	//存放视频或者流打开后的信息
	AVFormatContext *ic = nullptr;
	//打开文件流
	int re = avformat_open_input(&ic, path, nullptr, nullptr);
	if (re)
	{
		char buf[1024] = { 0 };
		av_strerror(re, buf, sizeof(buf));
		std::cout << "open failed:"<<buf<< std::endl;
		return -1;
	}
	int totalSec = ic->duration / AV_TIME_BASE;
	std::cout << "file total is " << totalSec / 60 << "min" << totalSec % 60 << "sec" << std::endl;
	int videoStream = 0;
	AVCodecContext *videoCtx = nullptr;
	for (int i = 0; i < ic->nb_streams; i++)
	{
		AVCodecContext *enc = ic->streams[i]->codec;
		if (enc->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			videoCtx = enc;
			videoStream = i;
			AVCodec *codec = avcodec_find_decoder(enc->codec_id);
			if (!codec)
			{
				std::cout << "video code not find";
				return -1;
			}
			int err = avcodec_open2(enc, codec,nullptr);
			if (err)
			{
				char buf[1024] = { 0 };
				av_strerror(err, buf, sizeof(buf));
				std::cout << buf<<std::endl;
				return -2;
			}
			std::cout << "open codec success!";
		}
	}
	AVFrame *yuv = av_frame_alloc();
	SwsContext *cCtx = nullptr;
	int outwidth = 800;
	int outheight = 600;
	char *rgb = new char[outwidth*outheight*4];
	for (;;)
	{	
		//存放读取的数据包 视频帧
		AVPacket pkt;
		re = av_read_frame(ic, &pkt);
		if (re)break;
		if (pkt.stream_index != vedioStream)
		{
			av_packet_unref(&pkt);
			continue;
		}
		//pts 是64位的时间戳 可以由此推算时间 根据time_base
		int pts = pkt.pts*r2d(ic->streams[pkt.stream_index]->time_base) * 1000;
		re = avcodec_send_packet(videoCtx, &pkt);
		if (re)
		{
			av_packet_unref(&pkt);
			continue;
		}
		re = avcodec_receive_frame(videoCtx, yuv);
		if (re)
		{
			av_packet_unref(&pkt);
			continue;
		}
		std::cout << "[D]";
		//转码器创建
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
			break;
		}
		uint8_t *data[AV_NUM_DATA_POINTERS];
		data[0] =(uint8_t *) rgb;
		int linesize[AV_NUM_DATA_POINTERS] = { 0 };
		linesize[0] = outwidth * 4;
		//rgb转换
		int h = sws_scale(cCtx, yuv->data, yuv->linesize, 0, videoCtx->height, data, linesize);
		if (h > 0)
		{
			std::cout <<"("<< h<<")";
		}
		std::cout << "pts = " << pts<<std::endl;
		av_packet_unref(&pkt);	
	}
	if (cCtx)
	{
		sws_freeContext(cCtx);
		cCtx = nullptr;
	}
	avformat_close_input(&ic);
	ic = nullptr;	
*/
    QApplication a(argc, argv);
    QFPlay w;
    w.show();
    return a.exec();
}
