#include <iostream>
#include <string>

//! ASSIGNMENT: #7 Functions and Arrays

//* 
//* 
//* 
//* 
//* 
//* 
//* 
//* 
//* 

void countPositiveNegative(int arr[], int n, int target[])
{
	for (size_t i = 0; i < n; i++)
	{
		if (arr[i] > 0) {
			target[0]++;
		}
		else if (arr[i]<0) {
			target[1]++;
		}
		else if (arr[i]==0) {
			target[2]++;
		}
	}
}

void rotateRight(int arr[], int n) {
	int temp = arr[n-1];
	for (size_t i = n-1; i > 0; i--)
	{
		arr[i] = arr[i-1];
	}
	arr[0] = temp;
	
}

int countNonAlpha(std::string input) {
	int counter = 0;
	for (size_t i = 0; i < input.size(); i++)
	{
		if (!(input[i]==32 || (input[i]>=65 && input[i]<=90)|| (input[i]>=97 && input[i]<=122))) {
			counter++;
		}
	}
	return counter;
}

int deleteZeros(int arr[], int n) {
	int output = 0;
	for (size_t i = 0; i < n; i++)
	{
		if (arr[i] == 0) {
			while (arr[i+output] == 0) {
				output++;
			}
		}
		// std::cout << i << "," << arr[i] << "," << arr[i+output] << std::endl;
		arr[i] = arr[i+output];
	}
	for (size_t i = n-output; i < n; i++)
	{
		arr[i] = 0;
	}
	return output;
}

int reverseCase(std::string input) {
	int output;
	for (size_t i = 0; i < input.size(); i++)
	{
		if (input[i] <= 90 && input[i] >=65) {
			input[i]+=32;
			output++;
		}
		else if (input[i] <= 122 && input[i] >=97) {
			input[i]-=32;
			output++;
		}
	}
	return output;
}

int main(void)
{
	int input[] = {-3,-2,-1,0,0,0,1,2,3,4};
	size_t sizeinput = sizeof(input)/sizeof(int);
	std::string string = "0123abcd: HeyOitsME.?";
	int output[3] = {0};
	int intout;

	countPositiveNegative(input,sizeinput,output);
	std::cout << "Testing countPositiveNegative\n";
	for (size_t i = 0; i < 3; i++)
	{
		std::cout << output[i] << " ";
	}
	std::cout << std::endl << std::endl;

	std::cout << "Testing rotateRight\n";
	rotateRight(input, sizeinput);
	for (size_t i = 0; i < sizeinput; i++)
	{
		std::cout << input[i] << " ";
	}
	std::cout << std::endl << std::endl;

	std::cout << "Testing countNonAlpha\n";
	intout = countNonAlpha(string);
	std::cout << intout;
	std::cout << std::endl << std::endl;

	std::cout << "Testing deleteZeros\n";
	intout = deleteZeros(input,sizeinput);
	std::cout << "Changed " << intout << " zeros.\n";
	for (size_t i = 0; i < sizeinput; i++)
	{
		std::cout << input[i] << " ";
	}
	std::cout << std::endl << std::endl;

	std::cout << "Testing reverseCase\n";
	intout = reverseCase(string);
	std::cout << "Changed " << intout << " letters" << std::endl;
	std::cout << string << std::endl;
	std::cout << std::endl << std::endl;
	return 0;
}
