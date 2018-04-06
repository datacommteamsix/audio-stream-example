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
	QString filename = QFileDialog::getOpenFileName(this, "Select file", QDir::homePath());
	ui.label->setText(filename);

	mSong = new QFile(filename);
	mSong->open(QFile::ReadOnly);

	mSocket = new QTcpSocket(this);
	mSocket->setSocketOption(QAbstractSocket::SendBufferSizeSocketOption, QVariant(BUFFERSIZE));
	mSocket->connectToHost("localhost", 42069);
}

void sender::streamSongHandler()
{
	int count = 0;

	while (count < mSong->size())
	{
		mSocket->write(mSong->read(BUFFERSIZE));
		mSocket->flush();
		count += BUFFERSIZE;
		qDebug() << count;
		QThread::msleep(10);
	}
}
