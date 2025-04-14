//------------------------------------------------------------------------------
// IDATE.CPP
//
// TIntlDate Class
//
// Author:  Daniel BERMAN (dberman@inge-com.fr)
// Written: 1st October 1995
//
// Most of the code is taken from Borland's TDate class.
//------------------------------------------------------------------------------
#include "StdAfx.h"
#include <stdio.h>
//#include <classlib\time.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "idate.h"

#ifndef min
	#define min(a,b) (((a)<(b))?(a):(b)) 
#endif
//#ifndef max
//	#define max(a,b) (((a)>(b))?(a):(b)) 
//#endif


static const unsigned char daysInMonth[12] =
	{31,28,31,30,31,30,31,31,30,31,30,31};

static const char* WeekDayNames[][7] =
	{
		{"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"},
		{"lundi","mardi","mercredi","jeudi","vendredi","samedi","dimanche"},
		{"Montag","Dienstag","Mittwoch","Donnerstag","Freitag","Samstag","Sonntag"},
		{"Lunes","Martes","Miercoles","Jueves","Viernes","Sabado","Domingo"}
	};

char monthStr[14][4] = {"   ","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec", "\0"};
//const char monthstr[14][4] = {"   ","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec", 0};

static const char* ShortWeekDayNames[][7] =
	{
		{"Mo","Tu","We","Th","Fr","Sa","Su"},
		{"Lu","Ma","Me","Je","Ve","Sa","Di"},
		{"Mo","Di","Mi","Do","Fr","Sa","Su"},
		{"Lu","Ma","Mi","Ju","Vi","Sa","Do"}
	};

static const char* MonthNames[][12] =
	{
		{"January","February","March","April","May","June",
			"July","August","September","October","November","December"},
		{"janvier","février","mars","avril","mai","juin",
			"juillet","août","septembre","octobre","novembre","décembre"},
		{"Januar","Februar","Marz","April","Mai","Juni",
			"Juli","August","September","Oktober","November","Dezember"},
		{"Enero","Febrero","Marzo","Abril","Mayo","Junio",
			"Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"}
	};

static const julTy Jul1901 = 2415386L;  // Julian day for 1/1/1901

#ifndef _Windows
static const char* DefaultShortDateFmt[] =
	{"MM/dd/yy", "dd/MM/yy", "dd/MM/yy", "dd/MM/yy"};
#endif

char TIntlDate::ShortDateFmt[11] = "";

static const unsigned long SECONDS_IN_DAY  = 86400L;

TIntlDate::HowToSpeak TIntlDate::Language = TIntlDate::English;


// Constructor for today's date
TIntlDate::TIntlDate()
{
	time_t timer = time(0);
	struct tm *now = localtime(&timer);
#if 0
	now_tm_sec = now->tm_sec;   /* Seconds */
	now_tm_min = now->tm_min;   /* Minutes */
	now_tm_hour = now->tm_hour;  /* Hour (0--23) */
	now_tm_mday = now->tm_mday;  /* Day of month (1--31) */
	now_tm_mon = now->tm_mon;   /* Month (0--11) */
	now_tm_year = now->tm_year;  /* Year (calendar year minus 1900) */
	now_tm_wday = now->tm_wday;  /* Weekday (0--6; Sunday = 0) */
	now_tm_yday = now->tm_yday;  /* Day of year (0--365) */
	now_tm_isdst = now->tm_isdst; /* 0 if daylight savings time is not in effect) */
#endif
	JulNum = Jday(now->tm_mday, now->tm_mon+1, now->tm_year+1900);
}

// Constructor for the given day, month, and year.
TIntlDate::TIntlDate(dayTy day, monthTy month, yearTy year)
{
	JulNum = Jday(day, month, year);
}
/*
#define fmt_MM_DD_YYYY			1
#define fmt_DD_MM_YYYY			2
#define fmt_YYYY_MM_DD			3

TIntlDate::TIntlDate(char *datestr, int fmt)
{
	dayTy day;
   monthTy month;
   yearTy year;
   char buf[30];
	strncpy(buf, datestr, 29);
   buf[29]=0x0;
   char sptr = buf+6;
   switch(fmt){
    case	fmt_MM_DD_YYYY:
         year = atoi(sptr);
         sptr--;
         *sptr = 0;
         sptr-=2;
         day = atoi(sptr);
         sptr--;
         *sptr = 0;
         month = atoi(buf);
    		break;
    default:
			time_t timer = time(0);
			struct tm *now = localtime(&timer);
			JulNum = Jday(now->tm_mday, now->tm_mon+1, now->tm_year+1900);
         break;
    }
	JulNum = Jday(day, month, year);
}
*/

