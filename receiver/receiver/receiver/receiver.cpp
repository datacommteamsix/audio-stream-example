#include "receiver.h"

receiver::receiver(QWidget *parent)
	: QMainWindow(parent)
	, mAudioOut(nullptr)
{
	ui.setupUi(this);

	// Create a server to listen for tcp request
	connect(&mServer, &QTcpServer::newConnection, this, &receiver::newConnectionHandler);
	mServer.listen(QHostAddress::Any, 42069);
}

void receiver::newConnectionHandler()
{
	// Grab an incoming connection
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

		// Common WAV file format
		format.setSampleRate(44100);
		format.setChannelCount(2);
		format.setSampleSize(16);
		format.setCodec("audio/pcm");
		format.setByteOrder(QAudioFormat::LittleEndian);
		format.setSampleType(QAudioFormat::UnSignedInt);

		// Create the audio output with specificed format and tcp socket
		mAudioOut = new QAudioOutput(format, this);
		mAudioOut->setBufferSize(8192);
		mAudioOut->start((QTcpSocket *)QObject::sender());
		qDebug() << "Music started";
	}
}