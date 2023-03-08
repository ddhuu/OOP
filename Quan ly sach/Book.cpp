
#include"Book.h"
Book ::Book(string isbn, string title, string author, string language, int publishedYear, float price, int stockLevel, DateTime inputDate)
 {
    this->isbn = isbn;
    this-> title = title;
    this->author = author;
    this->language = language;
    this -> publishedYear= publishedYear;
    this->price = price;
    this->stockLevel = stockLevel;
    this->inputDate= inputDate;
}
// Utility method
 bool Book:: compareBooksByPriceAndName(const Book& b1, const Book& b2) {
	if (b1.price < b2.price)
		return true;
	else if (b1.price == b2.price)
		return b1.title < b2.title;
	else
		return false;
}

 bool Book:: compareDate(Book& newBook, Book& book2) {
	DateTime dt1 = newBook.getInputDate();
	DateTime dt2 = book2.getInputDate();
	if (dt1.getYear() > dt2.getYear()) {
		return true;
	}
	else if (dt1.getYear() == dt2.getYear()) {
		if (dt1.getMonth() > dt2.getMonth()) {
			return true;
		}
		else if (dt1.getMonth() == dt2.getMonth()) {
			if (dt1.getDay() > dt2.getDay()) {
				return true;
			}
			else if (dt1.getDay() == dt2.getDay()) {
				if (dt1.getHour() > dt2.getHour()) {
					return true;
				}
				else if (dt1.getHour() == dt2.getHour()) {
					if (dt1.getMinute() > dt2.getMinute()) {
						return true;
					}
					else if (dt1.getMinute() == dt2.getMinute()) {
						if (dt1.getSecond() > dt2.getSecond()) {
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

 // I/O stream
istream& operator>>(istream& is, Book& book) {
    cout << "Enter book details:\n";
    cout << "ISBN: ";
    getline(is, book.isbn);
    cout << "Title: ";
    getline(is, book.title);
    cout << "Author: ";
    getline(is, book.author);
    cout<< "Publisher: ";
    getline(is, book.publisher);
    cout << "Publication Year: ";
    is >> book.publishedYear;
    cout << "Price: ";
    is >> book.price;
    cout << "Stock Level: ";
    is >> book.stockLevel;
    cin.ignore(); // ignore the newline character in the input stream
    book.inputDate = DateTime::now();
    return is;
}
ostream& operator<<(ostream& os, const Book& book) {
    os << "ISBN: " << book.isbn << "\n"
        << "Title: " << book.title << "\n"
        << "Author: " << book.author << "\n"
        << "Language : " << book.language << "\n"
        << "Published Year: " << book.publishedYear << "\n"
        << "Price: " << book.price << "\n"
        << "Stock Level: " << book.stockLevel << "\n"
        << "Input Date: " << book.inputDate<< "\n";

    return os;

}