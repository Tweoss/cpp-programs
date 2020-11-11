#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <ctype.h>

// #include <tgmath.h>

//! ASSIGNMENT: Manage Expenses Plus
//? Writes new expenses to the file when spending. 

class Expense {
	private:
	std::string adjusted_description;
	//* internal representation is a single int that counts the number of cents
	int expense; 
	public:
	std::string original_description; 

	Expense(int cents, std::string descrip) {
		expense = cents;
		original_description.assign(descrip);
		adjusted_description.resize(original_description.length());
		std::transform(original_description.begin(), original_description.end(), adjusted_description.begin(), ::tolower);
	}

	std::string print_expense() {
		//* prints the dollars, then a 0, then guaranteed 2-digit cents
		return std::to_string((int) expense/100).append(".").append(std::to_string(expense%100).append("0").substr(0,2));
	}

	//* make sure to lowercase the search string first
	bool search(std::string search_string)  {	
		if (adjusted_description.find(search_string) != std::string::npos) {
			return true;
		}
		else {
			return false;
		}
	}
	bool higher_than(int max) {
		if (expense < max) {
			return false;
		}
		else {
			return true;
		}
	}
	void print() {
		std::stringstream sstream;
		int padding; std::string paddingstring;
		//* Perfectly padded so that the largest integer possible would throw an error BEFORE the formatting goes wonky
		if ((int) expense/100 == 0) {
			paddingstring.assign("        ");
		}
		else {
			padding = 8 - (int) floor(log((int) expense/100)/log(10));
			// std::cout << log(420)/log(2.718281828);
			paddingstring.assign("");
			for (int i = 0; i < padding; i++)
			{
				paddingstring.append(" ");
			}
		}
		sstream << "AMOUNT($" << print_expense() << ")" << paddingstring << "DESC(" << original_description << ")";
		std::cout << sstream.str();
	}
};

class Container {
	std::vector<Expense> list;
	public:

	void load(std::string filename) {
		std::string templine;
		std::ifstream contentFile(filename);
		if (contentFile.is_open()) {
			int line;
			while (std::getline(contentFile,templine)) {
				//* splitting up the line to get the necessary fields
				line++;
				size_t index_of_period;
				index_of_period = templine.find(".");
				size_t end_of_num;
				end_of_num = templine.find(" ") - 1 ;
				//* If there are no spaces
				if (end_of_num == std::string::npos) {
					std::cout << "Failed to read line " << line;
					continue;
				}
				size_t begin_descrip;
				begin_descrip = templine.find_first_not_of(" ",end_of_num+1);
				if (index_of_period == std::string::npos) {
					list.push_back(Expense(std::stoi(templine.substr(0,end_of_num)) * 100,templine.substr(begin_descrip,templine.length())));
				}
				else {
					list.push_back(Expense(std::stoi(templine.substr(0,index_of_period)) * 100 + std::stoi(templine.substr(index_of_period + 1, end_of_num - index_of_period)),templine.substr(begin_descrip,templine.length())));
				}
			}
			contentFile.close();
		}
		else {
			//* FAILURE
			std::cout << "Failed to locate \"" << filename << ".\" Please check that the file exists.";
			exit(0);
		}
	}

	void show_all(void) {
		std::cout << "Expenses:\n";
		for (size_t i = 0; i < list.size(); i++)
		{
			list[i].print(); std::cout << std::endl;
		}
		
	}
	void search_string(std::string search) {
		//* transform the string to lowercase (to ignore)
		std::transform(search.begin(), search.end(), search.begin(), ::tolower);
		for (size_t i = 0; i < list.size(); i++)
		{
			if (list[i].search(search)) {
				list[i].print();
				std::cout << std::endl;
			}
		}
		
		//! PRINT THE THINGS
	}
	void search_value(int input) {
		for (size_t i = 0; i < list.size(); i++)
		{
			if (list[i].higher_than(input)) {
				list[i].print();
				std::cout << std::endl;
			}

		}
		
	}
	void add_entry(Expense entry, std::string filename) {
		//* add the expense to the list
		list.push_back(entry);
		//* and write it to the file
		std::ofstream contentFile;
		contentFile.open(filename, std::ios_base::app);
		contentFile << entry.print_expense() << "  " << entry.original_description << std::endl ;
		contentFile.close();
	}
};

int process_num(std::string input) {
	size_t index_of_period;
	index_of_period = input.find(".");
	size_t end_of_num;
	end_of_num = input.find(" ") - 1 ;
	//* WILL STOP EXECUTION if number conversion fails (new expenses are instantly saved, so nothing will be lost)
	if (index_of_period == std::string::npos) {
		return std::stoi(input.substr(0,end_of_num)) * 100;
	}
	else {
		return std::stoi(input.substr(0,index_of_period)) * 100 + std::stoi(input.substr(index_of_period + 1, end_of_num - index_of_period));
	}
}

bool check_str(std::string input) {
	for (size_t i = 0; i < input.length(); i++)
	{
		if (!(isdigit(input.at(i)) | (input.at(i) == '.'))) {
			return false;
		}
	}
	return true;
	
}

int main(int argc, char *argv[])
{
	Container container;
	//* Error checking and loading from file
	switch (argc)
	{
	case 1:
		std::cout << "Please use the file name of the Expenses file as an argument.\n";
		exit(1);
		break;
	case 2:
		container.load(argv[1]);
		break;
	default:
		std::cout << "Please enter a single file name as an argument.\n";
		exit(1);
		break;
	}

	while (true)
	{
		/* code */
		int option;
		std::cout << "Expense Management Menu:\n"
			<< "    1. show all\n"
			<< "    2. spend\n"
			<< "    3. search expenses containing this string\n"
			<< "    4. search expenses with greater than or equal to this amount\n"
			<< "    5. exit\n"
			<< "Enter your option: ";
		std::cin >> option;
		std::cin.clear();
		std::cin.ignore(INT_MAX,'\n');
		std::string str;
		switch (option)
		{
		case 1:
			std::cout << std::endl;
			container.show_all();
			std::cout << std::endl;
			break;
		case 2:
			std::cout << std::endl;
			std::cout << "Enter the dollars spent: ";
			std::getline(std::cin, str);
			if (!check_str(str)) {
				std::cout << "Enter a number instead.\n";
				break;
			}
			int dollars;
			dollars = process_num(str);
			if (dollars < 0) {
				std::cout << "Enter a positive number instead.\n";
				break;
			}
			std::cout << "Enter the description: ";
			std::getline(std::cin, str);
			container.add_entry(Expense(dollars, str),argv[1]);
			std::cout << std::endl;
			break;
		case 3:
			std::cout << std::endl;
			std::cout << "Please enter the search string: ";
			std::getline(std::cin, str);
			container.search_string(str);
			std::cout << std::endl;
			break;
		case 4:
			std::cout << std::endl;
			std::cout << "Please enter the amount: ";
			std::getline(std::cin, str);
			int tempinput;
			tempinput = process_num(str);
			container.search_value(tempinput);
			std::cout << std::endl;
			break;
		case 5: 
			return 0;
			break;
		default:
			std::cout << std::endl;
			std::cout << "Please enter a valid option";
			std::cout << std::endl;
			break;
		}
	}
	
	// Expense test(42069,"A BIG REE");
	// test.print(); std::cout << std::endl;
	// Expense test1(422069,"A BIG REE");
	// test1.print(); std::cout << std::endl;
	// Expense test2(4222069,"A BIG REE");
	// test2.print(); std::cout << std::endl;
	// Expense test3(00,"A BIG REE");
	// test3.print(); std::cout << std::endl;
	return 0;
}
