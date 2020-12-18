#include <iostream>
#include <string>
#include <vector>

//! ASSIGNMENT: Final


//* Declared up front to be used
//* Throw for failed var creation
class VarException : public std::runtime_error
{
private:
	//* not used, but is there
	int error_value;

public:
	//* constructor
	VarException(std::string errDesc, int value) : runtime_error(errDesc), error_value(value)
	{
	}
	//* to get the error value, not used
	int value(void) { return error_value; }
};

class Var4Bool
{
private:
	//* the name of the variable
	std::string name;
	//* the bool content of the variable
	bool bit;

public:
	//* default constructor (for inheritance), unneccessary b/c of try catch for incomplete
	Var4Bool() {}
	//* constructor (iname = input name)
	Var4Bool(std::string iname, bool ibit) : name(iname), bit(ibit)
	{
		if (name.length() == 0)
		{
			throw new VarException("no string entered", 1);
		}
		else if (name.find_first_not_of(' ') == std::string::npos)
		{
			throw new VarException("only spaces", 2);
		}
		//* uses the range of ascii values so doesnt test each digit
		else if (48 <= name[0] && name[0] <= 57)
		{
			throw new VarException("begins with a number", 3);
		}
	}
	//* virtual cuz will be overridden by Var4Int
	virtual std::string toString(void)
	{
		//* alternative to sstream (basically an inline if statement)
		return name + "(" + (bit ? "true" : "false") + ")";
	}
	//* searching
	bool searchIgnoreCase(std::string search)
	{
		bool output;
		std::string temp = name;
		std::transform(search.begin(), search.end(), search.begin(), ::tolower);
		std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
		if (temp.find(search) != std::string::npos)
		{
			output = true;
		}
		else
		{
			output = false;
		}
		return output;
	}
	std::string getName(void) { return name; }
	void setName(std::string set) { name = set; }
};

class Var4Int : public Var4Bool
{
private:
	// std::string name;
	int num;

public:
	Var4Int(std::string name, bool inum) : num(inum)
	{
		setName(name);
		if (name.length() == 0)
		{
			throw new VarException("no string entered", 1);
		}
		else if (name.find_first_not_of(' ') == std::string::npos)
		{
			throw new VarException("only spaces", 2);
		}
		else if (48 <= name[0] && name[0] <= 57)
		{
			throw new VarException("begins with a number", 3);
		}
	}
	std::string toString(void)
	{
		return getName() + "(" + std::to_string(num) + ")";
	}
	bool isGreater(Var4Int other) { return num > other.getNum(); }
	int getNum(void) { return num; }
};

//* "It will return the list of Var4Bool objects that have the variable names containing ..."

//* in order to return two things

std::vector<Var4Bool *> searchIgnoreCase(std::vector<Var4Bool *> input, std::string search, int *count)
{
	std::vector<Var4Bool *> container;
	for (size_t i = 0; i < input.size(); i++)
	{
		if (input[i]->searchIgnoreCase(search))
		{
			if (input[i]->getName() == search)
			{
				(*count)++;
			}
			container.push_back(input[i]);
		};
	}
	return container;
}

bool parse_bool(std::string input)
{
	return input == "true" ? true : input == "false" ? false : throw std::runtime_error("Improper Boolean");
}

Var4Bool *createNewVar(void)
{
	Var4Bool *output;
	std::string name = "";
	std::string other;
	bool stop = false;
	while (!stop)
	{
		std::cout << "Input name or 0 to stop: ";
		std::getline(std::cin, name);
		if (name == "0")
		{
			break;
		}
		std::cout << "Enter boolean or integer: ";
		std::getline(std::cin, other);
		try
		{
			if (other == "true" || other == "false")
			{
				output = new Var4Bool(name, parse_bool(other));
			}
			else
			{
				output = new Var4Int(name, std::stoi(other));
			}
			stop = true;
		}
		catch (const std::exception &e)
		{
			std::cerr << "Failed to create var because " << e.what() << '\n';
		}
	}
	return output;
}

int main(int argc, char *argv[])
{
	std::vector<Var4Bool *> container;
	std::cout << "\nTesting createNewVar. \n";
	int temp = 1;
	while (temp == 1)
	{
		container.push_back(createNewVar());
		std::cout << "Created " << container.back()->toString() << std::endl;
		std::cout << "Continue? (1 for Y): ";
		std::cin >> temp;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}

	std::cout << "\nTesting Searching. \n";
	while (true)
	{
		std::string name = "";
		std::cout << "Enter the name or 0 to stop: ";
		std::getline(std::cin, name);
		if (name == "0")
		{
			break;
		}
		int count;
		std::vector<Var4Bool *> output = searchIgnoreCase(container, name, &count);
		if (output.size() > 0)
		{
			std::cout << "Matched: \n";
			for (size_t i = 0; i < output.size(); i++)
			{
				std::cout << output[i]->toString() << std::endl;
			}
			std::cout << "and had " << count << " exact matches.\n";
		}
		else
		{
			std::cout << "No matches found.\n";
		}
	}

	return 0;
}
