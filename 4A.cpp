#include <iostream>
using namespace std;
// ASSIGNMENT: Buy Stocks
int main(){
	//user input price
	float stockprice;
	//user input quantity
	int stockquantity;
	//user input account balance
	float money;

	//Start User Input
	cout << "Welcome to my stock purchase program.";
	cout << "Enter the quantity of the stock to be bought: ";
	cin >> stockquantity;
	cout << "Enter the price of the stock to be bought: ";
	cin >> stockprice;
	cout << "How much money is currently available: ";
	cin >> money;
	//End User Input

	//the money that WOULD be left after purchase
	float remainder = money-stockprice*(float) stockquantity;
	//Output Results
	if (remainder < 0.) {
		printf("Your fund is not sufficient, needs %.2f more dollars.\n", -remainder);
	}
	else {
		printf("Congratulations, you have purchased %d shares.\nYour fund now contains $%.2f.\n",stockquantity,remainder);
	}
  	return 0;
}