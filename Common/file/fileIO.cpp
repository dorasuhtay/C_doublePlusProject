#include "StdAfx.h"
#include <stdlib.h>
#include <string.h>
#include <sys\stat.h>
#include "fileIO.h"

#ifdef _UNICODE
#include <tchar.h>
#endif



int Readln(FILE *fp, char *buf, int bufsize)
{
 int ch;
 char *bufptr = buf;
 int count = 0;
 int done = 0;
 while (!done) {
		ch = fgetc(fp);
		*bufptr  = (char)ch;
		bufptr++;
		count++;
		if (ch==EOF) {
			count = -1;
			break;
			}
		if (count>=bufsize) {
			count = -2;		// exceeded buf size
			break;
			}
	  if (ch==13) {			//CRLF
			//ch = fgetc(fp);
			//*bufptr  = (char)ch;
			//bufptr++;
			//count++;
			// (ch==10) {
				break;
				//
         }
	  if (ch==10) {			//LF
		  break;
	     }
	  }
 *bufptr = 0x00;
 return count;
}
/*
//-------------------------------------------------------------------------------
//Read a line from the file (non-UNICODE)
//PARAMETER: bufsize i the size of the number of unicode characters to read
//RETURN: the number of unicode characters read
//-------------------------------------------------------------------------------
int Readln(FILE *fp, char *buf, int bufsize)
{
    int ch;
    char *bufptr = buf;
    int count = 0;
    int done = 0;
    while (!done)
    {
		ch = fgetc(fp);
		*bufptr  = (char)ch;
		bufptr++;
		count++;
		if (ch==EOF)
		{
			count = -1;
			break;
		}
		if (count>=bufsize)
		{
			count = -2;		// exceeded buf size
			break;
		}
        if (ch==13)         //CRLF
        {
			ch = fgetc(fp);
			*bufptr  = (char)ch;
			bufptr++;
			count++;
			if (ch==10)
				break;
        }
        if (ch==10) 			//LF
		  break;
    }
    *bufptr = 0x00;
    return count;
}
*/

int file_copy_bin (const char *dest, const char *src)
{
	#define BLOCK_SIZE		16384
    FILE *inf, *outf;
    char *buffer;
    size_t chars_read, outread;                  /*  Amount read from stream          */
    int  feedback = -1;
	inf = fopen (src, "rb");
	if (inf)
	{
		buffer = (char *)malloc(BLOCK_SIZE);
		if (buffer)
		{
			outf = fopen (dest, "wb");
			if (outf)
			{
				while (!feof(inf))
				{
					chars_read = fread(buffer, 1, BLOCK_SIZE, inf);
					if (chars_read<=0)
						break;
					outread = fwrite (buffer, 1, chars_read, outf);
					if (outread != chars_read)
					{
						feedback = -4;
						break;
					}
				}
				fclose (outf);
			}
			free (buffer);	
		}
		fclose (inf);
	}
    return feedback;
}

int file_copy_2_backup(const char *src, const char *backupextension)
{
	int nn = 0;
	char *destpath = new char [strlen(src)+strlen(backupextension)+1];
	strcpy(destpath, src);
	char *sptr = strrchr(destpath, '.');
	if (sptr)
		*sptr = 0x0;
	strcat(destpath, backupextension);
	if (strcmp(src, destpath)!=0)
	{
		file_copy_bin (destpath, src);
		nn = 1;
	}
	delete destpath;
	return nn;
}

long get_file_size (const char *filename)
{
    struct stat stat_buf;
    if (stat ((char *) filename, &stat_buf) == 0)
        return ((long) stat_buf.st_size);
    else
        return (-1);
}

//----------------------------------------------------------------
//read a line that is terminated by a linefeed (10)
//linefeed within quote marks "" will not terminate line
//PARAMETER: fp ------- is the filestream pointer
//           buf ------ is the buffer that will hold the read line
//           bufsize -- is the max. size of the buffer buf
//----------------------------------------------------------------
int ReadlnEx(FILE *fp, char *buf, int bufsize)
{
 int ch;
 char *bufptr = buf;
 int count = 0;
 int done = 0;
 bool foundbeginofText = 0;
 while (!done) {
		ch = fgetc(fp);
		*bufptr  = (char)ch;
		bufptr++;
		count++;
		if (ch==EOF) {
			count = -1;
			break;
			}
		if (ch=='\"')
      	foundbeginofText = !foundbeginofText;
		if (count>=bufsize) {
			count = -2;		// exceeded buf size
			break;
			}
        if (ch=='\n')       //LF
        {
     		if(!foundbeginofText)
                break;
	    }
	  }
 *bufptr = 0x00;
 return count;
}



#ifdef _UNICODE
//-------------------------------------------------------------------------------
//Read a line from the file (UNICODE)
//PARAMETER: bufsize i the size of the number of unicode characters to read
//RETURN: the number of unicode characters read
//-------------------------------------------------------------------------------
int wcReadln(FILE *fp, TCHAR *buf, int bufsize)
{
    wint_t ch;
    TCHAR *bufptr = buf;
    int count = 0;
    int done = 0;
    while (!done)
    {
        ch = fgetwc(fp);
		*bufptr  = (TCHAR)ch;
		bufptr++;
		count++;
		if (ch==EOF)
		{
			count = -1;
			break;
		}
		if (count>=bufsize)
		{
			count = -2;		// exceeded buf size
			break;
		}
        if (ch=='\r')       //CRLF
        {
			ch = fgetwc(fp);
			*bufptr  = (TCHAR)ch;
			bufptr++;
			count++;
			if (ch=='\n')
				break;
         }
	  if (ch=='\n') 			//LF
		  break;
    }
    *bufptr = 0x00;
    return count;
}
#endif



void append2file(const char *filename, const char *data, int size)
{
    FILE *fp = fopen(filename, "a+b");
    if (fp)
    {
        fwrite(data, 1, size, fp);
        fclose(fp);
    }
}

#ifdef _UNICODE
void append2file(const wchar_t *filename, const wchar_t *data, int size)
{
    FILE *fp = _wfopen(filename, L"at+,ccs=UNICODE");
    if (fp)
    {
        fwrite(data, size*sizeof(wchar_t),  1,  fp);
        fclose(fp);
    }
}
#endif