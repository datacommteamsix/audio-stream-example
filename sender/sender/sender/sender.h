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

// Wave file header format
struct wavfile
{
    char   id[4];            // should always contain "RIFF"
    int    totalLength;      // total file length minus 8
    char   wavFormat[8];     // should be "WAVEfmt "
    int    format;           // 16 for PCM format
    short  pcm;              // 1 for PCM format
    short  channels;         // channels
    int    sampleRate;       // sampling frequency
    int    bytesPerSecond;
    short  bytesByCapture;
    short  bitsPerSample;
    char   data[4];          // should always contain "data"
    int    bytesInData;
};

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
	void selectSongHandler();
	void streamSongHandler();
};
