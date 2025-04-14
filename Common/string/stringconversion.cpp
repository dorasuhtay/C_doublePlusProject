#include "StdAfx.h"
#include <TCHAR.H>
#include <string.H>
#include "stringconversion.h"
#include "xplatform_define.h"
#ifdef _MSC_VER
#include <vcclr.h>  
#endif

const char *String2Char(String^ bData, char *out)
{
	int ii;
	out[0] = 0x0;
	if ((bData==nullptr)||(bData==""))
		return "";
	for (ii=0;ii<bData->Length;ii++)
		out[ii] = (char)bData[ii];
	out[ii] = 0x0;
	return out;
}

const char *String2Char_n(String^ bData, char *out, int size)
{
	int ii;
	out[0] = 0x0;
	if ((bData==nullptr)||(bData==""))
		return "";
	if (bData->Length<size)
		size = bData->Length;
	for (ii=0;ii<size;ii++)
		out[ii] = (char)bData[ii];
	out[ii] = 0x0;
	return out;
}
void String2CharArray(String^ bData, wchar_t *out)
{
	/*#ifdef _MSC_VER
		pin_ptr<const wchar_t> wch = PtrToStringChars(bData);
		_tcscpy_s(out, wch);
	#else*/
	if (out)
	{
		int ii;
		out[0] = 0x0;
		if ((bData==nullptr)||(bData==""))
		{
			_tcscpy(out, _T("null"));
			//wcscpy_s(out, L"null");
			return;
		}
		for (ii=0;ii<bData->Length;ii++)
			out[ii] = bData[ii];
		out[ii] = 0x0;
	}
	
}

const wchar_t *String2wChar_n(String^ bData, wchar_t *out, int size)
{
	#ifdef _MSC_VER
		pin_ptr<const wchar_t> wct = PtrToStringChars(bData);
		_tcsncpy(out, wct, size);
		out[size] = 0x0;
	#else
#error();
	sfsedf
	#endif
		return out;
}


void wchar_t2char(const wchar_t *bData, char *out)
{
	int ii;
	for (ii=0;ii<_tcslen(bData);ii++)
		out[ii] = bData[ii];
	out[ii] = 0x0;
}

bool isNum(String ^Str)
{
	double Num;
	return double::TryParse(Str->Trim(), Num);
}
//-----------------------------------------------------------------
//To replace "Convert::ToInt32"
//e.g. convert from decimalASCII to integer
//			String^ valuestr = "1234";
//			number = convertToInt32(valuestr);
//e.g. convert from hexASCII to integer
//			String^ valuestr = "007E";
//			number = convertToInt32(valuestr, 16);
//-----------------------------------------------------------------
int convertToInt32(String^ valuestr, int base)
{
	wchar_t wstr[128];
	valuestr->Trim();
	String2wChar_n(valuestr, wstr, 127);
	return _ttoi(wstr);
	/*
	if (base==10)
	{
		if (isNum(valuestr))
			return Convert::ToInt32(valuestr, base);
	}
	try
	{
		return Convert::ToInt32(valuestr, base);
	}
	catch(...)
	{
		return 0;
	}
	*/
 }



array<Byte>^ MakeManagedArray(unsigned char* input, int len)
{
    array<Byte>^ result = gcnew array<Byte>(len);
	result[0] = 0x0;
    for(int i = 0; i < len; i++)
        result[i] = input[i];
    return result;
}

array<Byte> ^MakeManagedArray(array<Byte> ^%arry, unsigned char* input, int len)
{
    arry = gcnew array<Byte>(len);
	arry[0] = 0x0;
	int i;
    for(i = 0; i < len; i++)
        arry[i] = input[i];
    return arry;
}

String^ StripStartTags( String^ cmdstring, String ^ValueIdentifier, String ^separator )
{
   // try to find a tag at the start of the line using StartsWith 
   if ( cmdstring->Trim()->StartsWith( ValueIdentifier ) )
   {
      // now search for the closing tag->->. 
      int lastLocation = cmdstring->IndexOf( separator );

      // remove the identified section, if it is a valid region 
      if ( lastLocation >= 0 )
	  {
            cmdstring = cmdstring->Substring( lastLocation + 1 );
			return cmdstring->Trim();
	  }
   }
   return nullptr;
}


