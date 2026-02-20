#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <cctype>
#include <algorithm>
#include "MainFile.cpp"

class LibraryUI {
private:
    Library library_;
    bool running_;
    
    // Helper functions
    std::string getUserInput(const std::string& prompt) {
        std::cout << prompt;
        std::string input;
        std::getline(std::cin, input);
        return input;
    }
    
    int getIntInput(const std::string& prompt) {
        std::string input = getUserInput(prompt);
        try {
            return std::stoi(input);
        } catch (...) {
            std::cout << "Invalid input. Please enter a number.\n";
            return -1;
        }
    }
    
    double getDoubleInput(const std::string& prompt) {
        std::string input = getUserInput(prompt);
        try {
            return std::stod(input);
        } catch (...) {
            std::cout << "Invalid input. Please enter a decimal number.\n";
            return -1.0;
        }
    }
    
    void displayMainMenu() {
        std::cout << "\n========================================\n";
        std::cout << "     LIBRARY MANAGEMENT SYSTEM\n";
        std::cout << "========================================\n";
        std::cout << "1. Add Item\n";
        std::cout << "2. Add Patron\n";
        std::cout << "3. Checkout Item\n";
        std::cout << "4. Return Item\n";
        std::cout << "5. Search Items\n";
        std::cout << "6. View Inventory\n";
        std::cout << "7. View Overdue Items\n";
        std::cout << "8. View Patron History\n";
        std::cout << "9. Exit\n";
        std::cout << "========================================\n";
    }
    
    void displayAddItemMenu() {
        std::cout << "\n--- Add Item ---\n";
        std::cout << "1. Add Book\n";
        std::cout << "2. Add Magazine\n";
        std::cout << "3. Add DVD\n";
        std::cout << "4. Back to Main Menu\n";
    }
    
    void displayAddPatronMenu() {
        std::cout << "\n--- Add Patron ---\n";
        std::cout << "1. Add Student\n";
        std::cout << "2. Add Faculty\n";
        std::cout << "3. Back to Main Menu\n";
    }
    
    void displaySearchMenu() {
        std::cout << "\n--- Search Items ---\n";
        std::cout << "1. Search by Title\n";
        std::cout << "2. Search by Author\n";
        std::cout << "3. Search by Genre\n";
        std::cout << "4. Search by Type\n";
        std::cout << "5. Back to Main Menu\n";
    }
    
    void addBook() {
        std::cout << "\n--- Add Book ---\n";
        std::string id = getUserInput("Enter Book ID: ");
        std::string title = getUserInput("Enter Title: ");
        std::string author = getUserInput("Enter Author: ");
        std::string isbn = getUserInput("Enter ISBN: ");
        std::string genre = getUserInput("Enter Genre: ");
        
        try {
            library_.addItem(std::make_unique<Book>(id, title, author, isbn, genre));
            std::cout << "✓ Book added successfully!\n";
        } catch (const std::exception& e) {
            std::cout << "✗ Error: " << e.what() << "\n";
        }
    }
    
    void addMagazine() {
        std::cout << "\n--- Add Magazine ---\n";
        std::string id = getUserInput("Enter Magazine ID: ");
        std::string title = getUserInput("Enter Title: ");
        std::string publisher = getUserInput("Enter Publisher: ");
        int issueNumber = getIntInput("Enter Issue Number: ");
        std::string publicationDate = getUserInput("Enter Publication Date (YYYY-MM-DD): ");
        
        try {
            library_.addItem(std::make_unique<Magazine>(id, title, publisher, issueNumber, publicationDate));
            std::cout << "✓ Magazine added successfully!\n";
        } catch (const std::exception& e) {
            std::cout << "✗ Error: " << e.what() << "\n";
        }
    }
    
    void addDVD() {
        std::cout << "\n--- Add DVD ---\n";
        std::string id = getUserInput("Enter DVD ID: ");
        std::string title = getUserInput("Enter Title: ");
        std::string director = getUserInput("Enter Director: ");
        int duration = getIntInput("Enter Duration (minutes): ");
        std::string releaseDate = getUserInput("Enter Release Date (YYYY-MM-DD): ");
        
        try {
            library_.addItem(std::make_unique<DVD>(id, title, director, duration, releaseDate));
            std::cout << "✓ DVD added successfully!\n";
        } catch (const std::exception& e) {
            std::cout << "✗ Error: " << e.what() << "\n";
        }
    }
    
    void handleAddItem() {
        while (true) {
            displayAddItemMenu();
            int choice = getIntInput("Select option: ");
            
            switch (choice) {
                case 1:
                    addBook();
                    break;
                case 2:
                    addMagazine();
                    break;
                case 3:
                    addDVD();
                    break;
                case 4:
                    return;
                default:
                    std::cout << "Invalid option. Please try again.\n";
            }
        }
    }
    
