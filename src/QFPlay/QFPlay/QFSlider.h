#pragma once
#include <qslider.h>
class QFSlider:public QSlider
{
	Q_OBJECT
public:
	QFSlider(QWidget *p = nullptr);
	~QFSlider();
	void mousePressEvent(QMouseEvent *e);
};

