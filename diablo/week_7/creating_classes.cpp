#include <iostream>
#include <vector>
#include <string.h>

// Create a class called
// Invoice that a hardware store might use to
// represent an invoice for an item sold at the
// store. An Invoice should include four data
// members—a part number (type string), a
// part description (type string), a quantity of
// the item being purchased (type int) and a
// price per item (type int)
class Invoice {
public:
	Invoice(std::string part_number, std::string part_description, int quantity, int price_per_item) {
		this->part_number = part_number;
		this->part_description = part_description;
		this->quantity = quantity;
		this->price_per_item = price_per_item;
	}

	std::string getPartNumber() {
		return this->part_number;
	}

	std::string getPartDescription() {
		return this->part_description;
	}

	int getQuantity() {
		return this->quantity;
	}

	int getPricePerItem() {
		return this->price_per_item;
	}

	void setPartNumber(std::string part_number) {
		this->part_number = part_number;
	}

	void setPartDescription(std::string part_description) {
		this->part_description = part_description;
	}

	void setQuantity(int quantity) {
		this->quantity = quantity;
	}

	void setPricePerItem(int price_per_item) {
		this->price_per_item = price_per_item;
	}

	int getInvoiceAmount() {
		int out = this->quantity * this->price_per_item;
		if (out < 0) {
			out = 0;
			std::cout << "quantity cannot be negative. quantity set to 0.";
		}
		return out;
	}

private:
	std::string part_number;
	std::string part_description;
	int quantity;
	int price_per_item;
};

// In addition, provide a member function named getInvoiceAmount that calculates the invoice
// amount (i.e., multiplies the quantity by the price per item), then returns the amount as an int
// value. If the quantity is not positive, it should be set to 0. If the price per item is not positive, it
// should be set to 0. Write a test program that demonstrates class Invoice’s capabilities.

int main() {
	std::cout << "Example output\n";
	Invoice invoice("123", "Laptop", 2, 100);
	std::cout << "Part number: " << invoice.getPartNumber() << std::endl;
	std::cout << "Part description: " << invoice.getPartDescription() << std::endl;
	std::cout << "Quantity: " << invoice.getQuantity() << std::endl;
	std::cout << "Price per item: " << invoice.getPricePerItem() << std::endl;
	std::cout << "Invoice amount: " << invoice.getInvoiceAmount() << std::endl;

	std::cout << "Taking input\n";
	std::string part_number;
	std::string part_description;
	int quantity;
	int price_per_item;
	std::cout << "Part number: ";
	std::cin >> part_number;
	std::cout << "Part description: ";
	std::cin >> part_description;
	std::cout << "Quantity: ";
	std::cin >> quantity;
	std::cout << "Price per item: ";
	std::cin >> price_per_item;
	Invoice invoice2(part_number, part_description, quantity, price_per_item);
	std::cout << "Part number: " << invoice2.getPartNumber() << std::endl;
	std::cout << "Part description: " << invoice2.getPartDescription() << std::endl;
	std::cout << "Quantity: " << invoice2.getQuantity() << std::endl;
	std::cout << "Price per item: " << invoice2.getPricePerItem() << std::endl;
	std::cout << "Invoice amount: " << invoice2.getInvoiceAmount() << std::endl;

	
	return 0;
}