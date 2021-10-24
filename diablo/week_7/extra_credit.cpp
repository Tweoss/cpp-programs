// Write a program that reads an integer, a list of words, and a character. The integer signifies how many words are in the list. The output of the program is every word in the list that contains the character at least once. Assume at least one word in the list will contain the given character.

// Ex: If the input is:

// 4 hello zoo sleep drizzle z
// then the output is:

// zoo
// drizzle
// To achieve the above, first read the list into a vector. Keep in mind that the character 'a' is not equal to the character 'A'.

#include <iostream>
#include <vector>
#include <string.h>

bool contains_char(std::string word, char b);
void which_words(std::vector<std::string> words, char b, std::vector<bool>& results);
std::vector<std::string> split_string(char * input);
void print_words(std::vector<std::string> words, std::vector<bool> indices);

bool contains_char(std::string word, char b) {
	for (int i = 0; i < word.length(); i++) {
		if (word[i] == b) {
			return true;
		}
	}
	return false;
}

void which_words(std::vector<std::string> words, char b, std::vector<bool>& results) {
	for (int i = 0; i < words.size(); i++) {
		if (contains_char(words[i], b)) {
			results[i] = true;
		}
	}
}

std::vector<std::string> split_string(std::string input) {
	std::vector<std::string> words;
	std::string word = "";
	for (int i = 0; i < input.length(); i++) {
		if (input[i] == ' ') {
			words.push_back(word);
			word = "";
		}
		else {
			word += input[i];
		}
	}
	words.push_back(word);
	return words;
}

void print_words(std::vector<std::string> words, std::vector<bool> indices) {
	for (int i = 0; i < indices.size(); i++) {
		if (indices[i]) {
			std::cout << words[i] << std::endl;
		}
	}
}

int main() {
	std::cout << "Enter input:\n";
	std::string input;
	std::getline(std::cin, input);
	std::vector<std::string> words = split_string(input);
	char b = words.back().at(0);
	words.pop_back();
	// first number is irrelevant by nature of data input
	words.erase(words.begin());
	std::vector<bool> results(words.size(), false);
	which_words(words, b, results);
	print_words(words, results);
	return 0;
}