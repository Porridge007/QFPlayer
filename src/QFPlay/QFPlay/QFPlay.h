#pragma once

#include <QtWidgets/QWidget>
#include "ui_QFPlay.h"

class QFPlay : public QWidget
{
    Q_OBJECT

public:
    QFPlay(QWidget *parent = Q_NULLPTR);
	~QFPlay();
	void timerEvent(QTimerEvent *e);
	void resizeEvent(QResizeEvent *e);
	void openFile(QString name);
public slots:
void open();
void play();
void sliderPress();
void sliderRelease();
private:
    Ui::QFPlayClass ui;
};
