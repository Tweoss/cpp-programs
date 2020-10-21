#include <iostream>
#include <string>
#include <sstream>
#include <vector>

//! ASSIGNMENT: Midterm #1

bool containFullComment(char *input)
{
	int i = 0;
	int openCommentLevel = 0;
	bool success = false;
	while (input[i] != 0 && !success)
	{
		if (input[i] == 47 && openCommentLevel == 0 && input[i+1] == 42) {
			openCommentLevel++;
		}
		else if (input[i] == 42 && openCommentLevel == 1 && input[i+1] == 47) {
			success = true;
		}
		i++;
	}
	return success;
}

int getStringType(char *input)
{
	int output;
	int i = 0;
	int location = -1;
	while (input[i] != 0)
	{
		if (!(input[i] >= 48 && input[i] <= 57))
		{
			if (input[i] == 46)
			{
				if (location == -1)
				{
					location = i;
				}
				else
				{
					output = 0;
				}
			}
			else
			{
				output = 0;
			}
		}
		i++;
	}
	if (output != 0)
	{
		if (location == 0 || location == i - 1)
		{
			output = 0;
		}
		else if (location != -1)
		{
			output = 2;
		}
		else
		{
			output = 1;
		}
	}
	return output;
}

bool acceptPINCode(int *input, int size)
{
	std::cout << "Please enter your PIN to verify: ";
	int pin;
	bool isGood = false;
	for (int i = 0; i < 3 && !isGood; i++)
	{
		std::cin >> pin;
		for (size_t j = 0; j < size; j++)
		{
			if (pin == input[j])
			{
				isGood = true;
			}
		}
		if (!isGood)
		{
			std::cout << "Incorrect PIN. Please try again: ";
		}
	}
	return isGood;
}

//* THIS ALLOWS FOR THE LARGEST TO EQUAL THE SMALLEST
int getBoundedListType(int *input, int size)
{
	int edgeleft = input[0];
	int edgeright = input[size - 1];
	bool shouldAscend = false;
	int output = 1;
	bool earlyEnd = false;
	if (edgeright >= edgeleft)
	{
		shouldAscend = true;
	}
	for (size_t i = 0; i < size && !earlyEnd; i++)
	{
		if ((input[i] > edgeleft || input[i] < edgeright) && !shouldAscend)
		{
			output = 3;
			earlyEnd = true;
		}
		else if ((input[i] < edgeleft || input[i] > edgeright) && shouldAscend)
		{
			output = 3;
			earlyEnd = true;
		}
	}
	if (!earlyEnd)
	{
		if (shouldAscend)
		{
			output = 1;
		}
		else
		{
			output = 2;
		}
	}
	return output;
}

int main(void)
{
	// int size;
	// double output;
	std::string inputstr;

	std::cout << "Input string to check for comment: ";
	std::getline(std::cin, inputstr);
	char funcinput1[inputstr.size() + 1];
	for (size_t i = 0; i < inputstr.size(); i++)
	{
		funcinput1[i] = inputstr[i];
	}
	funcinput1[inputstr.size()] = (char)0;

	std::cout << std::endl;

	std::cout << "Testing containFullComment\n";
	std::cout << std::boolalpha << containFullComment(funcinput1);
	std::cout << std::endl
			  << std::endl;

	std::cout << "Input a string to check its string type: ";
	std::getline(std::cin, inputstr);
	char funcinput2[inputstr.size() + 1];
	for (size_t i = 0; i < inputstr.size(); i++)
	{
		funcinput2[i] = inputstr[i];
	}
	funcinput2[inputstr.size()] = (char)0;

	std::cout << std::endl;

	std::cout << "Testing getStringType\n";
	std::cout << getStringType(funcinput2);

	std::cout << std::endl
			  << std::endl;

	std::cout << "Enter space-delimited array of integers for acceptable PIN's: ";
	std::vector<int> input;
	int size = 0;
	std::getline(std::cin, inputstr);
	std::istringstream sstr(inputstr);
	int temp;
	while (sstr >> temp)
	{
		input.push_back(temp);
		size++;
	}

	int funcinput3[size];
	for (size_t i = 0; i < size; i++)
	{
		funcinput3[i] = input[i];
	}

	std::cout << "\nTesting acceptPINCode\n";
	std::cout << std::boolalpha << acceptPINCode(funcinput3, size);

	std::cout << std::endl
			  << std::endl;

	std::cout << "Enter space-delimited array of integers for checking boundedness: ";
	size = 0;
	std::getline(std::cin, inputstr);
	std::istringstream sstr1(inputstr);
	input.clear();
	while (sstr1 >> temp)
	{
		input.push_back(temp);
		size++;
	}
	int funcinput4[size];
	for (size_t i = 0; i < size; i++)
	{
		funcinput4[i] = input[i];
	}

	std::cout << "\nTesting getBoundedListType\n";
	std::cout << getBoundedListType(funcinput4, size);

	std::cout << std::endl
			  << std::endl;

	return 0;
}
