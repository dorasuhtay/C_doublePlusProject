#include "StdAfx.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "xplatform_define.h"
 /*
 #ifdef WIN32
 #include <windows.h>
 #endif
 */
 #include "iniprofile.h"

#if defined (__GNUC__)
	#define iw_vsnprintf vsnprintf
#else
	#if _MSC_VER
		#define iw_vsnprintf vsnprintf
	#endif
#endif

//#if _MSC_VER >= 1400
//#endif
/*#else
 #include "iw_vsnprintf.h"		//was // #include "icutil.h"    temporal implementtation
#endif
 */
#ifndef iw_vsnprintf
	//#define iw_vsnprintf vsnprintf
#endif

#define iw_PRINTF_LENGTH		4096

// #ifdef WIN32
// static const char line_end[] = "\r\n";
// #else
 static const char line_end[] = "\n";
// #endif
 static const char null_string[] = "";

 pIniFile::pIniFile()
 {
   _firstSection = new rlSection;      // first section holds names with section name = null_string
   _firstSection->nextSection = NULL;
   _firstSection->firstName = NULL;
   _firstSection->name = new char[1];
   _firstSection->name[0] = '\0';
   currentSection = currentName = -1;
 }

 pIniFile::~pIniFile()
 {
   rlSection *section, *last_section;

   section = _firstSection;
   while(section != NULL)
   {
     deleteSectionNames(section);
     last_section = section;
     section = section->nextSection;
     delete last_section;
   }
 }

 void pIniFile::deleteSectionNames(rlSection *section)
 {
   rlSectionName *name, *last_name;

   if(section == NULL) return;
   name = section->firstName;
   while(name != NULL)
   {
     if(name->name  != NULL) delete [] name->name;
     if(name->param != NULL) delete [] name->param;
     last_name = name;
     name = name->nextName;
     delete [] last_name;
   }
   if(section->name != NULL) delete [] section->name;
 }

 void pIniFile::copyIdentifier(char *buf, const char *line)
 {
   int i = 1;
   buf[0] = '\0';
   if(line[0] != '[') return;
   while(line[i] != ']' && line[i] != '\0')
   {
     *buf++ = line[i++];
   }
   *buf = '\0';
 }

 void pIniFile::copyName(char *buf, const char *line)
 {
   int i = 0;
   buf[0] = '\0';
   //while(line[i] > ' ' && line[i] != '=')
   while(line[i] != '\0' && line[i] != '=')
   {
     *buf++ = line[i++];
   }
   *buf = '\0';
 }

 void pIniFile::copyParam(char *buf, const char *line)
 {
   char *cptr;
   buf[0] = '\0';
   cptr = strchr((char *)line,'=');
   if(cptr == NULL) return;
   cptr++;
   while((*cptr == ' ' || *cptr == '\t') && *cptr != '\0') cptr++;
   if(*cptr == '\0') return;
   while(*cptr != '\0' && *cptr != '\n') *buf++ = *cptr++;
   *buf = '\0';
 }

 int pIniFile::read(const char *filename)
 {
   FILE *fp;
   int len;
   char line[iw_PRINTF_LENGTH],
        name_section[iw_PRINTF_LENGTH],
        name_name[iw_PRINTF_LENGTH],
        name_param[iw_PRINTF_LENGTH];
   rlSection *s, *s_old;

   // delete old content
   s = _firstSection;
   while(s != NULL)
   {
     deleteSectionNames(s);
     s_old = s;
     s = s->nextSection;
     delete s_old;
   }

   // read the file
   _firstSection = new rlSection;      // first section holds names with section name = null_string
   _firstSection->nextSection = NULL;
   _firstSection->firstName = NULL;
   _firstSection->name = new char[1];
   _firstSection->name[0] = '\0';
   #ifdef WIN32
   fp = fopen(filename,"r+t");
   #else
   fp = fopen(filename,"r");
   #endif
   if(fp == NULL) return -1;
   name_section[0] = name_name[0] = name_param[0] = '\0';
   while(fgets(line,sizeof(line)-1,fp) != NULL)
   {
     if(line[0] == '[') // section identifier
     {
       copyIdentifier(name_section,line);
       setText(name_section, NULL, NULL);
     }
     else if(line[0] > ' ' && line[0] != '\t' && line[0] != '#') // name identifier
     {
       copyName(name_name,line);
       copyParam(name_param,line);
       setText(name_section, name_name, name_param);
     }
     else // it must be a comment line
     {
       len = strlen(line);
       if(len>0) line[len-1] = '\0';
       setText(name_section, line, NULL);
     }
   }
   fclose(fp);
   return 0;
 }

 int pIniFile::write(const char *filename)
 {
   FILE *fp;
   rlSection *s;
   rlSectionName *n;
   #ifdef WIN32
   fp = fopen(filename,"w+t");
   #else
   fp = fopen(filename,"w");
   #endif
   if(fp == NULL) return -1;

   s = _firstSection;
   while(s != NULL)
   {
     if     (s->name[0] == '#')  fprintf(fp,"%s%s",s->name, line_end);
     else if(s->name[0] == '\0') ;
     else                        fprintf(fp,"[%s]%s", s->name, line_end);
     n = s->firstName;
     while(n != NULL)
     {
       if     (n->name[0]  == '#')  fprintf(fp,"%s%s",n->name, line_end);
       else if(n->name[0]  == '\0') fprintf(fp,"%s",line_end);
       else if(n->param[0] == '\0') {/*fprintf(fp,"%s",line_end);*/}
       else                         fprintf(fp,"%s=%s%s",n->name,n->param,line_end);
       n = n->nextName;
     }
     s = s->nextSection;
   }

   fclose(fp);
   return 0;
 }

