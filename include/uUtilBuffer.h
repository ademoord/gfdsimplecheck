////////////////////////////////////////////////////////////////////////////////
///
/// \file	utilBuffer.h
///
///			buffer utility
///
/// \author J. Sounggalon S
///
// $URL: file:///Z:/Data/svn/gfd500/gfdhw05/trunk/simpleCheck/include/uUtilBuffer.h $
// $Rev: 20 $
// $Author: sounggalon $
// $Date: 2013-04-25 22:37:25 +0200 (Do, 25 Apr 2013) $
// $Id: uUtilBuffer.h 20 2013-04-25 20:37:25Z sounggalon $
////////////////////////////////////////////////////////////////////////////////
#ifndef UTILBUFFER_H_
#define UTILBUFFER_H_

#ifdef __cplusplus
 extern "C" {
#endif

// the buffer length must be a power of 2
typedef struct TCircBufferTag {
    short int lenMask;              ///< buffer length - 1 / wrap up mask
    short int tail;                 ///< buffer tail / output index
    short int head;                 ///< buffer head / input index
    char *buf;             			///< pointer to the buffer
} TCircBuffer;


// simple linear buffer with any length
typedef struct TBufferTag {
    short int size;                 ///< buffer max size
    char *buf;                      ///< pointer to the buffer
    short int len;                  ///< buffer current length
} TBuffer;

void initCircBuffer(TCircBuffer *me, char *p, int len);
int isCircBufferEmpty(TCircBuffer *me);
int isCircBufferFull(TCircBuffer *me);
int cbufWrite(TCircBuffer *me, char c);
int cbufRead(TCircBuffer *me, char *pc);
void initBuffer(TBuffer *me, char *p, int len);
int isBufEmpty(TBuffer *me);
void bufEmpty(TBuffer *me);
void bufWrite(TBuffer *me, char c);
void bufBackspace(TBuffer *me);



#ifdef __cplusplus
}
#endif

#endif

