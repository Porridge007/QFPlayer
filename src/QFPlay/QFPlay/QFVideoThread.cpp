#include "QFVideoThread.h"
#include "QFFFmpeg.h"
#include "QFAudioPlay.h"
#include <list>
using namespace std;
bool isexit = false;

static list<AVPacket> videos;
static int apts = -1;
void QFVideoThread::run()
{
	char  out[10000] = { 0 };
	while (!isexit)
	{
		if (!QFFFmpeg::Get()->isPlay)
		{
			msleep(10);
			continue;
		}
		int free = QFAudioPlay::Get()->GetFree();
		if (free < 10000)
		{
			msleep(1);
			continue;
		}
		while (videos.size()>0)
		{
			AVPacket pack = videos.front();
			int pts = QFFFmpeg::Get()->GetPts(&pack);
			if (pts > apts)
			{
				break;
			}
			QFFFmpeg::Get()->Decode(&pack);
			av_packet_unref(&pack);
			videos.pop_front();
		}
		AVPacket pkt = QFFFmpeg::Get()->Read();
		if (pkt.size<=0)
		{
			msleep(10);
			continue;
		}
		if(pkt.stream_index == QFFFmpeg::Get()->audioStream)
		{
			apts = QFFFmpeg::Get()->Decode(&pkt);
			av_packet_unref(&pkt);
			int len = QFFFmpeg::Get()->ToPCM(out);
			QFAudioPlay::Get()->Write(out, len);
			continue;
		}
		if (pkt.stream_index != QFFFmpeg::Get()->videoStream)
		{
			av_packet_unref(&pkt);
			continue;
		}
		videos.push_back(pkt);
// 		QFFFmpeg::Get()->Decode(&pkt);
// 		av_packet_unref(&pkt);
// 		if (QFFFmpeg::Get()->fps > 0)
// 			QThread::msleep(1000 / QFFFmpeg::Get()->fps);
	}
}
QFVideoThread::QFVideoThread()
{
}


QFVideoThread::~QFVideoThread()
{
}
