
#include"BookStore.h"
#include"Book.h"
#include"DateTime.h"
#include"Order.h"
int main()
{
	Bookstore store;
	store.loadBooks("books.txt",store);
    int choice;
    do {
        cout << "---------------------------------------" << endl;
        cout << "           MY BOOK STORE MENU           " << endl;
        cout << "---------------------------------------" << endl;
        cout << "1. View book by Price and Name" << endl;
        cout << "2. View Top k Newest Book " << endl;
        cout << "3. Add new Book to Store" << endl;
        cout << "4. Add  book to your Cart" << endl;
        cout << "5. Purchase and Get Bill" << endl;
        cout << "6. View books low on stock" << endl;
        cout << "0. Exit program" << endl;
        cout << "---------------------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            store.viewBooksByPriceAndName();
            break;
        case 2:
            store.viewTopBooks();
            break;
        case 3:
            store.addNewBook();
            break;
        case 4:
            store.addToCart();
            break;
        case 5:
            store.checkout();
            break;
        case 6:
            store.displayLowStockBooks();
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (choice != 0);
    // save book list to file
    store.saveBooksToFile();
    return 0;
}
