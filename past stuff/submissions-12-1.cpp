#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "LibraryItem.h"



//! ASSIGNMENT: PROJECT #3: MANAGE THE LIBRARY



class LibraryItemBase : LibraryItem {
	private:
	std::string is_available;
	// std::string searchable;
	std::string type;
	std::string uid;
	std::string title;
	std::string author;
	public:
	
	bool isOnLoan() {
		bool output = false;
		if (is_available != "available") {
			return true;
		}
		return output;
	}

	bool borrow() {
		bool output = false;
		if (!isOnLoan()) {
			is_available = "borrowed";
			return true;
		}
		return output;
	}
	bool takeBack() {
		bool output = false;
		if (isOnLoan()) {
			is_available = "available";
			return true;
		}
		return output;
	}
	std::string toString(void) {
		std::stringstream sstream;
		if (type == "BOOK") {
			sstream << "ID: " << uid << " TITLE: " << title << " STATUS: " << is_available << " AUTHOR: " << author << std::endl;
		}
		else if (type == "CD") {
			sstream << "ID: " << uid << " TITLE: " << title << " STATUS: " << is_available << " ARTIST: " << author << std::endl;
		}
		return sstream.str();
	}
	std::string toString1(bool must_be_available) {
		std::stringstream sstream;
		if (is_available == "available") {
			if (type == "BOOK") {
				sstream << "ID: " << uid << " TITLE: " << title << " STATUS: " << is_available << " AUTHOR: " << author << std::endl;
			}
			else if (type == "CD") {
				sstream << "ID: " << uid << " TITLE: " << title << " STATUS: " << is_available << " ARTIST: " << author << std::endl;
			}
		}
		return sstream.str();
	}
	std::string toString2(std::string book_or_cd) {
		std::stringstream sstream;
		if ((book_or_cd == "BOOK" && type == "BOOK")) {
			sstream << "ID: " << uid << " TITLE: " << title << " STATUS: " << is_available << " AUTHOR: " << author << std::endl;
		}
		else if (book_or_cd == "CD" && type == "CD") {
			sstream << "ID: " << uid << " TITLE: " << title << " STATUS: " << is_available << " ARTIST: " << author << std::endl;
		}
		return sstream.str();
	}
	bool search(std::string search_string) {
		std::string searchable = title;
		std::transform(searchable.begin(), searchable.end(), searchable.begin(), ::tolower);
		if (searchable.find(search_string) != std::string::npos) {
			return true;
		}
		else {
			return false;
		}
	}
	
	std::string get_is_available() {
		return is_available;
	}
	std::string get_type() {
		return type;
	}
	std::string get_uid() {
		return uid;
	}
	std::string get_title() {
		return title;
	}
	std::string get_author() {
		return author;
	}
	void set_is_available(std::string input) {
		is_available = input;
	}
	void set_type(std::string input) {
		type = input;
	}
	void set_uid(std::string input) {
		uid = input;
	}
	void set_title(std::string input) {
		title = input;
	}
	void set_author(std::string input) {
		author = input;
	}
};

class Book : public LibraryItemBase {
	public:
	Book(std::string ttype, std::string uuid, std::string ttile, std::string aauthor) {
		set_type(ttype); set_uid(uuid); set_title(ttile); set_author(aauthor); set_is_available("available"); 
	}

} ;


class Cd : public LibraryItemBase {
	public:
	Cd(std::string ttype, std::string uuid, std::string ttile, std::string aauthor) {
		set_type(ttype); set_uid(uuid); set_title(ttile); set_author(aauthor); set_is_available("available"); 
	}
};

