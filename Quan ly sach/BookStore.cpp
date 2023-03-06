
#include"BookStore.h"
void Bookstore::addBook(const Book& book) {
    books.push_back(book);
}
void Bookstore:: loadBooks(const std::string& filename, Bookstore& store) {
    std::ifstream inputFile(filename);
    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            std::string isbn = line;
            std::getline(inputFile, line);
            std::string title = line;
            std::getline(inputFile, line);
            std::string author = line;
            std::getline(inputFile, line);
            std::string language = line;
            std::getline(inputFile, line);
            int publishedYear;
            std::istringstream(line) >> publishedYear;
            std::getline(inputFile, line);
            double price;
            std::istringstream(line) >> price;
            std::getline(inputFile, line);
            int stockLevel;
            std::istringstream(line) >> stockLevel;
            std::getline(inputFile, line);
            DateTime inputDate = DateTime::fromString(line);
            Book book(isbn, title, author, language, publishedYear, price, stockLevel, inputDate);
            if (inputFile.good()) {
                store.addBook(book);
            }
        }
        inputFile.close();
    }
    else {
        std::cerr << "Failed to open file " << filename << std::endl;
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
    std::sort(this->books.begin(), this->books.end(), Book::compareBooksByPriceAndName);

    // Print the list of books
    std::cout << "List of books sorted by price and name:" << std::endl;
    for (const auto& book : this->books) {
        std::cout << book << std::endl;
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
bool Bookstore:: bookExists(const std::string& isbn) {
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
Book* Bookstore::findBookByISBN(const std::string& inputISBN) {
    for (Book& book : books) {
        if (book.getISBN() == inputISBN) {
            return &book;
        }
    }
    return nullptr;
}
void Bookstore::addToCart() {
    cin.ignore();
    std::string inputISBN;
    std::cout << "Enter ISBN of the book: ";
    std::getline(std::cin, inputISBN);

    Book* foundBook = findBookByISBN(inputISBN);
    if (foundBook == nullptr) {
        std::cout << "Book not found." << std::endl;
        return;
    }

    if (foundBook->getStockLevel() <= 0) {
        std::cout << "Out of stock." << std::endl;
        return;
    }

    foundBook->setStockLevel(foundBook->getStockLevel() - 1);

    std::string customerName;
    std::cout << "Enter customer name: ";
    std::getline(std::cin, customerName);

    Order newOrder(customerName, *foundBook);
    orders.push_back(newOrder);

    std::cout << "Book added to cart." << std::endl;
}

void Bookstore:: viewCart()  {
    if (orders.empty()) {
        std::cout << "No items in cart." << std::endl;
        return;
    }

    std::cout << "Cart items:" << std::endl;
    double totalCost = 0;
    for (auto& order : orders) {
        std::cout << order.getCustomerName() << " || " << order.getBook().getTitle() << " (" << order.getBook().getISBN() << "): "
            << order.getTotalCost() << " || " << order.getOrderDay() << std::endl;
        totalCost += order.getTotalCost();
    }
    std::cout << "Total: " << std::fixed << std::setprecision(2) << totalCost << "$" << std::endl;
    std::cout << "Thank you for shopping at our bookstore!" << std::endl;
}
void Bookstore:: saveOrdersToFile() {
    std::ofstream file("orders.txt", std::ios_base::trunc);
    if (!file) {
        std::cerr << "failed to open orders file." << std::endl;
        return;
    }

    for (auto order = orders.rbegin(); order != orders.rend(); ++order) {
        file << *order << std::endl;
    }

    file.close();
}

//Checkout function to initiate payment and save order to file
void Bookstore::checkout() {
    double total = 0.0;
    std::string customerName;
    std::cout << "Enter customer name: ";
    cin.ignore();
    std::getline(std::cin, customerName);

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

    std::cout << "Payment successful. Total: " << total << " VND." << std::endl;
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
    ofstream outputFile("book.txt", std::ios_base::trunc);
    if (!outputFile) {
        cerr << "Error: Unable to open output file." << endl;
        exit(1);
    }

    for (int i = 0; i < books.size(); i++) {

        outputFile << books[i].getISBN() << "\n"
            << books[i].getTitle() << "\n"
            << books[i].getAuthor() << "\n"
            // << "ISBN: " << book.getISBN() << "\n"
             //<< "Category: " << book. << "\n"
            // << "Publication Year: " << book.getPublicationYear() << "\n"
            // << "Number of Pages: " << book.getNumPages() << "\n"
            << books[i].getLanguage() << "\n"
            << books[i].getPublishedYear() << "\n"
            << books[i].getPrice() << "\n"
            << books[i].getStockLevel() << "\n"
            << books[i].getInputDate() << "\n";
    }

    cout << "Successfully saved the list of books to file." << endl;
}

