/*

Francis Chua

Recursion

10/31/2021

*/

//  implementing your own version of a "guess the number" game.  Your implementation must include a binary search (recursive) algorithm.

#include <iostream>

int binary_search(int low, int high, int true_value, bool print)
{
    int guess = (low + high) / 2;
    if (print)
    {
        std::cout << "low: " << low << " high: " << high << " guess: " << guess << std::endl;
    }
    if (guess == true_value)
    {
        return guess;
    }
    else if (guess < true_value)
    {
        return binary_search(guess + 1, high, true_value, print);
    }
    else
    {
        return binary_search(low, guess - 1, true_value, print);
    }
}

int main(int argc, char const *argv[])
{
    int max = 0, min = 0, value = 0;
    std::cout << "Enter the min: ";
    std::cin >> min;
    std::cout << "Enter the max: ";
    std::cin >> max;
    std::cout << "Enter the true value: ";
    std::cin >> value;
    if (value < min || value > max)
    {
        std::cout << "The value is not in the range" << std::endl;
        return 1;
    }

    binary_search(min, max, value, true);

    return 0;
}
