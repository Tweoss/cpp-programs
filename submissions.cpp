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
	// std::cin.clear();
	// std::cin.ignore(1024,'\n');
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
	std::cin >> tempwidth;
	std::cout << "Enter the height: ";
	int tempheight;
	std::cin >> tempheight;
	std::cout << "Output of printRectangle:" << std::endl;
	printRectangle(tempchar,tempwidth,tempheight);
	
	


	return 0;
}

