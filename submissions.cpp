#include <iostream>
#include <string>
#include <sstream>
#include <vector>


//! ASSIGNMENT: Practice questions on C++ class, object and command line arguments

//? 

class Holiday {
	private:
	int month; int day;
	public:
	std::string name;

	Holiday(void) {
		;
	}

	Holiday(const char *descrip, int monthnum, int daynum) {
		name = descrip;
		month = monthnum;
		day = daynum;
	}

	std::string toString(void) {
		std::stringstream sstream;
		sstream << name << " (" << month << "/" << day << ")";
		return sstream.str();
	}
	bool isLater(Holiday other) {
		if (month * 31 + day >= other.month * 31 + other.day) {
			return true;
		}
		else {
			return false;
		}
	}
	int getMonth(void) {
		return month;
	}
	int getDay(void) {
		return day;
	}
};



void checkAmount(int argc, char *argv[]) {
	bool output = false;
 	for (size_t i = 0; i < argc; i++)
	{
		//* needs "-amount" before checking for number
		if (std::strcmp(argv[i], "-amount") == 0) {
			//* if there is another item in the input list
			if (argc-1 > i) {
				output = true; //* temporarily
				for (size_t j = 0; j < sizeof(argv[i+1])/8; j++)
				{
					if (!(argv[i+1][j] == '0' | argv[i+1][j] == '1' | argv[i+1][j] == '2' | argv[i+1][j] == '3' | argv[i+1][j] == '4' | argv[i+1][j] == '5' | argv[i+1][j] == '6' | argv[i+1][j] == '7' | argv[i+1][j] == '8' | argv[i+1][j] == '9' | argv[i+1][j] == '.')) {
						output = false;
					}
				}
				
			}
		}
		if (output) {
			std::cout << argv[i+1] << std::endl;
			break;
		}
	}
	if (!output) {
		std::cout << "-1" << std::endl;
	}
}

std::vector<Holiday> getHolidayByMonth(std::vector<Holiday> input, int month) {
	std::vector<Holiday> output;
	for (size_t i = 0; i < input.size(); i++)
	{
		if (month == input[i].getMonth()) {
			output.push_back(input[i]);
		}
	}
	return output;
}

//* case-sensitive
std::vector<Holiday> getHolidayByWord(Holiday *input[], int size, std::string search) {
	std::vector<Holiday> output;
	for (size_t i = 0; i < size; i++)
	{
		if (input[i]->name.find(search) != std::string::npos) {
			output.push_back(*input[i]);
		}
	}

	return output;
}


int main(int argc, char *argv[])
{
	std::cout << "Testing checkAmount: " << std::endl;
	checkAmount(argc, argv);

	std::vector<Holiday> holidays;
	holidays.push_back(Holiday("Independence Day",7,4));
	holidays.push_back(Holiday("New Year",1,1));
	holidays.push_back(Holiday("MLK",1,20));
	holidays.push_back(Holiday("Memorial Day",5,25));
	holidays.push_back(Holiday("Labor Day",9,7));
	holidays.push_back(Holiday("Veterans Day",11,11));

	std::cout << "Testing getHolidayByMonth: " << std::endl;

	std::vector<Holiday> output = getHolidayByMonth(holidays,1);
	for (size_t i = 0; i < output.size(); i++)
	{
		std::cout << output[i].toString() << std::endl;
	}
	
	std::cout << "Testing getHolidayByWord: " << std::endl;
	Holiday *arr[holidays.size()];
	for (size_t i = 0; i < holidays.size(); i++)
	{
		arr[i] = &holidays[i];
	}
	
	std::string input;
	std::cout << "Input a string to search: ";
	std::cin >> input;
	output = getHolidayByWord(arr, holidays.size(), input);

	for (size_t i = 0; i < output.size(); i++)
	{
		std::cout << output[i].toString() << std::endl;
	}

	return 0;
}
