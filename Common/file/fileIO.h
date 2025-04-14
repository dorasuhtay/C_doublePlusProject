#ifndef ___fileIO__h
#define ___fileIO__h

#include <stdio.h>

extern int Readln(FILE *fp, char *buf, int bufsize);
extern int file_copy_bin (const char *dest, const char *src);
extern int file_copy_2_backup(const char *src, const char *backupextension);
extern long get_file_size (const char *filename);
extern void append2file(const char *filename, const char *data, int size);


#ifdef _UNICODE
//-------------------------------------------------------------------------------
//Read a line from the file (UNICODE)
//PARAMETER: bufsize i the size of the number of unicode characters to read
//RETURN: the number of unicode characters read
//-------------------------------------------------------------------------------
extern int wcReadln(FILE *fp, wchar_t *buf, int bufsize);
extern void append2file(const wchar_t *filename, const wchar_t *data, int size);
#endif

#endif
