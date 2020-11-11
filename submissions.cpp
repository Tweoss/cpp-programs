#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

// #include <tgmath.h>

//! ASSIGNMENT: Manage Expenses Plus
//? Assumes that the file has TWO SPACES between the dollar and description e.g. 12.34  Monthly day years expense
//? (the pdf instructions uses two spaces. the example input files use a fixed length. using two spaces allows for very large numbers, while a fixed length does not. THIS program uses TWO spaces, like in the PDF INSTRUCTIONS)

class Expense {
	private:
	std::string adjusted_description;
	int expense_int, expense_frac; 
	std::string frac_string;
	public:
	std::string original_description; 

	Expense(int dollar, int cent, std::string descrip) {
		expense_int = dollar; expense_frac = cent; 
		original_description.assign(descrip);
		std::transform(original_description.begin(), original_description.end(), adjusted_description.begin(), ::tolower);
		frac_string.assign(std::to_string(expense_frac));
		frac_string.insert(0, "0");
		frac_string = frac_string.substr(frac_string.length()-2, frac_string.length()-0);
	}

	std::string print_expense() {
		return std::to_string(expense_int).append(".").append(frac_string);
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
		if (expense_int < max) {
			return false;
		}
		else {
			return true;
		}
	}
	void print() {
		std::stringstream sstream;
		int padding; std::string paddingstring;
		if (expense_int == 0) {
			paddingstring.assign("        ");
		}
		else {
			padding = 8 - (int) floor(log(expense_int)/log(10));
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
			while (std::getline(contentFile,templine)) {
				//* splitting up the line to get the necessary fields
				size_t index_of_period;
				index_of_period = templine.find(".");
				templine.find_first_not_of
				list.push_back(Expense(std::stoi(templine.substr(0,index_of_period - 1)),std::stoi(templine.substr(index_of_period + 1,2)),templine.substr(index_of_period + 5,templine.length())));
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
		for (size_t i = 0; i < list.size(); i++)
		{
			std::cout << list[i].print_expense() << std::endl;
		}
		
	}
	void search_string(std::string search) {
		//* transform the string to lowercase (to ignore)
		std::transform(search.begin(), search.end(), search.begin(), ::tolower);
		for (size_t i = 0; i < list.size(); i++)
		{
			if (list[i].search(search)) {
				std::cout << list[i].print_expense() << std::endl;
			}
		}
		
		//! PRINT THE THINGS
	}
	void search_value(int intpart, int fracpart) {
		for (size_t i = 0; i < list.size(); i++)
		{
			if (list[i].higher_than(intpart))
		}
		
	}
	void add_entry(Expense entry, std::string filename) {
		//* add the expense to the list
		list.push_back(entry);
		//* and write it to the file
		std::ofstream contentFile;
		contentFile.open(filename);
		contentFile << entry.print_expense() << "  " << entry.original_description;
		contentFile.close();
	}
};


int main(int argc, char *argv[])
{
	Container container;
	//* Error checking and loading from file
	switch (argc)
	{
	case 1:
		std::cout << "Please use the file name of the Expenses file as an argument.\n";
		break;
	case 2:
		container.load(argv[1]);
		break;
	default:
		std::cout << "Please enter a single file name as an argument.\n";
		break;
	}

	Expense test(420,69,"A BIG REE");
	test.print(); std::cout << std::endl;
	Expense test1(4220,69,"A BIG REE");
	test1.print(); std::cout << std::endl;
	Expense test2(42220,69,"A BIG REE");
	test2.print(); std::cout << std::endl;
	Expense test3(0,0,"A BIG REE");
	test3.print(); std::cout << std::endl;
	return 0;
}
