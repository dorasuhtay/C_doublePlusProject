#include "StdAfx.h"
#include "chString.h"


const char chString::HexChars[] = {"0123456789ABCDEF"};

// Char Maximum length

const int chString::BCharMaxlength =  3;  		/**< BChar Max length in string format 		*/
const int chString::BShortMaxlength =  6;  		/**< BShort Max length in string format 	*/
const int chString::BIntMaxlength  = 11; 		/**< BInt Max length in string format 		*/
const int chString::BLongMaxlength =  11; 		/**< BLong Max length in string format 		*/
const int chString::BLong64Maxlength =  21; 	    /**< BLong64 Max length in string format 	*/

const int chString::BUCharMaxlength =  3; 		/**< BUChar Max length in string format 	*/
const int chString::BUShortMaxlength =  5; 		/**< BUShort Max length in string format 	*/
const int chString::BUIntMaxlength  = 10; 		/**< BUInt Max length in string format 		*/
const int chString::BULongMaxlength  = 10; 		/**< BULong Max length in string format 	*/
const int chString::BULong64Maxlength  = 20; 	/**< BULong64 Max length in string format 	*/

const int chString::BFloatMaxlength  = 15; 		/**< BFloat Max length in string format 	*/
const int chString::BDoubleMaxlength  = 15; 	    /**< BDouble Max length in string format 	*/
const int chString::BLDoubleMaxlength =  15; 	/**< BLDouble Max length in string format 	*/

// Maximum value rounded 10 to convert faster to string

const int chString::BChar10Max  = 2; 			/**< BChar Max length in string format 		*/
const int chString::BShort10Max  = 4;			/**< BShort Max length in string format 	*/
const int chString::BIntMax10 =  10;				/**< BInt Max length in string format 		*/
const int chString::BLongMax10 =  10;			/**< BLong Max length in string format 		*/
const int chString::BLong6410Max  = 18 ;			/**< BLong64 Max length in string format 	*/

const int chString::BUChar10Max  = 2;			/**< BUChar Max length in string format 	*/
const int chString::BUShort10Max =  4;			/**< BUShort Max length in string format 	*/
const int chString::BUInt10Max =  10;		 	/**< BUInt Max length in string format 		*/
const int chString::BULong10Max  = 10;		 	/**< BULong Max length in string format 	*/
const int chString::BULong6410Max =  20; 	    /**< BULong64 Max length in string format 	*/

const int chString::BFloat10Max  = 20; 		    /**< BFloat Max length in string format 	*/
const int chString::BDouble10Max =  20; 	        /**< BDouble Max length in string format 	*/
const int chString::BLDouble10Max =  20;     	/**< BLDouble Max length in string format 	*/

#define     WCTSTR_TOHEX(a, b)              \
    {                                       \
    int len = sizeof(a);                    \
	if (b) len+=2;                          \
	allocateIfNeeded(length+len+1);         \
    W_CHAR_T *str = this->wstring + length; \
    length += len;                          \
    if (b)                                  \
    {                                       \
        *str = '0';                         \
        ++str;                              \
        *str = 'x';                         \
        ++str;                              \
    }                                       \
    len = sizeof(a);                        \
	while(len--)                            \
	{                                       \
		*(str + len) = HexChars[0xf & a];   \
		a >>= 4;                            \
	}                                       \
    *(this->wstring + length) = '\0';       \
    }
/*
//---------------------------------------
// Check buffer size
//----------------------------------
bool chString::allocateIfNeeded(const int inRequeriedSpace)
{
        if( bufferlength <= inRequeriedSpace + length ){		// If the buffer is too small
                bufferlength = 2 * (length + inRequeriedSpace);	// calcul requierd buffer
                char * str = new char[bufferlength];				// allocate buffer

                if(string){
                        chString::Copy(string , str);					// copy original string
                        delete(string);								// remove buffer
		}
		else{
			str[0] = '\0';
		}
                string = str;
		return true;
	}
	return false;
}
*/
//---------------------------------------
// Check buffer size
//----------------------------------
bool chString::allocateIfNeeded(const int inRequeriedSpace)
{
    if( bufferlength <= inRequeriedSpace + length )
	{		// If the buffer is too small
        bufferlength = 2 * (length + inRequeriedSpace);	// calcul requierd buffer
        W_CHAR_T * str = new W_CHAR_T[bufferlength];				// allocate buffer

		if(wstring)
		{
            chString::Copy(wstring , str);					// copy original string
            delete(wstring);								// remove buffer
		}
		else
		{
			str[0] = '\0';
		}
		wstring = str;
		return true;
	}
	return false;
}


/**
* @brief chString implementation
* @file chString.cpp
*/


chString& chString::append(const W_CHAR_T * const inString){
        if(!inString) return *this;						// Test if null

        const int sl = chString::Strlen(inString);		// Check str length

	allocateIfNeeded(sl);

        chString::Copy(inString,&wstring[length]);	// copy append string
        length += sl;								// calcul new size

	return *this;
}
/*
    chString& chString::appendHex(const int& in_value)
    {
         if(in_value == 0 ) append(nHEX_ZERO);
        else
        ithex(in_value);
        //append(_T("0x02"));
        return *this;
    }
*/


