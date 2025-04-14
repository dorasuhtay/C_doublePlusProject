#include "StdAfx.h"

#if defined(__18CXX)
#include "Compiler.h"
#include <math.h>
#else
	#define ClrWdt()
#endif
#include <string.h>
#include "ibuf.h"



/*
#ifdef __BORLANDC__
#define __cplusplus
#endif

#ifdef __cplusplus
extern "C" {
#endif
*/
/*-------------------------------------------------------------------------------
SYNTAX:		   ibuf_initfill(ibuf_struct_type *fifo, char *buf, int bufsize);
DESCRIPTION:  Init, Zeros the locks, head and tail indices
PARAMETER1:   circularBuffer: buf.
PARAMETER2:   bufsize      : size of the fifo buffer "buf"
-------------------------------------------------------------------------------*/
void ibuf_init(ibuf_struct_type *fifo, unsigned int *buf, int bufsize)
{
	memset(fifo, 0x0, sizeof(ibuf_struct_type));
	fifo->bufsize = bufsize;
	fifo->buf = buf;
	memset(fifo->buf, 0x0, fifo->bufsize);
}

/*-------------------------------------------------------------------------------
SYNTAX:		   void ibuf_clear(ibuf_struct_type *fifo)
DESCRIPTION:  Clears the buffer and init the pointers
PARAMETER1:   fifo          : Circular buffer.
-------------------------------------------------------------------------------*/
void ibuf_clear(ibuf_struct_type *fifo)
{
	//while(fifo->lockbuf);
	//fifo->lockbuf = 1;
	fifo->tail = 0;
	fifo->head = fifo->tail;
	memset(fifo->buf, 0x0, fifo->bufsize);
	//fifo->lockbuf = 0;
}

/*-------------------------------------------------------------------------------
SYNTAX:		   void ibuf_fill(ibuf_struct_type *fifo, unsigned char chr);
DESCRIPTION:  Fills the buffer with a value
PARAMETER1:   fifo          : Circular buffer.
PARAMETER2:   value         : value to write
-------------------------------------------------------------------------------*/
void ibuf_initfill(ibuf_struct_type *fifo, unsigned int value)
{
	int ii;
	for (ii=0;ii<fifo->bufsize;ii++){
		ClrWdt();
		fifo->buf[ii] = value;
		}
}



/*-------------------------------------------------------------------------------
SYNTAX:		   void ibuf_putch(ibuf_struct_type *fifo, unsigned char chr);
DESCRIPTION:  puts the value into the next available position. If the
              buffer is full, chr is lost.
PARAMETER1:   fifo          : Circular buffer.
PARAMETER2:   value         : value to write
-------------------------------------------------------------------------------*/
void ibuf_put(ibuf_struct_type *fifo, unsigned int value)
{
	//while(fifo->lock);
	//fifo->lock = 1;
	fifo->buf[fifo->head] = value;
	fifo->head++;
	fifo->head = fifo->head%fifo->bufsize;
	//if overun then overwrite the last data
	if (fifo->head==fifo->tail)
		fifo->tail = fifo->tail%fifo->bufsize;
	//fifo->lock = 0;
}

void ibuf_push(ibuf_struct_type *fifo, unsigned int value)
{
	ibuf_put(fifo, value);
	fifo->tail++;
	fifo->tail = fifo->tail%fifo->bufsize;
}

float ibuf_average(ibuf_struct_type *fifo)
{
	int ii;
	float ave;
	ave = 0.0;
	for (ii=0;ii<fifo->bufsize;ii++){
		ClrWdt();
		ave+=(float)fifo->buf[ii];
		}
	return ave/(float)fifo->bufsize;
}
/*
float ibuf_StandDev(ibuf_struct_type *fifo)
{
	int ii;
	double SumY,SumY2,ff;
	int nn = 0;
 	SumY=SumY2=(double)0.0;
	for (ii=0;ii<fifo->bufsize;ii++){
		ff = (double)fifo->buf[ii];
		SumY  = SumY  + ff;
		SumY2 = SumY2 + (ff*ff);
		nn++;
		}
	SumY = (SumY*SumY/(double)nn);
	return (float)sqrt((SumY2 - SumY)/((double)nn-(double)1.0));
}
*/

/*-------------------------------------------------------------------------------
SYNTAX:		   int ibuf_used(ibuf_struct_type *fifo);
DESCRIPTION:  Calculates used up data space.
PARAMETER1:   fifo          : Circular buffer.
RETURN VALUE:	number of bytes in buffer

01234567890
 ^    ^
-------------------------------------------------------------------------------*/
int ibuf_used(ibuf_struct_type *fifo)
{
	//while(fifo->lockbuf);
	//fifo->lockbuf = 1;
	if (fifo->head==fifo->tail) {/*fifo->lockbuf = 0; */return 0;}
	if (fifo->head>fifo->tail)  {/*fifo->lockbuf = 0; */return fifo->head-fifo->tail;}
	if (fifo->head<fifo->tail)  {/*fifo->lockbuf = 0; */return (fifo->bufsize-fifo->tail)+fifo->head;}
	//fifo->lockbuf = 0;
	return 0;
}

/*-------------------------------------------------------------------------------
SYNTAX:		   int ibuf_getch(ibuf_struct_type *fifo);
DESCRIPTION:  returns the first character of the data, indicated by head.
PARAMETER1:   circularBuffer: Circular buffer.
RETURN VALUE:	-1 if the buffer is empty, the character at the head index
					if not.
-------------------------------------------------------------------------------*/
int ibuf_get(ibuf_struct_type *fifo, unsigned int *value)
{
//	long retvalue;
	//while(fifo->lockbuf);
	//fifo->lockbuf = 1;
	if (fifo->head==fifo->tail) {/*fifo->lockbuf = 0;*/return -1;	}
	*value = (long)fifo->buf[fifo->tail];
	fifo->tail++;
	fifo->tail = fifo->tail%fifo->bufsize;
	//fifo->lockbuf = 0;
	return 0;
}

/*
#ifdef __cplusplus
}
#endif
*/
