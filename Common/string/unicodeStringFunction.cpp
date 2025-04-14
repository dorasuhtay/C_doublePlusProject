#include "StdAfx.h"
//#include <stdio.h>
#include <windows.h>
#include <TCHAR.H>
#include <string.h>
#include "unicodeStringFunction.h"

#define deletechar(strbuf,pos) _tcscpy((strbuf+pos),(strbuf+pos+1))
//---------------------------------------------------------------------
//Function: strcrop
//Synopsis: Drops trailing whitespace from string by truncating string
//to the last non-whitespace character.  Returns string.  If string is
//null, returns null.
//---------------------------------------------------------------------
wchar_t *strcrop (wchar_t *string)
{
    wchar_t *last;
    if (string)
      {
        last = string + _tcslen (string);
        while (last > string)
          {
            if (!isspace (*(last - 1)))
                break;
            last--;
          }
        *last = 0;
      }
    return (string);
}

//---------------------------------------------------------------------
//Function: ltrim
//Synopsis: Deletes leading white spaces in string, and returns a
//pointer to the first non-blank character.  If this is a null, the
//end of the string was reached.
//---------------------------------------------------------------------
wchar_t *ltrim(wchar_t *string)
{
	while (isspace(*string))
       deletechar(string,0);
	return string;
}

//---------------------------------------------------------------------
//Function: trim
//Synopsis: Eats the whitespace's from the left and right side of a
//string.  This function maintains a proper pointer head.  Returns a
//pointer to head of the buffer.
//Submitted by Scott Beasley <jscottb@infoave.com>
//---------------------------------------------------------------------
wchar_t *trim (wchar_t *string)
{
    ltrim (string);
    strcrop (string);
    return string;
}