// Constructor for the given day of week, month, and year based on weekNum.
// if weekNum == 0, the last weekDay of month, year is used.
// weekNum maybe greater than the number of weekDay in the given month and year.
// example: TIntlDate(6, TIntlDate::Tuesday, 11, 1995) -> 12/12/95
TIntlDate::TIntlDate(int weekNum, dayTy weekDay, monthTy month, yearTy year)
{
	JulNum = Jday(1, month, year);
	if (JulNum <= 0)
		return;

	if (!AssertWeekDayNumber(weekDay))
   	return;

   if (weekNum == 0)
		AddMonths(1);

	int d = weekDay - WeekDay();
	JulNum += d;

	if (d > -1)
		weekNum--;

	AddWeeks(weekNum);
}

#ifdef __INCLUDECSTRING_FUNC
// Constructor for TTime
TIntlDate::TIntlDate(const TTime& t)
{
	JulNum = t.IsValid() ? Jul1901 + (julTy)(t.Seconds() / SECONDS_IN_DAY) : 0;
}
#endif

// Increments this TIntlDate by months.
TIntlDate& TIntlDate::AddMonths(int months)
{
	dayTy d, days;
	monthTy m;
	int mth;
	yearTy y;
   int yr;

	Mdy(d, m, y);
   mth = (int)m;
   yr = (int)y;
	mth += months;
	while (mth < 1) {
		mth += 12;
		yr--;
		}
	while (mth > 12) {
		mth -= 12;
		yr++;
		}
   m = (monthTy)mth;
   y = (yearTy)yr;
	days = daysInMonth[m-1];
	if (LeapYear(y) && m == 2)
		days++;

	JulNum = Jday(min(days, d), m, y);

	return *this;
}

// Increments this TIntlDate by weeks.
TIntlDate& TIntlDate::AddWeeks(int weeks)
{
	JulNum += weeks * 7;
	return *this ;
}

// Increments this TIntlDate by years.
TIntlDate& TIntlDate::AddYears(int years)
{
	dayTy d, days;
	monthTy m;
	yearTy y;

	Mdy(d, m, y);
	y += years;

	days = daysInMonth[m-1];
	if (LeapYear(y) && m == 2)
		days++;

	JulNum = Jday(min(days, d), m, y);

	return *this ;
}

char *TIntlDate::TimeNow(char *buf, int size, const char* format) const
{
    time_t     now;
    struct tm  *ts;
    /* Get the current time */
    now = time(NULL);
    /* Format and print the time, "ddd yyyy-mm-dd hh:mm:ss zzz" */
    ts = localtime(&now);
//    strftime(buf, size, "%H:%M:%S%p", ts);
    strftime(buf, size, "%H:%M:%S", ts);
	return buf;
}

