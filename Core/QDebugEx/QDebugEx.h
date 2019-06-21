/**
  * @version  1.12
  * @brief    Замена стандартного логера
  */
#ifndef QDEBUGEX_H
#define QDEBUGEX_H

#include <QString>
#include <QFlags>

class QDebugEx
{
	
public:
	enum EDebugExFlag {
		flgNoOption			= 0x00,
		flgDelOld				= 0x01,
		flgUseFile			= 0x02,
		flgUseStd				= 0x04,
		flgUseUtc				= 0x08,
	};
	Q_DECLARE_FLAGS(EDebugExFlags, EDebugExFlag)
	
// ======================================================================
	
public:
	QDebugEx(EDebugExFlags flags = flgNoOption, const QString &fileName = QString());

// ======================================================================
	
private:
  static void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);

// ======================================================================

};

Q_DECLARE_OPERATORS_FOR_FLAGS(QDebugEx::EDebugExFlags)

#endif // QDEBUGEX_H