chString& chString::append(const chString& inString){
        allocateIfNeeded(inString.length);
        chString::Copy(inString.wstring,&wstring[length]);	// copy append string
        length += inString.length;						// calcul new size

	return *this;
}


chString::~chString()
{
    if(wstring) delete wstring;
	if (this->bstring) delete this->bstring;
}


chString& chString::append(const W_CHAR_T in_char){
	allocateIfNeeded(1);								// check size

        wstring[length + 1] = this->wstring[length];			//
        wstring[length] = in_char;							// copy append char
        ++length;											// calcul new size

	return *this;
}

chString chString::operator+(const chString& inString) const
{
        chString concat(length + inString.length + 1);	// create a string with big buffer

        chString::Copy(wstring,concat.wstring);
        chString::Copy(inString.wstring,&concat.wstring[length]);
        concat.length = length + inString.length;

	return concat;
}


chString chString::operator+(const W_CHAR_T* const inString) const
{
        const int stringlength = chString::Strlen(inString);
        chString concat(length + stringlength + 1);			// create a string with big buffer

        chString::Copy(wstring,concat.wstring);				// add currrent string
        chString::Copy(inString,&concat.wstring[length]);	// add 2nd string
        concat.length = length + stringlength;

	return concat;
}


W_CHAR_T chString::operator[](const int in_index) const
{
	if(0 <= in_index && in_index < length) return wstring[in_index];
		return char();
}


#ifdef USE_UNICODE_____chString
chString& chString::operator=(const char * const inString)
{
	initObj();
	int len = strlen(inString);
	if(len >= bufferlength )
	{			
		// check if buffer is enought big
        if(wstring) delete(wstring);					// if not delete
        bufferlength = len + 1;			// allocate buffer
        wstring = new W_CHAR_T[bufferlength];
	}
    chString::Copy(inString,wstring);			// copy string
    length = len;						// save length
	return *this;
}
#endif


chString& chString::operator=(const chString & inString)
{
	initObj();
	if(inString.length >= bufferlength )
	{			
		// check if buffer is enought big
        if(wstring) delete(wstring);					// if not delete
        bufferlength = inString.length + 1;			// allocate buffer
        wstring = new W_CHAR_T[bufferlength];
	}
    chString::Copy(inString.wstring,wstring);			// copy string
    length = inString.length;						// save length
	return *this;
}


chString& chString::operator=(const W_CHAR_T* const inString)
{
	initObj();
    if(!inString)
	{
        if(wstring) this->wstring[0] = '\0';
			length = 0;
		return *this;
	}

    const int sl = chString::Strlen(inString);
    if(sl >= bufferlength )
	{
        if(wstring) delete(wstring);
        bufferlength = sl + 1;
        wstring = new W_CHAR_T[bufferlength];
	}

    chString::Copy(inString,wstring);
    length = sl;

	return *this;
}



bool chString::operator==(const chString& inString) const
{
        if( length != inString.length ||
                (length && this->wstring[0] != inString.wstring[0]) ) return false;

        for( int indexString = 0 ; indexString < length ; ++indexString ){
                if(wstring[indexString] != inString.wstring[indexString]) return false;
	}

	return true;
}

bool chString::operator==(const W_CHAR_T* inString) const
{
        if( length != chString::Strlen(inString) ||
                (length && this->wstring[0] != inString[0]) ) return false;

        for( int indexString = 0 ; indexString < length ; ++indexString ){
                if(wstring[indexString] != inString[indexString]) return false;
	}

	return true;
}


int chString::Strlen(const W_CHAR_T* const inString){
	int indexString = 0;
        if(inString){
                //while(inString[indexString] != '\n' && inString[indexString] != '\0') ++indexString;
                while(inString[indexString] != '\0') ++indexString;
	}
	return indexString;
}

#ifdef USE_UNICODE_____chString
int chString::Copy(const char* const in_src, W_CHAR_T* const in_dest){
	if(!in_dest) return 0;
	if(!in_src) {
		in_dest[0] = '\0';
		return 0;
	}

	int indexString = 0;

	//while(in_src[indexString] != '\n' && in_src[indexString] != '\0'){
	while(in_src[indexString] != '\0'){
		in_dest[indexString] = in_src[indexString];
		++indexString;
	}
	//in_dest[indexString] = in_src[indexString];
	in_dest[indexString] = '\0';

	return indexString;
}
#endif

int chString::Copy(const W_CHAR_T* const in_src, W_CHAR_T* const in_dest){
	if(!in_dest) return 0;
	if(!in_src) {
		in_dest[0] = '\0';
		return 0;
	}

	int indexString = 0;

	//while(in_src[indexString] != '\n' && in_src[indexString] != '\0'){
	while(in_src[indexString] != '\0'){
		in_dest[indexString] = in_src[indexString];
		++indexString;
	}
	//in_dest[indexString] = in_src[indexString];
	in_dest[indexString] = '\0';

	return indexString;
}