    void addStudent() {
        std::cout << "\n--- Add Student ---\n";
        std::string id = getUserInput("Enter Patron ID: ");
        std::string name = getUserInput("Enter Name: ");
        std::string contactInfo = getUserInput("Enter Contact Info (email): ");
        std::string studentId = getUserInput("Enter Student ID: ");
        std::string major = getUserInput("Enter Major: ");
        
        try {
            library_.addPatron(std::make_unique<Student>(id, name, contactInfo, studentId, major));
            std::cout << "✓ Student added successfully!\n";
        } catch (const std::exception& e) {
            std::cout << "✗ Error: " << e.what() << "\n";
        }
    }
    
    void addFaculty() {
        std::cout << "\n--- Add Faculty ---\n";
        std::string id = getUserInput("Enter Patron ID: ");
        std::string name = getUserInput("Enter Name: ");
        std::string contactInfo = getUserInput("Enter Contact Info (email): ");
        std::string department = getUserInput("Enter Department: ");
        std::string employeeId = getUserInput("Enter Employee ID: ");
        
        try {
            library_.addPatron(std::make_unique<Faculty>(id, name, contactInfo, department, employeeId));
            std::cout << "✓ Faculty added successfully!\n";
        } catch (const std::exception& e) {
            std::cout << "✗ Error: " << e.what() << "\n";
        }
    }
    
    void handleAddPatron() {
        while (true) {
            displayAddPatronMenu();
            int choice = getIntInput("Select option: ");
            
            switch (choice) {
                case 1:
                    addStudent();
                    break;
                case 2:
                    addFaculty();
                    break;
                case 3:
                    return;
                default:
                    std::cout << "Invalid option. Please try again.\n";
            }
        }
    }
    
    void checkoutItem() {
        std::cout << "\n--- Checkout Item ---\n";
        std::string itemId = getUserInput("Enter Item ID: ");
        std::string patronId = getUserInput("Enter Patron ID: ");
        
        try {
            auto checkout = library_.checkoutItem(itemId, patronId);
            std::cout << "\n✓ Item checked out successfully!\n";
            std::cout << checkout->getDetails() << "\n";
        } catch (const std::exception& e) {
            std::cout << "✗ Error: " << e.what() << "\n";
        }
    }
    
    void returnItem() {
        std::cout << "\n--- Return Item ---\n";
        std::string itemId = getUserInput("Enter Item ID: ");
        
        try {
            auto ret = library_.returnItem(itemId);
            std::cout << "\n✓ Item returned successfully!\n";
            std::cout << ret->getDetails() << "\n";
        } catch (const std::exception& e) {
            std::cout << "✗ Error: " << e.what() << "\n";
        }
    }
    
    void searchByTitle() {
        std::string title = getUserInput("Enter title to search: ");
        auto results = library_.searchItemsByTitle(title);
        
        if (results.empty()) {
            std::cout << "No items found with title containing: " << title << "\n";
        } else {
            std::cout << "\n--- Search Results ---\n";
            for (const auto& item : results) {
                std::cout << "ID: " << item->getId() << "\n";
                std::cout << "Title: " << item->getTitle() << "\n";
                std::cout << "Type: " << item->getItemType() << "\n";
                std::cout << "Status: " << (item->isAvailable() ? "Available" : "Checked Out") << "\n";
                std::cout << item->getDetails() << "\n";
                std::cout << "---\n";
            }
        }
    }
    
    void searchByAuthor() {
        std::string author = getUserInput("Enter author to search: ");
        auto results = library_.searchItemsByAuthor(author);
        
        if (results.empty()) {
            std::cout << "No books found by author: " << author << "\n";
        } else {
            std::cout << "\n--- Search Results ---\n";
            for (const auto& item : results) {
                std::cout << "ID: " << item->getId() << "\n";
                std::cout << "Title: " << item->getTitle() << "\n";
                std::cout << "Type: " << item->getItemType() << "\n";
                std::cout << "Status: " << (item->isAvailable() ? "Available" : "Checked Out") << "\n";
                std::cout << item->getDetails() << "\n";
                std::cout << "---\n";
            }
        }
    }
    
    void searchByGenre() {
        std::string genre = getUserInput("Enter genre to search: ");
        auto results = library_.searchItemsByGenre(genre);
        
        if (results.empty()) {
            std::cout << "No books found in genre: " << genre << "\n";
        } else {
            std::cout << "\n--- Search Results ---\n";
            for (const auto& item : results) {
                std::cout << "ID: " << item->getId() << "\n";
                std::cout << "Title: " << item->getTitle() << "\n";
                std::cout << "Type: " << item->getItemType() << "\n";
                std::cout << "Status: " << (item->isAvailable() ? "Available" : "Checked Out") << "\n";
                std::cout << item->getDetails() << "\n";
                std::cout << "---\n";
            }
        }
    }
    
