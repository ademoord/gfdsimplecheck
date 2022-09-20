////////////////////////////////////////////////////////////////////////////////
///
/// \file	bsp.cpp
///
///			Board Support Package routines
///
/// \author J. Sounggalon S
///
// $URL: file:///Z:/Data/svn/gfd500/gfdhw05/trunk/simpleCheck/source/bsp.cpp $
// $Rev: 20 $
// $Author: sounggalon $
// $Date: 2013-04-25 22:37:25 +0200 (Do, 25 Apr 2013) $
// $Id: bsp.cpp 20 2013-04-25 20:37:25Z sounggalon $
////////////////////////////////////////////////////////////////////////////////
#include "qp_port.h"
#include "main.h"



enum ISR_Priorities {      // ISR priorities starting from the highest urgency
	PRIO_USART2,
    PRIO_SYSTICK
    // ...
};


extern "C" void SysTick_Handler(void) __attribute__((__interrupt__));
extern "C" void SysTick_Handler(void) {

	QK_ISR_ENTRY();                           // inform QK about ISR entry

    QP::QF::TICK(&l_SysTick_Handler);         // process all armed time events

    QK_ISR_EXIT();                            // inform QK about ISR exit
}




void BSP_init(void) {

	gfdGPIO_init();					// initialize the GPIO
	USART2_init();					// init console terminal

	Power4V2(ENABLE);				// turn on power for lamp
}


//............................................................................
void QF::onStartup(void) {
                 // set up the SysTick timer to fire at BSP_TICKS_PER_SEC rate
    SysTick_Config(SystemCoreClock / BSP_TICKS_PER_SEC);

                          // set priorities of all interrupts in the system...
    NVIC_SetPriority(SysTick_IRQn,   PRIO_SYSTICK);
    NVIC_SetPriority(USART2_IRQn, PRIO_USART2);

//    NVIC_EnableIRQ(GPIOPortA_IRQn);
}
//............................................................................
void QF::onCleanup(void) {
}
//............................................................................
void QK::onIdle(void) {          // entered with interrupts LOCKED, see NOTE01


#if defined NDEBUG
    // put the CPU and peripherals to the low-power mode
    // you might need to customize the clock management for your application,
    // see the datasheet for your particular Cortex-M3 MCU.
    __WFI();                                             // Wait-For-Interrupt
#endif
}

//............................................................................
void Q_onAssert(char const Q_ROM * const Q_ROM_VAR file, int line) {
    (void)file;                                      // avoid compiler warning
    (void)line;                                      // avoid compiler warning
    QF_INT_DISABLE();            // make sure that all interrupts are disabled
    for (;;) {          // NOTE: replace the loop with reset for final version
    }
}
//............................................................................
// error routine that is called if the CMSIS library encounters an error
extern "C" void assert_failed(char const *file, int line) {
    Q_onAssert(file, line);
}

