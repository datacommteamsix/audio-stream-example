#include "receiver.h"

receiver::receiver(QWidget *parent)
	: QMainWindow(parent)
	, mPlayer(this, QMediaPlayer::StreamPlayback)
	, mData()
{
	ui.setupUi(this);

	mBuffer = new QBuffer(&mData, this);
	mBuffer->open(QIODevice::ReadWrite);

	connect(&mPlayer, &QMediaPlayer::mediaStatusChanged, this, &receiver::mediaStatusChangedHandler);

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
	QTcpSocket * socket = (QTcpSocket *)QObject::sender();
	QByteArray data = socket->readAll();
	mData.append(data, data.size());
	qDebug() << "buffer is at size" << mBuffer->size();

	if (mPlayer.state() != QMediaPlayer::PlayingState && mBuffer->size() > 56000)
	{
		mPlayer.setMedia(QMediaContent(), mBuffer);
		mPlayer.setPosition(0);
		mPlayer.play();
	}
}

void receiver::mediaStatusChangedHandler()
{
	qDebug() << mPlayer.mediaStatus();
}