/*
 int pIniFile::write(const char *filename)
 {
   FILE *fp;
   rlSection *s;
   rlSectionName *n;

   fp = fopen(filename,"w");
   if(fp == NULL) return -1;

   s = _firstSection;
   while(s != NULL)
   {
     if     (s->name[0] == '#')  fprintf(fp,"%s\n",s->name);
     else if(s->name[0] == '\0') ;
     else                        fprintf(fp,"[%s]\n",s->name);
     n = s->firstName;
     while(n != NULL)
     {
       if     (n->name[0]  == '#')  fprintf(fp,"%s\n",n->name);
       else if(n->name[0]  == '\0') fprintf(fp,"\n");
       else if(n->param[0] == '\0') fprintf(fp,"\n");
       else                         fprintf(fp,"%s=%s\n",n->name,n->param);
       n = n->nextName;
     }
     s = s->nextSection;
   }

   fclose(fp);
   return 0;
 }
*/

const char *pIniFile::getText(const char *section, const char *name, char *data, int len, const char *defValue)
{
	return getString(section, name, data, len, defValue);
}
/*
const char *pIniFile::getString(const char *section, const char *name, char *data, int len, const char *defValue)
{
	strncpy(data, text(section, name, defValue),len);
	data[len] = 0x0;
   return data;
}
*/
const char *pIniFile::getString(const char *section, const char *name, char *data, int len, const char *defValue)
{
	char *def = new char [len+1];
	STRNCPY(def, defValue, len);
	def[len] = 0x0;
	const char *sptr = text(section, name, defValue);
	if (sptr==null_string)
   		STRNCPY(data, def, len);
	else
		STRNCPY(data, sptr, len);
	def[len] = 0x0;
	delete def;
	return data;
}

const char *pIniFile::text(const char *section, const char *name, const char *defValue)
 {
   rlSection *s;
   rlSectionName *n;

   s = _firstSection;
   while(s != NULL)
   {
     if(strcmp(section,s->name) == 0)
     {
       n = s->firstName;
       while(n != NULL)
       {
         if(n->name != NULL && strcmp(name,n->name) == 0)
         {
           return n->param;
         }
         n = n->nextName;
       }
//       return null_string;
       return defValue;
     }
     s = s->nextSection;
   }
   return defValue;
 }

unsigned char pIniFile::getByte(const char *section, const char *name, unsigned char defvalue)
{
   char buf[16];
   SPRINTF(buf, sizeof(buf), "%d", defvalue);
   return (unsigned char)atoi(text(section, name, buf));
}

