// For this lab, you will write a program
// which will include a minimum function
// and a maximum function. Both
// functions should take in three values.
// The minimum function should return the minimum of the three values and the
// maximum should return the maximum of the three values.
// The values should be entered by the user.

#include <iostream>

int minimum(int a, int b, int c);
int maximum(int a, int b, int c);

int minimum(int a, int b, int c)
{
	if (a < b && a < c)
	{
		return a;
	}
	else if (b < a && b < c)
	{
		return b;
	}
	else
	{
		return c;
	}
}

int maximum(int a, int b, int c)
{
	if (a > b && a > c)
	{
		return a;
	}
	else if (b > a && b > c)
	{
		return b;
	}
	else
	{
		return c;
	}
}
int main()
{
	int a, b, c;
	std::cout << "Enter three numbers: ";
	std::cin >> a >> b >> c;
	std::cout << "The minimum is " << minimum(a, b, c) << std::endl;
	std::cout << "The maximum is " << maximum(a, b, c) << std::endl;
	return 0;
}