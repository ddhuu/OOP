
#include"BookStore.h"
void Bookstore::addBook(const Book& book) {
    books.push_back(book);
}
void Bookstore:: loadBooks(const string& filename, Bookstore& store) {
   ifstream inputFile(filename);
    if (inputFile.is_open()) {
       string line;
        while (getline(inputFile, line)) {
           string isbn = line;
           getline(inputFile, line);
           string title = line;
           getline(inputFile, line);
           string author = line;
           getline(inputFile, line);
           string language = line;
           getline(inputFile, line);
           int publishedYear;
           istringstream(line) >> publishedYear;
           getline(inputFile, line);
           double price;
           istringstream(line) >> price;
           getline(inputFile, line);
           int stockLevel;
           istringstream(line) >> stockLevel;
           getline(inputFile, line);
           DateTime inputDate = DateTime::fromString(line);
           Book book(isbn, title, author, language, publishedYear, price, stockLevel, inputDate);
           if (inputFile.good()) {
                store.addBook(book);
           }
        }
        inputFile.close();
    }
    else {
       cerr << "Failed to open file " << filename <<endl;
    }
}
void Bookstore::listBooks()  {
    if (books.empty()) {
        cout << "No books in the inventory.\n";
        return;
    }
    for (const auto& book : books) {
        cout << book << endl;
    }
}
void Bookstore:: viewBooksByPriceAndName() {
    // Sort books by price and name
   sort(this->books.begin(), this->books.end(), Book::compareBooksByPriceAndName);

    // Print the list of books
   cout << "List of books sorted by price and name:" <<endl;
    for (const auto& book : this->books) {
       cout << book <<endl;
    }
}
void Bookstore::viewTopBooks(int k ) {
    // Sắp xếp danh sách sách theo ngày nhập sách (input date)
    sort(books.begin(), books.end(), Book::compareDate);

    // In ra top K cuốn sách mới nhất
    cout << "Top " << k << " sach moi nhat:" << endl;
    for (int i = 0; i < k && i < books.size(); i++) {
        cout << books[i].getTitle() << " - " << books[i].getInputDate() << endl;
    }
}
bool Bookstore:: bookExists(const string& isbn) {
    for (const auto& book : books) {
        if (book.getISBN() == isbn) {
            return true;
        }
    }
    return false;
}
void Bookstore::addNewBook() {
    Book newBook;
    cin.ignore();
    cin >> newBook;
    if (!bookExists(newBook.getISBN())) {
        // Thêm sách mới nếu sách chưa tồn tại trong danh sách
        DateTime now = DateTime::now();
        Book book(newBook.getISBN(), newBook.getTitle(), newBook.getAuthor(),
            newBook.getLanguage(),
            newBook.getPublishedYear(), newBook.getPrice(),
            newBook.getStockLevel(), now);
        books.push_back(book);
    }
    else {
        // Tăng số lượng stock level nếu sách đã tồn tại trong danh sách
        for (auto& book : books) {
            if (book.getISBN() == newBook.getISBN()) {
                book.setStockLevel(book.getStockLevel() + newBook.getStockLevel());
                book.setInputDate(DateTime::now());
                break;
            }
        }
    }
}
Book* Bookstore::findBookByISBN(const string& inputISBN) {
    for (Book& book : books) {
        if (book.getISBN() == inputISBN) {
            return &book;
        }
    }
    return nullptr;
}
void Bookstore::addToCart() {
    cin.ignore();
   string inputISBN;
   cout << "Enter ISBN of the book: ";
   getline(cin, inputISBN);

    Book* foundBook = findBookByISBN(inputISBN);
    if (foundBook == nullptr) {
       cout << "Book not found." <<endl;
        return;
    }

    if (foundBook->getStockLevel() <= 0) {
       cout << "Out of stock." <<endl;
        return;
    }

    foundBook->setStockLevel(foundBook->getStockLevel() - 1);

   string customerName;
   cout << "Enter customer name: ";
   getline(cin, customerName);

    Order newOrder(customerName, *foundBook);
    orders.push_back(newOrder);

   cout << "Book added to cart." <<endl;
}

void Bookstore:: viewCart()  {
    if (orders.empty()) {
       cout << "No items in cart." <<endl;
        return;
    }

   cout << "Cart items:" <<endl;
    double totalCost = 0;
    for (auto& order : orders) {
       cout << order.getCustomerName() << " || " << order.getBook().getTitle() << " (" << order.getBook().getISBN() << "): "
            << order.getTotalCost() << " || " << order.getOrderDay() <<endl;
        totalCost += order.getTotalCost();
    }
   cout << "Total: " <<fixed <<setprecision(2) << totalCost << "$" <<endl;
   cout << "Thank you for shopping at our bookstore!" <<endl;
}
void Bookstore:: saveOrdersToFile() {
   ofstream file("orders.txt",ios_base::trunc);
    if (!file) {
       cerr << "failed to open orders file." <<endl;
        return;
    }

    for (auto order = orders.rbegin(); order != orders.rend(); ++order) {
        file << *order <<endl;
    }

    file.close();
}

//Checkout function to initiate payment and save order to file
void Bookstore::checkout() {
    double total = 0.0;
   string customerName;
   cout << "Enter customer name: ";
    cin.ignore();
   getline(cin, customerName);

    // Create a new order for each item in the cart and calculate the total
    for (auto& order : orders) {
        total += order.getBook().getPrice();
        order.setCustomerName(customerName);
        order.setorderDate(DateTime::now());
    }



    // Save the orders to file
    saveOrdersToFile();

    // Clear the cart
    orders.clear();

   cout << "Payment successful. Total: " << total << " VND." <<endl;
}

// Save orders to file in reverse chronological order


void Bookstore:: displayLowStockBooks(int stockThreshold ) {
    cout << "List of books running low on stock: " << endl;
    for (int i = 0; i < books.size(); i++) {
        if (books[i].getStockLevel() < stockThreshold) {
            cout << books[i].getTitle() << " by " << books[i].getAuthor()
                << " (ISBN: " << books[i].getISBN() << ")" << endl;
        }
    }
}
void Bookstore::saveBooksToFile() {
    ofstream outputFile("book.txt",ios_base::trunc);
    if (!outputFile) {
        cerr << "Error: Unable to open output file." << endl;
        exit(1);
    }

    for (int i = 0; i < books.size(); i++) {

        outputFile << books[i].getISBN() << "\n"
            << books[i].getTitle() << "\n"
            << books[i].getAuthor() << "\n"
            << books[i].getLanguage() << "\n"
            << books[i].getPublishedYear() << "\n"
            << books[i].getPrice() << "\n"
            << books[i].getStockLevel() << "\n"
            << books[i].getInputDate() << "\n";
    }

    cout << "Successfully saved the list of books to file." << endl;
}

