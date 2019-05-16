#include <QDebug>

#include "QStateMachineEx.h"


// ======================================================================

QStateMachineEx::QStateMachineEx(QObject *parent):
	QStateMachineEx(QString(), TStateName(), parent)
{
}

QStateMachineEx::QStateMachineEx(const QString &className, QObject *parent):
	QStateMachineEx(className, TStateName(), parent)	
{
}

QStateMachineEx::QStateMachineEx(const QString &className, const TStateName &stateNames, QObject *parent) : 
	QObject(parent),
	mState(_stStartup),
	mWorkerName(className),
	mStateNames(stateNames)
{
	mTimer.setSingleShot(true);
	connect(&mTimer, &QTimer::timeout, this, &QStateMachineEx::slotTimer);
}

// ======================================================================

// ======================================================================
//  protected                       
// ======================================================================

/**
	* @brief  Запуск/остановка таймера
	* @param  
	* @retval 
	*/
void QStateMachineEx::setTimer(quint32 timeout)
{
	if (timeout == U32_MAX_VALUE) {
		mTimer.stop();
		return;
	}
	
	mTimer.start(timeout);
}

// ======================================================================

/**
	* @brief  Смена состояния
	* @param  
	* @retval 
	*/
void QStateMachineEx::setState(int newState)
{
	qInfo()	<< "[" << mWorkerName << "]"
					<< "************* Set state from: " << mStateNames.value(mState, QString::number(mState))
					<< " to: " << mStateNames.value(newState, QString::number(newState))
					<< " ******************";
	mState = newState;
}

// ======================================================================

/**
	* @brief  Возвращает текущее состояние
	* @param  
	* @retval 
	*/
int QStateMachineEx::getState() const
{
	return mState;
}

// ======================================================================

/**
	* @brief  Возвращает строковое представление состояния
	* @param  
	* @retval 
	*/
QString QStateMachineEx::getStateStr() const
{
	return mStateNames.value(getState());
}

// ======================================================================

// ======================================================================
//  private slots                       
// ======================================================================

/**
	* @brief  Слот обработки тика таймера
	* @param  
	* @retval 
	*/
void QStateMachineEx::slotTimer()
{
	onEvTimer();
}

// ======================================================================

