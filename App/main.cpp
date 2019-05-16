#include "AppConfig.h"
#include "QMainClass.h"

int main(int argc, char *argv[])
{
	QMainClass::setArgs(argc, argv);
	QMainClass *mainClass = QMainClass::getMainClass();
	int res = mainClass->StartApp();
	delete mainClass;
	return res;
}

// ======================================================================

//	TODO LIST
