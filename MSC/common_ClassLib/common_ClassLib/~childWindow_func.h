#ifndef ____childWindow_func__H__
#define ____childWindow_func__H__


typedef struct{
	int X;
	int Y;
	int W;
	int H;
	int Opened;
	char name[32];
}childWindowType;

/*
extern int ChildWindowGetSize(childWindowType *chldWndw, int *W,  int *H);
extern int ChildWindowGetLocation(childWindowType *chldWndw, int *X,  int *Y);
extern void ChildWindowClosing(childWindowType *chldWndw, int X, int Y);
extern void ChildWindowResizeEnd(childWindowType *chldWndw, int Width,  int Height);
*/

extern void ChildWindowClosing(childWindowType *chldWndw, int X, int Y);		
extern void ChildWindowResizeEnd(childWindowType *chldWndw, int Width,  int Height);
extern int ChildWindowGetLocation(childWindowType *chldWndw, int *X,  int *Y);
extern int ChildWindowGetSize(childWindowType *chldWndw, int *W,  int *H);


#endif