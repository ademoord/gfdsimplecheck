////////////////////////////////////////////////////////////////////////////////
///
/// \file	uLamp.cpp
///
///			routine to handle the Lamp
///
/// \author J. Sounggalon S
///
// $URL: file:///Z:/Data/svn/gfd500/gfdhw05/trunk/simpleCheck/source/smBlinker.cpp $
// $Rev: 20 $
// $Author: sounggalon $
// $Date: 2013-04-25 22:37:25 +0200 (Do, 25 Apr 2013) $
// $Id: smBlinker.cpp 20 2013-04-25 20:37:25Z sounggalon $
////////////////////////////////////////////////////////////////////////////////
//#include "stm32f2xx.h"
#include "qp_port.h"
#include "main.h"


#define TIME_ON				(BSP_TICKS_PER_SEC / 2)
#define TIME_OFF			((BSP_TICKS_PER_SEC - TIME_ON))

class Blinker : public QActive {
private:
	uint16_t	ctrFlash;
	QTimeEvt	evTime;

public:
	Blinker();

protected:
	static QState initial(Blinker *me, QEvent const *e);
	static QState idle(Blinker *me, QEvent const *e);
	static QState blinking(Blinker *me, QEvent const *e);
	static QState on(Blinker *me, QEvent const *e);
	static QState off(Blinker *me, QEvent const *e);
};




static Blinker l_blinker;
QActive * const aoBlinker = (QActive*)&l_blinker;


Blinker::Blinker() : QActive(
		(QStateHandler)&Blinker::initial),
		ctrFlash(0),
		evTime(SIG_TIMEOUT) {

}


QState Blinker::initial(Blinker *me, QEvent const *e) {

	return Q_TRAN(&Blinker::idle);
}




QState Blinker::idle(Blinker *me, QEvent const *e) {
	switch(e->sig) {
		case Q_ENTRY_SIG: {
			Lamp(DISABLE);
			return Q_HANDLED();
		}
		case SIG_FLASHING: {
			return Q_TRAN(&Blinker::on);
		}

	}
    return Q_SUPER(&QHsm::top);
}


QState Blinker::blinking(Blinker *me, QEvent const *e) {
	switch(e->sig) {
		case Q_ENTRY_SIG: {
			return Q_HANDLED();
		}
		case SIG_FLASHING: {
			return Q_TRAN(&Blinker::idle);
		}
	}
    return Q_SUPER(&QHsm::top);
}


QState Blinker::on(Blinker *me, QEvent const *e) {
	switch(e->sig) {
		case Q_ENTRY_SIG: {
			me->evTime.postIn(me, TIME_ON);
			Lamp(ENABLE);
			return Q_HANDLED();
		}
		case SIG_TIMEOUT: {
			return Q_TRAN(&Blinker::off);
		}
	}
    return Q_SUPER(&Blinker::blinking);
}


QState Blinker::off(Blinker *me, QEvent const *e) {
	switch(e->sig) {
		case Q_ENTRY_SIG: {
			me->evTime.postIn(me, TIME_OFF);
			Lamp(DISABLE);
			return Q_HANDLED();
		}
		case SIG_TIMEOUT: {
				return Q_TRAN(&Blinker::on);
		}
	}
    return Q_SUPER(&Blinker::blinking);
}




