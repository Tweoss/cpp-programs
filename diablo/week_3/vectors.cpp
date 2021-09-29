#include <iostream>
#include <vector>

// Prompt user for 12 weights.
// Store in a vector of doubles
// Print the vector
// Print total weight
// Print Average weight
// Print max weight
int main() {
	std::vector<double> weights;
	double weight;
	double total = 0;
	double average;
	double max = 0;
	for (int i = 0; i < 12; i++) {
		std::cout << "Enter weight: ";
		std::cin >> weight;
		std::cout << weight << std::endl;
		weights.push_back(weight);
		total += weight;
		if (weight > max) {
			max = weight;
		}
	}
	average = total / 12;
	std::cout << "You entered: ";
	for (int i = 0; i < 12; i++) {
		std::cout << weights[i] << " ";
	}
	std::cout << std::endl << std::endl;
	std::cout << "Total weight: " << total << std::endl;
	std::cout << "Average weight: " << average << std::endl;
	std::cout << "Max weight: " << max << std::endl;
	return 0;
}
