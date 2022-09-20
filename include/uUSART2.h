////////////////////////////////////////////////////////////////////////////////
///
/// \file	hdlrUSART2.h
///
///			USART handler and support routines
///
/// \author J. Sounggalon S
///
// $URL: file:///Z:/Data/svn/gfd500/gfdhw05/trunk/simpleCheck/include/uUSART2.h $
// $Rev: 17 $
// $Author: sounggalon $
// $Date: 2013-04-25 17:35:30 +0200 (Do, 25 Apr 2013) $
// $Id: uUSART2.h 17 2013-04-25 15:35:30Z sounggalon $
////////////////////////////////////////////////////////////////////////////////
#ifndef UUSART2_H_
#define UUSART2_H_



void USART2_init (void);
void USART2_putc (char c);
int USART2_getc (void);
void USART2_puts (const char* s);
void USART2_putline (void);
int USART2_KeyHit (void);
int USART2_available (void);



#endif
