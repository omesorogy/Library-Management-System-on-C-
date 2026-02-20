# Library-Management-System-on-C++

# Library Management System

A C++ library management system with a menu-driven interface for managing books, magazines, DVDs, patrons, and transactions.

## Compilation

```bash
g++ -std=c++17 UI.cpp -o LibrarySystem
```

## Running the Program

```bash
./LibrarySystem
```

## Main Features

- **Add Items**: Add books, magazines, and DVDs to the library
- **Add Patrons**: Register students and faculty members
- **Checkout Items**: Borrow items with automatic due dates
- **Return Items**: Return items and calculate late fees
- **Search**: Find items by title, author, genre, or type
- **View Inventory**: See all available items
- **Check Overdue**: View overdue items and fines
- **Patron History**: Track borrowing history for each patron

## Menu Navigation

1. Select options from the main menu (1-9)
2. Follow prompts to enter information
3. View results and confirmations
4. Return to main menu to continue

## Sample Data Included

The program comes pre-loaded with:
- 4 books
- 2 magazines  
- 2 DVDs
- 3 students
- 2 faculty members

## File Overview

- **MainFile.cpp** - Core library classes and logic
- **UI.cpp** - Menu interface and user interaction

Late fees: Books $0.50/day, Magazines $0.25/day, DVDs $1.00/day
