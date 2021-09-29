## Understand the difference between arrays and vectors

Arrays and vectors are fundamentally a form of memory access, just as loops are fundamentally a form of jumping around in instructions. 

In terms of implementation differences, arrays can be stack-allocated (where a typical variable would reside) or heap-allocated (where large or dynamically allocated variables ought to be stored). Vectors are heap-allocated, with a pointer to their location stored on the stack. Vectors also contain a (somewhat) hidden value for its length, meaning there is an extremely small additional overhead associated with using vectors. 

In terms of usage, arrays are less used simply because the large lists of value in programming typically have varying length. Vectors, by virtue of retaining a length attribute, can have bounds checking for memory access and raise errors instead of resulting in undefined behavior (when accessing memory out of bounds). 

We can implement both arrays and vectors using dynamic memory allocation. Both structures boil down to memory access, as is demonstrated by the following example. 

```cpp
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
```

Here is some sample output:
```
Enter 3 elements: 
1
2
3
The elements are: 
1
2
3
2020
2021
```