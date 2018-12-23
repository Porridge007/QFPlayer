#pragma once
#include <QThread>
class QFVideoThread:public QThread
{
public:
	static QFVideoThread *Get()
	{
		static QFVideoThread vt;
		return &vt;
	}
	void run();
	QFVideoThread();
	virtual ~QFVideoThread();
};