// ------------------------------------------------------------------- //
// ------------------------  ItoA functions      --------------------- //
// ------------------------------------------------------------------- //
/*
void appenddebugfile(char *msg)
{
   FILE *fp;
   fopen("debug_file.txt", "a+t");
   if (fp)
   {
       fwrite(msg, strlen(msg), 1, fp);
       fclose(fp);
   }
   
}
*/
/*
void chString::ithex(int val, bool hexprefix)
{
    int len = sizeof(val);
	if (hexprefix) len+=2;
	allocateIfNeeded(length+len+1);
    W_CHAR_T *str = this->wstring + length;
    length += len;
    if (hexprefix)
    {
        *str = '0';
        ++str;
        *str = 'x';
        ++str;
    }
    len = sizeof(val);
	while(len--)
	{
		*(str + len) = HexChars[0xf & val];
		val >>= 4;
	}
    *(this->wstring + length) = '\0';
 }
 */
/*
void chString::ul64thex(ULONG64 val, bool hexprefix)
{
    int len = sizeof(val);
	if (hexprefix) len+=2;
	allocateIfNeeded(length+len+1);
    W_CHAR_T *str = this->wstring + length;
    length += len;
    if (hexprefix)
    {
        *str = '0';
        ++str;
        *str = 'x';
        ++str;
    }
    len = sizeof(val);
	while(len--)
	{
		*(str + len) = HexChars[0xf & val];
		val >>= 4;
	}
    *(this->wstring + length) = '\0';
}
*/

void chString::ucthex(unsigned char val, bool hexprefix)   {WCTSTR_TOHEX(val, hexprefix);}
void chString::ithex(int val, bool hexprefix)              {WCTSTR_TOHEX(val, hexprefix);}
void chString::uithex(unsigned int val, bool hexprefix)    {WCTSTR_TOHEX(val, hexprefix);}
void chString::lthex(long val, bool hexprefix)             {WCTSTR_TOHEX(val, hexprefix);}
void chString::ulthex(unsigned long val, bool hexprefix)   {WCTSTR_TOHEX(val, hexprefix);}
void chString::l32thex(LONG32 val, bool hexprefix)         {WCTSTR_TOHEX(val, hexprefix);}
void chString::ul32thex(ULONG32 val, bool hexprefix)       {WCTSTR_TOHEX(val, hexprefix);}
void chString::l64thex(LONG64 val, bool hexprefix)         {WCTSTR_TOHEX(val, hexprefix);}
void chString::ul64thex(ULONG64 val, bool hexprefix)       {WCTSTR_TOHEX(val, hexprefix);}


/*
void chString::uithex(unsigned int val, bool hexprefix)
{
	int len = sizeof(val);
	if (hexprefix) len+=2;
	allocateIfNeeded(length+len+1);
    W_CHAR_T *str = this->wstring + length;
    length += len;
    if (hexprefix)
    {
        *str = '0';
        ++str;
        *str = 'x';
        ++str;
    }
    len = sizeof(val);
	while(len--)
	{
		*(str + len) = HexChars[0xf & val];
		val >>= 4;
	}
    *(this->wstring + length) = '\0';
}
*/
void chString::bytetbinary(unsigned char val)
{
    int len = sizeof(val)*8;
	allocateIfNeeded(length+len+1);
    W_CHAR_T *str = this->wstring + length;
    length += len;
	while(len--)
	{
	    if (0x01 & val)
            *(str + len) = '1';
        else
            *(str + len) = '0';
		val >>= 1;
	}
    *(this->wstring + length) = '\0';
}

/*
void chString::ulthex(unsigned long val, bool hexprefix)
{
    int len = sizeof(val);
	if (hexprefix) len+=2;
	allocateIfNeeded(length+len+1);
    W_CHAR_T *str = this->wstring + length;
    length += len;
    if (hexprefix)
    {
        *str = '0';
        ++str;
        *str = 'x';
        ++str;
    }
    len = sizeof(val);
	while(len--)
	{
		*(str + len) = HexChars[0xf & val];
		val >>= 4;
	}
    *(this->wstring + length) = '\0';
}
*/

void chString::stoa (short num){
	allocateIfNeeded(BShortMaxlength);

    W_CHAR_T *str = this->wstring + length;

	// check if is a negative number
    if (num < 0) {
		// print '-'
        *str = '-';
		++str;
                ++length;
		// convert int to positif
        num = -num;
    }

	short diviser = 1;
	while( num >= diviser*10 ) diviser *= 10;

	short tmp;
	while( num ){
		tmp = num/diviser;

		num -= (tmp*diviser);
		*str = char('0' + tmp);
		++str;

                ++length;
		diviser /= 10;
	}
	*str = '\0';
}


