#include <iostream>
using namespace std;
#include <vector>
#include <numeric>
#include <iomanip>

//! ASSIGNMENT: Print Pay Stub

//* Ask the user for the employee pay info: name (string), the starting working date (mm/dd/yyyy), number of hours (double), hourly pay rate (double). Then it prints out the simple summary of the paysub (please see an example below)
//* The overtime pay is calculated as follows
//* any hour more than 60 hours per week is calculated as double time
//* any hour more than 40 hours per week but less than or equal 60 is calculated as 1.5 pay
//* any hour equal or under 40 hours is calculated as regular pay
//* Continuously ask the user to enter another set of data until the user chooses to exit the program
//* Before exiting the program, it will print out the summary that includes
//* the total number of employees that it has printed out the paystub
//* the total number of hours for all employees that have been entered
//* the total pay amount for all employees

bool getContinue(void)
{
	char input;
	while (true)
	{
		cout << "Do you want to enter another pay info (y/n)? ";
		cin >> input;
		if (input == 89 || input == 121)
		{ //ascii codes for y/Y
			return true;
		}
		else if (input == 78 || input == 110)
		{
			return false;
		}
		else
		{
			cout << "Please enter one of the following: n,N,y,Y.\n";
		}
		fflush(stdin);
	}
}

float calculatePay(float hours, float rate)
{
	return rate * (((hours - 60) * 2 + 20 * 1.5 + 40 * 1) * (hours > 60) + ((hours - 40) * 1.5 + 40 * 1) * (hours > 40 && hours <= 60) + ((hours)*1) * (hours <= 40));
}

bool goodBounds(float hours, float rate)
{
	bool returnvalue = true; //so that we can print multiple errors
	if (hours < 0) {
		cout << "Error: number of hours cannot be 0 or negative. \n";
		returnvalue = false;
	}
	else if (hours > 168) {
		cout << "Error: number of hours cannot be greater 168 hours (24*7) per week. \n";
		returnvalue = false;
	}
	if (rate < 0) {
		cout << "Error: Pay rate cannot be negative. \n";
		returnvalue = false;
	}
	else if (rate > 9999) {
		cout << "Wow, I would like to have " << rate << " as my hourly rate. \n";
	}
	return returnvalue;
}

int main(void)
{
	int totalEmployees = 0;
	float totalHours = 0;
	float totalPayment = 0;
	bool continuing = true;
	std::cout << std::fixed;
	cout << setprecision(2);
	while (continuing)
	{
		fflush(stdin);
		float hours;
		float payment;
		string name;
		string startdate;
		float rate;

		cout << "Please enter the employee's name: ";
		getline(cin, name);
		cout << "Please enter the starting work date (mm/dd/yyyy): ";
		cin >> startdate;
		cout << "Please enter how many hours that the employee has worked for this week: ";
		cin >> hours;
		cout << "Please enter the employee's hourly rate: ";
		cin >> rate;

		if (!goodBounds(hours,rate)) {
			continue;
		}
		payment = calculatePay(hours, rate);

		cout << "=======PAY STUB========================= \n"
			 << "Employee name:   " << name << endl
			 << "Number of hours: " << hours << endl
			 << "Hourly rate:    "
			 << "$" << rate << endl
			 << "Gross pay:      "
			 << "$" << payment << endl
			 << "Date:            " << startdate << endl
			 << "========================================" << endl;

		totalEmployees++;
		totalHours += hours;
		totalPayment += payment;
		continuing = getContinue();
		if (!continuing)
		{
			cout << "=======TOTAL PAY SUMMARY================" << endl
				 << "Total number of employees:   " << totalEmployees << endl
				 << "Total number of paid hours:  " << totalHours << endl
				 << "Total amount of payment:    "
				 << "$" << totalPayment << endl
				 << "========================================" << endl;
		}
	}

	return 0;
}
