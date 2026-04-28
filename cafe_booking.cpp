#include<bits/stdc++.h>
using namespace std;

// ================= CUSTOMER CLASS =================
class Customer {
protected:
    int customerID;
    string name;
    string phone;
    string username;
    string password;

    // Check duplicate Customer ID
    bool isDuplicateCustomerID(int id) {
        ifstream file("customers.txt");
        if (!file.is_open()) return false;

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string tempID;
            getline(ss, tempID, '|');

            if (stoi(tempID) == id) {
                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }

public:
    // Constructor
    Customer() {
        customerID = 0;
        name = "";
        phone = "";
        username = "";
        password = "";
    }

    // Customer Registration Function
    void registerCustomer() {
        ofstream file("customers.txt", ios::app);

        if (!file.is_open()) {
            cout << "\nError opening customer file!\n";
            return;
        }

        cout << "\n================ CUSTOMER REGISTRATION ================\n";

        while (true) {
            cout << "Enter Customer ID: ";
            cin >> customerID;

            if (cin.fail() || customerID <= 0) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid ID! Please enter positive numbers only.\n";
                continue;
            }

            if (isDuplicateCustomerID(customerID)) {
                cout << "Customer ID already exists! Enter unique ID.\n";
                continue;
            }

            break;
        }

        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Phone Number: ";
        getline(cin, phone);

        cout << "Enter Username: ";
        getline(cin, username);

        cout << "Enter Password: ";
        getline(cin, password);

        // Plain text password storage
        file << customerID << "|"
             << name << "|"
             << phone << "|"
             << username << "|"
             << password << endl;

        file.close();

        cout << "\nCustomer Registered Successfully!\n";
    }

    // Customer Login Function
    bool loginCustomer() {
        string user, pass;
        bool found = false;

        cout << "\n================ CUSTOMER LOGIN =================\n";

        cout << "Enter Username: ";
        cin >> user;

        cout << "Enter Password: ";
        cin >> pass;

        ifstream file("customers.txt");

        if (!file.is_open()) {
            cout << "\nError opening customer records!\n";
            return false;
        }

        string id, nm, ph, u, p;

        while (getline(file, id, '|')) {
            getline(file, nm, '|');
            getline(file, ph, '|');
            getline(file, u, '|');
            getline(file, p);

            if (u == user && p == pass) {
                customerID = stoi(id);
                name = nm;
                phone = ph;
                username = u;
                password = p;

                found = true;
                break;
            }
        }

        file.close();

        if (found) {
            cout << "\nLogin Successful!\n";
            cout << "Welcome, " << name << endl;
            return true;
        } else {
            cout << "\nInvalid Username or Password!\n";
            return false;
        }
    }

    // Virtual Display Function
    virtual void displayCustomer() {
        cout << "\nCustomer ID: " << customerID;
        cout << "\nName: " << name;
        cout << "\nPhone: " << phone;
        cout << "\nUsername: " << username << endl;
    }

    // Getter
    int getCustomerID() {
        return customerID;
    }

    // Destructor
    virtual ~Customer() {}
};
// ================= BOOKING CLASS =================
class Booking : public Customer {
protected:
    int bookingID;
    int tableNumber;
    string bookingDate;

