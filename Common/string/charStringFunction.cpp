#include "StdAfx.h"
//#include <stdio.h>
#include <windows.h>
#include <string.h>
#include "charStringFunction.h"

#define deletechar(strbuf,pos) strcpy((strbuf+pos),(strbuf+pos+1))
//---------------------------------------------------------------------
//Function: strcrop
//Synopsis: Drops trailing whitespace from string by truncating string
//to the last non-whitespace character.  Returns string.  If string is
//null, returns null.
//---------------------------------------------------------------------
char *strcrop (char *string)
{
    char *last;
    if (string)
      {
        last = string + strlen (string);
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
char *ltrim(char *string)
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
char *trim (char *string)
{
    ltrim (string);
    strcrop (string);
    return string;
}