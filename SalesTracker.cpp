// --- SalesTracker.cpp ---
// This file will implement the SalesTracker class methods.

#include "SalesTracker.h"
#include <fstream>
#include <iostream>
#include <iomanip>  // for setprecision
#include <map>      // for storing sales by date
#include <sstream>
#include <vector>
#include <algorithm> // for sort and lowercase transform
using namespace std;

// Adds a sale to the internal list
void SalesTracker::addSale(const Sale &sale) {
	sales.push_back(sale);
}

// Loads sales from a file
void SalesTracker::loadSalesFromFile(const string &filename) {
	ifstream infile(filename);
	if (!infile) {
		cout << "No existing sales file found." << endl;
		return;
	}

	string line;
	while (getline(infile, line)) {
		if (line.empty() || line.find("===") != string::npos)
			continue;

		stringstream ss(line);
		string cName, product, date, amountStr;
		double amount;

		getline(ss, cName, ',');
		getline(ss, product, ',');
		getline(ss, date, ',');
		getline(ss, amountStr, ',');

		amount = stod(amountStr);

		sales.emplace_back(cName, product, date, amount);
	}
	infile.close();
}

// Saves all sales to a file
void SalesTracker::saveSalesToFile(const string &filename) const {
	ofstream outfile(filename);

	for (const auto &sale : sales) {
		outfile << sale.getCustomerName() << "," << sale.getProduct() << ","
		        << sale.getDate() << "," << sale.getAmount() << endl;
	}

	outfile.close();
}

//////////////////////// display monthly summary ////////////////////////

void SalesTracker::displayMonthlySummary(const string &monthYear) const {
	string monthNum = monthYear.substr(0, 2);
	string yearNum = monthYear.substr(3, 4);

	string monthName;
	if (monthNum == "01") monthName = "January";
	else if (monthNum == "02") monthName = "February";
	else if (monthNum == "03") monthName = "March";
	else if (monthNum == "04") monthName = "April";
	else if (monthNum == "05") monthName = "May";
	else if (monthNum == "06") monthName = "June";
	else if (monthNum == "07") monthName = "July";
	else if (monthNum == "08") monthName = "August";
	else if (monthNum == "09") monthName = "September";
	else if (monthNum == "10") monthName = "October";
	else if (monthNum == "11") monthName = "November";
	else if (monthNum == "12") monthName = "December";
	else monthName = "Unknown";

	cout << "\n=========================================" << endl;
	cout << "         Monthly Summary: " << monthName << " " << yearNum << endl;
	cout << "=========================================\n" << endl;

	double total = 0;
	map<string, double> dayTotals;
	map<string, vector<Sale>> salesByDate;
	map<string, double> productTotals; // <-- NEW: to store product totals

	for (const auto &sale : sales) {
		string month = sale.getDate().substr(0, 2);
		string year = sale.getDate().substr(6, 4);
		string saleMonthYear = month + "/" + year;

		if (saleMonthYear == monthYear) {
			salesByDate[sale.getDate()].push_back(sale);
			total += sale.getAmount();
			dayTotals[sale.getDate()] += sale.getAmount();
			productTotals[sale.getProduct()] += sale.getAmount(); // NEW
		}
	}

	if (salesByDate.empty()) {
		cout << "No sales found for this month.\n";
		return;
	}

	stringstream summaryStream;
	summaryStream << "Monthly Summary: " << monthName << " " << yearNum << "\n";
	summaryStream << "-------------------------\n\n";

	for (const auto &entry : salesByDate) {
		cout << "========== " << entry.first << " ==========" << endl;
		summaryStream << "========== " << entry.first << " ==========\n";

		for (const auto &sale : entry.second) {
			cout << "- " << sale.getCustomerName()
			     << " (" << sale.getProduct()
			     << ") - $" << fixed << setprecision(2) << sale.getAmount() << endl;

			summaryStream << "- " << sale.getCustomerName()
			              << " (" << sale.getProduct()
			              << ") - $" << fixed << setprecision(2) << sale.getAmount() << "\n";
		}

		cout << "    Total: $" << fixed << setprecision(2) << dayTotals[entry.first] << "\n";
		cout << endl;
		summaryStream << "    Total: $" << fixed << setprecision(2) << dayTotals[entry.first] << "\n\n";
	}

	// Product Totals section
	cout << "-----------------------------------------\n";
	cout << "Product Totals:\n";
	summaryStream << "-----------------------------------------\n";
	summaryStream << "Product Totals:\n";

	for (const auto &product : productTotals) {
		cout << "  - " << product.first << ": $" << fixed << setprecision(2) << product.second << endl;
		summaryStream << "  - " << product.first << ": $" << fixed << setprecision(2) << product.second << "\n";
	}

	string bestDay;
	double bestDayAmount = 0;
	for (const auto &day : dayTotals) {
		if (day.second > bestDayAmount) {
			bestDayAmount = day.second;
			bestDay = day.first;
		}
	}

	cout << "\n-----------------------------------------\n";
	cout << "Total Sales: $" << fixed << setprecision(2) << total << endl;
	cout << "Best Day: " << bestDay << " ($" << fixed << setprecision(2) << bestDayAmount << ")" << endl;
	cout << "=========================================\n";

	summaryStream << "\n-----------------------------------------\n";
	summaryStream << "Total Sales: $" << fixed << setprecision(2) << total << "\n";
	summaryStream << "Best Day: " << bestDay << " ($" << fixed << setprecision(2) << bestDayAmount << ")\n";

	//////////////////// Ask to export////////////////////////////////////
	cout << "\nWould you like to export this monthly summary to a file? (Y/N): ";
	char exportChoice;
	cin >> exportChoice;

	if (exportChoice == 'Y' || exportChoice == 'y') {
		string filename = "summary" + monthNum + "_" + yearNum + ".txt"; // name the fil

		ofstream outFile(filename);
		if (outFile) {
			outFile << summaryStream.str();
			outFile.close();
			cout << "\nSummary exported successfully to " << filename << "!\n";
		} else {
			cout << "\nFailed to export summary.\n";
		}
	}
}