    // Check duplicate Booking ID
    bool isDuplicateBookingID(int id) {
        ifstream file("bookings.txt");
        if (!file.is_open()) return false;

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string tempID;
            getline(ss, tempID, '|');

            if (stoi(tempID) == id) {
                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }

    // Check if table is already booked on same date
    bool isTableBooked(int table, string date) {
        ifstream file("bookings.txt");
        if (!file.is_open()) return false;

        string line;
        while (getline(file, line)) {
            stringstream ss(line);

            string booking, customer, tableNo, bookDate;

            getline(ss, booking, '|');
            getline(ss, customer, '|');
            getline(ss, tableNo, '|');
            getline(ss, bookDate);

            if (stoi(tableNo) == table && bookDate == date) {
                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }

public:
    // Constructor
    Booking() {
        bookingID = 0;
        tableNumber = 0;
        bookingDate = "";
    }

    // Display Available Tables
    void displayTables() {
        cout << "\n===== Available Tables =====\n";
        for (int i = 1; i <= 10; i++) {
            cout << "Table Number: " << i << endl;
        }
    }

    // Book Table Function
    void bookTable() {
        ofstream file("bookings.txt", ios::app);

        if (!file.is_open()) {
            cout << "\nError opening booking file!\n";
            return;
        }

        cout << "\n================ TABLE BOOKING SCREEN =================\n";

        while (true) {
            cout << "Enter Booking ID: ";
            cin >> bookingID;

            if (cin.fail() || bookingID <= 0) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid Booking ID! Enter positive number.\n";
                continue;
            }

            if (isDuplicateBookingID(bookingID)) {
                cout << "Booking ID already exists! Enter unique ID.\n";
                continue;
            }

            break;
        }

        displayTables();

        while (true) {
            cout << "Enter Table Number: ";
            cin >> tableNumber;

            if (cin.fail() || tableNumber <= 0 || tableNumber > 10) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid Table Number! Choose between 1-10.\n";
                continue;
            }

            break;
        }

        cin.ignore();

        cout << "Enter Booking Date: ";
        getline(cin, bookingDate);

        if (isTableBooked(tableNumber, bookingDate)) {
            cout << "\nTable already booked for this date!\n";
            file.close();
            return;
        }

        file << bookingID << "|"
             << customerID << "|"
             << tableNumber << "|"
             << bookingDate << endl;

        file.close();

        cout << "\nTable Booked Successfully!\n";
    }

    // Search Booking Function
    void searchBooking() {
        int searchID;
        bool found = false;

        cout << "\nEnter Booking ID to Search: ";
        cin >> searchID;

        ifstream file("bookings.txt");

        if (!file.is_open()) {
            cout << "\nError opening booking file!\n";
            return;
        }

        string line;

        while (getline(file, line)) {
            stringstream ss(line.substr(0, line.find('|')));
            int id;
            ss >> id;

            if (id == searchID) {
                stringstream data(line);

                string booking, customer, table, date;

                getline(data, booking, '|');
                getline(data, customer, '|');
                getline(data, table, '|');
                getline(data, date);

                cout << "\nBooking Found:\n";
                cout << "Booking ID   : " << booking << endl;
                cout << "Customer ID  : " << customer << endl;
                cout << "Table Number : " << table << endl;
                cout << "Booking Date : " << date << endl;

                found = true;
                break;
            }
        }

        file.close();

        if (!found) {
            cout << "\nBooking Not Found!\n";
        }
    }

    // Update Booking Function
    void updateBooking() {
        int updateID;
        bool found = false;

        cout << "\nEnter Booking ID to Update: ";
        cin >> updateID;

        ifstream file("bookings.txt");
        ofstream temp("temp.txt");

        if (!file.is_open() || !temp.is_open()) {
            cout << "\nError opening booking files!\n";
            return;
        }

        string line;

        while (getline(file, line)) {
            stringstream ss(line.substr(0, line.find('|')));
            int id;
            ss >> id;

            if (id == updateID) {
                int newTable;
                string newDate;
                string booking, customer;

                stringstream data(line);

                getline(data, booking, '|');
                getline(data, customer, '|');

                while (true) {
                    cout << "Enter New Table Number: ";
                    cin >> newTable;

                    if (cin.fail() || newTable <= 0 || newTable > 10) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Invalid Table Number!\n";
                        continue;
                    }

                    break;
                }

                cin.ignore();

                cout << "Enter New Booking Date: ";
                getline(cin, newDate);

                if (isTableBooked(newTable, newDate)) {
                    cout << "\nTable already booked on this date!\n";
                    temp << line << endl;
                } else {
                    temp << booking << "|"
                         << customer << "|"
                         << newTable << "|"
                         << newDate << endl;

                    found = true;
                }

            } else {
                temp << line << endl;
            }
        }

        file.close();
        temp.close();

        remove("bookings.txt");
        rename("temp.txt", "bookings.txt");

        if (found) {
            cout << "\nBooking Updated Successfully!\n";
        } else {
            cout << "\nBooking ID Not Found or Update Failed!\n";
        }
    }

