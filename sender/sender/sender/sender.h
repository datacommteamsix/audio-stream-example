#pragma once

#include <QDebug>

#include <QDir>
#include <QFileDialog>
#include <QHostAddress>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QTcpSocket>
#include <QThread>

#include <QtWidgets/QMainWindow>
#include "ui_sender.h"

#define BUFFERSIZE 8192

class sender : public QMainWindow
{
	Q_OBJECT

public:
	sender(QWidget *parent = Q_NULLPTR);

private:
	Ui::senderClass ui;
	QFile * mSong;
	QTcpSocket * mSocket;

private slots:
	void connectHandler();
	void selectSongHandler();
	void streamSongHandler();
};