    void searchByType() {
        std::cout << "Item Types:\n";
        std::cout << "1. Book\n";
        std::cout << "2. Magazine\n";
        std::cout << "3. DVD\n";
        int choice = getIntInput("Select type: ");
        
        std::string type;
        switch (choice) {
            case 1:
                type = "Book";
                break;
            case 2:
                type = "Magazine";
                break;
            case 3:
                type = "DVD";
                break;
            default:
                std::cout << "Invalid type.\n";
                return;
        }
        
        auto results = library_.searchItemsByType(type);
        
        if (results.empty()) {
            std::cout << "No items found of type: " << type << "\n";
        } else {
            std::cout << "\n--- Search Results ---\n";
            for (const auto& item : results) {
                std::cout << "ID: " << item->getId() << "\n";
                std::cout << "Title: " << item->getTitle() << "\n";
                std::cout << "Type: " << item->getItemType() << "\n";
                std::cout << "Status: " << (item->isAvailable() ? "Available" : "Checked Out") << "\n";
                std::cout << item->getDetails() << "\n";
                std::cout << "---\n";
            }
        }
    }
    
    void handleSearch() {
        while (true) {
            displaySearchMenu();
            int choice = getIntInput("Select option: ");
            
            switch (choice) {
                case 1:
                    searchByTitle();
                    break;
                case 2:
                    searchByAuthor();
                    break;
                case 3:
                    searchByGenre();
                    break;
                case 4:
                    searchByType();
                    break;
                case 5:
                    return;
                default:
                    std::cout << "Invalid option. Please try again.\n";
            }
        }
    }
    
    void viewInventory() {
        library_.printInventory();
    }
    
    void viewOverdueItems() {
        library_.printOverdueItems();
    }
    
    void viewPatronHistory() {
        std::string patronId = getUserInput("Enter Patron ID: ");
        library_.printPatronHistory(patronId);
    }
    
public:
    LibraryUI() : running_(true) {}
    
    void run() {
        std::cout << "\n╔════════════════════════════════════════╗\n";
        std::cout << "║  Welcome to Library Management System  ║\n";
        std::cout << "╚════════════════════════════════════════╝\n";
        
        // Load some sample data
        loadSampleData();
        
        while (running_) {
            displayMainMenu();
            int choice = getIntInput("Select option: ");
            
            switch (choice) {
                case 1:
                    handleAddItem();
                    break;
                case 2:
                    handleAddPatron();
                    break;
                case 3:
                    checkoutItem();
                    break;
                case 4:
                    returnItem();
                    break;
                case 5:
                    handleSearch();
                    break;
                case 6:
                    viewInventory();
                    break;
                case 7:
                    viewOverdueItems();
                    break;
                case 8:
                    viewPatronHistory();
                    break;
                case 9:
                    running_ = false;
                    std::cout << "\n✓ Thank you for using the Library Management System!\n";
                    std::cout << "Goodbye!\n\n";
                    break;
                default:
                    std::cout << "Invalid option. Please try again.\n";
            }
        }
    }
    
    void loadSampleData() {
        std::cout << "\nLoading sample data...\n";
        
        // Add sample books
        library_.addItem(std::make_unique<Book>("B001", "The Great Gatsby", "F. Scott Fitzgerald", "978-3-16-148410-0", "Fiction"));
        library_.addItem(std::make_unique<Book>("B002", "1984", "George Orwell", "978-0451524935", "Dystopian"));
        library_.addItem(std::make_unique<Book>("B003", "To Kill a Mockingbird", "Harper Lee", "978-0061120084", "Fiction"));
        library_.addItem(std::make_unique<Book>("B004", "The Catcher in the Rye", "J.D. Salinger", "978-0316769174", "Fiction"));
        
        // Add sample magazines
        library_.addItem(std::make_unique<Magazine>("M001", "National Geographic", "National Geographic Society", 156, "2023-01-15"));
        library_.addItem(std::make_unique<Magazine>("M002", "Time", "Time Inc.", 3, "2023-02-01"));
        
        // Add sample DVDs
        library_.addItem(std::make_unique<DVD>("D001", "Inception", "Christopher Nolan", 148, "2010-07-16"));
        library_.addItem(std::make_unique<DVD>("D002", "The Shawshank Redemption", "Frank Darabont", 142, "1994-10-14"));
        
        // Add sample students
        library_.addPatron(std::make_unique<Student>("S001", "Alice Johnson", "alice@university.edu", "STU123001", "Computer Science"));
        library_.addPatron(std::make_unique<Student>("S002", "Bob Smith", "bob@university.edu", "STU123002", "Literature"));
        library_.addPatron(std::make_unique<Student>("S003", "Charlie Brown", "charlie@university.edu", "STU123003", "History"));
        
        // Add sample faculty
        library_.addPatron(std::make_unique<Faculty>("F001", "Dr. Jane Wilson", "jane.wilson@university.edu", "English", "FAC001"));
        library_.addPatron(std::make_unique<Faculty>("F002", "Prof. John Davis", "john.davis@university.edu", "Science", "FAC002"));
        
        std::cout << "✓ Sample data loaded successfully!\n";
    }
};

int main() {
    LibraryUI ui;
    ui.run();
    return 0;
}