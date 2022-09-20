////////////////////////////////////////////////////////////////////////////////
///
/// \file	uMonitor.cpp
///
///			monitor commands for GFD500
///
/// \author J. Sounggalon S
///
// $URL: file:///Z:/Data/svn/gfd500/gfdhw05/trunk/simpleCheck/source/uMonitor.cpp $
// $Rev: 20 $
// $Author: sounggalon $
// $Date: 2013-04-25 22:37:25 +0200 (Do, 25 Apr 2013) $
// $Id: uMonitor.cpp 20 2013-04-25 20:37:25Z sounggalon $
////////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "qp_port.h"
#include "main.h"


/// Show the software versions
int cmdVersion (int argc, char *argv[]) {

    xprintf (sWelcome);
    xprintf ("QP %s\r\n\r\n", QF::getVersion());
    return 0;
}

int cmdBlink (int argc, char *argv[]) {

	if (argc == 1) {
		xprintf("Needs arguments\n");
		return 0;
	}
	else if (strcmp(argv[1], "on") == 0) {
		TEvtCommon *ev = Q_NEW(TEvtCommon, SIG_FLASHING);
		aoBlinker->POST(ev, (void*)0);
	}
	else if (strcmp(argv[1], "off") == 0) {
		TEvtCommon *ev = Q_NEW(TEvtCommon, SIG_FLASHING);
		aoBlinker->POST(ev, (void*)0);
	}

	return 0;
}




/// Turn the lamp on or off
int cmdLamp (int argc, char *argv[]) {

	if (argc == 1) {
		xprintf("Needs arguments\n");
		return 0;
	}
	else if (strcmp(argv[1], "on") == 0) {
		Lamp(ENABLE);
	}
	else if (strcmp(argv[1], "off") == 0) {
		Lamp(DISABLE);
	}

    return 0;
}




const struct TCommandEntry tblCommand[] = {
	    { "ver",    		cmdVersion      		},
	    { "lamp",    		cmdLamp         		},
	    { "blink",    		cmdBlink         		},

		{ 0,            	0               		}
	};

