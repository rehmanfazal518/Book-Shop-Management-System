#include <iostream>
#include <sstream>	  
#include <fstream>    
#include <limits>     
#include <algorithm>  
#include <cctype>
#include "node.h"
using namespace std;

int login(const string& pass);

bool isStringValid(const string& str) {
	return all_of(str.begin(), str.end(), [](char c) {
		return isalpha(c) || c == ' ';
	});
}

void saveInventoryToFile(Category* categoryList) {
	ofstream outputFile("inventory.txt");
	if (!outputFile) {
		cout << "Error" << endl;
		return;
	}

	Category* category = categoryList;
	while (category != nullptr) {
		Book* book = category->root;
		while (book != nullptr) {
			outputFile << category->name << ",";
			outputFile << book->title << ",";
			outputFile << book->author << ",";
			outputFile << book->price << ",";
			outputFile << book->quantity << "\n";

			book = book->right;
		}
		category = category->next;
	}

	outputFile.close();
	cout << "Inventory saved to file." << endl;
}

void loadInventoryFromFile(Category*& categoryList) {
	ifstream inputFile("inventory.txt");
	if (!inputFile) {
		cout << "Error: Could not open the file." << endl;
		return;
	}

	categoryList = nullptr;

	string line;
	while (getline(inputFile, line)) {
		stringstream ss(line);
		string categoryName, title, author;
		float price;
		int quantity;

		getline(ss, categoryName, ',');
		getline(ss, title, ',');
		getline(ss, author, ',');
		ss >> price;
		ss.ignore();
		ss >> quantity;

		Functions f;
		f.addBook(categoryList, categoryName, title, author, price, quantity);
	}

	inputFile.close();
	cout << "Inventory loaded from file." << endl;
}

int main() {
	cout << "\t\t\t\tWelcome to the Book Management System!" << endl;
	cout << "\t\t\t\t======================================" << endl;
	cout << "\nPlease login to continue." << endl;

	string password;
	int loggedIn = 0;

	while (loggedIn == 0) {
		cout << "Enter Password: ";
		cin >> password;
		loggedIn = login(password);

		if (loggedIn == 0) {
			cout << "Wrong password. Please try again.\n" << endl;
		}
	}

	cout << "Login successful!" << endl;

	Category* categoryList = NULL;
	Functions f;

	loadInventoryFromFile(categoryList);  // Load inventory from file

	while (true) {
		cout << "\nMenu:\n"
		     << "1. Add a book\n"
		     << "2. Remove a book\n"
		     << "3. Update a book\n"
		     << "4. Display all books\n"
		     << "5. Display Books By Category\n"
		     << "6. Exit\n"
		     << "Enter your choice: ";

		int choice;
		cin >> choice;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Please enter a valid choice.\n";
			continue;
		}

		switch (choice) {
			case 1: {

				string categoryName, title, author;
				float price;
				int quantity;

				while(true) {
					cout << "Enter the category name: ";
					cin.ignore();
					getline(cin, categoryName);

					if (!isStringValid(categoryName)) {
						cout << "Invalid input. Please enter alphabetic characters only for the category name." << endl;
						continue;
					} else break;
				}

				cout << "Enter the title: ";
				getline(cin, title);

				while(true) {
					cout << "Enter the author's name: ";
					getline(cin, author);

					if (!isStringValid(author)) {
						cout << "Invalid input. Please enter alphabetic characters only for the author's name." << endl;
						continue;
					} else break;
				}

				while(true) {
					cout << "Enter the price: ";
					cin >> price;

					if (cin.fail()) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Invalid input. Please enter a valid price.\n";
						continue;
					} else break;
				}

				while(true) {
					cout << "Enter the quantity: ";
					cin >> quantity;

					if (cin.fail()) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Invalid input. Please enter a valid quantity.\n";
						continue;
					} else break;
				}
				f.addBook(categoryList, categoryName, title, author, price, quantity);
				saveInventoryToFile(categoryList);
				break;
			}
			case 2: {
				string title, category;
				cout << "Enter the category name: ";
				cin.ignore();
				getline(cin, category);
				cout << "Enter the title: ";
				getline(cin, title);
				f.removeBook(categoryList, category, title);
				saveInventoryToFile(categoryList);  // Save inventory after removing book
				break;
			}
			case 3: {
				string title, category;
				cout << "Enter the category name: ";
				cin.ignore();
				getline(cin, category);
				cout << "Enter the title: ";
				getline(cin, title);
				f.updateBook(categoryList, category, title);
				saveInventoryToFile(categoryList);  // Save inventory after updating book
				break;
			}
			case 4:
				f.displayBooks(categoryList);
				break;
			case 5: {
				string category;
				cout << "Enter the category name: ";
				cin.ignore();
				getline(cin, category);
				f.displayBooksByCategory(categoryList, category);
				break;
			}
			case 6:
				saveInventoryToFile(categoryList);  // Save inventory before exiting
				cout << "Exiting the program.\n";
				return 0;
			default:
				cout << "Invalid choice. Please try again.\n";
		}
	}
	return 0;
}

int login(const string& pass) {
	if (pass == "Ali123") {
		return 1;
	}
	return 0;
}