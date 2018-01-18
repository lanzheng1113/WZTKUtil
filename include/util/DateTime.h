/**
* \copyright (C)2016 �������
* \file DateTime.h 
* \brief ��װ��һ������ʱ��DateTime
* \version 1.0
* \author Philippe Bernery
* \date 2016/11/11
*/

#ifndef OWDATETIME_H
#define OWDATETIME_H


#include <ctime>
#include <string>

#include "util/Date.h"
#include "util/TimeEx.h"
#include "util/DateTimeSpan.h"

/**
 * \brief ��װ��һ������ʱ��DateTime
 * \ingroup DATE_TIME
 *
 * DateTime��ĳ��÷���ʾ����
 * \code
 * // ��ĳ��time_tʱ�乹�����
 * time_t t = time(NULL);
 * DateTime dtx(t);
 * // �Ե�ǰʱ�乹�����
 * DateTime dt;
 * // ת��Ϊ YYYY-mm-DD HH:MM:SS��ʽ���ַ���
 * string DateTimeString = dt.toString();
 * // ��YYYY-mm-DD HH:MM:SS��ʽ���ַ����������
 * DateTime dt1;
 * string DateTimeString1 = "1990-1-1 12:00:00";
 * bool isOk = DateTime::fromString(DateTimeString1,dt1);
 * // ���ϻ��߼�ȥĳһ��ʱ�䣬�õ�һ��ʱ�䡣
 * DateTimeSpan span(1,1,1,1);
 * dt += span;
 * dt -= span;
 * // ת��Ϊtime_t
 * time_t t = dt.toTime_tFormat();
 * \endcode
 */
class DateTime
{
public:

	/**
	* Creates a date with the current time.
	*/
	DateTime();

	/**
	* Copy constructor.
	*/
	DateTime(const DateTime & datetime);

	/**
	* Creates a date from a day a month and a year.
	*
	* @param day day of the date
	* @param month month of the date
	* @param year year of the date
	*/
	DateTime(unsigned day, unsigned month, unsigned year,unsigned hour,unsigned minute,unsigned second);

	/**
	* Creates a datetime from time_t type value
	*/
	DateTime(std::time_t t);

	~DateTime();

	bool operator==(const DateTime & datetime) const;

	DateTime operator +( DateTimeSpan timeSpan ) const;
	DateTime operator -( DateTimeSpan timeSpan ) const;
	DateTimeSpan operator -( DateTime time ) const;
	DateTime& operator +=( DateTimeSpan span );
	DateTime& operator -=( DateTimeSpan span );
	DateTime& operator = (const DateTime& datetime){
		_day = datetime._day;
		_month = datetime._month;
		_year = datetime._year;
		_hour = datetime._hour;
		_minute = datetime._minute;
		_second = datetime._second;
		return *this;
	}
	/**
	* @return the day number of the date. Day range: 1-31.
	*/
	unsigned getDay() const;

	/**
	* Sets the date day.
	*
	* @see getDay()
	*/
	void setDay(unsigned day);

	/**
	* @return the month number of the date. Month range: 1-12.
	*/
	unsigned getMonth() const;

	/**
	* Sets the date month.
	*
	* @see getMonth()
	*/
	void setMonth(unsigned month);

	/**
	* Gets the date year. Year range: 0-infinite.
	*/
	unsigned getYear() const;

	/**
	* Sets date year.
	*
	* @see getYear()
	*/
	void setYear(unsigned year);
	/**
	* @return the hour of the time. range: 0-23.
	*/
	unsigned getHour() const;

	/**
	* Sets the hour.
	*/
	void setHour(unsigned hour);

	/**
	* @return the minute of the time. range: 0-59.
	*/
	unsigned getMinute() const;

	/**
	* Sets the minute.
	*/
	void setMinute(unsigned minute);

	/**
	* Gets the second. range: 0-59.
	*/
	unsigned getSecond() const;

	/**
	* Sets second.
	*/
	void setSecond(unsigned second);

	/**
	* Get Date part.
	*/
	Date getDate() const;

	/**
	* Get Time part.
	*/
	Time getTime() const;

	/**
	* @return a string representing the datetime. (e.g: "yyyy-mm-dd hh:MM:ss")
	*/
	std::string toString() const;

	/**
	* @return a DateTime representing the string. (e.g: "yyyy-mm-dd hh:MM:ss")
	*/
	static bool fromString(const std::string& strDateTime,DateTime& dt);

	/**
	 * @return a datetim representing the string as "yyyy/mm/dd/hh/mm/ss"
	 */
	static bool fromStringSlash(const std::string& strDateTime,DateTime& dt);

	/**
	* to time_t value;
	*/
	std::time_t toTime_tFormat() const;

	/**
	 * \brief ���㵱ǰ���������ڼ�
	 * \return ����0~6���ֱ������һ�����ա�
	 */
	int calcWeekDay() const;

	/**
	 * \brief �жϵ�ǰ�����Ƿ������һ��������ʱ�䡣���ڹ��캯��ʹ�������յ������������������ֵ��
	 * \return ��Ч����true,���򷵻�false.
	 */
	bool isValid() const;

	/**
	 * \brief �ж������ʱ���Ƿ���һ��������ʱ�䡣
	 * \return ��Ч����true,���򷵻�false.
	 */
	static bool isValid(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microsecond = 0);
	
	/**
	 * \brief �ж�ĳ�����м���
	 * \return ��������б仯���������ǹ̶���ֵ��
	 */
	static int daysOfMonth(int year, int month);

	/**
	 * \brief �ж�ĳһ���Ƿ�Ϊ����
	 * \return �����귵��true,���򷵻�false.
	 */
	static bool isLeapYear(int year);
private:
	unsigned _day;
	unsigned _month;
	unsigned _year;
	unsigned _hour;
	unsigned _minute;
	unsigned _second;
};
#endif