//////////////////////// display yearly summary ////////////////////////

void SalesTracker::displayYearlySummary(const string &year) const {
	cout << "\n=========================================" << endl;
	cout << "            Yearly Summary: " << year << endl;
	cout << "=========================================\n" << endl;

	double total = 0;
	map<string, double> monthTotals;
	map<string, double> productTotals;

	for (const auto &sale : sales) {
		string saleYear = sale.getDate().substr(6, 4);
		if (saleYear == year) {
			string month = sale.getDate().substr(0, 2);
			monthTotals[month] += sale.getAmount();
			productTotals[sale.getProduct()] += sale.getAmount();
			total += sale.getAmount();
		}
	}

	if (monthTotals.empty()) {
		cout << "No sales found for this year.\n";
		return;
	}

	const string months[12] = {"01", "02", "03", "04", "05", "06",
	                           "07", "08", "09", "10", "11", "12"
	                          };
	const string monthNames[12] = {
		"January", "February", "March", "April", "May", "June",
		"July", "August", "September", "October", "November", "December"
	};

	cout << "Month Totals:\n-----------------------------------------\n";
	stringstream summaryStream;
	summaryStream << "Yearly Summary: " << year << "\n";
	summaryStream << "-------------------------\n\n";

	for (int i = 0; i < 12; ++i) {
		if (monthTotals.find(months[i]) != monthTotals.end()) {
			cout << "  " << monthNames[i] << ": $" << fixed << setprecision(2)
			     << monthTotals[months[i]] << endl;
			summaryStream << monthNames[i] << ": $" << fixed << setprecision(2)
			              << monthTotals[months[i]] << "\n";
		}
	}

	cout << "\nProduct Totals:\n-----------------------------------------\n";
	summaryStream << "\n-------------------------\n";
	summaryStream << "Total Sales by Product:\n";

	for (const auto &product : productTotals) {
		cout << "  " << product.first << ": $" << fixed << setprecision(2)
		     << product.second << endl;
		summaryStream << "- " << product.first << ": $" << fixed << setprecision(2)
		              << product.second << "\n";
	}

	string bestMonth;
	double bestMonthAmount = 0;
	for (const auto &entry : monthTotals) {
		if (entry.second > bestMonthAmount) {
			bestMonthAmount = entry.second;
			bestMonth = entry.first;
		}
	}

	string bestMonthName = bestMonth;
	for (int i = 0; i < 12; ++i) {
		if (bestMonth == months[i]) {
			bestMonthName = monthNames[i];
			break;
		}
	}

	cout << "\nSummary:\n-----------------------------------------\n";
	cout << "  Total Sales: $" << fixed << setprecision(2) << total << endl;
	cout << "  Best Month: " << bestMonthName << " ($" << fixed << setprecision(2)
	     << bestMonthAmount << ")" << endl;
	cout << "=========================================\n";

	summaryStream << "\n-------------------------\n";
	summaryStream << "Total Sales: $" << fixed << setprecision(2) << total << "\n";
	summaryStream << "Best Month: " << bestMonthName << " ($" << fixed << setprecision(2)
	              << bestMonthAmount << ")\n";




	/////////Ask to export////////////
	cout << "\nWould you like to export this yearly summary to a file? (Y/N): ";
	char exportChoice;
	cin >> exportChoice;

	if (exportChoice == 'Y' || exportChoice == 'y') {
		string filename = "summary_" + year + ".txt";

		ofstream outFile(filename);
		if (outFile) {
			outFile << summaryStream.str();
			outFile.close();
			cout << "\nSummary exported successfully to " << filename << "!\n";
		} else {
			cout << "\nFailed to export summary.\n";
		}
	}
}

