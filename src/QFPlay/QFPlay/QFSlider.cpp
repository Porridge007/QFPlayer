#include "QFSlider.h"
#include <QMouseEvent>

void QFSlider::mousePressEvent(QMouseEvent *e)
{
	//�ض���qt�ؼ�
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