void chString::ustoa (unsigned short num){
	allocateIfNeeded(BUShortMaxlength);

    W_CHAR_T *str = this->wstring + length;

	short diviser = 1;
	while( num >= diviser*10 ) diviser *= 10;

	short tmp;
	while( num ){
		tmp = num/diviser;

		num -= (tmp*diviser);
		*str = char('0' + tmp);
		++str;

                ++length;
		diviser /= 10;
	}
	*str = '\0';
}


/**
* @brief Convert int to char
*/
void chString::itoa (int num){
	allocateIfNeeded(BIntMaxlength);

        W_CHAR_T *str = this->wstring + length;

	// check if is a negative number
    if (num < 0) {
		// print '-'
        *str = '-';
		++str;
                ++length;
		// convert int to positif
        num = -num;
    }

	int diviser = 1;
	while( num >= diviser*10 ) diviser *= 10;

	int tmp;
	while( num ){
		tmp = num/diviser;

		num -= (tmp*diviser);
		*str = char('0' + tmp);
		++str;

                ++length;
		diviser /= 10;
	}
	*str = '\0';

}

/**
* @brief Convert int to char
*/
void chString::uitoa (unsigned int num){
	allocateIfNeeded(BUIntMaxlength);

    W_CHAR_T *str = this->wstring + length;

	unsigned int diviser = 1;
	unsigned int tmp;

	while( num >= diviser*10u ) diviser *= 10u;

	while( num ){
		tmp = num/diviser;

		num -= (tmp*diviser);
		*str = char('0' + tmp);
		++str;

                ++length;
		diviser /= 10u;
	}
	*str = '\0';
}

/**
* @brief Convert int to char
*/
void chString::litoa (long num){
	allocateIfNeeded(BLongMaxlength);

    W_CHAR_T *str = this->wstring + length;
	// check if is a negative number
	if (num < 0) {
		// print '-'
		*str = '-';
		++str;
                ++length;
		// convert int to positif
		num = -num;
	}

	long diviser = 1;
	long tmp;

	while( num >= diviser*10 ) diviser *= 10;

	while( num ){
		tmp = num/diviser;

		num -= (tmp*diviser);
		*str = char('0' + tmp);
		++str;

                ++length;
		diviser /= 10;
	}
	*str = '\0';
}

/**
* @brief Convert int to char
*/
void chString::ulitoa (unsigned long num){
	allocateIfNeeded(BULongMaxlength);

    W_CHAR_T *str = this->wstring + length;

	unsigned long diviser = 1;
	unsigned long tmp;

	while( num >= diviser*10 ) diviser *= 10;

	while( num ){
		tmp = num/diviser;

		num -= (tmp*diviser);
		*str = char('0' + tmp);
		++str;

                ++length;
		diviser /= 10;
	}
	*str = '\0';
}


/**
* @brief Convert float to char
*/
void chString::ftoa (float num){
	allocateIfNeeded(BFloatMaxlength);

    float digit_value;
	short digit;
        W_CHAR_T *str = this->wstring + length;

	// check if is a negative number
    if (num < 0) {
		// print '-'
        *str = '-';
		++str;
                ++length;
		// convert int to positif
        num = -num;
    }

	// start from 1
    digit_value = 1;
	// progress until this is under the number we want to convert
    while (digit_value*10 <= num){
		digit_value *= 10;
	}


	// then while this non zeros value
    while (digit_value >= 1) {
		// copy division
        digit = static_cast<short>( num / digit_value );
		// dec number
        num -= digit * digit_value;
		// print value
        *str = char('0' + digit);
		++str;
                ++length;
		// dec by base
        digit_value /= 10;
    }

	if( num >= 0.000001 ){
		digit_value = 100000;
		num *= digit_value * 10;
		*str = '.';
		++str;
                ++length;
		// then while this non zeros value
	    while (digit_value > 1) {
			// copy division
	        digit = static_cast<short>( num / digit_value );
			// dec number
	        num -= digit * digit_value;
			// print value
	        *str = char('0' + digit);
			++str;
                        ++length;
			// dec by base
	        digit_value /= 10;
	    }
	}

	*str = '\0';
}


/**
* @brief Convert double to char
*/
void chString::dtoa (double num){
	allocateIfNeeded(BDoubleMaxlength);

    double digit_value;
	short digit;
        W_CHAR_T *str = this->wstring + length;

	// check if is a negative number
    if (num < 0) {
		// print '-'
        *str = '-';
		++str;
                ++length;
		// convert int to positif
        num = -num;
    }

	// start from 1
    digit_value = 1;
	// progress until this is under the number we want to convert
    while (digit_value*10 <= num){
		digit_value *= 10;
	}


	// then while this non zeros value
    while (digit_value >= 1) {
		// copy division
        digit = static_cast<short>( num / digit_value );
		// dec number
        num -= digit * digit_value;
		// print value
        *str = char('0' + digit);
		++str;
                ++length;
		// dec by base
        digit_value /= 10;
    }

	if( num >= 0.000001 ){
		digit_value = 100000;
		num *= digit_value * 10;
		*str = '.';
		++str;
                ++length;
		// then while this non zeros value
	    while (digit_value > 1) {
			// copy division
	        digit = static_cast<short>( num / digit_value );
			// dec number
	        num -= digit * digit_value;
			// print value
	        *str = char('0' + digit);
			++str;
                        ++length;
			// dec by base
	        digit_value /= 10;
	    }
	}

	*str = '\0';
}

