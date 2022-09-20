////////////////////////////////////////////////////////////////////////////////
///
/// \file	main.h
///
///			header for this application
///
/// \author J. Sounggalon S
///
// $URL: file:///Z:/Data/svn/gfd500/gfdhw05/trunk/simpleCheck/include/main.h $
// $Rev: 20 $
// $Author: sounggalon $
// $Date: 2013-04-25 22:37:25 +0200 (Do, 25 Apr 2013) $
// $Id: main.h 20 2013-04-25 20:37:25Z sounggalon $
////////////////////////////////////////////////////////////////////////////////
#ifndef MAIN_H
#define MAIN_H

#include <stm32f2xx.h>
#include "term_io.h"
#include "uUSART2.h"
#include "uGPIO.h"
#include "bsp.h"
#include "uUtilBuffer.h"


using namespace QP;


enum GfdSignals {
   SIG_TIMEOUT = Q_USER_SIG,
   SIG_FLASHING,
   SIG_CHAR_IN,
   MAX_SIG                                                  // the last signal
};



class TEvtCommon : public QEvent {
public:
    uint32_t par;
};


struct  TCommandEntry {
    const char	*name;            		// Name of command seen by user.
    int     	(*func)(int, char**);   // Function called when command is invoked.
};


extern QActive* const aoBlinker;
extern QActive* const aoInterpreter;
extern const char sWelcome[];
extern const struct TCommandEntry tblCommand[];


#endif                                                                // MAIN_H


