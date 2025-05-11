//  --- Sale.cpp ---
// This file will implement the Sale class methods. okay
#include "Sale.h"
#include <iostream> // for pontential debugging
#include <sstream>  // for parsing date
using namespace std;

// Constructor for Sale class
Sale::Sale(string cName, string prod, string dt, double amt)
	: customerName(cName), product(prod), date(dt), amount(amt) {}

// Getter methods
string Sale::getCustomerName() const {
	return customerName;
} // getter for customer
string Sale::getProduct() const {
	return product;    // getter for product
}
string Sale::getDate() const {
	return date;    // getter for date
}
double Sale::getAmount() const {
	return amount;    // getter for amount
}

// convert sale to string for display
string Sale::toFileString() const {
	stringstream ss; // string stream to format the output
	ss << customerName << "," << product << "," << date << ","
	   << amount; // format the output
	return ss.str();
}