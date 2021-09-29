#include <iostream>
#include <string>
#include <vector>
#include <math.h> 

const double GALLON_TO_FEET = 350.0;

// Enter wall height (feet): 12.0
// Enter wall width (feet): 15.0
// Wall area: 180 square feet
// Paint needed: 0.514286 gallons
// Cans needed: 1 can(s)

// Prompt the user to input a wall's height and width. Calculate and output the wall's area.
// Extend to also calculate and output the amount of paint in gallons needed to paint the wall. Assume a gallon of paint covers 350 square feet. Store this value using a const double variable.
// Extend to also calculate and output the number of 1 gallon cans needed to paint the wall. Hint: Use a math function to round up to the nearest gallon.


double wall_area(double height, double width) {
	return height * width;
}

double paint_needed(double wall_area, const double paint_per_gallon) {
	return wall_area / paint_per_gallon;
}

// rounds up paint_needed in gallons
int cans_needed(double paint_needed) {
	return ceil(paint_needed);
}


bool run_test() {
	double wall_height = 2.0;
	double wall_width = 3.0;
	double area = wall_area(wall_height, wall_width);
	double needed = paint_needed(area, GALLON_TO_FEET);
	int cans = cans_needed(needed);
	return area == 6.0 && needed == 2.0 * 3.0 / 350.0 && cans == 1;
}

int main(int argc, char *argv[])
{
	if (argc == 2 && argv[1] == std::string("test")) {
		if (run_test() ) {
			std::cout << "All tests passed" << std::endl;
			return 0;
		}
		std::cout << "Tests Failed" << std::endl;
		return 1;
	}
	double height = 0.0;
	double width = 0.0;
	std::cout << "Input the height in feet: ";
	std::cin >> height;
	std::cout << "Input the width in feet: ";
	std::cin >> width;
	std::cout << "Wall area: " << wall_area(height, width) << " square feet." << std::endl;
	std::cout << "Paint needed: " << paint_needed(wall_area(height, width), GALLON_TO_FEET) << " gallons." << std::endl;
	std::cout << "Cans needed: " << cans_needed( paint_needed(wall_area(height, width), GALLON_TO_FEET)) << " cans." << std::endl;
	return 0;
}
