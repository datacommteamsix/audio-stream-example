#include "receiver.h"

receiver::receiver(QWidget *parent)
	: QMainWindow(parent)
	, mAudioOut(nullptr)
{
	ui.setupUi(this);

	connect(&mServer, &QTcpServer::newConnection, this, &receiver::newConnectionHandler);
	mServer.listen(QHostAddress::Any, 42069);
}

void receiver::newConnectionHandler()
{
	mSocket = mServer.nextPendingConnection();
	mSocket->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, QVariant(8192));
	connect(mSocket, &QTcpSocket::readyRead, this, &receiver::incomingDataHandler);
	qDebug() << "Incoming connection from" << mSocket->peerAddress();
}

void receiver::incomingDataHandler()
{
	if (!mAudioOut)
	{
		QAudioFormat format;

		// GOOD WAV FILE
		format.setSampleRate(48000);
		format.setChannelCount(2);
		format.setSampleSize(16);
		format.setCodec("audio/pcm");
		format.setByteOrder(QAudioFormat::LittleEndian);
		format.setSampleType(QAudioFormat::UnSignedInt);

		mAudioOut = new QAudioOutput(format, this);
		mAudioOut->setBufferSize(8192);
		mAudioOut->start((QTcpSocket *)QObject::sender());
		qDebug() << "Music started";
	}
}