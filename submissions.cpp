#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <sstream>

//! ASSIGNMENT: Example Midterm


//* Instead of returning an object, I will return an array with the number of each grade, then the number of invalids
int* analyzeScores(int arr[], int n) {
	int a=0,b=0,c=0,d=0,f=0,inval=0;
	for (size_t i = 0; i < n; i++)
	{
		if (arr[i] >= 90) {
			a++;
		}
		else if (arr[i] >= 80) {
			b++;
		}
		else if (arr[i] >= 70) {
			c++;
		}
		else if (arr[i] >= 60) {
			d++;
		}
		else if (arr[i] >= 0) {
			f++;
		}
		else {
			inval++;
		}
	}
	int * result;
	result = new int[6];
	result[0] = a;
	result[1] = b;
	result[2] = c;
	result[3] = d;
	result[4] = f;
	result[5] = inval;
	return result;
}


void printRectangle(char out, int width, int height) {
	int i,j;
	for (i=0;i<height;i++) {
		for (j=0;j<width;j++) {
			if ((i==0 || i==height-1) || (j==0 || j==width-1)) {
				std::cout << out;
			}
			else {
				std::cout << " ";
			}
		}
		std::cout << std::endl;
	}
}

//* will modify input string instead of create new one
bool extractComment(std::string & input) {
	bool output = false;
	if (input.length() > 3) {
		if (input[0] == '/' && input[1] == '/' && input[2] == ' ') {
			output = true;
			input[0] = ' '; input[1] = ' '; 
			std::rotate(input.begin(),input.begin() + 3, input.end());
		}
	}
	return output;
}

bool checkAgainstVariableNamingRules(std::string input) {
	bool output = true;
	if (input.length() > 255 || input.length() == 0) {
		output = false;
	}
	else if (input[0] != 95 && !(input[0] > 64 && input[0] < 91) && !(input[0] > 96 && input[0] < 123)){
		output = false;
	}
	else {
		for (size_t i = 0; i< input.length(); i++) {
			if (!(input[i] == 95 || (input[i] > 47 && input[i] < 58) || (input[i] > 64 && input[i] < 91) || (input[i] > 96 && input[i] < 123))) {
				output = false;
				break;
			}
		}
	}
	// std::cout << input[0] << std::endl;
	// std::cout << (int) input[1] << std::endl;
	// std::cout << (int) input[2] << std::endl;
	// std::cout << (int) input[3] << std::endl;
	// std::cout << (int) input[4] << std::endl;
	// std::cout << (int) input[5] << std::endl;
	// std::cout << (int) input[6] << std::endl;
	// std::cout << (int) input[7] << std::endl;
	// std::cout << (int) input[8] << std::endl;
	// std::cout << (int) input[9] << std::endl;
	return output;
}

bool isBoundedList(void) {
	int max, min;
	int input, first_input, last_input;
	bool output = false;
	std::cout << "Please enter non-negative score: ";
	std::cin >> first_input;
	max = first_input; min = first_input;
	input = first_input;
	last_input = first_input;
	while (input >= 0) {
		last_input = input;
		if (input > max) {
			max = input;
		}
		else if (input < min) {
			min = input;
		}
		std::cout << "Please enter non-negative score: ";
		std::cin >> input;
	}
	if (first_input == max) {
		if (last_input == min) {
			output = true;
		}
	}
	else if (first_input == min) {
		if (last_input == max) {
			output = true;
		}
	}
	return output;
}

int main(void)
{
	std::cout << "TESTING analyzeScores\n";
	std::cout << "Enter space-delimited array of integers for grades: ";
	std::vector<int> input;
	int size = 0;
	std::string inputstr;
	std::getline(std::cin, inputstr);
	std::istringstream sstr(inputstr);
	int temp;
	while(sstr >> temp) {
		input.push_back(temp);
		size++;
	}
	
	int arr[size];
	for (size_t i = 0; i < size; i++)
	{
		arr[i]=input[i];
	}
	
	int * output;
	output = new int[6];
	output = analyzeScores(arr,size);
	std::cout << "Output of analyzeScores:" << std::endl;
	std::cout << "A:" << output[0] << ", " << "B:" << output[1] << ", " << "C:" << output[2] << ", " << "D:" << output[3] << ", " << "F:" << output[4] << ", " << "Fail:" << output[5];
	std::cout << std::endl;

	std::cout << std::endl << "TESTING printRectangle\n";
	std::cout << "Enter a character: ";
	char tempchar;
	std::cin >> tempchar;
	std::cout << "Enter the width: ";
	int tempwidth;
std::cin.clear();
std::cin.ignore(1024,'\n');
	std::cin >> tempwidth;
	std::cout << "Enter the height: ";
	int tempheight;
std::cin.clear();
std::cin.ignore(1024,'\n');
	std::cin >> tempheight;
	std::cout << "Output of printRectangle:" << std::endl;
	printRectangle(tempchar,tempwidth,tempheight);
	
std::cin.clear();
std::cin.ignore(1024,'\n');

	std::cout << std::endl << "TESTING extractComment\n";
	std::cout << "Enter a string: ";
	std::string inputstring;
	std::getline(std::cin,inputstring);
	bool tempbool;
	tempbool = extractComment(inputstring);
	std::cout << "\nOutput of extractComment:" << std::endl;
	if (tempbool) {
		std::cout << inputstring << std::endl;
	}
	else {
		std::cout << "No comment to extract\n";
	}

	std::cout << std::endl << "TESTING checkAgainstVariableNamingRules\n";
	std::cout << "Enter a string: ";
	std::getline(std::cin,inputstring);
	tempbool = checkAgainstVariableNamingRules(inputstring);
	std::cout << "\nOutput of checkAgainstVariableNamingRules:" << std::endl;
	if (tempbool) {
		std::cout << "Good Variable Name\n";
	}
	else {
		std::cout << "Bad Variable Name\n";
	}

	std::cout << std::endl << "TESTING isBoundedList\n";
	std::cout << "Output of isBoundedList:" << std::endl;
	tempbool = isBoundedList();
	std::cout << std::boolalpha;   
    std::cout<< tempbool <<"\n";
	return 0;
}

