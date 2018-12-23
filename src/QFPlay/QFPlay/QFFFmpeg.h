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
	///����ģʽ
	///@return ���������������ָ��
	static QFFFmpeg *Get()
	{
		static QFFFmpeg ff;
		return &ff;
	}
	//////////////////////////////////////////////////////////////////////////
	///����Ƶ�ļ�������ϴ��Ѿ��򿪻��ȹر�
	///@para path ��Ƶ�ļ�·��
	///@return int return total ms
	int Open(const  char *path);
	//////////////////////////////////////////////////////////////////////////
	///�ر�ָ��ic
	void Close();
	//////////////////////////////////////////////////////////////////////////
	///��ȡ�ɹ�������Ƶ֡�����ʧ�ܷ��ؿ�
	///����ֵ��Ҫ�û�����
	AVPacket Read();
	//////////////////////////////////////////////////////////////////////////
	int GetPts(const AVPacket *pkt);
	//////////////////////////////////////////////////////////////////////////
	///ʹ���°汾���� ��������Ƶ��Ƶ
	///@return ����pts
	int Decode(const AVPacket *pkt);
	//////////////////////////////////////////////////////////////////////////
	///���ش�����Ϣ
	std::string GetError();
	//////////////////////////////////////////////////////////////////////////
	///תrgb
	bool ToRGB(char *out, int outwidth, int outheight);
	//////////////////////////////////////////////////////////////////////////
	int ToPCM(char *out);
	//////////////////////////////////////////////////////////////////////////
	///������� ȷ��������Ϊ��
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
	//�����Ƶ�������򿪺����Ϣ
	AVFormatContext *ic = nullptr;
	AVFrame *yuv = nullptr;
	AVFrame *pcm = nullptr;
	//ת����
	SwsContext *cCtx = nullptr;
	SwrContext *aCtx = nullptr;
	QMutex mutex;
	//����ģʽ
	QFFFmpeg();
};

