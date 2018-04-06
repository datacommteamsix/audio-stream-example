#pragma once

#include <QDebug>

#include <QAudioDecoder>
#include <QAudioFormat>
#include <QAudioOutput>
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

	QAudioOutput * mAudioOut;

	QTcpServer mServer;
	QTcpSocket * mSocket;

private slots:
	void newConnectionHandler();
	void incomingDataHandler();
};
