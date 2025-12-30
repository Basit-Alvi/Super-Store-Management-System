#include <iostream>
using namespace std;

/* ---------- STRUCTURE FOR PRODUCT ---------- */
struct Product {
    int id;
    char name[30]; /*TO STORE PRODUCT NAME UPTO 30 CHARACTER------*/
    int quantity;
    float price;
};



/* ---------- GLOBAL VARIABLE ---------- */
Product products[100];  /*TO STORE 100 PRODUCT A TIME-----*/

int productCount = 0;   /*USED TO DISPLAY TOTAL PRODUCT ON SCREEN----*/

/* ---------- FUNCTION DECLARATIONS ---------- */
void addProduct();     /* TO ADD PRODUCTS----*/
void displayProducts();/* TO DISPLAY TOTAL PRODUCTS----*/
void searchProduct();  /*TO SEARCH AVAILABILITY OF PRODUCT---*/
void purchaseProduct();/*TO PURCHASE PRODUCT---*/
void mainMenu();       /*TO DISPLAY MENU---*/
void deleteProduct();  /*TO DELETE PRODUCT---*/
bool isIdExists(int id);/*TO NOT ADD PRODUCT WITH SAME ID---*/



/* ---------- ADD PRODUCT ---------- */
void addProduct() {
    int id;

    cout << "\nEnter Product ID: ";
    cin >> id;

    if (isIdExists(id)) {
        cout << "\n? Product ID already exists! Use a unique ID.\n";
        return;
    }

    products[productCount].id = id;
	    cin.ignore();

    cout << "Enter Product Name: ";
    cin.getline(products[productCount].name, 30);

    cout << "\n Enter Quantity: ";
    cin >> products[productCount].quantity;

    cout << "Enter Price: ";
    cin >> products[productCount].price;

   productCount++;
    cout << "\n? Product added successfully!\n";
}

/*TO CHECK ID IS NOT SAME FOR ANY PRODUCT---*/
bool isIdExists(int id) {
    for (int i = 0; i < productCount; i++)/*IF i IS LESS THAN THE TOTAL NUMBER OF PRODUCT--*/ {
        if (products[i].id == id) {
            return true; // ID already exists
        }
    }
    return false; // ID is unique
}

void deleteProduct() {
    int id;
    cout << "\nEnter Product ID to delete: ";
    cin >> id;

    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {

            // Shift products left
            for (int j = i; j < productCount - 1; j++) {
                products[j] = products[j + 1];
            }

            productCount--;
            cout << "\n? Product deleted successfully!\n";
            return;
        }
    }

    cout << "\n? Product not found!\n";
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
    string  searchName;
    cout << "\nEnter Product Name to search: ";
    cin >> searchName;

    for (int i = 0; i < productCount; i++) {
        if (products[i].name == searchName) {
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
            case 6: cout << "\nThank you! Exiting program.\n"; break;
            default: cout << "\nInvalid choice! Try again.\n";
        }
    } while (choice != 6);
}

/* ---------- MAIN FUNCTION ---------- */
int main() {
	
    mainMenu();
    return 0;
    
}