// ------------------------------------------------------------------- //
// ------------------------  out of class functions ------------------ //
// ------------------------------------------------------------------- //


/*bool operator==(const chString& in_string1, const chString& in_string2){
	if( in_string1.length() != in_string2.length() ||
		(in_string1.length() && in_string1[0] != in_string2[0]) ) return false;

	for( int indexString = 0 ; indexString < in_string1.length() ; ++indexString ){
		if(in_string1[indexString] != in_string2[indexString]) return false;
	}

	return true;
}*/


/*chString operator+(const chString& in_string1, const chString& in_string2){
	chString concat(in_string1.length() + in_string2.length());

	concat.append(in_string1);
	concat.append(in_string2);

	return concat;
}*/







#ifdef USING_CSTR

sdgdsfg

//Strings.h
#if !defined(STRINGS_H)
#define STRINGS_H
#define EXPANSION_FACTOR      2
#define MINIMUM_ALLOCATION   16

class String
{
 public:
 ~String();                               //String Destructor
 String();                                //Uninitialized Constructor
 String(const TCHAR);                     //Constructor Initializes String With TCHAR
 String(const TCHAR*);                    //Constructor Initializes String With TCHAR*
 String(const String&);                   //Constructor Initializes String With Another String (Copy Constructor)
 String(const int);                       //Constructor Initializes Buffer To Specific Size
 String& operator=(const TCHAR);          //Assigns TCHAR To String
 String& operator=(const TCHAR*);         //Assigns TCHAR* To String
 String& operator=(const String&);        //Assigns one String to another (this one)
 bool operator==(const String);           //For comparing Strings
 String& operator+(const TCHAR);          //For adding TCHAR to String
 String& operator+(const TCHAR*);         //For adding null terminated TCHAR array to String
 String& operator+(const String&);        //For adding one String to Another
 String Left(unsigned int);               //Returns String of iNum Left Most chars of this
 String Right(unsigned int);              //Returns String of iNum Right Most chars of this
 String Mid(unsigned int, unsigned int);  //Returns String consisting of number of chars from some offset
 String Remove(const TCHAR*, bool);       //Returns A String With A Specified TCHAR* Removed
 int InStr(const TCHAR);                  //Returns one based offset of a specific TCHAR in a String
 int InStr(const TCHAR*, bool);           //Returns one based offset of a particular TCHAR pStr in a String
 int InStr(const String&, bool);          //Returns one based offset of where a particular String is in another String
 String LTrim();                          //Returns String with leading spaces/tabs removed
 String RTrim();                          //Returns String with spaces/tabs removed from end
 String Trim();                           //Returns String with both leading and trailing whitespace removed
 unsigned int ParseCount(const TCHAR);    //Returns count of Strings delimited by a TCHAR passed as a parameter
 void Parse(String*, TCHAR);              //Returns array of Strings in first parameter as delimited by 2nd TCHAR delimiter
 String CStr(const int);                  //Converts String to integer
 String CStr(const unsigned int);         //Converts String to unsigned int
 String CStr(const short int);            //Converts String to 16 bit int
 String CStr(const double);               //Converts String to double
 int iVal();                              //Returns int value of a String
 int LenStr(void);                        //Returns the length of the String
 TCHAR* lpStr();                          //Returns the address of the 1st byte of the String buffer this->pStrBuffer
 void Print(bool);

 protected:
 TCHAR* pStrBuffer;
 int    iAllowableCharacterCount;
};

#endif
//Strings.cpp
#include  <windows.h>
#include  <tchar.h>
#include  <stdlib.h>
#include  <stdio.h>
#include  <string.h>
#include  "Strings.h"


String::~String()                                      //String Destructor - frees a string's memory
{                                                      //allocation
 delete [] pStrBuffer;
}


String::String()                                       //Uninitialized Constructor - For variable
{                                                      //declarations such as; String strName;
 pStrBuffer=new TCHAR[MINIMUM_ALLOCATION];
 pStrBuffer[0]=_T('\0');
 this->iAllowableCharacterCount=MINIMUM_ALLOCATION-1;
}


String::String(const TCHAR ch)  //Constructor: Initializes with TCHAR
{
 pStrBuffer=new TCHAR[16];
 pStrBuffer[0]=ch;
 pStrBuffer[1]=_T('\0');
 iAllowableCharacterCount=MINIMUM_ALLOCATION-1;
}


