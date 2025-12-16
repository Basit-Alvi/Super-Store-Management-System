#include <iostream>
using namespace std;

/* ---------- STRUCTURE ---------- */
struct Product {
    int id;
    char name[30];
    int quantity;
    float price;
};

/* ---------- GLOBAL VARIABLES ---------- */
Product products[100];
int productCount = 0;

/* ---------- FUNCTION DECLARATIONS ---------- */
void addProduct();
void displayProducts();
void searchProduct();
void purchaseProduct();
void mainMenu();

/* ---------- ADD PRODUCT ---------- */
void addProduct() {
    cout << "\nEnter Product ID: ";
    cin >> products[productCount].id;

    cout << "Enter Product Name: ";
    cin >> products[productCount].name;

    cout << "Enter Quantity: ";
    cin >> products[productCount].quantity;

    cout << "Enter Price: ";
    cin >> products[productCount].price;

    productCount++;
    cout << "\nProduct added successfully!\n";
}

/* ---------- DISPLAY PRODUCTS ---------- */
void displayProducts() {
    if (productCount == 0) {
        cout << "\nNo products available!\n";
        return;
    }

    cout << "\nID\tName\tQuantity\tPrice\n";
    cout << "-----------------------------------------\n";

    for (int i = 0; i < productCount; i++) {
        cout << products[i].id << "\t"
             << products[i].name << "\t"
             << products[i].quantity << "\t\t"
             << products[i].price << endl;
    }
}

/* ---------- SEARCH PRODUCT ---------- */
void searchProduct() {
    int searchId;
    cout << "\nEnter Product ID to search: ";
    cin >> searchId;

    for (int i = 0; i < productCount; i++) {
        if (products[i].id == searchId) {
            cout << "\nProduct Found!\n";
            cout << "Name: " << products[i].name << endl;
            cout << "Quantity: " << products[i].quantity << endl;
            cout << "Price: " << products[i].price << endl;
            return;
        }
    }
    cout << "\nProduct not found!\n";
}

/* ---------- PURCHASE PRODUCT ---------- */
void purchaseProduct() {
    int id, qty;
    float total;

    cout << "\nEnter Product ID: ";
    cin >> id;

    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            cout << "Enter Quantity to purchase: ";
            cin >> qty;

            if (qty > products[i].quantity) {
                cout << "\nNot enough stock available!\n";
                return;
            }

            total = qty * products[i].price;
            products[i].quantity -= qty;

            cout << "\n------ BILL ------\n";
            cout << "Product: " << products[i].name << endl;
            cout << "Quantity: " << qty << endl;
            cout << "Total Price: " << total << endl;
            cout << "------------------\n";
            return;
        }
    }
    cout << "\nProduct not found!\n";
}

/* ---------- MAIN MENU ---------- */
void mainMenu() {
    int choice;

    do {
        cout << "\n====== STORE MANAGEMENT SYSTEM ======\n";
        cout << "1. Add Product\n";
        cout << "2. Display Products\n";
        cout << "3. Search Product\n";
        cout << "4. Purchase Product\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addProduct(); break;
            case 2: displayProducts(); break;
            case 3: searchProduct(); break;
            case 4: purchaseProduct(); break;
            case 5: cout << "\nThank you! Exiting program.\n"; break;
            default: cout << "\nInvalid choice! Try again.\n";
        }
    } while (choice != 5);
}

/* ---------- MAIN FUNCTION ---------- */
int main() {
    mainMenu();
    return 0;
}

