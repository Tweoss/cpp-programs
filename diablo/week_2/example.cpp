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