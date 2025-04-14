#ifndef INIPROFILE_H_INCLUDED
#define INIPROFILE_H_INCLUDED

// #include "rldefine.h"
struct inipropertyDatafileStruct{
	char *inifile;
	char *sectionname;
};

 class pIniFile
 {
 public:
   pIniFile();
   ~pIniFile();
   int read(const char *filename);
   int write(const char *filename);
   const char *text(const char *section, const char *name, const char *defValue);
   const char *getString(const char *section, const char *name, char *data, int len, const char *defValue);
   const char *getText(const char *section, const char *name, char *data, int len, const char *defValue);
	void setInt (const char *section, const char *name, int value);
   int getInt  (const char *section, const char *name, int defvalue);
	void setByte (const char *section, const char *name, unsigned char value);
   unsigned char getByte  (const char *section, const char *name, unsigned char defvalue);
	void setLong(const char *section, const char *name, long value);
   long getlong(const char *section, const char *name, long defvalue);
	void setfloat(const char *section, const char *name, float value, const char *fmt);
//	void setdouble(const char *section, const char *name, double value, char *fmt);
	void setdouble(const char *section, const char *name, const char *fmt, double value);
	float getfloat(const char *section, const char *name, const char *fmt, float defvalue);
   void getfloat(const char *section, const char *name, float *value, const char *fmt);
	double getdouble(const char *section, const char *name, const char *fmt, double defvalue);
   void setText(const char *section, const char *name, const char *text);
   int  printf(const char *section, const char *name, const char *format, ...);
   void remove(const char *section);
   void remove(const char *section, const char *name);
   const char *firstSection();
   const char *nextSection();
   const char *firstName(const char *section);
   const char *nextName(const char *section);
 private:
   typedef struct _rlSectionName_
   {
     _rlSectionName_ *nextName;
     char            *name;
     char            *param;
   }rlSectionName;

   typedef struct _rlSection_
   {
     _rlSection_   *nextSection;
     rlSectionName *firstName;
     char          *name;
   }rlSection;

   void copyIdentifier(char *buf, const char *line);
   void copyName(char *buf, const char *line);
   void copyParam(char *buf, const char *line);
   void deleteSectionNames(rlSection *section);
   rlSection *_firstSection;
   int currentSection, currentName;
 };

extern int getiniTextString(pIniFile *ini, const char *section, const char *prompt, char *value, int vsize);

#endif // INIPROFILE_H_INCLUDED