String::String(const TCHAR* pStr)  //Constructor: Initializes with TCHAR*
{
 int iLen,iNewSize;

 iLen=_tcslen(pStr);
 iNewSize=(iLen/16+1)*16;
 pStrBuffer=new TCHAR[iNewSize];
 this->iAllowableCharacterCount=iNewSize-1;
 _tcscpy(pStrBuffer,pStr);
}


String::String(const String& s)  //Constructor Initializes With Another String, i.e., Copy Constructor
{
 int iLen,iNewSize;

 iLen=_tcslen(s.pStrBuffer);
 iNewSize=(iLen/16+1)*16;
 this->pStrBuffer=new TCHAR[iNewSize];
 this->iAllowableCharacterCount=iNewSize-1;
 _tcscpy(this->pStrBuffer,s.pStrBuffer);
}


String::String(const int iSize)  //Constructor Creates String With Custom Sized
{                                //Buffer (rounded up to paragraph boundary)
 int iNewSize;

 iNewSize=(iSize/16+1)*16;
 pStrBuffer=new TCHAR[iNewSize];
 this->iAllowableCharacterCount=iNewSize-1;
}


String& String::operator=(const TCHAR ch)  //Overloaded operator = for assigning a TCHARacter to a String
{
 this->pStrBuffer[0]=ch;
 this->pStrBuffer[1]=_T('\0');

 return *this;
}


String& String::operator=(const TCHAR* pStr)   //Constructor For If Pointer To Asciiz String Parameter
{
 int iLen,iNewSize;

 iLen=_tcslen(pStr);
 if(iLen<this->iAllowableCharacterCount)
    _tcscpy(pStrBuffer,pStr);
 else
 {
    delete [] pStrBuffer;
    iNewSize=(iLen/16+1)*16;
    pStrBuffer=new TCHAR[iNewSize];
    this->iAllowableCharacterCount=iNewSize-1;
    _tcscpy(pStrBuffer,pStr);
 }

 return *this;
}


String& String::operator=(const String& strRight)    //Overloaded operator = for assigning
{                                                   //another String to a String
 int iRightLen,iThisLen,iNewSize;
 TCHAR* pNew;

 if(this==&strRight)
    return *this;
 iRightLen=_tcslen(strRight.pStrBuffer);
 iThisLen=_tcslen(this->pStrBuffer);
 if(iRightLen < this->iAllowableCharacterCount)
    _tcscpy(pStrBuffer,strRight.pStrBuffer);
 else
 {
    if(iThisLen) //There Is Something Stored In This!
    {
       iNewSize=iThisLen+iRightLen+1;
       iNewSize=(iNewSize/16+1)*16;
       pNew=new TCHAR[iNewSize];
       this->iAllowableCharacterCount=iNewSize-1;
       _tcscpy(pNew,pStrBuffer);
       _tcscat(pNew,strRight.pStrBuffer);
       delete [] this->pStrBuffer;
       pStrBuffer=pNew;
    }
    else
    {
       iNewSize=(iRightLen/16+1)*16;
       delete [] this->pStrBuffer;
       this->pStrBuffer=new TCHAR[iNewSize];
       this->iAllowableCharacterCount=iNewSize-1;
       _tcscpy(pStrBuffer,strRight.pStrBuffer);
    }
 }

 return *this;
}


bool String::operator==(const String strCompare)
{
 if(_tcscmp(this->pStrBuffer,strCompare.pStrBuffer)==0)  //strcmp
    return true;
 else
    return false;
}


String& String::operator+(const TCHAR ch)      //Overloaded operator + (Puts TCHAR in String)
{
 int iLen,iNewSize;
 TCHAR* pNew;

 iLen=_tcslen(this->pStrBuffer);
 if(iLen<this->iAllowableCharacterCount)
 {
    this->pStrBuffer[iLen]=ch;
    this->pStrBuffer[iLen+1]=_T('\0');
 }
 else
 {
    iNewSize=((this->iAllowableCharacterCount*EXPANSION_FACTOR)/16+1)*16;
    pNew=new TCHAR[iNewSize];
    this->iAllowableCharacterCount=iNewSize-1;
    _tcscpy(pNew,this->pStrBuffer);
    delete [] this->pStrBuffer;
    this->pStrBuffer=pNew;
    this->pStrBuffer[iLen]=ch;
    this->pStrBuffer[iLen+1]=_T('\0');
 }

 return *this;
}


String& String::operator+(const TCHAR* pChar) //Overloaded operator + (Adds TCHAR literals
{                                             //or pointers to Asciiz Strings)
 int iLen,iNewSize;
 TCHAR* pNew;

 iLen=_tcslen(this->pStrBuffer)+_tcslen(pChar);
 if(iLen<this->iAllowableCharacterCount)
    _tcscat(this->pStrBuffer,pChar);
 else
 {
    iNewSize=(iLen*EXPANSION_FACTOR/16+1)*16;
    pNew=new TCHAR[iNewSize];
    this->iAllowableCharacterCount = iNewSize-1;
    _tcscpy(pNew,this->pStrBuffer);
    delete [] pStrBuffer;
    _tcscat(pNew,pChar);
    this->pStrBuffer=pNew;
 }

 return *this;
}


