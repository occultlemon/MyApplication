#include "kmainwindow.h"
#include"klogin.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	//KMainWindow w;
	//w.show();

	KLogin wLogin;
	wLogin.show();

	return a.exec();
}
