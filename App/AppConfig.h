/**
	* @version  
	* @brief    Файл с индивидуальными настройки для приложения
	*/
#ifndef APPCONFIG_H
#define APPCONFIG_H

#include "Core/AppConfigEx.h"

// ======================================================================

// набор настроек приложения
#define MAKE_SETTINGS_TABLE()     \
  SETTINGS_BEGIN_GROUP(COMMON)  \
    SETTING_STR_VAL(COMMON, LOG_FILE_NAME, "APP_LOG.log")         \
  SETTINGS_END_GROUP(COMMON)    \
	

// набор для мониторинга приложения
#ifdef USE_MONITORING_SERVICE 

#define MAKE_MONITORING_TABLE()													\
	MONITORING_TABLE_BEGIN																\
	MONITORING_TABLE_BODY0(AppStart)										\
	MONITORING_TABLE_END																	\

#endif // USE_MONITORING_SERVICE

// список команд приложения
#ifdef USE_COMMANDS_SERVICE

#define MAKE_COMMANDS_TABLE()	\
	COMMANDS_TABLE_BEGIN	\
	COMMANDS_TABLE_END	\
	
#endif // USE_COMMANDS_SERVICE
	
#endif // APPCONFIG_H
