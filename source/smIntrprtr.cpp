////////////////////////////////////////////////////////////////////////////////
///
/// \file	smIntrprtr.cpp
///
///			state machine for terminal interpreter
///
/// \author J. Sounggalon S
///
// $URL: file:///Z:/Data/svn/gfd500/gfdhw05/trunk/simpleCheck/source/smIntrprtr.cpp $
// $Rev: 20 $
// $Author: sounggalon $
// $Date: 2013-04-25 22:37:25 +0200 (Do, 25 Apr 2013) $
// $Id: smIntrprtr.cpp 20 2013-04-25 20:37:25Z sounggalon $
////////////////////////////////////////////////////////////////////////////////
#include <string.h>
#include "qp_port.h"
#include "main.h"


#define MAX_ARGUMENT_COUNT      64
#define SIZE_BUFFER_COMMAND		128

class Interpreter: public QActive {
private:
	char	inCmd[SIZE_BUFFER_COMMAND];
	TBuffer	bufRx;

public:
	Interpreter();

protected:
	static QState initial(Interpreter *me, QEvent const *e);
	static QState waiting(Interpreter *me, QEvent const *e);
};



const char sPrompt[] = "\r\n> ";

int tokenize(char *string, char *argv[]);
int executeCommand(char *s);

static Interpreter myInterpreter;
QActive *const aoInterpreter = (QActive*)&myInterpreter;



/// Class constructor
Interpreter::Interpreter() : QActive((QStateHandler)&Interpreter::initial)
{

}

/// Initial condition
QState Interpreter::initial(Interpreter *me, QEvent const *e) {

    xprintf(sWelcome);
	return Q_TRAN(&Interpreter::waiting);
}



QState Interpreter::waiting(Interpreter *me, QEvent const *e) {

	switch(e->sig) {
		case SIG_CHAR_IN: {

			// get the character from event
			char	c = ((TEvtCommon const *)e)->par;
			xputc(c);				// echo char to console

			switch (c) {
				case '\b':		// backspace char
					xputc(' ');
					xputc(c);
                    bufBackspace(&me->bufRx);   // backpace in buffer
					break;

				case '\r':		// carriage return
					xputc('\n');
					bufWrite(&(me->bufRx), 0);          // terminate string
					executeCommand(me->bufRx.buf);

					xprintf(sPrompt);
                    bufEmpty(&me->bufRx);
					break;

				default:		// other chars
                    bufWrite(&me->bufRx, c);
                    break;
			}

			return Q_HANDLED();
		}
	}

    return Q_SUPER(&QHsm::top);
}



/// Get the command line, tokenize the command and execute it from command table
/// \param s	command line string
int executeCommand(char *s) {

static struct TCommandEntry *pCmd;              ///< pointer to table command
static char *argv[MAX_ARGUMENT_COUNT];          ///< arguments list
static int argc;                                ///< argument count

	argc = tokenize(s, argv);

	// scan through the whole command table
	for (pCmd = (struct TCommandEntry*)tblCommand; pCmd->name; pCmd++)
		if (strcmp(argv[0], pCmd->name) == 0)
			break;

	// if the command is found then call it
	if (pCmd->name)
		return pCmd->func(argc, argv);     // pass the argument to the function
	else {
		USART2_puts ("Command not found\r\n");
		return -1;
	}
}


/// Take the incoming string and create an argv[] array from that.  The
/// incoming string is assumed to be writeable.  The argv[] array is simple
/// a set of pointers into that string, where the whitespace delimited
/// character sets are each NULL terminated.
/// \param string   pointer to buffer
/// \param argv     array of argument list
/// \return         number of arguments
int tokenize(char *string, char *argv[]) {

int	argc, done;

	/* Null out the incoming argv array. */
	for(argc=0; argc<MAX_ARGUMENT_COUNT; argc++)
		argv[argc] = (char *)0;

	argc = 0;
	while(1) {
		while ((*string == ' ') || (*string == '\t'))
			string++;
		if (*string == 0)
			break;
		argv[argc] = string;
		while ((*string != ' ') && (*string != '\t')) {
			if ((*string == '\\') && (*(string+1) == '"')) {
				strcpy(string,string+1);
			}
			else if (*string == '"') {
				strcpy(string,string+1);
				while(*string != '"') {
					if ((*string == '\\') && (*(string+1) == '"'))
						strcpy(string,string+1);
					if (*string == 0)
						return(-1);
					string++;
				}
				strcpy(string,string+1);
				continue;
			}
			if (*string == 0)
				break;
			string++;
		}
		if (*string == 0)
			done = 1;
		else {
			done = 0;
			*string++ = 0;
		}
		argc++;
		if (done)
			break;
		if (argc >= MAX_ARGUMENT_COUNT) {
			argc = -1;
			break;
		}
	}
	return(argc);
}


