#ifndef IBUF_H_INCLUDED
#define IBUF_H_INCLUDED

typedef struct {
	int head;
	int tail;
	unsigned int *buf;
	int bufsize;
	unsigned char lock;
	int overruncounter;
}ibuf_struct_type;

/*
#ifdef __BORLANDC__
#define __cplusplus
#endif
#ifdef __cplusplus
extern "C" {
#endif
*/


extern int ibuf_get(ibuf_struct_type *fifo, unsigned int *value);
extern int ibuf_used(ibuf_struct_type *fifo);
extern void ibuf_put(ibuf_struct_type *fifo, unsigned int value);
extern void ibuf_init(ibuf_struct_type *fifo, unsigned int *buf, int bufsize);
extern void ibuf_clear(ibuf_struct_type *fifo);
extern void ibuf_push(ibuf_struct_type *fifo, unsigned int value);
extern float ibuf_average(ibuf_struct_type *fifo);
extern void ibuf_initfill(ibuf_struct_type *fifo, unsigned int value);
/*
#ifdef __cplusplus
	}
#endif
*/


#endif // IBUF_H_INCLUDED