String& String::operator+(const String& strRight)  //Overloaded operator + Adds Another String
{                                                  //to the left operand
 int iLen,iNewSize;
 TCHAR* pNew;

 iLen=_tcslen(this->pStrBuffer) + _tcslen(strRight.pStrBuffer);
 if(iLen < this->iAllowableCharacterCount)
 {
    if(this->pStrBuffer)
       _tcscat(this->pStrBuffer,strRight.pStrBuffer);
    else
       _tcscpy(this->pStrBuffer,strRight.pStrBuffer);
 }
 else
 {
    if(this->pStrBuffer)
    {
       iNewSize=(iLen*EXPANSION_FACTOR/16+1)*16;
       pNew=new TCHAR[iNewSize];
       this->iAllowableCharacterCount=iNewSize-1;
       _tcscpy(pNew,this->pStrBuffer);
       delete [] pStrBuffer;
       _tcscat(pNew,strRight.pStrBuffer);
       this->pStrBuffer=pNew;
    }
    else
    {
       iNewSize=(iLen*EXPANSION_FACTOR/16+1)*16;
       pNew=new TCHAR[iNewSize];
       this->iAllowableCharacterCount=iNewSize-1;
       _tcscpy(pNew,strRight.pStrBuffer);
       this->pStrBuffer=pNew;
    }
 }

 return *this;
}


String String::Left(unsigned int iNum)
{
 unsigned int iLen,i,iNewSize;
 String sr;

 iLen=_tcslen(this->pStrBuffer);
 if(iNum<iLen)
 {
    iNewSize=(iNum*EXPANSION_FACTOR/16+1)*16;
    sr.iAllowableCharacterCount=iNewSize-1;
    sr.pStrBuffer=new TCHAR[iNewSize];
    for(i=0;i<iNum;i++)
        sr.pStrBuffer[i]=this->pStrBuffer[i];
    sr.pStrBuffer[iNum]=_T('\0');
    return sr;
 }
 else
 {
    sr=*this;
    return sr;
 }
}


String String::Remove(const TCHAR* pToRemove, bool blnCaseSensitive)
{
 int i,j,iParamLen,iReturn=0;
 bool blnFound=false;

 if(*pToRemove==0)
    return true;
 iParamLen=_tcslen(pToRemove);
 i=0, j=0;
 do
 {
  if(pStrBuffer[i]==0)
     break;
  if(blnCaseSensitive)
     iReturn=_tcsncmp(pStrBuffer+i,pToRemove,iParamLen);  //strncmp
  else
     iReturn=_tcsnicmp(pStrBuffer+i,pToRemove,iParamLen); //_strnicmp
  if(iReturn!=0)
  {
     if(blnFound)
        pStrBuffer[j]=pStrBuffer[i];
     j++, i++;
  }
  else   //made a match
  {
     blnFound=true;
     i=i+iParamLen;
     pStrBuffer[j]=pStrBuffer[i];
     j++, i++;
  }
 }while(1);
 if(blnFound)
    pStrBuffer[i-iParamLen]=_T('\0');
 String sr=pStrBuffer;

 return sr;
}


String String::Right(unsigned int iNum)  //Returns Right$(strMain,iNum)
{
 unsigned int iLen,i,j,iNewSize;
 String sr;

 iLen=_tcslen(this->pStrBuffer);
 if(iNum<iLen)
 {
    iNewSize=(iNum*EXPANSION_FACTOR/16+1)*16;
    sr.iAllowableCharacterCount=iNewSize-1;
    sr.pStrBuffer=new TCHAR[iNewSize];
    j=0;
    for(i=iLen-iNum;i<=iLen;i++)
    {
        _tprintf(_T("%u\t%u\t%c\n"),i,j,pStrBuffer[i]);
        sr.pStrBuffer[j]=this->pStrBuffer[i];
        j++;
    }
    sr.pStrBuffer[iNum]=_T('\0');
    return sr;
 }
 else
 {
    sr=*this;
    return sr;
 }
}


String String::Mid(unsigned int iStart, unsigned int iCount)
{
 unsigned int iLen,i,j,iNewSize;
 String sr;

 iLen=_tcslen(this->pStrBuffer);
 if(iStart && iStart<=iLen)
 {
    if(iCount && iStart+iCount-1<=iLen)
    {
       iNewSize=(iCount*EXPANSION_FACTOR/16+1)*16;
       sr. iAllowableCharacterCount=iNewSize-1;
       sr.pStrBuffer=new TCHAR[iNewSize];
       j=0;
       sr.pStrBuffer=new TCHAR[iNewSize];
       for(i=iStart-1;i<iStart+iCount-1;i++)
       {
           sr.pStrBuffer[j]=this->pStrBuffer[i];
           j++;
       }
       sr.pStrBuffer[iCount]=_T('\0');
       return sr;
    }
    else
    {
       sr=*this;
       return sr;
    }
 }
 else
 {
    sr=*this;
    return sr;
 }
}


