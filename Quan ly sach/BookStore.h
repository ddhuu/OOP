
#include"Order.h"
#pragma once
using namespace std;
class Bookstore{
private :
	string name;
    std::vector<Book> books;
    std::vector<Order> orders;
public:
	//Constructor
	Bookstore() {};
    //Utility method
    void loadBooks(const std::string& filename, Bookstore& store);
    void addBook(const Book& book);
    void listBooks() ;
    void viewBooksByPriceAndName();
    void viewTopBooks(int k = 10);
    bool bookExists(const std::string& isbn);
    void addNewBook();
    Book* findBookByISBN(const std::string& inputISBN);
    void addToCart();
    void viewCart();
    void saveOrdersToFile();
    void checkout();
    void displayLowStockBooks(int stockThreshold = 50);
    void saveBooksToFile();
    // Destructor
    ~Bookstore() {};


   




};