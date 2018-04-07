#include "sender.h"

sender::sender(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.buttonSelect, &QPushButton::pressed, this, &sender::selectSongHandler);
	connect(ui.buttonStream, &QPushButton::pressed, this, &sender::streamSongHandler);
}

void sender::selectSongHandler()
{
	// Select a file
	QString filename = QFileDialog::getOpenFileName(this, "Select file", QDir::homePath());
	ui.label->setText(filename);

	// Open the song file
	mSong = new QFile(filename);
	mSong->open(QFile::ReadOnly);

	// Example on how to grab the header values
	wavfile header;
	memset(&header, 0, sizeof(wavfile));
	mSong->read((char *)&header, sizeof(header));

	qDebug() << "sample rate" << header.sampleRate;
	qDebug() << "sample size" << header.bitsPerSample;
	qDebug() << "bytes in data" << header.bytesInData;
	qDebug() << "bytes per second" << header.bytesPerSecond;
	qDebug() << "total length of song in bytes" << header.totalLength;
	qDebug() << "total length of song in seconds" << header.totalLength / header.bytesPerSecond;

	// Connect to receiver
	mSocket = new QTcpSocket(this);
	mSocket->setSocketOption(QAbstractSocket::SendBufferSizeSocketOption, QVariant(BUFFERSIZE));
	mSocket->connectToHost("localhost", 42069);
}

void sender::streamSongHandler()
{
	int count = 0;

	// Stream the song
	while (count < mSong->size())
	{
		mSocket->write(mSong->read(BUFFERSIZE));
		mSocket->flush();
		count += BUFFERSIZE;
		qDebug() << count;
		QThread::msleep(10);
	}
}
