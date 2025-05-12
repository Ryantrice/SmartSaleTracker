/*
* Developers: Abdulla Nadvi ,Michael Harwich, Ryan Trice
* Title: Sales tracker v.2.0.
* Function: tracks and stores sales values, customer names, and dates of purchase in text files,
* and reads them out to user, as well as exporting data to other files
*/


#include <iostream>
#include <iomanip>
#include "SalesTracker.h"
using namespace std;

void spacing();
void error_Invalid_input(int num_needed, string& input);


int main() {

	cout <<setw(45)<<right <<"=======INSTRUCTIONS======="<<endl;

	cout << endl;

	cout << setw(70) <<right << setfill('=')<<" "<<endl;

	cout << setw(12) <<right<<
	     R"(
        Choose between numbers 1 through 5 and fill in
    data to be saved as shown in examples along side the prompts
     other wise, choose option 4 and delete the wrong data. )"<<endl;

	cout << endl;

	cout << setw(70) <<right << setfill('=')<<" "<<endl;

	SalesTracker tracker;  // Create an instance of SalesTracker

	tracker.loadSalesFromFile(
	    SALES_FILENAME);  // Load existing sales data from file

	int choice;          // User's menu choice

	do {
		cout << endl;
		// Display the main menu
		cout << setw(49) << setfill('=') << " SmartSales Tracker Menu =============" << endl;
		cout << "     * 1. Add Sale\n";
		cout << "     * 2. Monthly Summary\n";
		cout << "     * 3. Yearly Summary\n";
		cout << "     * 4. Manage Sales\n";
		cout << "     * 5. Exit\n";
		spacing();
		cout << "Enter your choice: ";

		cin >> choice;  //intake user integer for choice of function
		spacing();//function designed to add spacing and visual seperation between each inout and section

		if (choice == 1) {
			// Add a new sale
			string name, product, date;
			double amount;

            cout << " Enter customer by full name. \n";
            cout << " EXAMPLE:"<<"\033[31mJhon Smith\033[0m"<<endl;//section gives example 
			cout << "Enter customer name: ";
			cin.ignore(); // Clear the newline from the buffer
			getline(cin, name);

			spacing();
			
            cout <<"Insert name of product. \n";
            cout <<"EXAMPLE:"<<"\033[31mOIL\033[0m"<<endl;//section gives example 
			cout << "Enter product name: ";
			
			getline(cin, product);

			spacing();

			cout << "Enter date in of purchase in (MM/DD/YYYY) format \n";
			cout<<"EXAMPLE:"<<"\033[31m04/12/2024\033[0m"<<" for"<<" \033[36mApril 12th, 2024\033[0m\n"<<endl;//section gives example 
			cout<< "for simplicity sake,"<< "\033[31;1m add back slashes /\033[0m \n"<<endl;
			
			cout<< "Enter calender date of purchase: ";
			getline(cin, date);//get string equal to that of the date
			
          spacing();
          
            error_Invalid_input(10, date);



			cout << " Enter dollar amount equal to price paid, inluding cents if neccesary\n ";
			cout << " EXAMPLES :"<< "\033[31m' 12.24 ' or ' 34 ' \033[0m"<<endl;
			cout << " Enter dollar ammount: ";
			cin >> amount;

			// Add the sale to the tracker
			tracker.addSale(Sale(name, product, date, amount));
			tracker.saveSalesToFile(SALES_FILENAME); // Save updated sales to file

		}
		else if (choice == 2) {
		    
			// Display monthly summary
			string monthYear;
			cout << "Enter month and year (MM/YYYY): ";
			cin >> monthYear;
			
            error_Invalid_input(7, monthYear);
            
			tracker.displayMonthlySummary(monthYear);
            void spacing();
		}
		else if (choice == 3) {
			// Display yearly summary
			string year;
			cout << " Please Add all 4 digits of the year you wish to view the summary of \n"<<" EXAMPLE: "<<"\033[31m 2004\033[0m "<<endl;
			cout << " Enter year (YYYY): ";
			cin >> year;



			tracker.displayYearlySummary(year);
		
		}
		else if (choice == 4) {
			tracker.manageSales();
		
		}
		else if (choice == 5) {
		    void spacing();
			cout << "Thank you for using SmartSales Tracker!" << endl;
			
			break; // Exit the loop/program
		}
		else {
			cout << "Invalid choice. Please try again.\n";
		}

	} while (choice != 5); // Repeat until the user chooses to exit

	return 0;
}


void spacing(){
    cout << endl;
	cout << setw(49) <<"=\n" << endl;
	cout << endl;
}



void error_Invalid_input(int num_needed, string& input){
    if (input.length() != num_needed){
        
        cerr<<"Sorry, input is invalid, please input number with "<< num_needed <<" characters and numbers"<<endl;
        cout <<"Remember to add your zeros and backslashes to your dates! \n";
        
        cout<<"Re-enter: ";
        cin>>input;
        
        spacing();
        
        if (input.length() != num_needed){ error_Invalid_input( num_needed, input);}
        
         }//function that displays error message if input is more or less than needed digits, to avoid data issues and user error
    
}
