# SmartSales Tracker

## Project Overview

SmartSales Tracker is a C++ console application designed to help users manage and analyze sales data efficiently. It allows users to add new sales, view monthly and yearly summaries, and search or delete records. The program reads and writes data to a file, keeping everything saved between uses.

This project demonstrates core C++ concepts such as:
- Classes and Object-Oriented Programming
- File Streams (I/O)
- Recursion (used in input validation)
- Searching Algorithms (searching by customer, product, or date)

---

## Features

- Add new sales (customer name, product, date, amount)
- View monthly and yearly summaries
- Product and date-wise breakdown of totals
- Search for sales using keywords (customer/product/date)
- Delete specific sales
- Export summaries to external `.txt` files

---

## Key Requirements Implemented

| Requirement              | How It Was Met                                                                 |
|--------------------------|---------------------------------------------------------------------------------|
| Streams                  | Used `ifstream` and `ofstream` to load and save sales to files (`SALE_data.txt`) |
| Classes                  | `Sale` and `SalesTracker` classes manage individual sales and overall logic     |
| Recursion                | Used in error handling functions (like invalid input loops)                     |
| Searching Algorithms     | Case-insensitive search by keyword across customer, product, and date fields    |

---

## File Structure

| File                | Description                                                                 |
|---------------------|-----------------------------------------------------------------------------|
| `main.cpp`          | Contains the main menu and program flow                                     |
| `Sale.h/.cpp`       | Defines the `Sale` class, representing individual sale entries              |
| `SalesTracker.h/.cpp` | Handles all operations like adding sales, summaries, searching, and saving|

---

## How to Use

1. Compile the code using any C++ IDE or `g++`.
2. Run the program and use the numbered menu to:
   - Add new sale records
   - View monthly or yearly summaries
   - Manage and delete sales
3. Export summaries as text files when prompted.

---

## Sample Data File

All sales are saved in a file named:  
SALE_data.txt

Each sale entry looks like this:
John Doe, Car Wash,03/15/2025,20.50


---

## Credits

Created by Abdullah Nadvi, Michael Harwich, Ryan W.G. Trice
 
Project for COMPSCI-2 (Final Project)


