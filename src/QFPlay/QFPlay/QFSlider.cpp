#include "QFSlider.h"
#include <QMouseEvent>

void QFSlider::mousePressEvent(QMouseEvent *e)
{
	//重定义qt控件
	int value = ((float)e->pos().x() / (float)this->width())*(this->maximum()+1);
	this->setValue(value);
	QSlider::mousePressEvent(e);
}
QFSlider::QFSlider(QWidget *p) :QSlider(p)
{
}


QFSlider::~QFSlider()
{
}
