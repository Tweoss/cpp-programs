#include <iostream>
#include <vector>
#include <stdlib.h>

// Receives a pointer to the pointer to the first element of the vector
// and the size of the vector.
// Returns the new length
int push_back(int **array, int *size, int value)
{
	if (*size == 0)
	{
		*array = (int *)malloc(sizeof(int));
		(*array)[0] = value;
		size += 1;
		return *size;
	}
	*size += 1;
	*array = (int *)realloc(*array, *size * sizeof(int));
	(*array)[*size - 1] = value;
	return *size;
}

int main()
{
	int size = 3;
	int i, n;
	int *buffer;

	buffer = (int *)malloc(i);
	if (buffer == NULL)
		exit(1);

	std::cout << "Enter 3 elements: \n";
	// Setting the values
	for (i = 0; i < size; i++)
	{
		std::cin >> n;
		// buffer[i] = n; as an array
		// buffer.at(i); as a vector
		*(buffer + i) = n;
	}

	// Resizing
	// 
	// Like a vector, can resize
	// buffer.resize(size + 1);
	buffer = (int *)realloc(buffer, (size + 1) * sizeof(int));
	size += 1;
	// capable of using array notation
	buffer[size - 1] = 2020;
	
	// Like a vector can push_back
	// buffer.push_back(n);
	push_back(&buffer, &size, 2021);

	std::cout << "The elements are: \n";
	// Like an array or vector, can get the values using array notation
	// We could also run bounds checking here using the size variable
	for (i = 0; i < size; i++)
	{
		std::cout << buffer[i] << std::endl;
	}
	free(buffer);
}