#ifdef __INCLUDECSTRING_FUNC
// Return a string for this TIntlDate according to the [Intl] section in win.ini
string TIntlDate::AsString(const char* format) const
{
	const char* picture;

	char buf[80];
	char temp[80];
	ostrstream strtemp(buf, sizeof(buf));
	strtemp.fill('0');

	SetIntlOptions();
	picture = format ? format : ShortDateFmt;

	while (*picture) {
		switch (*picture) {
			case 'd':
			case 'D': {
				int length = 0;
				while (*picture == 'd' || *picture == 'D') {
					picture++;
					length++;
				}
				strtemp.width(length);
				strtemp << DayOfMonth();
				break;
			}
			case 'm':
			case 'M': {
				int length = 0;
				while (*picture == 'm' || *picture == 'M') {
					picture++;
					length++;
				}
				strtemp.width(length);
				strtemp << Month();
				break;
			}
			case 't':
			case 'T': {
				int length = 0;
				while (*picture == 't' || *picture == 'T') {
					picture++;
					length++;
				}
				strtemp.width(length);
            TimeNow(temp, sizeof(temp), "HH:MM:SSPP");
				strtemp << temp;
				break;
			}
#if 0
	now_tm_sec = now->tm_sec;   /* Seconds */
	now_tm_min = now->tm_min;   /* Minutes */
	now_tm_hour = now->tm_hour;  /* Hour (0--23) */
	now_tm_mday = now->tm_mday;  /* Day of month (1--31) */
	now_tm_mon = now->tm_mon;   /* Month (0--11) */
	now_tm_year = now->tm_year;  /* Year (calendar year minus 1900) */
	now_tm_wday = now->tm_wday;  /* Weekday (0--6; Sunday = 0) */
	now_tm_yday = now->tm_yday;  /* Day of year (0--365) */
	now_tm_isdst = now->tm_isdst; /* 0 if daylight savings time is not in effect) */
#endif

			case 'y':
			case 'Y': {
				int length = 0;
				while (*picture == 'y' || *picture == 'Y') {
					picture++;
					length++;
				}
//				if (length == 2)
//					strtemp << (Year() % 100);
//				else
					strtemp << Year();
				break;
			}
			default: {
				strtemp << *picture;
				picture++;
			}
		}
	}

	strtemp << ends;
	return string(buf);
}
#endif

// Returns a new TIntlDate for the first day of this TIntlDate month.
TIntlDate TIntlDate::BeginOfMonth()
{
	dayTy d; monthTy m; yearTy y;
	Mdy(d, m, y);
	return TIntlDate(1, m, y);
}

/*
// Returns a new TIntlDate for the last day of this TIntlDate month.
TIntlDate TIntlDate::EndOfMonth()
{
	dayTy d; monthTy m; yearTy y;
	Mdy(d, m, y);
	return TIntlDate(DaysInMonth(m), m, y);
}
*/
// Returns a new TIntlDate for the first day of this TIntlDate year.
TIntlDate TIntlDate::BeginOfYear()
{
	dayTy d; monthTy m; yearTy y;
	Mdy(d, m, y);
	return TIntlDate(1, 1, y);
}

// Returns a string name for the day of the week,
// where Monday is 1 and Sunday is 7.
// Returns 0 for an invalid weekDayNumber.
const char* TIntlDate::DayName(dayTy weekDayNumber)
{
	if (AssertWeekDayNumber(weekDayNumber))
		return WeekDayNames[Language][weekDayNumber-1];
	else
		return 0;
}

// Returns the day of the month of this TIntlDate
dayTy TIntlDate::DayOfMonth() const
{
	dayTy d; monthTy m; yearTy y;
	Mdy(d, m, y);
	return d;
}

// Returns the day of the year of this TIntlDate
dayTy TIntlDate::DayOfYear() const
{
	dayTy d; monthTy m; yearTy y;
	Mdy(d, m, y);
	return dayTy(JulNum - Jday(1, 1, y) + 1);
}

// Is a day (1-31) within a given month?
int TIntlDate::DayWithinMonth(dayTy day, monthTy month, yearTy year)
{
	if (day <= 0 || !AssertIndexOfMonth(month))
		return 0;

	unsigned d = daysInMonth[month-1];
	if (LeapYear(year) && month == 2)
		d++;

	return day <= d;
}

// Return the number of days of a given month
// Return 0 if "month" is outside of the range 1 through 12, inclusive.
int TIntlDate::DaysInMonth(monthTy month) const
{
	unsigned days = 0;

	if (month == 0)
		month = Month();

	if (AssertIndexOfMonth(month)) {
		days = daysInMonth[month-1];
		if(Leap() && month == 2)
		days++;
	}

	return days;
}

TIntlDate::HowToSpeak TIntlDate::GetLanguageOption()
{
	return Language;
}

// Returns the date with the greater Julian number.
TIntlDate TIntlDate::Max(const TIntlDate& dt) const
{
	return dt.JulNum > JulNum ? dt : *this;
}

// Returns the date with the lesser Julian number.
TIntlDate TIntlDate::Min(const TIntlDate& dt) const
{
	return dt.JulNum < JulNum ? dt : *this;
}

monthTy TIntlDate::Month() const
{
	dayTy d; monthTy m; yearTy y;
	Mdy(d, m, y);
	return m;
}