class LibraryCatalog {
	std::vector<LibraryItemBase> container;
	public:
	LibraryCatalog(std::string file) {
		std::string templine;
		std::ifstream contentFile(file);
		if (contentFile.is_open()) {
			int line;
			while (std::getline(contentFile,templine)) {
				//* splitting up the line to get the necessary fields
				line++;
				//* if it is whitespace then "//" or if its does not begin with a B or a C (for BOOK and CD)
				if ((templine.find("//") == templine.find_first_not_of(" ")) | !((templine.find("B") == 0) | (templine.find("C" == 0)))) {
					continue;
				}
				else {
					//* the first edge is end of type, second is start of UID, third is end of UID
					//* the line is REQUIRED to start with either a B or a C
					size_t edges[6];
					edges[0] = templine.find(" ")-1;
					//* the next word will be separated by some amount of whitespace
					edges[1] = templine.find_first_not_of(" ",edges[0] + 1);
					edges[2] = templine.find(" ",edges[1]);
					edges[3] = templine.find_first_not_of(" ",edges[2] + 1);
					edges[4] = templine.find("|",edges[3]-4);
					edges[5] = edges[4]+2;
					
					//* If there is a problem
					if (edges[0] == std::string::npos | edges[1] == std::string::npos | edges[2] == std::string::npos | edges[3] == std::string::npos | edges[4] == std::string::npos | edges[5] > templine.length()) {
						std::cout << "Failed to read line " << line;
						continue;
					}
					if (templine.substr(0,edges[0]+1) == "BOOK") {
						container.push_back(Book("BOOK", templine.substr(edges[1],edges[2]-edges[1]), templine.substr(edges[3],edges[4]-edges[3]-1), templine.substr(edges[5],templine.length()-1-edges[5])));
					}
					else if (templine.substr(0,edges[0]+1) == "CD") {
						container.push_back(Cd("CD", templine.substr(edges[1],edges[2]-edges[1]), templine.substr(edges[3],edges[4]-edges[3]-1), templine.substr(edges[5],templine.length()-1-edges[5])));
					}
					
				}
			}
			contentFile.close();
		}
		else {
			//* FAILURE
			std::cout << "Failed to locate \"" << file << ".\" Please check that the file exists.";
			//* Chose to exit
			exit(0);
		}
	}
	void list(void) {
		for (size_t i = 0; i < container.size(); i++)
		{
			std::cout << container[i].toString();
		}
	}
	void list(std::string input) {
		if (input == "available") {
			for (size_t i = 0; i < container.size(); i++)
			{
				std::cout << container[i].toString1(true);
			}			
		}
		else if (input == "books") {
			for (size_t i = 0; i < container.size(); i++)
			{
				std::cout << container[i].toString2("BOOK");
			}
		}
		else if (input == "cds") {
			for (size_t i = 0; i < container.size(); i++)
			{
				std::cout << container[i].toString2("CD");
			}
		}
	}
	void search(std::string input) {
		bool onefound = false;
		std::transform(input.begin(), input.end(), input.begin(), ::tolower);
		for (size_t i = 0; i < container.size(); i++)
		{
			if (container[i].search(input)) {
				onefound = true;
				std::cout << container[i].toString();
			}
		}
		if (!onefound) {
			std::cout << "Search string not found." << std::endl;
		}
	}
		
	void check_out(std::string uid) {
		bool found  = false;
		for (size_t i = 0; i < container.size(); i++)
		{
			if (container[i].get_uid() == uid && !found) {
				if (container[i].borrow()) {
					std::cout << "Successfully borrowed item \'" << uid << "\'.\n";
				}
				else {
					std::cout << "Failed to borrow \'" << uid <<"\'. Is already borrowed.\n";
				}
				found = true;
			}
		}
		if (!found) {
			std::cout << "Failed to borrow \'" << uid <<"\'. Does not exist.\n";
		}
	}
	void return_book(std::string uid) {
		bool found = false;
		for (size_t i = 0; i < container.size(); i++)
		{
			if (container[i].get_uid() == uid) {
				if (container[i].takeBack()) {
					std::cout << "Successfully returned \'" << uid << "\'.\n";
				}
				else {
					std::cout << "Failed to return \'" << uid << "\'. Already returned.\n";
				}
				found = true;
			}
		}
		if (!found) {
			std::cout << "Failed to borrow \'" << uid <<"\'. Does not exist.\n";
		}
	}
};

void check_argsize(int argc) {
	//* Error checking and loading from file
	switch (argc)
	{
	case 1:
		std::cout << "Please use the file name of the Library file as an argument.\n";
		//* better to exit than throw
		exit(1);
		break;
	case 2:
		break;
	default:
		std::cout << "Please enter a single file name as an argument.\n";
		//* better to exit than throw
		exit(1);
		break;
	}
}



int main(int argc, char *argv[])
{
	check_argsize(argc);
	LibraryCatalog library(argv[1]);
	while (true)
	{
		int option;
		std::cout << "Library:\n"
			<< "    1. list all items\n"
			<< "    2. list available items\n"
			<< "    3. list only books\n"
			<< "    4. list only music CDs\n"
			<< "    5. search\n"
			<< "    6. check out\n"
			<< "    7. return\n"
			<< "    8. exit program\n"
			<< "Enter your selection: ";
		// option = 5;
		std::cin >> option;
		std::cin.clear();
		std::cin.ignore(INT_MAX,'\n');
		std::string str;
		std::cout << std::endl;
		switch (option)
		{
		case 1:
			library.list();
			break;
		case 2:
			library.list("available");
			break;
		case 3:
			library.list("books");
			break;
		case 4:
			library.list("cds");
			break;
		case 5: 
			std::cout << "Please enter the search string: ";
			std::getline(std::cin, str);
			// str.assign("can it be");
			library.search(str);
			break;
		case 6:
			std::cout << "Please enter the item's id: ";
			std::getline(std::cin, str);
			library.check_out(str);
			break;
		case 7:
			std::cout << "Please enter the item's id: ";
			std::getline(std::cin, str);
			library.return_book(str);
			break;
		case 8:
			return 0;
			break;
		default:
			std::cout << std::endl;
			std::cout << "Please enter a valid option";
			break;
		}
		std::cout << std::endl;
	}
	return 0;
}
