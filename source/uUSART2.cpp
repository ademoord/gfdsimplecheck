////////////////////////////////////////////////////////////////////////////////
///
/// \file	hdlrUSART2.cpp
///
///			USART handler and support routines
///
/// \author J. Sounggalon S
///
// $URL: file:///Z:/Data/svn/gfd500/gfdhw05/trunk/simpleCheck/source/uUSART2.cpp $
// $Rev: 17 $
// $Author: sounggalon $
// $Date: 2013-04-25 17:35:30 +0200 (Do, 25 Apr 2013) $
// $Id: uUSART2.cpp 17 2013-04-25 15:35:30Z sounggalon $
////////////////////////////////////////////////////////////////////////////////
#include "qp_port.h"
#include "main.h"



/// Initialize the USART2 for 115K 8N1 at PD5 and PD6
void USART2_init (void) {

USART_InitTypeDef	USART_InitStructure;
GPIO_InitTypeDef	GPIO_InitStructure;
NVIC_InitTypeDef	NVIC_InitStructure;

	// Turn on the driving clock
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	// Connect PXx to USARTx_Tx, Rx
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);

	// Configure USART Tx as alternate function
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	// Configure USART Rx as alternate function
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	// USART configuration
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);


    // Configure the NVIC Preemption Priority Bits
//    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    // Enable the USARTy Interrupt
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // Enable USARTz Receive and Transmit interrupts
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    //USART_ITConfig(USART1, USART_IT_TXE, ENABLE);

	// Enable USART
	USART_Cmd(USART2, ENABLE);
}




void USART2_putc (char c) {

	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
		;
	USART_SendData(USART2, c);

}


int USART2_getc (void) {

	return USART_ReceiveData(USART2);
}


void USART2_puts (const char* s) {

	while (*s)
		USART2_putc(*s++);
}


void USART2_putline (void) {

	USART2_putc('\r');
	USART2_putc('\n');
}


int USART2_KeyHit (void) {

	return USART_GetFlagStatus(USART2, USART_FLAG_RXNE);
}



int USART2_available (void) {

	return 0;
}


extern "C" void USART2_IRQHandler(void) __attribute__((__interrupt__));
extern "C" void USART2_IRQHandler(void) {

    QK_ISR_ENTRY();                          // inform QK about ISR entry

	// Receiver interrupt handler
	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET) {

		// Read one byte from the receive data register
		TEvtCommon *ev = Q_NEW(TEvtCommon, SIG_CHAR_IN);
		ev->par = USART_ReceiveData(USART2);
		aoInterpreter->POST(ev, (void*)0);
	}

	// Transmitter interrupt handler
	if(USART_GetITStatus(USART2, USART_IT_TXE) == SET) {

	}

    QK_ISR_EXIT();                            // inform QK about ISR exit
}

