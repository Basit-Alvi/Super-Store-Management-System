 #include <iostream>     // For input/output
#include <fstream>      // For file handling
#include <string>       // For string
using namespace std;

/* ---------- STRUCTURE FOR PRODUCT ---------- */
struct Product {
    int id;             // Product ID
    string name;        // Product Name
    int quantity;       // Quantity
    float price;        // Price
};

/* ---------- GLOBAL VARIABLES ---------- */
Product products[100];     // Store up to 100 products
int productCount = 0;      // Count of products

/* ---------- FUNCTION DECLARATIONS ---------- */
void addProduct();
void displayProducts();
void searchProduct();
void purchaseProduct();
void deleteProduct();
void mainMenu();
bool isIdExists(int id);
void saveToFile();
void loadFromFile();

/* ---------- ADD PRODUCT Function ---------- */
void addProduct() {
    int id;

    cout << "\nEnter Product ID: ";
    cin >> id;

    if (id <= 0) {
        cout << "Invalid ID! Must be greater than 0.\n";
        return;
    }

    // Check duplicate ID
    if (isIdExists(id)) {
        cout << "Product ID already exists!\n";
        return;
    }

    products[productCount].id = id;
    cin.ignore();   // Clear buffer

    cout << "Enter Product Name: ";
    getline(cin, products[productCount].name);

    cout << "Enter Quantity: ";
    cin >> products[productCount].quantity;
    if (products[productCount].quantity < 0) {
        cout << "Invalid quantity! Must be 0 or more.\n";
        return;
    }

    cout << "Enter Price: ";
    cin >> products[productCount].price;
    if (products[productCount].price <= 0) {
        cout << "Invalid price! Must be greater than 0.\n";
        return;
    }

    productCount++;
    saveToFile();
    cout << "Product added successfully!\n";
}

/* ---------- CHECK ID ---------- */
bool isIdExists(int id) {
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id)
            return true;
    }
    return false;
}

/* ---------- DISPLAY PRODUCTS ---------- */
void displayProducts() {
    if (productCount == 0) {
        cout << "No products available!\n";
        return;
    }

    cout << "\nID\t Name\t Quantity\t Price\n";
    cout << "----------------------------------\n";

    for (int i = 0; i < productCount; i++) {
        cout << products[i].id << "\t"
             << products[i].name << "\t"
             << products[i].quantity << "\t\t"
             << products[i].price;
        if (products[i].quantity <= 5) {  // Stock alert
            cout << "  <-- Low Stock!";
        }
        cout << endl;
    }
}

/* ---------- SEARCH PRODUCT ---------- */
void searchProduct() {
    string searchName;
    cin.ignore();

    cout << "\nEnter Product Name to search: ";
    getline(cin, searchName);

    for (int i = 0; i < productCount; i++) {
        if (products[i].name == searchName) {
            cout << "\nProduct Found!\n";
            cout << "Name: " << products[i].name << endl;
            cout << "Quantity: " << products[i].quantity;
            if (products[i].quantity <= 5) cout << "  <-- Low Stock!";
            cout << endl;
            cout << "Price: " << products[i].price << endl;
            return;
        }
    }
    cout << "Product not found!\n";
}

/* ---------- PURCHASE PRODUCT ---------- */
void purchaseProduct() {
    int id, qty;
    char confirm;

    cout << "\nEnter Product ID: ";
    cin >> id;

    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {

            cout << "Enter Quantity to purchase: ";
            cin >> qty;

            if (qty <= 0) {
                cout << "Invalid quantity! Must be greater than 0.\n";
                return;
            }

            if (qty > products[i].quantity) {
                cout << "Not enough stock!\n";
                return;
            }

            float total = qty * products[i].price;

            cout << "\n----- BILL -----\n";
            cout << "Product: " << products[i].name << endl;
            cout << "Quantity: " << qty << endl;
            cout << "Total Price: " << total << endl;
            cout << "Confirm order (y/n): ";
            cin >> confirm;

            if (confirm == 'y' || confirm == 'Y') {
                products[i].quantity -= qty;
                saveToFile();
                cout << "Order Confirmed!\n";

                if (products[i].quantity <= 5) {
                    cout << "Warning: Stock for this product is low!\n";
                }
            } else {
                cout << "Order Cancelled!\n";
            }
            return;
        }
    }
    cout << "Product not found!\n";
}

/* ---------- DELETE PRODUCT ---------- */
void deleteProduct() {
    int id;
    cout << "\nEnter Product ID to delete: ";
    cin >> id;

    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {

            for (int j = i; j < productCount - 1; j++) {
                products[j] = products[j + 1];
            }

            productCount--;
            saveToFile();

            cout << "Product deleted successfully!\n";
            return;
        }
    }
    cout << "Product not found!\n";
}

/* ---------- SAVE TO FILE ---------- */
void saveToFile() {
    ofstream file("products.txt");

    for (int i = 0; i < productCount; i++) {
        file << products[i].id << " "
             << products[i].name << " "
             << products[i].quantity << " "
             << products[i].price << endl;
    }

    file.close();
}

/* ---------- LOAD FROM FILE ---------- */
void loadFromFile() {
    ifstream file("products.txt");

    while (file >> products[productCount].id
                >> products[productCount].name
                >> products[productCount].quantity
                >> products[productCount].price) {
        productCount++;
    }

    file.close();
}

/* ---------- MAIN MENU ---------- */
void mainMenu() {
    int choice;

    do {
        cout << "\n===== STORE MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Product\n";
        cout << "2. Display Products\n";
        cout << "3. Search Product\n";
        cout << "4. Purchase Product\n";
        cout << "5. Delete Product\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addProduct(); break;
            case 2: displayProducts(); break;
            case 3: searchProduct(); break;
            case 4: purchaseProduct(); break;
            case 5: deleteProduct(); break;
            case 6: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 6);
}

/* ---------- MAIN FUNCTION ---------- */
int main() {
    loadFromFile();   // Load saved data
    mainMenu();       // Show menu
    return 0;
}
