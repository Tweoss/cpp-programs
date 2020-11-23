#ifndef SIMPLEDATE_H
#define SIMPLEDATE_H
#include <iostream>
#include <string>
class SimpleDate
{
private:
	int m_month, m_day;

public:
	SimpleDate(int month, int day) : m_month(month), m_day(day)
	{
	}
	int getMonth() { return m_month; }
	int getDay() { return m_day; }
	virtual std::string toString()
	{
		return std::to_string(m_month) + "/" + std::to_string(m_day);
	}
};

class Event : public SimpleDate
{
private:
	std::string m_descrip;

public:
	Event(int month, int day, std::string descrip);
	virtual std::string toString();
	bool isEqual(Event other);
	std::string getDescrip() { return m_descrip; }
};

class Holiday : public Event
{
private:

public:
	Holiday(int month, int day, std::string descrip);
	std::string toString();
};

#endif