int pIniFile::getInt(const char *section, const char *name, int defvalue)
{
   char buf[40];
   SPRINTF(buf, sizeof(buf), "%d", defvalue);
   return atoi(text(section, name, buf));
}

double pIniFile::getdouble(const char *section, const char *name, const char *fmt, double defvalue)
{
   char buf[256];
   SPRINTF(buf, sizeof(buf), fmt, defvalue);
   return atof(text(section, name, buf));
}

float pIniFile::getfloat(const char *section, const char *name, const char *fmt, float defvalue)
{
   char buf[256];
   SPRINTF(buf, sizeof(buf), fmt, defvalue);
   return (float)atof(text(section, name, buf));
}

void pIniFile::setdouble(const char *section, const char *name, const char *fmt, double value)
{
   char buf[64];
   SPRINTF(buf, sizeof(buf), fmt, value);
   setText(section, name, buf);
}

/*
void pIniFile::setdouble(const char *section, const char *name, double value, char *fmt)
{
   char buf[64];
   sprintf(buf, fmt, value);
   setText(section, name, buf);
}
*/
void pIniFile::setfloat(const char *section, const char *name, float value, const char *fmt)
{
	setdouble(section, name, fmt, value);
}

void pIniFile::getfloat(const char *section, const char *name, float *value, const char *fmt)
{
	*value = getfloat(section, name, fmt, *value);
}


long pIniFile::getlong(const char *section, const char *name, long defvalue)
{
   char buf[40];
   
   SPRINTF(buf, sizeof(buf), "%ld", defvalue);
   return atol(text(section, name, buf));
/*
   if (sptr!=null_string)
      return atol(sptr);
   else
      return 0L;
*/
}

void pIniFile::setByte (const char *section, const char *name, unsigned char value)
{
   char buf[16];
   
   SPRINTF(buf, sizeof(buf), "%d", value);
   setText(section, name, buf);
}

void pIniFile::setInt(const char *section, const char *name, int value)
{
   char buf[64];
   
   SPRINTF(buf, sizeof(buf), "%d", value);
   setText(section, name, buf);
}



void pIniFile::setLong(const char *section, const char *name, long value)
{
   char buf[64];
   
   SPRINTF(buf, sizeof(buf), "%ld", value);
   setText(section, name, buf);
}


