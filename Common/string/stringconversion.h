#ifndef __stringconversion__h
#define __stringconversion__h

using namespace System;
extern const char *String2Char(String^ bData, char *out);
extern const char *String2Char_n(String^ bData, char *out, int size);
extern void String2CharArray(String^ bData, wchar_t *out);
extern void wchar_t2char(const wchar_t *bData, char *out);

extern bool isNum(String ^Str);
extern int convertToInt32(String^ valuestr, int base=10);
extern array<Byte>^ MakeManagedArray(unsigned char* input, int len);
extern array<Byte> ^MakeManagedArray(array<Byte> ^%arry, unsigned char* input, int len);
extern String^ StripStartTags( String^ cmdstring, String ^ValueIdentifier, String ^separator );
extern int getCommaDelimitedField(char *buf, int len, int fieldno, char *field, int fieldlen);


#endif