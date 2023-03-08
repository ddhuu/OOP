
#include"Order.h"
#pragma once
using namespace std;
class Bookstore{
private :
	string name;
    vector<Book> books;
    vector<Order> orders;
public:
	//Constructor
	Bookstore() {};
    //Utility method
    void loadBooks(const string& filename, Bookstore& store);
    void addBook(const Book& book);
    void listBooks() ;
    void viewBooksByPriceAndName();
    void viewTopBooks(int k = 10);
    bool bookExists(const string& isbn);
    void addNewBook();
    Book* findBookByISBN(const string& inputISBN);
    void addToCart();
    void viewCart();
    void saveOrdersToFile();
    void checkout();
    void displayLowStockBooks(int stockThreshold = 50);
    void saveBooksToFile();
    // Destructor
    ~Bookstore() {};


   




};