#include "StdAfx.h"
#include "childWindow_func.h"

void ChildWindowClosing(childWindowType *chldWndw, int X, int Y)
{
	chldWndw->X = X;
	chldWndw->Y = Y;
	//SaveConfigINI();
}
		
void ChildWindowResizeEnd(childWindowType *chldWndw, int Width,  int Height)
{
	chldWndw->W = Width;
	chldWndw->H = Height;
	//SaveConfigINI();
}
		

int ChildWindowGetLocation(childWindowType *chldWndw, int *X,  int *Y)
{
	if ((chldWndw->X>0)&&(chldWndw->Y>0))
	{
		*X = chldWndw->X;
		*Y = chldWndw->Y;
		return 1;
	}
	return 0;
}

int ChildWindowGetSize(childWindowType *chldWndw, int *W,  int *H)
{
	if ((chldWndw->W>40)&&(chldWndw->H>40))
	{
		*W = chldWndw->W;
		*H = chldWndw->H;
		return 1;
	}
	return 0;
}