    // Cancel/Delete Booking Function
    void cancelBooking() {
        int cancelID;
        bool found = false;

        cout << "\nEnter Booking ID to Cancel/Delete: ";
        cin >> cancelID;

        ifstream file("bookings.txt");
        ofstream temp("temp.txt");

        if (!file.is_open() || !temp.is_open()) {
            cout << "\nError opening booking files!\n";
            return;
        }

        string line;

        while (getline(file, line)) {
            stringstream ss(line.substr(0, line.find('|')));
            int id;
            ss >> id;

            if (id != cancelID) {
                temp << line << endl;
            } else {
                found = true;
            }
        }

        file.close();
        temp.close();

        remove("bookings.txt");
        rename("temp.txt", "bookings.txt");

        if (found) {
            cout << "\nBooking Cancelled Successfully!\n";
        } else {
            cout << "\nBooking ID Not Found!\n";
        }
    }

    // Virtual Display Function
    virtual void displayBooking() {
        cout << "\nBooking ID   : " << bookingID;
        cout << "\nTable Number : " << tableNumber;
        cout << "\nBooking Date : " << bookingDate << endl;
    }

    // Destructor
    virtual ~Booking() {}
};
// ================= ORDER CLASS =================
class Order : public Booking {
protected:
    float totalAmount;

public:
    // Constructor
    Order() {
        totalAmount = 0;
    }

    // Display Food Menu (Polymorphism)
    virtual void displayMenu() {
        cout << "\n===== Cafe Food Menu =====\n";
        cout << "1. Coffee        - Rs.120\n";
        cout << "2. Sandwich      - Rs.180\n";
        cout << "3. Pizza         - Rs.350\n";
        cout << "4. Pasta         - Rs.250\n";
        cout << "5. Cold Drink    - Rs.90\n";
        cout << "6. Burger        - Rs.220\n";
        cout << "7. French Fries  - Rs.150\n";
        cout << "8. Momos         - Rs.160\n";
        cout << "9. Ice Cream     - Rs.130\n";
        cout << "10. Brownie      - Rs.200\n";
    }

    // Place Order Function
    void placeOrder() {
        int choice, quantity;
        char more;

        // Reset total for new order session
        totalAmount = 0;

        ofstream file("orders.txt", ios::app);

        if (!file.is_open()) {
            cout << "\nError opening orders file!\n";
            return;
        }

        do {
            displayMenu();

            cout << "\nEnter Food Choice: ";
            cin >> choice;

            if (cin.fail() || choice < 1 || choice > 10) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid Choice!\n";
                continue;
            }

            cout << "Enter Quantity: ";
            cin >> quantity;

            if (cin.fail() || quantity <= 0) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid Quantity! Must be positive.\n";
                continue;
            }

            float itemCost = 0;
            string itemName;

            if (choice == 1) {
                itemName = "Coffee";
                itemCost = 120 * quantity;
            } else if (choice == 2) {
                itemName = "Sandwich";
                itemCost = 180 * quantity;
            } else if (choice == 3) {
                itemName = "Pizza";
                itemCost = 350 * quantity;
            } else if (choice == 4) {
                itemName = "Pasta";
                itemCost = 250 * quantity;
            } else if (choice == 5) {
                itemName = "Cold Drink";
                itemCost = 90 * quantity;
            } else if (choice == 6) {
                itemName = "Burger";
                itemCost = 220 * quantity;
            } else if (choice == 7) {
                itemName = "French Fries";
                itemCost = 150 * quantity;
            } else if (choice == 8) {
                itemName = "Momos";
                itemCost = 160 * quantity;
            } else if (choice == 9) {
                itemName = "Ice Cream";
                itemCost = 130 * quantity;
            } else if (choice == 10) {
                itemName = "Brownie";
                itemCost = 200 * quantity;
            }

