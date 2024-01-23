#include <iostream>
#include <iomanip>
#include <limits>   
#include <algorithm>
#include "node.h"

bool isValid(const string& str) {
	return all_of(str.begin(), str.end(), [](char c) {
		return isalpha(c) || c == ' ';
	});
}


Book* Functions::createBook(const string& title, const string& author, float price, int quantity) {
	Book* newBook = new Book;
	newBook->title = title;
	newBook->author = author;
	newBook->price = price;
	newBook->quantity = quantity;
	newBook->left = NULL;
	newBook->right = NULL;
	return newBook;
}

void Functions::addBook(Category*& categoryList, const string& categoryName, const string& title, const string& author, float price, int quantity) {
	Category* currentCategory = categoryList;
	Category* prevCategory = NULL;

	// Search for the category in the categoryList
	while (currentCategory != NULL && currentCategory->name != categoryName) {
		prevCategory = currentCategory;
		currentCategory = currentCategory->next;
	}

	// Category not found, create a new category node
	if (currentCategory == NULL) {
		currentCategory = new Category;
		currentCategory->name = categoryName;
		currentCategory->root = NULL;
		currentCategory->next = NULL;

		// Add the new category node to the end of the categoryList
		if (prevCategory == NULL) {
			categoryList = currentCategory;
		} else {
			prevCategory->next = currentCategory;
		}
	}

	addBookToBST(currentCategory->root, title, author, price, quantity);
//	cout << "Book added to the inventory successfully." << endl;
}

void Functions::addBookToBST(Book*& root, const string& title, const string& author,
                             float price, int quantity) {
	if (root == NULL) {
		root = createBook(title, author, price, quantity);
	} else {
		if (title < root->title) {
			addBookToBST(root->left, title, author, price, quantity);
		} else if (title > root->title) {
			addBookToBST(root->right, title, author, price, quantity);
		} else {
			root->quantity += quantity;
			cout << "Quantity updated for book with title: " << title << endl;
		}
	}
}


void Functions::removeBook(Category*& categoryList, const string& categoryName, const string& title) {
	Category* currentCategory = categoryList;

	// Search for the specified category
	while (currentCategory != NULL && currentCategory->name != categoryName) {
		currentCategory = currentCategory->next;
	}

	if (currentCategory == NULL) {
		cout << "Category not found." << endl;
		return;
	}

	removeBookFromBST(currentCategory->root, title);
}



void Functions::removeBookFromBST(Book*& root, const string& title) {
	if (root == NULL) {
		cout << "The book '" << title << "' was not found." << endl;
	} else {
		if (title < root->title) {
			removeBookFromBST(root->left, title);
		} else if (title > root->title) {
			removeBookFromBST(root->right, title);
		} else {
			Book* nodeToDelete = root;

			if (root->left == NULL) {
				root = root->right;
			} else if (root->right == NULL) {
				root = root->left;
			} else {
				Book* successor = root->right;
				while (successor->left != NULL) {
					successor = successor->left;
				}
				root->title = successor->title;
				root->author = successor->author;
				root->price = successor->price;
				root->quantity = successor->quantity;
				removeBookFromBST(root->right, successor->title);
				return;
			}

			delete nodeToDelete;
			cout << "Book removed from the inventory successfully." << endl;
		}
	}
}

void Functions::updateBook(Category*& categoryList, const string& categoryName, const string& title) {
	Category* currentCategory = categoryList;

	// Search for the specified category
	while (currentCategory != nullptr && currentCategory->name != categoryName) {
		currentCategory = currentCategory->next;
	}

	if (currentCategory == nullptr) {
		cout << "Category not found." << endl;
		return;
	}

	// Update the book in the category's BST
	updateBookInBST(currentCategory->root, title);
}

void Functions::updateBookInBST(Book*& root, const string& title) {
	if (root == NULL) {
		cout << "The book '" << title << "' was not found." << endl;
	} else {
		if (title < root->title) {
			updateBookInBST(root->left, title);
		} else if (title > root->title) {
			updateBookInBST(root->right, title);
		} else {
			string title, author;
			float price;
			int quantity;
			cout << "Enter the title: ";
			getline(cin, title);

			while(true) {
				cout << "Enter the author's name: ";
				getline(cin, author);

				if (!isValid(author)) {
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
			root->title = title;
			root->author = author;
			root->quantity = quantity;
			root->price = price;
			cout << "Book updated successfully." << endl;
			return;
		}
	}
}

void Functions::displayBooks(const Category* categoryList) {
	const Category* currentCategory = categoryList;
	while (currentCategory != NULL) {
		cout << "Category: " << currentCategory->name << endl;
		displayBooksInBST(currentCategory->root);
		cout << endl;
		currentCategory = currentCategory->next;
	}
}

void Functions::displayBooksInBST(const Book* root) {
    if (root != NULL) {
        displayBooksInBST(root->left);
        std::cout << std::left << std::setw(20) << "Title: " << root->title << std::endl;
        std::cout << std::left << std::setw(20) << "Author: " << root->author << std::endl;
        std::cout << std::left << std::setw(20) << "Price: " << root->price << std::endl;
        std::cout << std::left << std::setw(20) << "Quantity: " << root->quantity << std::endl;
        std::cout << std::endl;
        displayBooksInBST(root->right);
    }
}

void Functions::displayBooksByCategory(const Category* categoryList, const string& categoryName) {
	const Category* currentCategory = categoryList;
	while (currentCategory != NULL) {
		if (currentCategory->name == categoryName) {
			cout << "Category: " << currentCategory->name << endl;
			displayBooksInBST(currentCategory->root);
			return;
		}
		currentCategory = currentCategory->next;
	}
	cout << "Category not found." << endl;
}