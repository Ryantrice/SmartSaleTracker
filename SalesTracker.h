// --- SalesTracker.h ---
// SalesTracker class manages all sales by adding new entries,
//loading and saving data from a file, displaying monthly and yearly
//summaries with product totals, and allowing searches or deletions.

#ifndef SALESTRACKER_H
#define SALESTRACKER_H

#include "Sale.h"
#include <string>
#include <vector> // to store a list of sales

const std::string SALES_FILENAME =
    "SALE_data.txt"; // file name to store sales data give you the ability to
// change the file name easily.

class SalesTracker {
private:
	std::vector<Sale> sales; // vector to store sales

public:
	void addSale(const Sale &sale); // add a sale to the list

	void loadSalesFromFile(const std::string &filename); // load sales from a file

	void
	saveSalesToFile(const std::string &filename) const; // save sales to a file

	void displayMonthlySummary(
	    const std::string &monthYear) const; // display monthly sales

	void
	displayYearlySummary(const std::string &year) const; // display yearly sales

	void manageSales(); // mange sales ( search delete, update)
};
#endif
