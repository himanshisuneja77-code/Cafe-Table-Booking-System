# Cafe Table Booking & Management System ☕

A high-performance console application developed in **C++** that digitizes the operations of a modern cafe. This project utilizes **Object-Oriented Programming (OOP)** and **File Handling** to manage customer data, table reservations, food orders, and automated billing.

## 🚀 Key Features

- **User Authentication:** Secure registration and login for customers.
- **Table Management:** Real-time availability checks to prevent double-booking on the same date.
- **Interactive Menu:** A selection of 10 food/drink items with dynamic quantity selection.
- **Automated Billing:** Instant invoice generation with a 5% GST calculation.
- **Admin Panel:** A protected administrative area (Username: `admin`, Password: `admin123`) to search, update, and delete bookings.
- **Persistent Storage:** All data is stored in `.txt` files, acting as a lightweight database.

## 🏗️ System Architecture

The project is built on a **Multilevel Inheritance** model, ensuring a seamless flow of data from the user's identity to the final financial transaction.



### Class Hierarchy:
1. **Customer:** Handles basic profile data and authentication.
2. **Booking (Inherits Customer):** Manages table IDs and reservation dates.
3. **Order (Inherits Booking):** Handles the food menu and calculates the subtotal.
4. **Bill (Inherits Order):** Finalizes the invoice with taxes and saves the transaction.

## 🛠️ OOP Concepts Implemented

- **Encapsulation:** Data members are protected to prevent unauthorized external access.
- **Polymorphism:** Used virtual functions for displaying summaries, allowing for dynamic binding.
- **File Handling:** Uses `ifstream` and `ofstream` with custom delimiters (`|`) for data parsing.
- **Constructors/Destructors:** Ensures proper object initialization and memory cleanup.
- **Abstraction:** Complex file-swapping logic for record updates is hidden behind simple method calls.

## 📂 File Structure

The system automatically generates and manages the following files:
- `customers.txt`: Stores registered user credentials.
- `bookings.txt`: Contains all table reservation records.
- `orders.txt`: Itemized history of all food orders.
- `bills.txt`: Finalized billing statements for accounting.

