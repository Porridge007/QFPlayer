#include "QFAudioPlay.h"
#include <QAudioOutput>
#include <QThread>
class CQFAudioPlay :public QFAudioPlay
{
public:
	QAudioOutput *output = nullptr;
	QIODevice *io = nullptr;
	QMutex mutex;
	void Stop()
	{
		mutex.lock();
		if (output)
		{
			output->stop();
			delete output;
			output = nullptr;
			io = nullptr;
		}
		mutex.unlock();
	}
	bool Start()
	{
		Stop();
		mutex.lock();
		QAudioFormat fmt;
		fmt.setSampleRate(this->sampleRate);//Ò»ÃëÖÓ48000¸öÒôÆµ
		fmt.setSampleSize(this->sampleSize);
		fmt.setChannelCount(this->channel);
		fmt.setCodec("audio/pcm");
		fmt.setByteOrder(QAudioFormat::LittleEndian);
		fmt.setSampleType(QAudioFormat::UnSignedInt);
		output = new QAudioOutput(fmt);
		io = output->start();
		mutex.unlock();
		return true;
	}
	void Play(bool isplay)
	{	
		if (!output)
		{
			mutex.unlock();
			return;
		}
		if (isplay)
		{
			output->resume();
		}
		else
		{
			output->suspend();
		}
		mutex.unlock();
	}
	virtual int GetFree()
	{
		mutex.lock();
		if (!output)
		{
			mutex.unlock();
			return 0;
		}
		int free = output->bytesFree();
		mutex.unlock();
		return free;
	}

	bool Write(const char *data, int datasize)
	{
		mutex.lock();
		if (io)
			io->write(data, datasize);
		mutex.unlock();
		return true;
	}

};

QFAudioPlay::QFAudioPlay()
{
}


QFAudioPlay::~QFAudioPlay()
{
}

QFAudioPlay* QFAudioPlay::Get()
{
	static CQFAudioPlay ap;
	return &ap;
}