// --- Sale.h ---
//The Sale class represents individual sales, storing customer name, product, date, and amount
#ifndef SALE_H
#define SALE_H
#include <string>

// Define the Sale class
class Sale {
private:
	std::string customerName; // customer name
	std::string product;      // product or service
	std::string date;         // date of sale in MM/DD/YYYY format
	double amount;            // sale amount in dollars

public:
	Sale(std::string cName, std::string prod, std::string dt, double amt); // constructor to initialize a sale object (name, product, date, and  amount)

	std::string getCustomerName() const; // gettter for customer name
	std::string getProduct() const;      // getter for product or service
	std::string getDate() const;         // getter for  date of sale
	double getAmount() const;            // getter for sale amount in dollars

	std::string toFileString()
	const; // method to convert sale object to string for file storage
};
#endif
