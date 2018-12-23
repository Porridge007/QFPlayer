#pragma once
#include <QtWidgets/qwidget.h>
#include <QOpenGLWidget>
class VideoWidget:public QOpenGLWidget
{
public:
	VideoWidget(QWidget *p = nullptr);
	//////////////////////////////////////////////////////////////////////////
	///窗口的重新绘制
	void paintEvent(QPaintEvent *e);
	//////////////////////////////////////////////////////////////////////////
	///刷新 定时器
	void timerEvent(QTimerEvent *e);
	virtual ~VideoWidget();
};

