#ifndef __stationSettingClass_H
#define __stationSettingClass_H
#include "wctString.h"
typedef struct
{
	wchar_t stnID[4];
	int infeed;
	int infeedoffset;
	int outfeed;
	int outfeedoffset;
	//wchar_t prodlineID[4];
} stationParameterType;

typedef struct{
	char Idstring[3];
	int versionMajor;
	int versionMinor;
	char spare[64];
	int reccount;
	char endheaderCheckId[3];
}stationParameterFileHeaderType;


#define MAX_STATIONARRAY_SIZE		128
class stationSettingClass{
private:
	int count;
	bool storeLock;
	stationParameterType *stationPara[MAX_STATIONARRAY_SIZE];
	stationParameterFileHeaderType	FileHeader;
	wctString *filepath;
	wctString *filepathname;
	wctString *userfilepathname;
	wchar_t wt_prodline[32];
public:
	
	stationSettingClass(const wchar_t *path, wchar_t *prodline);
	~stationSettingClass();
	//const char *getfile_Name();
	const wchar_t *wgetfile_Name();
	const char *cgetfile_Name();
	const wchar_t *getprodline(){return wt_prodline;}
	void setuserfilepathname(const wchar_t *filepath)
	{
		userfilepathname = new wctString(filepath);

	}
	int getcount(){return count;}
	void add(stationParameterType *sPara);
	int get(int ii, stationParameterType *sPara);
	int set(int ii, stationParameterType *sPara);
	void export2CSV(const char *filename);
	int importFromCSV(const char *filename);
	wchar_t *getCSVtitleLine(wchar_t *title, int size);
	void deleteAll();



private:
	void CSVformat2TableRow(int col, int row, char *linebuf, int *width, int *height, stationParameterType *sPara);
	void arrayData(int icol, const char *vbuf, stationParameterType *sPara);
	void writeDat();
	void readDat();
};


#endif