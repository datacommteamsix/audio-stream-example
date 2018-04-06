#pragma once

#include <QDebug>

#include <QBuffer>
#include <QByteArray>
#include <QMediaPlayer>
#include <QTcpServer>
#include <QTcpSocket>

#include <QtWidgets/QMainWindow>
#include "ui_receiver.h"

class receiver : public QMainWindow
{
	Q_OBJECT

public:
	receiver(QWidget *parent = Q_NULLPTR);

private:
	Ui::receiverClass ui;

	QMediaPlayer mPlayer;
	QBuffer * mBuffer;
	QByteArray mData;

	QTcpServer mServer;
	QTcpSocket * mSocket;

private slots:
	void newConnectionHandler();
	void incomingDataHandler();
	void mediaStatusChangedHandler();
};
