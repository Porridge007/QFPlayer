#include "QFPlay.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFFFmpeg.h>
#include <QFAudioPlay.h>

static bool isPressSlider = false;
static bool isPlay = true;

QFPlay::QFPlay(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	startTimer(40);
	//openFile("video.mp4");
}

void QFPlay::resizeEvent(QResizeEvent *e)
{
	ui.openGLWidget->resize(size());
	ui.playButton->move(this->width() / 2 + 50, this->height() - 80);
	ui.openButton->move(this->width() / 2 - 50, this->height() - 80);
	ui.playslider->move(25, this->height() - 120);
	ui.playslider->resize(this->width() - 50, ui.playslider->height());
	ui.playtime->move(65, ui.playButton->y());
	ui.label->move(ui.playtime->x() + ui.playtime->width() - 25, ui.playtime->y());
	ui.totaltime->move(150, ui.playButton->y());
}

void QFPlay::timerEvent(QTimerEvent *e)
{
	int hour = QFFFmpeg::Get()->pts / 1000/3600;
	int min = (QFFFmpeg::Get()->pts / 1000 - 3600 * hour) / 60;
	int sec = QFFFmpeg::Get()->pts / 1000%60;
	char buf[1024] = { 0 };
	sprintf(buf,"%d:%d:%d", hour, min, sec);
	ui.playtime->setText(buf);

	if (QFFFmpeg::Get()->totalMs > 0)
	{
		float rate = (float)QFFFmpeg::Get()->pts / (float)QFFFmpeg::Get()->totalMs;
		if (!isPressSlider)
			ui.playslider->setValue(rate * 1000);
	}
}

void QFPlay::sliderPress()
{
	isPressSlider = true;
}

void QFPlay::sliderRelease()
{
	isPressSlider = false;
	float pos = 0;
	pos = (float)ui.playslider->value()/(ui.playslider->maximum()+1);
	QFFFmpeg::Get()->Seek(pos);
}
void QFPlay::play()
{
	isPlay = !isPlay;
	QFFFmpeg::Get()->isPlay = isPlay;
	if (isPlay)
	{
		//显示pause图标
		ui.playButton->setStyleSheet("QPushButton{border-image: url(:/QFPlay/Resources/pause_normal.png);}");
	}
	else
	{
		ui.playButton->setStyleSheet("QPushButton{border-image: url(:/QFPlay/Resources/play_normal.png);}");
	}
}

void QFPlay::openFile(QString name)
{
	if (name.isEmpty())
		return;
	this->setWindowTitle(name);
	int totalMs = QFFFmpeg::Get()->Open(name.toLocal8Bit());
	if (totalMs <= 0)
	{
		QMessageBox::information(this, "err", "file open failed!");
		return;
	}
	QFAudioPlay::Get()->sampleRate = QFFFmpeg::Get()->sampleRate;
	QFAudioPlay::Get()->channel = QFFFmpeg::Get()->channel;
	QFAudioPlay::Get()->sampleSize = 16;
	QFAudioPlay::Get()->Start();
	char buf[1024] = { 0 };
	int min = (totalMs / 1000) / 60;
	int sec = (totalMs / 1000) % 60;
	sprintf(buf, "%03d:%02d", min, sec);
	ui.totaltime->setText(buf);
	isPlay = false;
	play();
}

void QFPlay::open()
{
	QString name = QFileDialog::getOpenFileName(
		this, QString::fromLocal8Bit("选择视频文件"));
	openFile(name);
}

QFPlay::~QFPlay()
{
}