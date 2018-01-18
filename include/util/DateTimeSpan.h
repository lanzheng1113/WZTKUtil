/**
* \copyright (C)2016 �������
* \file DateTime.h
* \brief ��װ��һ������ʱ�������DateTimeSpan
* \version 1.0
* \author FDD
* \date 2016/11/11
*/

#ifndef OWDATETIMESPAN_H
#define OWDATETIMESPAN_H

#include <ctime>
#include <string>
/**
 * \brief ��װ��һ������ʱ�������DateTimeSpan ʹ�÷�������COleDateTimeSpan, @see DateTime
 * \ingroup DATE_TIME
 */
class DateTimeSpan
{
public:
	bool operator ==( DateTimeSpan span ) const;
	bool operator !=( DateTimeSpan span ) const;
	bool operator <( DateTimeSpan span ) const;
	bool operator >( DateTimeSpan span ) const;
	bool operator <=( DateTimeSpan span ) const;
	bool operator >=( DateTimeSpan span ) const;
	DateTimeSpan operator +( DateTimeSpan span ) const;
	DateTimeSpan operator -( DateTimeSpan span ) const;
	DateTimeSpan& operator +=( DateTimeSpan span );
	DateTimeSpan& operator -=( DateTimeSpan span );
public:
	DateTimeSpan( );   //Constructs an uninitialized CTimeSpan object.
	DateTimeSpan( const DateTimeSpan& dtSpan);   //Constructs a CTimeSpan object from another CTimeSpan value.
	DateTimeSpan( time_t t);   //Constructs a CTimeSpan object from a time_t type.
	DateTimeSpan( int lDays,int nHours,int nMins,int nSecs );   //Constructs a CTimeSpan object from components with each component constrained to the following ranges:
	
	int GetDays( ) const;
	int GetHours( ) const;
	int GetTotalHours( ) const;
	int GetMinutes( ) const;
	int GetTotalMinutes( ) const;
	int GetSeconds( ) const;
	int GetTotalSeconds( ) const;
	time_t GetTimeSpan( ) const;
	std::string toString() const;
private:
	time_t _difftime;
};
#endif