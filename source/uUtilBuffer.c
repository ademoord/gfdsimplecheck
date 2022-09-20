////////////////////////////////////////////////////////////////////////////////
///
/// \file	utilBuffer.c
///
///			buffer utility
///
/// \author J. Sounggalon S
///
// $URL: file:///Z:/Data/svn/gfd500/gfdhw05/trunk/simpleCheck/source/uUtilBuffer.c $
// $Rev: 20 $
// $Author: sounggalon $
// $Date: 2013-04-25 22:37:25 +0200 (Do, 25 Apr 2013) $
// $Id: uUtilBuffer.c 20 2013-04-25 20:37:25Z sounggalon $
////////////////////////////////////////////////////////////////////////////////
#include "uUtilBuffer.h"


/// Initialize the circular buffer for operation
/// \param *cb  pointer to the circular buffer structure
/// \param *p   pointer to the buffer to be managed
/// \param len  buffer length must be a power of 2
void initCircBuffer(TCircBuffer *me, char *p, int len) {

    me->lenMask = len - 1;
    me->tail = me->head = 0;
    me->buf = p;
}


/// Check if the circular buffer empty
/// \param cb   pointer to the circular buffer
/// \return     TRUE if buffer empty
int isCircBufferEmpty(TCircBuffer *me) {

    return (me->tail == me->head);
}


/// Check if the circular buffer full
/// \param cb   pointer to the circular buffer
/// \return     TRUE if buffer already full
int isCircBufferFull(TCircBuffer *me) {

    return (((me->head+1) & me->lenMask) == me->tail);
}


/// Write a character into the circular buffer
/// \param *cb  pointer to the circular buffer
/// \param c    character to be written
/// \return     0 successful write
///             -1 error, buffer is already full
int cbufWrite(TCircBuffer *me, char c) {

    if (isCircBufferFull(me))       // if buffer already full
        return -1;                  // return with error code

    me->buf[me->head++] = c;        // store and increment the pointer
    me->head &= me->lenMask;        // wrap up the head pointer
    return 0;
}


/// Read a character from the circular buffer
/// \param *cb  pointer to the circular buffer
/// \param *c   pointer to character to be read
/// \return     0 successful read
///             -1 error, buffer is already empty
int cbufRead(TCircBuffer *me, char *pc) {

    if (isCircBufferEmpty(me))      // if buffer already empty
        return -1;                  // return with error code

    *pc = me->buf[me->tail++];      // get a character out of the buffer
    me->tail &= me->lenMask;        // wrap up the tail pointer
    return 0;
}



/// Initialize the linear buffer
/// \param *me  pointer to the buffer structure
/// \param *p   pointer to the buffer to be managed
/// \param len  buffer length could be any length
void initBuffer(TBuffer *me, char *p, int len) {

    me->size = len;
    me->buf = p;
    me->len = 0;
}


/// Empty the buffer
/// \param *me  pointer to the buffer structure
void bufEmpty(TBuffer *me) {

    me->len = 0;
}


/// Check if the buffer is empty
/// \param *me  pointer to the buffer structure
/// \return     TRUE if empty
int isBufEmpty(TBuffer *me) {

    return (me->len == 0);
}


/// Insert a byte into the buffer
/// \param *me  pointer to the buffer structure
/// \param c    character to be written
void bufWrite(TBuffer *me, char c) {

    me->buf[me->len] = c;               // store the character
    if (++me->len == me->size-1)        // prevent buffer overflow
        me->len = me->size-2;           // let one place holder for null termination
}

/// Delete the last character
void bufBackspace(TBuffer *me) {

    if (me->len > 0)
        me->len--;
}

