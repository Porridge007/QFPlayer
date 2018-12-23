#pragma once
extern "C"
{
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
}
#include <string>
#include <QMutex>
class QFFFmpeg
{
public:
	///单例模式
	///@return 返回所创建对象的指针
	static QFFFmpeg *Get()
	{
		static QFFFmpeg ff;
		return &ff;
	}
	//////////////////////////////////////////////////////////////////////////
	///打开视频文件，如果上次已经打开会先关闭
	///@para path 视频文件路径
	///@return int return total ms
	int Open(const  char *path);
	//////////////////////////////////////////////////////////////////////////
	///关闭指针ic
	void Close();
	//////////////////////////////////////////////////////////////////////////
	///读取成功返回视频帧，如果失败返回空
	///返回值需要用户清理
	AVPacket Read();
	//////////////////////////////////////////////////////////////////////////
	int GetPts(const AVPacket *pkt);
	//////////////////////////////////////////////////////////////////////////
	///使用新版本方法 不区分视频音频
	///@return 返回pts
	int Decode(const AVPacket *pkt);
	//////////////////////////////////////////////////////////////////////////
	///返回错误信息
	std::string GetError();
	//////////////////////////////////////////////////////////////////////////
	///转rgb
	bool ToRGB(char *out, int outwidth, int outheight);
	//////////////////////////////////////////////////////////////////////////
	int ToPCM(char *out);
	//////////////////////////////////////////////////////////////////////////
	///计算进度 确保除数不为零
/*	double r2d(AVRational r);*/
	//////////////////////////////////////////////////////////////////////////
	///pos 0~1
	bool Seek(float pos);
	
	virtual ~QFFFmpeg();
	int totalMs = 0;
	int fps = 0;
	int pts = 0;
	bool isPlay = false;
	int videoStream = 0;
	int audioStream = 1;
	int sampleRate = 48000;
	int sampleSize = 16;
	int channel = 2;
protected:
	
	char errorbuf[1024];
	//存放视频或者流打开后的信息
	AVFormatContext *ic = nullptr;
	AVFrame *yuv = nullptr;
	AVFrame *pcm = nullptr;
	//转换器
	SwsContext *cCtx = nullptr;
	SwrContext *aCtx = nullptr;
	QMutex mutex;
	//单例模式
	QFFFmpeg();
};

