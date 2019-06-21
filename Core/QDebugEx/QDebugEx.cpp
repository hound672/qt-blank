#include <QDebug>
#include <QDateTime>
#include <QFile>
#include <QFileInfo>
#include <QTextCodec>
#include <QMutex>
#include <QMutexLocker>
#ifdef Q_OS_ANDROID
	#include <android/log.h>
#endif // Q_OS_ANDROID

#include "Core/Includes.h"

#include "QDebugEx.h"

static QTextStream sTs;
static QFile sOutFile;
static QMutex sMutex;
static QDebugEx::EDebugExFlags sFlags;
static bool sDebugMode = false;


// ======================================================================

/**
  * @brief  Конструктор инициализации логирования
  * @param  logName: имя файла для логирования
  * @param  del: флаг удаления файла, если true то файл будет удален перед инициализацией логирования
  * @param  onlyFile: при true пишет лог только в файл
  * @retval None
  */
QDebugEx::QDebugEx(EDebugExFlags flags, const QString &fileName)
{
	sFlags = flags;
	
#ifdef QT_DEBUG
	sDebugMode = true;
#endif
	
	QIODevice::OpenMode mode;
	mode |= QIODevice::WriteOnly;
	mode |= sFlags.testFlag(EDebugExFlag::flgDelOld) ? QIODevice::NotOpen : QIODevice::Append;

	if (sFlags.testFlag(EDebugExFlag::flgUseFile)) {
		sOutFile.setFileName(fileName);
		if (!sOutFile.open(mode)) {
			throw "Cannot open file!";
		}
	}
  sTs.setDevice(&sOutFile);
	
  qInstallMessageHandler(myMessageOutput);
}

// ======================================================================

void QDebugEx::myMessageOutput(QtMsgType type, const QMessageLogContext& context, const QString &msg)
{
  QMutexLocker locker(&sMutex);

  QByteArray localMsg = msg.toLocal8Bit();
  QString str;
  QByteArray typeMessage;
  QString fileName = QString::fromLatin1(context.file);

#ifdef Q_OS_WIN
  QStringList list = fileName.split('\\');
  fileName = list.isEmpty() ? "UNKNOWN_FILE" : list.last();
#endif

	QDateTime dateTime = sFlags.testFlag(EDebugExFlag::flgUseUtc) ? QDateTime::currentDateTimeUtc() :
																																	QDateTime::currentDateTime();
			
	QByteArray date = dateTime.toString("dd.MM.yy hh:mm:ss.zzz").toUtf8();;
	
  switch (type) 
	{
	// ======================================================================  
	case QtDebugMsg:
		
		if (!sDebugMode && !IS_ENV_SET("QDEBUG")) {
			return;
		}
			
		typeMessage = "DBG";
		break;
	// ======================================================================
	case QtWarningMsg:
		typeMessage = "WRN";
		break;
	// ======================================================================
	case QtCriticalMsg:
		typeMessage = "CRI";
		break;
	// ======================================================================
	case QtFatalMsg:
		typeMessage = "FAT";
		break;
	// ======================================================================
	case QtInfoMsg:
		typeMessage = "INF";
		break;
	// ======================================================================
	default:
		typeMessage = "UNK";
	} // switch (type)

  str = QString("[%1] [%2] [%3@%4] %5").arg(date.constData()).arg(typeMessage.constData())
                          .arg(fileName).arg(context.line).arg(localMsg.constData());

	// ======================================================================
	if (sFlags.testFlag(EDebugExFlag::flgUseFile)) {
		sTs << str << "\r\n";
		sTs.flush();
	}
	// ======================================================================
	if (sFlags.testFlag(EDebugExFlag::flgUseStd)) {

#ifdef Q_OS_ANDROID
		__android_log_write(ANDROID_LOG_INFO, "", str.toLocal8Bit().constData());
#else
    QTextStream screen(stdout, QIODevice::WriteOnly);
    screen << str << endl;
#endif
  }
}

// ======================================================================