//////////////////////// manage sales ////////////////////////

void SalesTracker::manageSales() {
	cout << "\n=========================================" << endl;
	cout << "             Manage Sales" << endl;
	cout << "=========================================\n" << endl;

	cout << "Enter search term (customer name, product, or date): ";

	string searchTerm;
	cin.ignore();
	getline(cin, searchTerm);

	transform(searchTerm.begin(), searchTerm.end(), searchTerm.begin(), ::tolower);

	vector<int> matchingIndexes;

	for (int i = 0; i < sales.size(); ++i) {
		string customer = sales[i].getCustomerName();
		string product = sales[i].getProduct();
		string date = sales[i].getDate();

		transform(customer.begin(), customer.end(), customer.begin(), ::tolower);
		transform(product.begin(), product.end(), product.begin(), ::tolower);
		transform(date.begin(), date.end(), date.begin(), ::tolower);

		if (customer.find(searchTerm) != string::npos ||
		        product.find(searchTerm) != string::npos ||
		        date.find(searchTerm) != string::npos) {
			matchingIndexes.push_back(i);
		}
	}

	if (matchingIndexes.empty()) {
		cout << "\nNo sales found matching your search.\n";
		return;
	}

	cout << "\n=========================================" << endl;
	cout << "             Search Results" << endl;
	cout << "=========================================\n" << endl;

	for (int i = 0; i < matchingIndexes.size(); ++i) {
		int idx = matchingIndexes[i];
		cout << i + 1 << ". "
		     << sales[idx].getDate() << " - "
		     << sales[idx].getCustomerName() << " ("
		     << sales[idx].getProduct() << ") - $"
		     << fixed << setprecision(2) << sales[idx].getAmount() << endl;
		cout << endl;
	}

	cout << "=========================================\n" << endl;

	cout << "Select a sale number to delete (0 to cancel): ";
	int choice;
	cin >> choice;

	if (choice == 0) {
		cout << "Cancelled.\n";
		return;
	}

	if (choice < 1 || choice > matchingIndexes.size()) {
		cout << "Invalid selection.\n";
		return;
	}

	int deleteIndex = matchingIndexes[choice - 1];

	cout << "Are you sure you want to delete this sale? (Y/N): ";
	char confirm;
	cin >> confirm;

	if (confirm == 'Y' || confirm == 'y') {
		sales.erase(sales.begin() + deleteIndex);
		saveSalesToFile("sales_2025.txt"); // <-- update filename if needed
		cout << "Sale deleted successfully!\n";
	} else {
		cout << "Deletion cancelled.\n";
	}
}
