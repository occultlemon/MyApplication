#include "ktodomainwindow.h"
#include <QtWidgets/QApplication>
#include<qmessagebox.h>
#include"kloginpage.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	//KTodoMainWindow w;
	//w.show();
	KLoginPage login;
	login.show();



	return a.exec();
}