void pIniFile::setText(const char *section, const char *name, const char *text)
{
   rlSection *s, *last_section;
   rlSectionName *n, *last_name;

   if(section == NULL) return;
   last_section = NULL;
   last_name = NULL;
   s = _firstSection;
   while(s != NULL)
   {
     if(strcmp(section,s->name) == 0)
     {
       last_name = NULL;
       n = s->firstName;
       while(n != NULL)
       {
         if(name != NULL && name[0] != '#' && name[0] != '\0' && strcmp(name,n->name) == 0)
         {
           if(n->param != NULL) delete [] n->param;
           if(text == NULL)
           {
             n->param = new char[1];
             n->param[0] = '\0';
           }
           else
           {
             n->param = new char[strlen(text)+1];
             strcpy(n->param,text);
           }
           return;
         }
         last_name = n;
         n = n->nextName;
       }
       if(last_name == NULL)
       {
         s->firstName = new rlSectionName;
         n = s->firstName;
       }
       else
       {
         last_name->nextName = new rlSectionName;
         n = last_name->nextName;
       }
       if(name == NULL)
       {
         n->name = new char[1];
         n->name[0] = '\0';
       }
       else
       {
         n->name = new char[strlen(name)+1];
         strcpy(n->name,name);
       }
       if(text == NULL)
       {
         n->param = new char[1];
         n->param[0] = '\0';
       }
       else
       {
/*
       	if (strlen(text)>0){
	         n->param = new char[strlen(text)+1];
   	      strcpy(n->param,text);
            }
*/
/*
       	if (strlen(text)==0)
         	strcpy((char *)text, " ");
         n->param = new char[strlen(text)+1];
         strcpy(n->param,text);
*/
         n->param = new char[strlen(text)+1];
         strcpy(n->param,text);
       }
       n->nextName = NULL;
       return;
     }
     last_section = s;
     s = s->nextSection;
   }
   if(last_section == NULL)
   {
     _firstSection = new rlSection;
     last_section = _firstSection;
   }
   else
   {
     last_section->nextSection = new rlSection;
     last_section = last_section->nextSection;
   }
   last_section->name = new char[strlen(section)+1];
   strcpy(last_section->name,section);
   last_section->nextSection = NULL;
   if(name == NULL)
   {
     last_section->firstName = NULL;
   }
   else
   {
     last_section->firstName = new rlSectionName;
     n = last_section->firstName;
     n->name = new char[strlen(name)+1];
     strcpy(n->name,name);
     if(text == NULL)
     {
       n->param = new char[1];
       n->param[0] = '\0';
     }
     else
     {
       n->param = new char[strlen(text)+1];
       strcpy(n->param,text);
     }
     n->nextName = NULL;
   }
   return;
 }

 int pIniFile::printf(const char *section, const char *name, const char *format, ...)
 {
   int ret;
   char buf[iw_PRINTF_LENGTH]; // should be big enough

   va_list ap;
   va_start(ap,format);
   ret = iw_vsnprintf(buf, iw_PRINTF_LENGTH - 1, format, ap);
   va_end(ap);
   if(ret > 0) setText(section, name, buf);
   return ret;
 }

 void pIniFile::remove(const char *section)
 {
   rlSection *s, *last;

   last = NULL;
   s = _firstSection;
   while(s != NULL)
   {
     if(strcmp(section,s->name) == 0)
     {
       deleteSectionNames(s);
       if(last != NULL) last->nextSection = s->nextSection;
       delete s;
       return;
     }
     last = s;
     s = s->nextSection;
   }
 }

 void pIniFile::remove(const char *section, const char *name)
 {
   rlSection *s;
   rlSectionName *n, *last;

   s = _firstSection;
   while(s != NULL)
   {
     if(strcmp(section,s->name) == 0)
     {
       last = NULL;
       n = s->firstName;
       while(n != NULL)
       {
         if(strcmp(name,n->name) == 0)
         {
           if(n->name  != NULL) delete [] n->name;
           if(n->param != NULL) delete [] n->param;
           if(last != NULL) last->nextName = n->nextName;
           delete n;
           return;
         }
         last = n;
         n = n->nextName;
       }
       return;
     }
     s = s->nextSection;
   }
 }

 const char *pIniFile::firstSection()
 {
   currentSection = 0;
   return _firstSection->name;
 }

 const char *pIniFile::nextSection()
 {
   rlSection *s;
   int i;

   if(currentSection < 0) return NULL;
   currentSection++;
   i = 0;
   s = _firstSection;
   while(s != NULL)
   {
     if(i == currentSection) return s->name;
     s = s->nextSection;
     i++;
   }
   currentSection = -1;
   return NULL;
 }

 const char *pIniFile::firstName(const char *section)
 {
   rlSection *s;
   rlSectionName *n;

   s = _firstSection;
   while(s != NULL)
   {
     if(strcmp(section,s->name) == 0)
     {
       n = s->firstName;
       currentName = 0;
       return n->name;
     }
     s = s->nextSection;
   }
   return NULL;
 }

 const char *pIniFile::nextName(const char *section)
 {
   rlSection *s;
   rlSectionName *n;
   int i;

   if(currentName < 0) return NULL;
   currentName++;
   i = 0;
   s = _firstSection;
   while(s != NULL)
   {
     if(strcmp(section,s->name) == 0)
     {
       n = s->firstName;
       while(n != NULL)
       {
         if(i == currentName) return n->name;
   i++;
         n = n->nextName;
       }
       return NULL;
     }
     s = s->nextSection;
   }
   return NULL;
 }


int getiniTextString(pIniFile *ini, const char *section, const char *prompt, char *value, int vsize)
{
    if (!ini) return 0;
    ini->getText(section, prompt, value, vsize, "");
    if (value[0]) return 1;
    return 0;
}
