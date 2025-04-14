#include "StdAfx.h"
#include "numberconversion.h"

const unsigned char tab_char[16]=
{ '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'} ;

void htoa(char *str, unsigned char num)
{
    unsigned char tmp;
    tmp=num;
    tmp=tmp&(unsigned char)0xf0;
    tmp>>=4;
    *str= tab_char [ tmp];
    str++;
    *str= tab_char [ num &0x0f];
    str++;
	*str=0x0;
}

const unsigned char char_tab[128]=
             {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
             0,1,2,3,4,5,6,7,8,9,0,0,0,0,0,0,
             0,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0,0,0,0,0,0,0,0,0,
             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
             0,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0,0,0,0,0,0,0,0,0,
             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
              };

unsigned char a2toh(unsigned char *str)
{
   unsigned char tmp;
//   tmp=0;
   tmp=char_tab[*str];
   str++;
   tmp=tmp*16 + char_tab[* str];
   return tmp;

}
