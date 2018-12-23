#include "VideoWidget.h"
#include <QPainter>
#include "QFFFmpeg.h"
#include "QFVideoThread.h"
VideoWidget::VideoWidget(QWidget *p) :QOpenGLWidget(p)
{
	//QFFFmpeg::Get()->Open("video.mp4");
	startTimer(20);
	QFVideoThread::Get()->start();
}


VideoWidget::~VideoWidget()
{
	
}

void VideoWidget::paintEvent(QPaintEvent *e)
{
	static QImage *image = nullptr;
	static int w = 0;
	static int h = 0;
	//解决窗口大小变化问题
	if (w != width() || h != height())
	{
		if (image)
		{
			delete image->bits();
			delete image;
			image = nullptr;
		}
	}
	if (image == nullptr)
	{
		uchar *buf = new uchar[width()*height() * 4];
		image = new QImage(buf,width(),height(),QImage::Format_ARGB32);

	}
	/*
	AVPacket pkt = QFFFmpeg::Get()->Read();
	if (pkt.stream_index != QFFFmpeg::Get()->videoStream)
	{
		av_packet_unref(&pkt);
		return;
	}
	if (pkt.size == 0)return;
	AVFrame *yuv = QFFFmpeg::Get()->Decode(&pkt);
	av_packet_unref(&pkt);
	if (yuv == nullptr)return;*/
	QFFFmpeg::Get()->ToRGB((char*)image->bits(), width(), height());
	QPainter painter;
	painter.begin(this);
	painter.drawImage(QPoint(0, 0),*image);
	painter.end();
}
void VideoWidget::timerEvent(QTimerEvent *e)
{
	this->update();
}