            totalAmount += itemCost;

            // Save each order item
            file << customerID << "|"
                 << bookingID << "|"
                 << itemName << "|"
                 << quantity << "|"
                 << itemCost << endl;

            cout << itemName << " added successfully! Cost: Rs." << itemCost << endl;

            cout << "Do You Want to Add More Items? (y/n): ";
            cin >> more;

        } while (more == 'y' || more == 'Y');

        file.close();

        cout << "\nTotal Order Amount: Rs." << totalAmount << endl;
    }

    // Return Total Amount
    float getTotal() {
        return totalAmount;
    }

    // Display Order Summary
    virtual void displayOrder() {
        cout << "\nTotal Order Amount: Rs." << totalAmount << endl;
    }

    // Destructor
    virtual ~Order() {}
};
// ================= BILL CLASS =================
class Bill : public Order {
public:
    // Constructor
    Bill() {}

    // Generate Final Bill
    void generateBill() {
        if (totalAmount <= 0) {
            cout << "\nNo order placed yet! Please place an order first.\n";
            return;
        }

        float tax;
        float finalBill;

        tax = getTotal() * 0.05;   // 5% GST
        finalBill = getTotal() + tax;

        cout << "\n======= FINAL BILL =======\n";
        cout << fixed << setprecision(2);
        cout << "Customer ID : " << customerID << endl;
        cout << "Booking ID  : " << bookingID << endl;
        cout << "Food Total  : Rs." << getTotal() << endl;
        cout << "GST (5%)    : Rs." << tax << endl;
        cout << "Final Bill  : Rs." << finalBill << endl;
        cout << "==========================\n";

        // Save bill record
        ofstream file("bills.txt", ios::app);

        if (!file.is_open()) {
            cout << "\nError opening bills file!\n";
            return;
        }

        file << customerID << "|"
             << bookingID << "|"
             << fixed << setprecision(2)
             << getTotal() << "|"
             << tax << "|"
             << finalBill << endl;

        file.close();

        cout << "\nBill saved successfully!\n";
    }

    // Display Bill Details (Polymorphism)
    virtual void displayBill() {
        float tax = getTotal() * 0.05;
        float finalBill = getTotal() + tax;

        cout << "\nCustomer ID : " << customerID;
        cout << "\nBooking ID  : " << bookingID;
        cout << "\nFood Total  : Rs." << getTotal();
        cout << "\nGST (5%)    : Rs." << tax;
        cout << "\nFinal Bill  : Rs." << finalBill << endl;
    }

    // Destructor
    virtual ~Bill() {}
};
// ================= ADMIN PANEL FUNCTION =================
bool adminLogin() {
    string adminUser, adminPass;

    cout << "\n=========== ADMIN LOGIN ===========\n";
    cout << "Enter Admin Username: ";
    cin >> adminUser;

    cout << "Enter Admin Password: ";
    cin >> adminPass;

    // Hardcoded admin credentials
    if (adminUser == "admin" && adminPass == "admin123") {
        cout << "\nAdmin Login Successful!\n";
        return true;
    } else {
        cout << "\nInvalid Admin Credentials!\n";
        return false;
    }
}

