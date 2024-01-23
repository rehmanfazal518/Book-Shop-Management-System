#ifndef NODE_H
#define NODE_H

#include <string>
using namespace std;
struct Book {
    string title;
    string author;
    float price;
    int quantity;
    Book* left;
    Book* right;
};

struct Category {
    string name;
    Book* root;
    Category* next;
};

struct Functions {
    Book* createBook(const string& title, const string& author, float price, int quantity);
    void addBook(Category*& categoryList, const string& categoryName, const string& title,const string& author, float price, int quantity);
    void addBookToBST(Book*& root, const string& title, const string& author, float price, int quantity);
    void removeBook(Category*& categoryList, const string& categoryName, const string& title);
    void removeBookFromBST(Book*& root, const string& title);
    void updateBook(Category*& categoryList, const string& categoryName, const string& title);
    void updateBookInBST(Book*& root, const string& title);
    void displayBooks(const Category* categoryList);
    void displayBooksInBST(const Book* root);
    void displayBooksByCategory(const Category* categoryList, const string& categoryName);

};

#endif
