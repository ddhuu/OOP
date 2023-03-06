

#include"DateTime.h"
#pragma once
using namespace std;

class Book {
private:
	string isbn;
	string title;
	string author;
	string publisher;
	string language;
	int  publishedYear;
	double price;
	int stockLevel;
	DateTime  inputDate;
public:
	//Constructor
	Book() {};
	
	Book(string isbn, string title, string author,
		string publisher, int publishedYear,
		float price, int stockLevel, DateTime inputDate);

	// Getters 
	string getISBN() const {
		return isbn;
	}
	string getTitle() const {
		return title;
	}
	string getAuthor() const {
		return author;
	}
	string getPublisher() const {
		return publisher;
	}
	string getLanguage() const {
		return language;
	}
	int getPublishedYear() const {
		return publishedYear;
	}
	double getPrice() const {
		return price;
	}
	int getStockLevel() const {
		return stockLevel;
	}
	DateTime getInputDate() const {
		return inputDate;
	}

	// Setters
	void setISBN(const string& _isbn) {
		isbn = _isbn;
	}
	void setTitle(const string& _title) {
		title = _title;
	}
	void setAuthor(const string& _author) {
		author = _author;
	}
	void setPublisher(const string& _publisher) {
		publisher = _publisher;
	}
	void setLanguage(const string& _language) {
		language = _language;
	}
	void setPublishedYear(int _publishedYear) {
		publishedYear = _publishedYear;
	}
	void setPrice(double _price) {
		price = _price;
	}
	void setStockLevel(int _stockLevel) {
		stockLevel = _stockLevel;
	}
	void setInputDate(const DateTime& _inputDate) {
		inputDate = _inputDate;
	}

	
	//Utility

	static bool compareBooksByPriceAndName(const Book& b1, const Book& b2);
	static bool compareDate(Book& newBook, Book& book2);
	
	// input/output 
	friend  istream& operator>>(istream& is, Book& book);
	friend  ostream& operator<<(ostream& os, const Book& book);
};


