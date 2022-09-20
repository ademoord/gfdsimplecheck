////////////////////////////////////////////////////////////////////////////////
///
/// \file	hdlrGPIO.h
///
///			GPIO handler and support routines
///
/// \author J. Sounggalon S
///
// $URL: file:///Z:/Data/svn/gfd500/gfdhw05/trunk/simpleCheck/include/uGPIO.h $
// $Rev: 20 $
// $Author: sounggalon $
// $Date: 2013-04-25 22:37:25 +0200 (Do, 25 Apr 2013) $
// $Id: uGPIO.h 20 2013-04-25 20:37:25Z sounggalon $
////////////////////////////////////////////////////////////////////////////////
#ifndef UGPIOA_H_
#define UGPIOA_H_


void Lamp(FunctionalState NewState);
void Power4V2(FunctionalState NewState);

void gfdGPIO_init(void);


#endif
