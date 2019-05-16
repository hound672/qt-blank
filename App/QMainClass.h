#ifndef QMAINCLASS_H
#define QMAINCLASS_H

#include <QObject>

#include "Core/QSetupClass.h"

class QMainClass : public QSetupClass
{
	Q_OBJECT

private:
	explicit QMainClass(int argc, char *argv[]);
	
// ======================================================================
	
public:
	static void setArgs(int argc, char **argv);
	static QMainClass *getMainClass();
	
protected:
	void makeSignalSlots();
	int setup();
	int start();
	
// ======================================================================
	
};

#endif // QMAINCLASS_H