// Returns the string name for the given monthNumber (1-12).
const char* TIntlDate::MonthName(monthTy monthNumber)
{
	if (AssertIndexOfMonth(monthNumber))
		return MonthNames[Language][monthNumber-1];
	else
		return 0;
}

#ifdef __INCLUDECSTRING_FUNC
// Convert a string to a date according to the [Intl] section in win.ini or the
// passed format specifier
void TIntlDate::ParseFrom(const char *str, const char* format)
{
	int day, month, year;
	const char* picture;

	JulNum = day = month = year = 0;

	SetIntlOptions();
	picture = format ? format : ShortDateFmt;

	while (*picture && *str) {
		switch (*picture) {
			case 'd':
			case 'D': {
				int length = 0;
				while (*picture == 'd' || *picture == 'D') {
					picture++;
					length++;
				}
            int i ;
				for ( i = 0; i <= length; i++)
					if (!isdigit(*(str+i)))
						break;
				i = i > 2 ? 2 : i;
				day  = atoi(string(str, 0, i).c_str());
				str += i;
				break;
			}
			case 'm':
			case 'M': {
				int length = 0;
				while (*picture == 'm' || *picture == 'M') {
					picture++;
					length++;
				}
            int i ;
				for ( i = 0; i <= length; i++)
					if (!isdigit(*(str+i)))
						break;
				i = i > 2 ? 2 : i;
				month  = atoi(string(str, 0, i).c_str());
				str += i;
				break;
			}
			case 'y':
			case 'Y': {
				int length = 0;
				while (*picture == 'y' || *picture == 'Y') {
					picture++;
					length++;
				}
            int i ;
				for ( i = 0; i <= length; i++)
					if (!isdigit(*(str+i)))
						break;
				i = i > 2 ? 4 : 2;
				year  = atoi(string(str, 0, i).c_str());
				str += i;
				break;
			}
			default: {
				picture++;
				str++;
			}
		}
	}

	JulNum = Jday(day, month, year);
	if (JulNum < 1)
		JulNum = 0;
}
#endif

void TIntlDate::SetIntlOptions()
{
/*
#ifdef _Windows
	GetProfileString("intl", "sShortDate",  "MM/dd/yy", ShortDateFmt, sizeof(ShortDateFmt));
#else
	strcpy(ShortDateFmt, DefaultShortDateFmt[Language]);
#endif
*/
 strcpy(ShortDateFmt,"dd.MM.yyyy");
}

TIntlDate::HowToSpeak TIntlDate::SetLanguageOption(HowToSpeak l)
{
	HowToSpeak old = Language;
	Language = l;
	return old;
}

const char*	TIntlDate::ShortDayName(dayTy weekDayNumber)
{
	if (AssertWeekDayNumber(weekDayNumber))
		return ShortWeekDayNames[Language][weekDayNumber-1];
	else
		return 0;
}

// Returns 1 (Monday) through 7 (Sunday).
dayTy TIntlDate::WeekDay(dayTy day) const
{
	julTy julnum = (day == 0 ? JulNum : Jday(day, Month(), Year()));
	return dayTy(((((julnum+1)%7)+6)%7)+1);
}

// Returns the week number for this TIntlDate
int TIntlDate::WeekOfYear() const
{
	return int(((JulNum - Jday(1, 1, Year()) + 1) / 7) + 1);
}

// Returns the year of this TIntlDate.
yearTy TIntlDate::Year() const
{
	dayTy d; monthTy m; yearTy y;
	Mdy(d, m, y);
	return y;
}


//-- Algorithm from Communications of the ACM. ---------------------------------


// Convert Gregorian calendar date to the corresponding Julian day number j.
// Algorithm 199 from Communications of the ACM.
// Gregorian calendar started on Sep. 14, 1752.
// This function not valid before that.
// Returns 0 if the date is invalid.
julTy TIntlDate::Jday(dayTy d, monthTy m, yearTy y) const
{
	unsigned long c, ya;

	if (y >= 80 && y <= 99)
		y += 1900;
	else if (y < 80)
		y += 2000;

	if (!DayWithinMonth(d, m, y))
		return (julTy)0;

	if (m > 2)
		m -= 3;
	else {
		m += 9;
		y--;
	}

	c = y / 100;
	ya = y - 100*c;

	return ((146097L*c)>>2) + ((1461*ya)>>2) + (153*m + 2)/5 + d + 1721119L;
}

