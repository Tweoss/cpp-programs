#include <iostream>
#include <string>
#include <vector>
#include "Event.h"

//! ASSIGNMENT: Final Practice Questions


std::vector<Event*> searchEvents(std::vector<Event*> input, int month) {
	//* uses a vector as output, dynamic memory essentially required
	std::vector<Event*> output;
	for (size_t i = 0; i < input.size(); i++)
	{
		if ((*input[i]).getMonth() == month)
		{
			output.push_back(input[i]);
		}
	}
	return output;
}


int main(int argc, char *argv[])
{
	std::vector<Event*> container;
	std::cout << "\nTesting Event Class. \n";
	while (true)
	{
		int day = 0, month = 0; std::string descrip = "";
		std::cout << "Enter the description or 0 to stop: ";
		std::getline(std::cin, descrip);
		if (descrip == "0") {
			break;
		}
		std::cout << "Enter the month: ";
		std::cin >> month;
		std::cout << "Enter the day: ";
		std::cin >> day;
		std::cin.clear();
		std::cin.ignore(INT_MAX,'\n');
		container.push_back(new Event(month,day,descrip));
		bool duplicate = false;
		for (size_t i = 0; i < container.size()-1; i++)
		{
			if ((*container[container.size()-1]).isEqual(*container[i])) {
				std::cout << "Event is duplicate, will be ignored.\n";
				container.pop_back();
				duplicate = true;
				break;
			}
		}
		if (!duplicate) {
			std::cout << "Created: " << (*container[container.size()-1]).toString() << std::endl;
		}
	}

	
	std::cout << "\nTesting Holiday derived Class. \n";
	while (true)
	{
		int day = 0, month = 0; std::string descrip = "";
		std::cout << "Enter the description or 0 to stop: ";
		std::getline(std::cin, descrip);
		if (descrip == "0") {
			break;
		}
		std::cout << "Enter the month: ";
		std::cin >> month;
		std::cout << "Enter the day: ";
		std::cin >> day;
		std::cin.clear();
		std::cin.ignore(INT_MAX,'\n');
		container.push_back(new Holiday(month,day,descrip));
		bool duplicate = false;
		for (size_t i = 0; i < container.size()-1; i++)
		{
			if ((*container[container.size()-1]).isEqual(*container[i])) {
				std::cout << "Event is duplicate, will be ignored.\n";
				container.pop_back();
				duplicate = true;
				break;
			}
		}
		if (!duplicate) {
			std::cout << "Created: " << (*container[container.size()-1]).toString() << std::endl;
		}
	}

	std::cout << "\nTesting searchEvents. \n";
	while (true)
	{
		int month = 0; 
		std::cout << "Enter the month or 0 to stop: ";
		std::cin >> month;
		std::cin.clear();
		std::cin.ignore(INT_MAX,'\n');
		if (month == 0) {
			break;
		}
		std::vector<Event*> output = searchEvents(container,month);
		std::cout << "Matched: \n"; if (output.size() == 0) {std::cout << "None.\n";}
		for (size_t i = 0; i < output.size(); i++)
		{
			std::cout << (*output[i]).toString() << std::endl;
		}
	}
	

	return 0;
}