//-----------------------------------------------------------------------
//Parse a delimited csv string
//Handles    "abcde","defgh","rtf",,,,abdget,ueybh,1,
//-----------------------------------------------------------------------
int parseField(char *str, int strlength, int fieldno, char fielddelimiter, char textstartqualifier, char textendqualifier, char *fieldbuf, int fieldlen)
{
	char linendqualifier = '\n';
	int count;//, sametextqualifier;
//	int ii, count, sametextqualifier;
   char *sptr = str;
//   bool fieldfound = 0;
   static bool block = 0;
   static bool block2 = 0;
   static bool foundfielddelimiter=0;
   int fieldbufptr = 0;
 //  bool done = 0;
//   char textEnd = textendqualifier;
   count = 0;
   fieldbuf[0] = 0x0;
//	if (textstartqualifier==textendqualifier)
//   	sametextqualifier = 1;
//   else
//	   sametextqualifier = 0;
//	bool takechar = 1;
//   int iptr = 0;
   block = 0;
   block2 = 0;
   foundfielddelimiter=0;
	while(*sptr){
      //---------------------------------------------------------------------------------)
		//handles the spaces before a fielddata (remove the left spaces of a fielddata
      //---------------------------------------------------------------------------------)
   	if ((!block)&&(!block2)){
			if (foundfielddelimiter){
				if (*sptr!=' '){
     		      foundfielddelimiter = 0;
					fieldbufptr = 0;
         		}
	      	}
         }

		//when block is set data is being extracted
      //block is set when:-
      // 1) separator is detected followed by a textstartqualifier
      // 2) separator is detected followed by a non-space character

   	if (block||block2){		//
         //-----------------------------------------------------------------
			//\"   this takes care of "inches symbol"
         //inches symbols are usually exported to CSV type file as 2""  (refers to 2 inches)
         //the symbol for inches is " (0x22) same as text delimiter
         //-----------------------------------------------------------------
	   	if (*sptr==0x22){		//\"   this takes care of "inches symbol"
		   	if (*(sptr+1)==0x22){		//\"
			      if (count==fieldno){
						fieldbuf[fieldbufptr] = *sptr;
						fieldbufptr = (fieldbufptr+1) % fieldlen;
     					fieldbuf[fieldbufptr] = 0x0;
			         sptr+=2;
         			continue;
						}
               }
         	}
      	}

   	if ((sptr==str)&&(*sptr==textstartqualifier)){
      	block=1;
         sptr++;
         continue;
      	}

      if (count!=fieldno){
	   	if (block&&(*sptr==textendqualifier)){
				block = 0;
				fieldbufptr=0;                               //cases such as ..., C1, "test this line",
         	sptr++;
	         continue;
   	   	}
         }

   	if ((!block)&&(*sptr==textstartqualifier)){
			block = 1;
			fieldbufptr=0;                               //cases such as ..., C1, "test this line",
         sptr++;
         continue;
      	}

/*
   	if (*sptr==textendqualifier){                      //",
	   	if (*(sptr+1)==fielddelimiter){
	      	block=0;
	         sptr++;
            if (*sptr==0) 	break;
            count++;
            if (count>fieldno){
			   	return fieldbufptr;
	            }
            fieldbufptr = 0;
	         sptr++;
            continue;
            }
      	}
*/
   	if (*sptr==textstartqualifier){
	   	if (*(sptr-1)==fielddelimiter){
	      	block=1;
	         sptr++;
            continue;
         	}
      	}

		// ...."\n   last item in the list
   	if (*sptr==textendqualifier){
	   	if (*(sptr+1)==linendqualifier){
				break;
         	}
         }
		// ...."\0   last item in the list
   	if (*sptr==textendqualifier){
	   	if (*(sptr+1)==0){
				break;
         	}
         }

		if (!block){
			// ...."\0   last item in the list
   		if (*sptr==linendqualifier)
				break;
      	}

   	if (*sptr==fielddelimiter){
      	if (!block){
         	foundfielddelimiter=1;
            count++;
            if (count>fieldno){
			   	return fieldbufptr;
	            }
            fieldbufptr = 0;
         	sptr++;
            continue;
            }
      	}
      if (count>fieldno){
	   	return fieldbufptr;
      	}

      if (count==fieldno){
			if ((!block)&&(*sptr==textstartqualifier)){
				fieldbufptr=0;                               //cases such as ..., C1, "test this line",
				block = 1;												//start blocking
            }
			else
         	{
            if (*sptr==textendqualifier)
			   	return fieldbufptr;
				fieldbuf[fieldbufptr] = *sptr;
				fieldbufptr = (fieldbufptr+1) % fieldlen;
     			fieldbuf[fieldbufptr] = 0x0;
            }
//         if(strncmp(fieldbuf, "CLCF_YES", 8)==0)
//         	printf("");
         }
		sptr++;
	  	}
	if (fieldbufptr>0)
		return fieldbufptr;	//found the last field
   else
   	return -1;				//no such field
/*
	//handles the first field
	if ((fieldno==0)&&(*sptr!=textstartqualifier)){
		while(*sptr){
      	if (*sptr==fielddelimiter)
				break;
			fieldbuf[fieldbufptr] = *sptr;
         fieldbufptr = (fieldbufptr+1) % fieldlen;
         sptr++;
      	}
		fieldbuf[fieldbufptr] = 0x0;
   	return fieldbufptr;
   	}

	//handles all others
	for(ii=0;ii<strlength;ii++){
   	if (*sptr==0)
      	break;

      if (fieldfound&&(count==fieldno)){
			fieldbuf[fieldbufptr] = *sptr;
         fieldbufptr = (fieldbufptr+1) % fieldlen;
         }

		if (count>fieldno){
  	     	if (fieldbufptr>0)
				fieldbufptr--;
      	return fieldbufptr;
         }

		if ((!fieldfound)&&(*sptr==fielddelimiter)&&(*(sptr+1)==fielddelimiter)){
			count++;
  	      done = 0;
     	   sptr++;
        	continue;
         }

		if ((!fieldfound)&&(*sptr==fielddelimiter)&&(*(sptr+1)==textstartqualifier)){
			textEnd = textstartqualifier;
			count++;
         done = 0;
         sptr++;
         continue;
         }
		// parse ,\n
		if ((!fieldfound)&&(*sptr==fielddelimiter)&&(*(sptr+1)=='\n')){
         fieldbuf[0] = 0x0;
         return 0;
      	}
		// parse ,\r
		if ((!fieldfound)&&(*sptr==fielddelimiter)&&(*(sptr+1)=='\r')){
         fieldbuf[0] = 0x0;
         return 0;
      	}
		// parse ,\0
		if ((!fieldfound)&&(*sptr==fielddelimiter)&&(*(sptr+1)==0)){
         fieldbuf[0] = 0x0;
         return 0;
      	}
		// parse ,1234
		if ((!fieldfound)&&(*sptr==fielddelimiter)&&(*(sptr+1)!=textstartqualifier)){
			count++;
      	if (count==fieldno){
		      fieldfound = 1;
				textEnd = fielddelimiter;
            }
         done = 0;
         sptr++;
         continue;
         }

		//-----------------------------------------
		if (sametextqualifier){
			if (*sptr==textEnd){
            fieldfound = !fieldfound;
            if (!fieldfound)
	            done = 1;
            }
			if (done){
  		      if (count==fieldno){
      	     	if (fieldbufptr>0)
						fieldbufptr--;
	   	   	return fieldbufptr;
   	  			}
      	 	}

     	}
      else
      	{
			if (*sptr==textEnd)
				fieldfound=1;
			if (*sptr==textendqualifier){
				fieldfound=0;
	         if (count==fieldno){
              	if (fieldbufptr>0)
						fieldbufptr--;
   	      	return fieldbufptr;
         		}
         	}
         }
		sptr++;
   	}
   return -1;
*/
}

//---------------------------------------------------------------------------------
//Parse a delimited csv string
//0x22 is "
//Handles    "abcde","defgh","rtf",,,,abdget,ueybh,1,
//PARAMETER: buf -- the comma delimited
//           len -- the len of the comma delimited buf to process
//           fieldno -- the field starting from 0 (i.e. 0, 1,2, ...)
//RETURNS: if >=0 length of the extracted field
//         if <0 no field found
//         in field -- the string of length max fieldlen
//
//---------------------------------------------------------------------------------
int getCommaDelimitedField(char *buf, int len, int fieldno, char *field, int fieldlen)
{
	char fieldbuf[1024];
    static int rlen;
	rlen = parseField(buf, len, fieldno, ',', 0x22, 0x22, fieldbuf, sizeof(fieldbuf)-1);        //0x22 is "
	if (rlen>=0){
		fieldbuf[rlen] = 0x0;
		STRNCPY(field, fieldbuf, fieldlen);
		field[fieldlen] = 0x0;
		return rlen;
		}
	field[0] = 0x0;
	return -1;
}