int String::InStr(const TCHAR ch)
{
 int iLen,i;

 iLen=_tcslen(this->pStrBuffer);
 for(i=0;i<iLen;i++)
 {
     if(this->pStrBuffer[i]==ch)
        return (i+1);
 }

 return 0;
}


int String::InStr(const TCHAR* pStr, bool blnCaseSensitive)
{
 int i,iParamLen,iRange;

 if(*pStr==0)
    return 0;
 iParamLen=_tcslen(pStr);
 iRange=_tcslen(pStrBuffer)-iParamLen;
 if(iRange>=0)
 {
    for(i=0;i<=iRange;i++)
    {
        if(blnCaseSensitive)
        {
           if(_tcsncmp(pStrBuffer+i,pStr,iParamLen)==0)   //strncmp
              return i+1;
        }
        else
        {
           if(_tcsnicmp(pStrBuffer+i,pStr,iParamLen)==0)  //_strnicmp
              return i+1;
        }
    }
 }

 return 0;
}


int String::InStr(const String& s, bool blnCaseSensitive)
{
 int i,iParamLen,iRange,iLen;

 iLen=_tcslen(s.pStrBuffer);
 if(iLen==0)
    return 0;
 iParamLen=iLen;
 iRange=_tcslen(pStrBuffer)-iParamLen;
 if(iRange>=0)
 {
    for(i=0;i<=iRange;i++)
    {
        if(blnCaseSensitive)
        {
           if(_tcsncmp(pStrBuffer+i,s.pStrBuffer,iParamLen)==0)  //strncmp
              return i+1;
        }
        else
        {
           if(_tcsnicmp(pStrBuffer+i,s.pStrBuffer,iParamLen)==0) //_strnicmp
              return i+1;
        }
    }
 }

 return 0;
}


String String::LTrim()
{
 unsigned int i,iCt=0,iLenStr;

 iLenStr=this->LenStr();
 for(i=0;i<iLenStr;i++)
 {
     if(pStrBuffer[i]==32||pStrBuffer[i]==9)
        iCt++;
     else
        break;
 }
 if(iCt)
 {
    for(i=iCt;i<=iLenStr;i++)
        pStrBuffer[i-iCt]=pStrBuffer[i];
 }

 return *this;
}


String String::RTrim()
{
 unsigned int iCt=0, iLenStr;

 iLenStr=this->LenStr()-1;
 for(unsigned int i=iLenStr; i>0; i--)
 {
     if(this->pStrBuffer[i]==32 || this->pStrBuffer[i]==9)
        iCt++;
     else
        break;
 }
 this->pStrBuffer[this->LenStr()-iCt]=0;

 return *this;
}


String String::Trim()
{
 this->LTrim();
 this->RTrim();

 return *this;
}


unsigned int String::ParseCount(const TCHAR c)  //returns one more than # of
{                                              //delimiters so it accurately
 unsigned int iCtr=0;                          //reflects # of strings delimited
 TCHAR* p;                                      //by delimiter.

 p=this->pStrBuffer;
 while(*p)
 {
  if(*p==c)
     iCtr++;
  p++;
 }

 return ++iCtr;
}


void String::Parse(String* pStr, TCHAR delimiter)
{
 unsigned int i=0;
 TCHAR* pBuffer=0;
 TCHAR* c;
 TCHAR* p;

 pBuffer=new TCHAR[this->LenStr()+1];
 if(pBuffer)
 {
    p=pBuffer;
    c=this->pStrBuffer;
    while(*c)
    {
     if(*c==delimiter)
     {
        pStr[i]=pBuffer;
        p=pBuffer;
        i++;
     }
     else
     {
        *p=*c;
        p++;
        *p=0;
     }
     c++;
    }
    pStr[i]=pBuffer;
    delete [] pBuffer;
 }
}


int String::iVal()
{
 return _ttoi(this->pStrBuffer);  //atoi
}


String String::CStr(const int iNum)
{
 String sr;
 _stprintf(sr.pStrBuffer,_T("%d"),iNum);
 return sr;
}


String String::CStr(const unsigned int iNum)
{
 String sr;
 _stprintf(sr.pStrBuffer,_T("%u"),iNum);
 return sr;
}


String String::CStr(const short int iNum)
{
 String sr;
 _stprintf(sr.pStrBuffer,_T("%d"),iNum);
 return sr;
}


String String::CStr(const double dblNum)
{
 String sr(32);
 _stprintf(sr.pStrBuffer,_T("%f"),dblNum);
 return sr;
}


int String::LenStr(void)
{
 return _tcslen(this->pStrBuffer);
}


TCHAR* String::lpStr()
{
 return pStrBuffer;
}

void String::Print(bool blnCrLf)
{
 _tprintf(_T("%s"),pStrBuffer);
 if(blnCrLf)
    _tprintf(_T("\n"));
}
#endif
