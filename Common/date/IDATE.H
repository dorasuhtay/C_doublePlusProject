//------------------------------------------------------------------------------
// IDATE.H
//
// Header file for TIntlDate Class
//
// Author: Daniel BERMAN (dberman@inge-com.fr)
//------------------------------------------------------------------------------

#ifndef _iDate_h
#define _iDate_h

#ifdef __INCLUDECSTRING_FUNC
#include <cstring.h>
#include <strstrea.h>
#endif

#ifdef __INCLUDECSTRING_FUNC
class TTime;
#endif

typedef unsigned int dayTy;
typedef unsigned int monthTy;
typedef unsigned int yearTy;
typedef unsigned long julTy;
typedef unsigned int hourTy;

class TIntlDate
{
public:
	enum HowToSpeak {English, French, German, Spanish};
	enum Months     {January = 1, February, March, April, May, June, July,
						  August, September, October, November, December};
	enum WDays 	    {Monday = 1, Tuesday, Wednesday, Thursday, Friday,
						  Saturday, Sunday};

	TIntlDate();
	TIntlDate(dayTy day, monthTy month, yearTy year);
	TIntlDate(int weekNum, dayTy weekDay, monthTy month, yearTy year);
	#ifdef __INCLUDECSTRING_FUNC
	TIntlDate(const char* str, const char *format = NULL);
	TIntlDate(const TTime& t);
	#endif
	char *					TimeNow(char *buf, int size, const char* format) const;
#ifdef __INCLUDECSTRING_FUNC   
	string					AsString(const char* format = NULL) const;
#endif
//	hourTy 					Hour() const;
	dayTy						DayOfMonth() const;
	monthTy					Month() const;
	yearTy					Year() const;

	dayTy						WeekDay(dayTy day = 0) const;

	int						IsValid() const;

	int						Leap() const;
	static int				LeapYear(yearTy year);

	int						DaysInMonth(monthTy month = 0) const;
	static int				DayWithinMonth(dayTy day, monthTy month, yearTy year);

	dayTy						DayOfYear() const;
	int						WeekOfYear() const;

	TIntlDate				BeginOfMonth();
	TIntlDate				EndOfMonth();

	TIntlDate				BeginOfYear();
	TIntlDate				EndOfYear();

	const char*				NameOfDay() const;
	const char*				NameOfMonth() const;

	static const char*	DayName(dayTy weekDayNumber);
	static const char*	ShortDayName(dayTy weekDayNumber);
	static const char*	MonthName(monthTy monthNumber);

	static HowToSpeak		SetLanguageOption(HowToSpeak l);
	static HowToSpeak		GetLanguageOption();

	TIntlDate&				AddMonths(int months = 1);
	TIntlDate&				AddWeeks(int weeks = 1);
	TIntlDate&				AddYears(int years = 1);

	int						Between(const TIntlDate& d1, const TIntlDate& d2) const;
	TIntlDate				Max(const TIntlDate& dt) const;
	TIntlDate				Min(const TIntlDate& dt) const;

	int operator != (const TIntlDate& date) const;
	int operator <  (const TIntlDate& date) const;
	int operator <= (const TIntlDate& date) const;
	int operator == (const TIntlDate& date) const;
	int operator >  (const TIntlDate& date) const;
	int operator >= (const TIntlDate& date) const;

	julTy operator - (const TIntlDate& dt) const;
	friend TIntlDate operator + (const TIntlDate& dt, int dd);
	friend TIntlDate operator + (int dd, const TIntlDate& dt);
	friend TIntlDate operator - (const TIntlDate& dt, int dd);

	void operator ++ ();
	void operator ++ (int);
	void operator -- ();
	void operator -- (int);
	void operator += (int dd);
	void operator -= (int dd);

	#ifdef __INCLUDECSTRING_FUNC
	friend ostream& operator << (ostream& s, const TIntlDate& d);
	friend istream& operator >> (istream& s, TIntlDate& d);
	#endif
protected:
#ifdef __INCLUDECSTRING_FUNC
	void					ParseFrom(const char* strDate, const char* format = NULL);
#endif

	static void			SetIntlOptions();

	static int			AssertWeekDayNumber(dayTy day);
	static inline int	AssertIndexOfMonth(monthTy month);

private:
#if 0
  int now_tm_sec;   /* Seconds */
  int now_tm_min;   /* Minutes */
  int now_tm_hour;  /* Hour (0--23) */
  int now_tm_mday;  /* Day of month (1--31) */
  int now_tm_mon;   /* Month (0--11) */
  int now_tm_year;  /* Year (calendar year minus 1900) */
  int now_tm_wday;  /* Weekday (0--6; Sunday = 0) */
  int now_tm_yday;  /* Day of year (0--365) */
  int now_tm_isdst; /* 0 if daylight savings time is not in effect) */
#endif

	julTy JulNum;

	static char ShortDateFmt[11];

	static HowToSpeak Language;

	TIntlDate(julTy j);

