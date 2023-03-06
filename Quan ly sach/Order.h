
#include"Book.h"
#pragma once
using namespace std;

class Order {
private:
    std::string customerName;
    Book book;
    int quantity;
    DateTime orderDate;
public:
    Order(std::string customerName, Book book)
    {
        this->customerName = customerName;
        this->book = book;
        this->quantity = 1;
        this->orderDate = DateTime::now();
    }
    double getTotalCost() const {
        return quantity * book.getPrice();
    }


    
    std::string getCustomerName() const {
        return customerName;
    }

    Book getBook() const {
        return book;
    }


    DateTime getOrderDay() const {
        return this->orderDate;
    }

    void setCustomerName(std::string name) { this->customerName = name; }
    void setBook(Book book) { this->book = book; }
    void setorderDate(DateTime date) { this->orderDate = date; }


    // OPerator Overloadiing

    friend std::ostream& operator<<(std::ostream& os, const Order& order) {
        os << "Customer name: " << order.customerName << std::endl;
        os << order.book << std::endl;
        os << "Sold date: " << order.orderDate << std::endl;
        return os;
    }
    friend std::ifstream& operator>>(std::ifstream& ifs, Order& order) {
        std::getline(ifs, order.customerName);
        ifs >> order.book;
        ifs >> order.orderDate;
        ifs.ignore();
        return ifs;
    }
};

