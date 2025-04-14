#ifndef ___fileIO__h
#define ___fileIO__h

#include <stdio.h>

extern int Readln(FILE *fp, char *buf, int bufsize);
extern int file_copy_bin (const char *dest, const char *src);
extern int file_copy_2_backup(const char *src, const char *backupextension);
extern long get_file_size (const char *filename);

#endif