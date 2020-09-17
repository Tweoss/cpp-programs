#include <fstream>
using namespace std;
#include <sstream>
std::string line;

int main() {
    int sum = 0;
    int x;
    
    ifstream inFile;
    inFile.open("test.txt");
	double value;

	if (std::getline(inFile, line))
	{
	std::istringstream iss(line);
	while (iss >> value) { printf("%f ",value); }
	}
	if (std::getline(inFile, line))
	{
	std::istringstream iss(line);
	while (iss >> value) { printf("%f ",value); }
	}
}
