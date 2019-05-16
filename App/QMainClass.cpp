#include <QDebug>

#include "QMainClass.h"

// ======================================================================
static int sArgc;
static char **sArgv;
// ======================================================================

QMainClass::QMainClass(int argc, char *argv[]) : 
	QSetupClass(argc, argv)
{
}

// ======================================================================

/**
	* @brief  Сохраняет переданые при запуске программы аргументы
	* @param  
	* @retval 
	*/
void QMainClass::setArgs(int argc, char **argv)
{
	sArgc = argc;
	sArgv = argv;
}

QMainClass *QMainClass::getMainClass()
{
	static QMainClass *mainClass = NULL;
	if (!mainClass) {
		mainClass = new QMainClass(sArgc, sArgv);
	}
	return mainClass;
}

// ======================================================================

// ======================================================================
//  protected                       
// ======================================================================

/**
	* @brief  Создает связку сигналов-слотов
	* @param  
	* @retval 
	*/
void QMainClass::makeSignalSlots()
{
	qDebug() << "Make signal slots";
}

// ======================================================================

/**
	* @brief  Инициализация компонентов для запуска приложения
	* @param  
	* @retval 
	*/
int QMainClass::setup()
{
	return 1;
}

// ======================================================================

/**
	* @brief  Запуск приложения
	* @param  
	* @retval 
	*/
int QMainClass::start()
{
	return 1;
}

// ======================================================================
