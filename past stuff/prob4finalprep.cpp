#include <iostream>
#include <string>
#include <exception>

// 4
// Define another exception class named InvalidDaythat inherits from C++exception class.Define a Date class that contains day, month and year.It will generate an exception of “InvalidDay”if it is given a bad date.Write a method named createDatethat reads from the user month and day.It will try to create a Date object. If the user has entered incorrect date, it should generate the “InvalidDay” exception with proper error information.The function should continue to ask the user to read in new values until a correct date is entered and successful creation of the Date objectusing “new”operatorand the function willreturn the pointer to the Date object.

class InvalidDay : public std::runtime_error
{

public:
	InvalidDay(std::string errDesc) : runtime_error(errDesc)
	{
	}
};

class Date
{
private:
	int day, month, year;

public:
	Date(int iday, int imonth) : day(iday), month(imonth)
	{
		int month_days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
		if (month < 1 || month > 12)
		{
			throw new InvalidDay("Month not valid");
		}
		else if (day < 1 || day > month_days[month])
		{
			throw new InvalidDay("Day not valid");
		}
	}
	Date(int iday, int imonth, int iyear) : day(iday), month(imonth), year(iyear)
	{
		int month_days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
		if (month < 1 || month > 12)
		{
			throw new InvalidDay("Month not valid");
		}
		else if (day < 1 || day > month_days[month-1])
		{
			throw new InvalidDay("Day not valid");
		}
		else if (year < 0) {
			std::cout << "Are u really that old?\n";
		}
	}
	std::string toString()
	{
		return std::to_string(month) + "/" + std::to_string(day) + "/" + std::to_string(year);
	}
};

Date* createDate(void) {
	bool unsuccessful = true;
	int day = 0, month = 0, year = 0;
	Date *output;
	while (unsuccessful)
	{
		unsuccessful = false;
		try
		{
			std::cout << "Please enter the following information as integers: \nMonth: ";
			std::cin >> month;
			std::cin.clear();
			std::cin.ignore(1024, '\n');
			std::cout << "Please enter the following information as integers: \nDay: ";
			std::cin >> day;
			std::cin.clear();
			std::cin.ignore(1024, '\n');
			std::cout << "Please enter the following information as integers: \nYear: ";
			std::cin >> year;
			std::cin.clear();
			std::cin.ignore(1024, '\n');

			output = new Date(day,month,year);
		}
		catch (InvalidDay *pItemErr)
		{
			std::cout << "Bad Date" << std::endl << pItemErr->what() << std::endl;
			unsuccessful = true;
			delete output;
		}
		catch (...)
		{
			std::cout << "Unrecoverable Error\n";
			unsuccessful = true;
			delete output;
			throw; 
		}
		
	}
	return output;
}

int main()
{
	Date *output = createDate();
	std::cout << "Created date: " << output->toString();
	return 0;
}
