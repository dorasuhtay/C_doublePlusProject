#ifndef __csvStringClass__H
#define __csvStringClass__H

#define MAX_PARSED_ELEMENT		256

class csvStringClass
{
private:
	int count;
	wchar_t *wstr[MAX_PARSED_ELEMENT];
	wchar_t *inputstr;
	int length, vbuflen;
	wchar_t *vbuf;
public:
	csvStringClass(wchar_t *str);
	~csvStringClass();
	void parseCSV(wchar_t delimiter);
	int add(wchar_t *str);
	int getcount(){return count;}
	int get(int index, wchar_t *str, int len);
};

extern void CSVformat2TableRow(int col, int row, char *linebuf, int *width, int *height, void(*func)(int icol, const char *vbuf, void *sPara), void *sPara);


#endif