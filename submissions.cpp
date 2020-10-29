#include <iostream>
#include <string>
#include <sstream>
#include <vector>

//! ASSIGNMENT: selected questions in Chapter 13 

class Date
{
	//not using m_
	private:
	int month, day, year; std::string month_string;

	public:
	Date() {
		month = 12; day = 30; year = 2000; month_string = "December";
	}

	Date(int a, int b, int c) {
		month = a;
		day = b;
		year = c;
		if (day > 31 || day < 1 || month > 12 || month < 1) {
			std::cout << "Error, date is not valid.\n";
			exit(EXIT_FAILURE);
		}
		switch (a)
		{
			case 1:
				month_string.assign("January");
				break;
			case 2:
				month_string.assign("February");
				break;
			case 3:
				month_string.assign("March");
				break;
			case 4:
				month_string.assign("April");
				break;
			case 5:
				month_string.assign("May");
				break;
			case 6:
				month_string.assign("June");
				break;
			case 7:
				month_string.assign("July");
				break;
			case 8:
				month_string.assign("August");
				break;
			case 9:
				month_string.assign("September");
				break;
			case 10:
				month_string.assign("October");
				break;
			case 11:
				month_string.assign("November");
				break;
			
			case 12:
				month_string.assign("December");
				break;
		};
	}
	void print_slash() {
		std::cout << month << "/" << day << "/" << year << std::endl;
	}
	void print_comma() {

		std::cout << month_string << " " << day << ", " << year << std::endl;
	}
	void print_plain() {
		std::cout << day << " " << month_string << " " << year << std::endl;
	}
};

void test_date(void) {
	int temp1, temp2, temp3, choice; 
	choice = INT_MAX;
	std::cout << "Testing Date class." << std::endl;
	while (choice != 0) {
		std::cout << "Enter month as a positive integer: ";
		std::cin >> temp1;
		std::cin.clear();
		std::cin.ignore(INT_MAX,'\n');

		std::cout << "Enter day as a positive integer: ";
		std::cin >> temp2;
		std::cin.clear();
		std::cin.ignore(INT_MAX,'\n');

		std::cout << "Enter year as a positive integer: ";
		std::cin >> temp3;
		std::cin.clear();
		std::cin.ignore(INT_MAX,'\n');

		Date date(temp1,temp2,temp3);

		std::cout << "Enter 1 to format as 12/30/2000, 2 to format as December 30, 2000, 3 to format as 30 December 2000, or anything else to exit.\n";
		std::cout << "Choice: ";
		std::cin >> choice;
		std::cin.clear();
		std::cin.ignore(INT_MAX,'\n');
		switch (choice)
		{
		case 1:
			date.print_slash();
			break;
		case 2:
			date.print_comma();
			break;
		case 3:
			date.print_plain();
			break;
		default:
			std::cout << "Exiting.\n";
			choice = 0;
			break;
		}
	}
}

class Employee {
	private:
	std::string name, department, position; int idNumber;
	public:
	Employee() {
		name.assign(""); department.assign(""); position.assign(""); idNumber = 0;
	}
	Employee(std::string a, int b) {
		name.assign(a); idNumber = b;
		department.assign(""); position.assign("");
	}
	Employee(std::string a, int b, std::string c, std::string d) {
		name.assign(a); idNumber = b; department.assign(c); position.assign(d);
	}
	void change_name(std::string a) {
		name.assign(a);
	}
	void change_id(int a) {
		idNumber = a;
	}
	void change_department(std::string a) {
		department.assign(a);
	}
	void change_position(std::string a) {
		position.assign(a);
	}
	std::string read_name() {
		return name;
	}
	int read_id() {
		return idNumber;
	}
	std::string read_department() {
		return department;
	}
	std::string read_position() {
		return position;
	}


};

void test_employee(void) {
	std::cout << "Testing Employee class." << std::endl;
	Employee susan("Susan Meyers", 47899, "Accounting", "Vice President");
	std::cout << susan.read_name() << ", a " << susan.read_position() << " from " << susan.read_department() << ", has id number " << susan.read_id() << ".\n";
	Employee mark("Mark Jones", 39119, "IT", "Programmer");
	std::cout << mark.read_name() << ", a " << mark.read_position() << " from " << mark.read_department() << ", has id number " << mark.read_id() << ".\n";
	Employee joy("Joy Rogers", 81774, "Manufacturing", "Engineer");
	std::cout << joy.read_name() << ", a " << joy.read_position() << " from " << joy.read_department() << ", has id number " << joy.read_id() << ".\n";
}

class Car {
	private:
	int yearModel, speed; std::string make;
	public:
	Car(int a, std::string b) {
		yearModel = a;
		make.assign(b);
		speed = 0;
	}
	int get_year(void) {
		return yearModel;
	}
	std::string get_make(void) {
		return make;
	}
	int get_speed(void) {
		return speed;
	}
	void accelerate(void) {
		speed += 5;
	}
	void brake(void) {
		speed -= 5;
	}
};

void test_car(void) {
	std::cout << "Testing Car class." << std::endl;
	Car car(2000, "XYZ CORP");
	car.accelerate(); std::cout << "Speed is now " << car.get_speed() << ".\n";
	car.accelerate(); std::cout << "Speed is now " << car.get_speed() << ".\n";
	car.accelerate(); std::cout << "Speed is now " << car.get_speed() << ".\n";
	car.accelerate(); std::cout << "Speed is now " << car.get_speed() << ".\n";
	car.accelerate(); std::cout << "Speed is now " << car.get_speed() << ".\n";
	car.brake(); std::cout << "Speed is now " << car.get_speed() << ".\n";
	car.brake(); std::cout << "Speed is now " << car.get_speed() << ".\n";
	car.brake(); std::cout << "Speed is now " << car.get_speed() << ".\n";
	car.brake(); std::cout << "Speed is now " << car.get_speed() << ".\n";
	car.brake(); std::cout << "Speed is now " << car.get_speed() << ".\n";
}

int main(void)
{

	// test_date();
	// test_employee();
	test_car();
	return 0;
}