// Algorithm from K & R, "The C Programming Language", 1st ed.
int TIntlDate::LeapYear(yearTy year)
{
	return (year&3) == 0 && year%100 != 0 || year % 400 == 0;
}

// Convert a Julian day number to its corresponding Gregorian calendar date.
// Algorithm 199 from Communications of the ACM.
// Gregorian calendar started on Sep. 14, 1752.
// This function not valid before that.
void TIntlDate::Mdy(dayTy& day, monthTy& month, yearTy& year) const
{
	unsigned long d;
	julTy j = JulNum - 1721119L;

	year  = (yearTy) (((j<<2) - 1) / 146097L);
	j     = (j<<2) - 1 - 146097L * year;
	d     = (j>>2);
	j     = ((d<<2) + 3) / 1461;
	d     = (d<<2) + 3 - 1461 * j;
	d     = (d + 4)>>2;
	month = (monthTy)(5 * d - 3)/153;
	d     = 5 * d - 3 - 153 * month;
	day   = (dayTy)((d + 5) / 5);
	year  = (yearTy)(100 * year + j);

	if (month < 10)
		month += 3;
	else {
		month -= 9;
		year++;
	}
}

//---------------------------------------------------------------------------------------
//Calculate the date period from today to a date of "mthPeriods" in the future if the
// "mthPeriods" is positive.
//Calculate the date period from a date of "mthPeriods" ago in the past to today if the
// "mthPeriods" is negative.
//PARAMETER:
//  roundStyle --- specifies how the date is calculated
//      date_INCLUSIVE --- means that the from date starts from first day of month and the
//                         to date is the last day of the month (round to a month inclusive)
//      0 ---------------- means that the from date starts from a day "mthPeriods" and the
//                         to date is the todays date (absolute day) for -ve "mthPeriods"
//                         Likewise vice versa for +ve "mthPeriods"
//  fmdate --- is the 1st date
//  todate --- is the 2nd date
//RETURN:
//  fmdate --- is the 1st date
//  todate --- is the 2nd date
//---------------------------------------------------------------------------------------
void CalcdateRange(int mthPeriods, TIntlDate *fmdate, TIntlDate *todate, int roundStyle)
{
   if (mthPeriods){
   	if (mthPeriods<0){
			switch (roundStyle){
          case	date_INCLUSIVE:
					fmdate->AddMonths(mthPeriods+1);
					*fmdate = fmdate->BeginOfMonth();
					*todate = todate->EndOfMonth();
               break;
			 default:
					fmdate->AddMonths(mthPeriods);
          }
         }
      else
      	{
			switch (roundStyle){
          case	date_INCLUSIVE:
					todate->AddMonths(mthPeriods-1);
	         	*fmdate = fmdate->BeginOfMonth();
					*todate = todate->EndOfMonth();
               break;
			 default:
					todate->AddMonths(mthPeriods);
          }
         }
	   }
}
//input format (datestr):
//    APR 10
void ExtractDayMnth(char *datestr, int *day, int *month)
{
//      int dayNumber;
//      int monthNumber;
      char monthstr[6];
      char daystr[6];
      strncpy(monthstr, datestr+4,3);
      monthstr[3] = 0x0;
      strncpy(daystr, datestr+8,2);
      daystr[2] = 0x0;
      *day = atoi(daystr);
      *month = getMonthValue(monthstr);
}


int DateLessThan(char *datestr, TIntlDate *startDate)
{
	int dayNumber;
	int monthNumber;
	ExtractDayMnth(datestr, &dayNumber, &monthNumber);
	if ((monthNumber>=1)&&(monthNumber<=12)){
		TIntlDate sDate(dayNumber, monthNumber, startDate->Year());
		if (sDate<(*startDate))
			return 1;
		return 0;
		}
   else
   	return -1;
}


int getMonthValue(char *mthstr)
{
	int ii = 1;
	while(1){
		if (!monthStr[ii]) break;
		if (strcmp(monthStr[ii],mthstr)==0)	return ii;
      ii++;
   	}
	return 0;
}