void adminPanel() {
    if (!adminLogin()) {
        return;
    }

    Booking booking;
    int choice;

    do {
        cout << "\n============= ADMIN PANEL =============\n";
        cout << "1. Search Booking\n";
        cout << "2. Update Booking\n";
        cout << "3. Delete Booking\n";
        cout << "4. View All Bookings\n";
        cout << "5. Exit Admin Panel\n";
        cout << "=======================================\n";
        cout << "Enter Choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Input! Please enter numbers only.\n";
            continue;
        }

        if (choice == 1) {
            booking.searchBooking();

        } else if (choice == 2) {
            booking.updateBooking();

        } else if (choice == 3) {
            booking.cancelBooking();

        } else if (choice == 4) {
            ifstream file("bookings.txt");

            if (!file.is_open()) {
                cout << "\nError opening bookings file!\n";
                continue;
            }

            string line;
            cout << "\n========= ALL BOOKINGS =========\n";

            while (getline(file, line)) {
                stringstream data(line);

                string bookingID, customerID, tableNumber, bookingDate;

                getline(data, bookingID, '|');
                getline(data, customerID, '|');
                getline(data, tableNumber, '|');
                getline(data, bookingDate);

                cout << "Booking ID   : " << bookingID << endl;
                cout << "Customer ID  : " << customerID << endl;
                cout << "Table Number : " << tableNumber << endl;
                cout << "Booking Date : " << bookingDate << endl;
                cout << "-------------------------------\n";
            }

            file.close();

        } else if (choice == 5) {
            cout << "\nExiting Admin Panel...\n";

        } else {
            cout << "Invalid Choice!\n";
        }

    } while (choice != 5);
}
// ================= LOGIN / REGISTRATION PANEL =================
bool showLoginPanel(Bill &cafe) {
    int choice;

    while (true) {
        cout << "\n=====================================\n";
        cout << "       CAFE MANAGEMENT SYSTEM        \n";
        cout << "=====================================\n";
        cout << "1. Login (Existing Customer)\n";
        cout << "2. Register (New Customer)\n";
        cout << "3. Exit\n";
        cout << "=====================================\n";
        cout << "Enter Selection: ";
        cin >> choice;

        // Input validation
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Input! Please enter numbers only.\n";
            continue;
        }

        if (choice == 1) {
            if (cafe.loginCustomer()) {
                return true;
            }

        } else if (choice == 2) {
            cafe.registerCustomer();

        } else if (choice == 3) {
            cout << "\nThank You for Visiting Cafe Management System!\n";
            exit(0);

        } else {
            cout << "Invalid Choice! Try again.\n";
        }
    }
}


// ================= MAIN FUNCTION =================
int main() {
    Bill cafe;
    int choice;
    bool loggedIn = false;

    // Initial Login/Register
    loggedIn = showLoginPanel(cafe);

    while (true) {
        if (!loggedIn) {
            loggedIn = showLoginPanel(cafe);
        }

        cout << "\n========== CAFE TABLE BOOKING SYSTEM ==========\n";
        cout << "1. Display Available Tables\n";
        cout << "2. Book Table\n";
        cout << "3. Cancel Booking\n";
        cout << "4. Search Booking\n";
        cout << "5. Update Booking\n";
        cout << "6. Place Food Order\n";
        cout << "7. Generate Bill\n";
        cout << "8. Admin Panel\n";
        cout << "9. Logout\n";
        cout << "10. Exit\n";
        cout << "===============================================\n";
        cout << "Enter Your Choice: ";
        cin >> choice;

        // Input validation
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Input! Please enter valid numeric choice.\n";
            continue;
        }

        if (choice == 1) {
            cafe.displayTables();

        } else if (choice == 2) {
            cafe.bookTable();

        } else if (choice == 3) {
            cafe.cancelBooking();

        } else if (choice == 4) {
            cafe.searchBooking();

        } else if (choice == 5) {
            cafe.updateBooking();

        } else if (choice == 6) {
            cafe.placeOrder();

        } else if (choice == 7) {
            cafe.generateBill();

        } else if (choice == 8) {
            adminPanel();

        } else if (choice == 9) {
            cout << "\nLogging Out Successfully...\n";
            loggedIn = false;

        } else if (choice == 10) {
            cout << "\nThank You for Using Cafe Table Booking System!\n";
            break;

        } else {
            cout << "Invalid Choice!\n";
        }
    }

    return 0;
}