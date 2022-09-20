////////////////////////////////////////////////////////////////////////////////
///
/// \file	hdlrGPIO.cpp
///
///			GPIO handler and support routines
///
/// \author J. Sounggalon S
///
// $URL: file:///Z:/Data/svn/gfd500/gfdhw05/trunk/simpleCheck/source/uGPIO.cpp $
// $Rev: 20 $
// $Author: sounggalon $
// $Date: 2013-04-25 22:37:25 +0200 (Do, 25 Apr 2013) $
// $Id: uGPIO.cpp 20 2013-04-25 20:37:25Z sounggalon $
////////////////////////////////////////////////////////////////////////////////
#include "qp_port.h"
#include "main.h"


/// Initialize the GFD500 lamp
void gfdGPIO_init(void) {

GPIO_InitTypeDef GPIO_InitStructure;

	// Enable the GPIO_LED Clock
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	// Configure the GPIO_LED pin
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIOA->BSRRH = GPIO_Pin_7 | GPIO_Pin_15;	// disable gprs power and lamp
}


/// Turn on and turn off the lamp
/// \param NewState	ENABLE / DISABLE to turn on/off the lamp
void Lamp(FunctionalState NewState) {

	if (NewState == DISABLE)
		GPIOA->BSRRH = GPIO_Pin_7;
	else
		GPIOA->BSRRL = GPIO_Pin_7;
}


/// Turn on and turn off the GPRS power
/// \param NewState	ENABLE / DISABLE to turn on/off the GPRS powr
void Power4V2(FunctionalState NewState) {

	if (NewState == DISABLE)
		GPIOA->BSRRH = GPIO_Pin_15;
	else
		GPIOA->BSRRL = GPIO_Pin_15;
}