	julTy	Jday(dayTy day, monthTy month, yearTy year) const;
	void	Mdy(dayTy& day, monthTy& month, yearTy& year) const;
};

// Holidays & Other Special Days
inline TIntlDate NewYearsDay(yearTy year)		{return(TIntlDate( 1, TIntlDate::January, year));}
inline TIntlDate ValentinesDay(yearTy year)	{return(TIntlDate(14, TIntlDate::February, year));}
inline TIntlDate StPatricksDay(yearTy year)	{return(TIntlDate(17, TIntlDate::March, year));}
inline TIntlDate MothersDay(yearTy year)		{return(TIntlDate( 2, TIntlDate::Sunday, TIntlDate::May, year));}
inline TIntlDate FathersDay(yearTy year)		{return(TIntlDate( 3, TIntlDate::Sunday, TIntlDate::June, year));}
inline TIntlDate BastilleDay(yearTy year)		{return(TIntlDate(14, TIntlDate::July, year));}
inline TIntlDate ChristmasDay(yearTy year)	{return(TIntlDate(25, TIntlDate::December, year));}

#ifdef __INCLUDECSTRING_FUNC
// Constructor for string date.
inline TIntlDate::TIntlDate(const char* str, const char *format)
{
	ParseFrom(str, format);
}
#endif

// Constructor for Julian day.
inline TIntlDate::TIntlDate(julTy j)
{
	JulNum = j;
}

inline int TIntlDate::AssertIndexOfMonth(monthTy month)
{
	return month >= 1 && month <= 12;
}

inline int TIntlDate::AssertWeekDayNumber(dayTy day)
{
	return day >= 1 && day <= 7;
}

inline int TIntlDate::Between(const TIntlDate& d1, const TIntlDate& d2) const
{
	return JulNum >= d1.JulNum && JulNum <= d2.JulNum;
}

inline TIntlDate TIntlDate::EndOfMonth()
{
	return TIntlDate(DaysInMonth(), Month(), Year());
}

inline TIntlDate TIntlDate::EndOfYear()
{
	return TIntlDate(31, 12, Year());
}

inline int TIntlDate::IsValid() const
{
	return JulNum >= 2361222L;		// Sep 14, 1752
}

inline int TIntlDate::Leap() const
{
	return LeapYear(Year());
}

inline const char* TIntlDate::NameOfDay() const
{
	return DayName(WeekDay());
}

inline const char* TIntlDate::NameOfMonth() const
{
	return MonthName(Month());
}

inline int TIntlDate::operator != (const TIntlDate& date) const
{
	return JulNum != date.JulNum;
}

inline int TIntlDate::operator < (const TIntlDate& date) const
{
	return JulNum < date.JulNum;
}

inline int TIntlDate::operator <= (const TIntlDate& date) const
{
	return JulNum <= date.JulNum;
}

inline int TIntlDate::operator > (const TIntlDate& date) const
{
	return JulNum > date.JulNum;
}

inline int TIntlDate::operator == (const TIntlDate& date) const
{
	return JulNum == date.JulNum;
}

inline int TIntlDate::operator >= (const TIntlDate& date) const
{
	return JulNum >= date.JulNum;
}

inline julTy TIntlDate::operator - (const TIntlDate& dt) const
{
	return JulNum - dt.JulNum;
}

inline TIntlDate operator - (const TIntlDate& dt, int dd)
{
	return TIntlDate(dt.JulNum - dd);
}

inline TIntlDate operator + (const TIntlDate& dt, int dd)
{
	return TIntlDate(dt.JulNum + dd);
}

inline TIntlDate operator + (int dd, const TIntlDate& dt)
{
	return TIntlDate(dt.JulNum + dd);
}

inline void TIntlDate::operator ++ ()
{
	JulNum += 1;
}

inline void TIntlDate::operator -- ()
{
	JulNum -= 1;
}

inline void TIntlDate::operator ++ (int)
{
	JulNum += 1;
}

inline void TIntlDate::operator -- (int)
{
	JulNum -= 1;
}

inline void TIntlDate::operator += (int dd)
{
	JulNum += dd;
}

inline void TIntlDate::operator -= (int dd)
{
	JulNum -= dd;
}

#ifdef __INCLUDECSTRING_FUNC
inline ostream& operator << (ostream& s, const TIntlDate& d)
{
	s << d.AsString().c_str();
	return s;
}

inline istream& operator >> (istream& s, TIntlDate& d)
{
	string str;
	s >> str;
	d.ParseFrom(str.c_str());
	return s;
}
#endif

#define date_INCLUSIVE		1		//start with 1 (non-zero)
extern char monthStr[14][4];
extern void CalcdateRange(int mthPeriods, TIntlDate *fmdate, TIntlDate *todate, int roundStyle);
extern int DateLessThan(char *datestr, TIntlDate *startDate);
extern int getMonthValue(char *mthstr);
extern void ExtractDayMnth(char *datestr, int *day, int *month);

#endif

