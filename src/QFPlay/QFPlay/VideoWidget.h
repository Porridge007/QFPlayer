#pragma once
#include <QtWidgets/qwidget.h>
#include <QOpenGLWidget>
class VideoWidget:public QOpenGLWidget
{
public:
	VideoWidget(QWidget *p = nullptr);
	//////////////////////////////////////////////////////////////////////////
	///���ڵ����»���
	void paintEvent(QPaintEvent *e);
	//////////////////////////////////////////////////////////////////////////
	///ˢ�� ��ʱ��
	void timerEvent(QTimerEvent *e);
	virtual ~VideoWidget();
};

