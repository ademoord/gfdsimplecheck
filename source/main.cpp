////////////////////////////////////////////////////////////////////////////////
///
/// \file	main.cpp
///
///			main routine
///
/// \author J. Sounggalon S
///
// $URL: file:///Z:/Data/svn/gfd500/gfdhw05/trunk/simpleCheck/source/main.cpp $
// $Rev: 17 $
// $Author: sounggalon $
// $Date: 2013-04-25 17:35:30 +0200 (Do, 25 Apr 2013) $
// $Id: main.cpp 17 2013-04-25 15:35:30Z sounggalon $
////////////////////////////////////////////////////////////////////////////////
#include "qp_port.h"
#include "main.h"


enum Active_Object_Priorities {	// AO priorities starting from the lowest priority
    PRIO_BLINKER = 1,                                            // highest priority
    PRIO_INTERPRETER,
    PRIO_CHARGER,
    PRIO_GPRS
};


#define SIZE_QUEUE_BLINKER		2
#define SIZE_QUEUE_INTERPRETER	4
#define SIZE_SMALL_POOL			256

static QEvent const *queBlinker[SIZE_QUEUE_BLINKER];
static QEvent const *queInterpreter[SIZE_QUEUE_INTERPRETER];

static union SmallEvents {
    void   *e0;                                          // minimum event size
    uint8_t e1[sizeof(TEvtCommon)];
} poolSmall[SIZE_SMALL_POOL];                 // storage for the small event pool


const char sWelcome[] =
        "Ground Fault Detector with STM32F205VC\r\n"
        "GFD500 HW R01 $Rev: 17 $; " __DATE__ " " __TIME__ "\r\n";


int main(void) {

	// I M P O R T A N T:
	// ==================
	// If running from embedded SRAM then remap NVIC vectors to RAM
	// Already made in system_stm32f2xx.c
	NVIC_SetVectorTable(NVIC_VectTab_RAM, 0);

	// the hardware use other resonator frequency as default, so update the
	// clock system parameters
	SystemCoreClockUpdate();

    BSP_init();                             // initialize the BSP
    QF::init();       						// initialize the framework
    QF::poolInit(poolSmall,					// initialize the event pool
    		sizeof(poolSmall), sizeof(poolSmall[0]));

    // initialize active objects
    aoBlinker->start(PRIO_BLINKER,				// priority
    		queBlinker, Q_DIM(queBlinker),		// queue storage and size
    		0, 0,								// stack storage and size
    		0 );								// no initialization event

    aoInterpreter->start(PRIO_INTERPRETER,		// priority
    		queInterpreter, Q_DIM(queInterpreter),	// queue storage and size
    		0, 0,								// stack storage and size
    		0 );								// no initialization event

    return QF::run();                                // run the QF application
}

