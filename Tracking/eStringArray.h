#ifndef __eStringArray__H
#define __eStringArray__H

using namespace System;

#define MAX_ESTRINGARRAY		512
class eStringArray{
private:
	int count;
	//String ^sstr[MAX_ESTRINGARRAY];
public:
	eStringArray();
	~eStringArray();
	void add(String ^str);
	//String ^get(int index);
	int getcount() {return count;}
};


#endif