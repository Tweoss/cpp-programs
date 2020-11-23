#include <iostream>
#include <string>
#include "Event.h"


Event::Event(int month, int day, std::string descrip) : SimpleDate(month, day) {
	m_descrip = descrip;
	if (!(0 < month && month < 13)) {
		std::cout << "Failed to create Event due to month bounds (1-12).\n";
		exit(1);
	}
}

bool Event::isEqual(Event other) {
	if (other.getDay() == getDay() && other.getMonth() == getMonth() && other.m_descrip == m_descrip)
	{
		return true;
	}
	return false;
}

std::string Event::toString()
{
	return "\"" + std::to_string(getMonth()) + "/" + std::to_string(getDay()) + ": " + m_descrip + "\"";
}

Holiday::Holiday(int month, int day, std::string descrip) : Event(month,day,descrip) {}

std::string Holiday::toString() 
{
	return "\"" + std::to_string(getMonth()) + "/" + std::to_string(getDay()) + ": " + getDescrip() + " (Holiday)" + "\"";
}