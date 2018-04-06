#include "receiver.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	receiver w;
	w.show();
	return a.exec();
}
