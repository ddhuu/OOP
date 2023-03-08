
#include"Book.h"
#pragma once
using namespace std;

class Order {
private:
    string customerName;
    Book book;
    int quantity;
    DateTime orderDate;
public:
    Order(string customerName, Book book)
    {
        this->customerName = customerName;
        this->book = book;
        this->quantity = 1;
        this->orderDate = DateTime::now();
    }
    double getTotalCost() const {
        return quantity * book.getPrice();
    }


    
    string getCustomerName() const {
        return customerName;
    }

    Book getBook() const {
        return book;
    }


    DateTime getOrderDay() const {
        return this->orderDate;
    }

    void setCustomerName(string name) { this->customerName = name; }
    void setBook(Book book) { this->book = book; }
    void setorderDate(DateTime date) { this->orderDate = date; }


    // OPerator Overloadiing

    friend ostream& operator<<(ostream& os, const Order& order) {
        os << "Customer name: " << order.customerName << endl;
        os << order.book << endl;
        os << "Sold date: " << order.orderDate << endl;
        return os;
    }
    friend ifstream& operator>>(ifstream& ifs, Order& order) {
        getline(ifs, order.customerName);
        ifs >> order.book;
        ifs >> order.orderDate;
        ifs.ignore();
        return ifs;
    }
};

