## Understand the difference between a while loop and a for loop.

Loops come in a few forms, though all loop related control statements boil down to jumps. While loops evaluate a condition then jump if the condition is true. A for loop performs an initial statement then on each iteration evaluates a condition, performing a given statement then jumping if valid. 

Thus, all loops are simply syntactic sugar around conditional jumps and statements. In the following example, a while and an equivalent for loop are deconstructed into jump statements. 

```cpp
bool strange_function(double a) {
	return -0.01 * a * a * a * a + 0.5 * a * a * a - 2.0 * a * a + 0.3 * a - 2.0 > 0.0;
}
// while loop
double i = 5.0;
while (strange_function(i))
{
	std::cout << i << " ";
	i += 2.0;
}

// for loop
for (double j = 5.0; strange_function(j); j += 2.0)
{
	std::cout << j << " ";
}
// jump statement
double k = 5.0;
location:
if (strange_function(k))
{
	std::cout << k << " ";
	k += 2.0;
	goto location;
}
```

Here is a full program with all of the above

```cpp
#include <iostream>

bool strange_function(double a)
{
	return -0.01 * a * a * a * a + 0.5 * a * a * a - 2.0 * a * a + 0.3 * a - 2.0 > 0.0;
}

int main()
{
	double i = 5.0;
	while (strange_function(i))
	{
		std::cout << i << " ";
		i += 2.0;
	}
	std::cout << "\ni is now: " << i << std::endl;

	double temp;
	for (double j = 5.0; strange_function(j); j += 2.0)
	{
		std::cout << j << " ";
		temp = j;
	}
	std::cout << "\nj is now: " << temp << std::endl;

	double k = 5.0;
location:
	if (strange_function(k))
	{
		std::cout << k << " ";
		k += 2.0;
		goto location;
	}
	else {
		std::cout << "\nk is now: " << k << std::endl;
	}
}
```

and the output

```cpp
5 7 9 11 13 15 17 19 21 23 25 27 29 31 33 35 37 39 41 43 45 
i is now: 47
5 7 9 11 13 15 17 19 21 23 25 27 29 31 33 35 37 39 41 43 45 
j is now: 45
5 7 9 11 13 15 17 19 21 23 25 27 29 31 33 35 37 39 41 43 45 
k is now: 47
```
We can see from the final values that the final addition statement is not executed in the for statement but is in the others by the nature of the control flow. However, the major logic is completely identical, demonstrating that all loops are equal in power but their syntactic sugar may result in slightly different end results. 