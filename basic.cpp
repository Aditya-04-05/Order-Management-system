#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;
void save()
{
    system("converter.exe");
}
class Customer
{
public:
    string name;
    string phoneNumber;

    Customer(string name, string phoneNumber)
        : name{name}, phoneNumber{phoneNumber} {}
};
class Order
{
private:
    static int nextOrderId;
    int orderId;
    Customer customer;
    double paymentPaid;
    double paymentRemaining;
    string orderDate;
    string dueDate;
    string status;

public:
    Order(string customerName, string phoneNumber, double paymentPaid, double paymentRemaining,
          string orderDate, string dueDate, string status)
        : orderId{nextOrderId++},
          customer{customerName, phoneNumber},
          paymentPaid{paymentPaid}, paymentRemaining{paymentRemaining},
          orderDate{orderDate}, dueDate{dueDate}, status{status} {}

    int getOrderId() const { return orderId; }
    string getOrderDate() const { return orderDate; }
    string getStatus() const { return status; }
    string getCustomerName() const { return customer.name; }
    double getPaymentPaid() const { return paymentPaid; }
    double getPaymentRemaining() const { return paymentRemaining; }
    string getDueDate() const { return dueDate; }
    static void total()
    {
        cout << nextOrderId - 1 << endl;
    }
    static void resetOrderId()
    {
        nextOrderId = 1;
    }
    void displayOrder() const
    {
        cout << "Order ID: " << orderId << endl;
        cout << "Customer Name: " << customer.name << endl;
        cout << "Phone Number: " << customer.phoneNumber << endl;
        cout << "Payment Paid: " << paymentPaid << endl;
        cout << "Payment Remaining: " << paymentRemaining << endl;
        cout << "Order Date: " << orderDate << endl;
        cout << "Due Date: " << dueDate << endl;
        cout << "Status: " << status << endl;
        cout << "----------------------------------------" << endl;
    }

    void updatePayment(double amount)
    {
        if (amount > paymentRemaining)
        {
            cout << "Payment exceeds the remaining balance!" << endl;
        }
        else
        {
            paymentPaid += amount;
            paymentRemaining -= amount;
            cout << "Payment updated successfully!" << endl;
        }
    }

    void updateStatus(string newStatus)
    {
        status = newStatus;
        cout << "Order status updated to: " << status << endl;
    }

    string toFileString() const
    {
        stringstream ss;
        ss << orderId << "," << customer.name << "," << customer.phoneNumber << ","
           << paymentPaid << "," << paymentRemaining << "," << orderDate << ","
           << dueDate << "," << status;
        return ss.str();
    }

    static Order fromFileString(const string &orderStr)
    {
        stringstream ss(orderStr);
        string token;
        int orderId;
        string name, phone, orderDate, dueDate, status;
        double paymentPaid, paymentRemaining;

        getline(ss, token, ',');
        orderId = stoi(token);
        getline(ss, name, ',');
        getline(ss, phone, ',');
        getline(ss, token, ',');
        paymentPaid = stod(token);
        getline(ss, token, ',');
        paymentRemaining = stod(token);
        getline(ss, orderDate, ',');
        getline(ss, dueDate, ',');
        getline(ss, status, ',');

        if (orderId >= nextOrderId)
            nextOrderId = orderId;

        return Order(name, phone, paymentPaid, paymentRemaining, orderDate, dueDate, status);
    }
};

int Order::nextOrderId = 1;

class OrderManagementSystem
{
private:
    vector<Order> orders;
    const string fileName = "orders.txt";
    const string adminPassword = "securepass"; // Change this to your preferred password

    void saveOrdersToFile() const
    {
        ofstream outFile(fileName);
        for (const auto &order : orders)
        {
            outFile << order.toFileString() << endl;
        }
        outFile.close();
    }

    void loadOrdersFromFile()
    {
        ifstream inFile(fileName);
        string line;
        while (getline(inFile, line))
        {
            orders.push_back(Order::fromFileString(line));
        }
        inFile.close();
    }

    void clearOrdersFromFile()
    {
        ofstream outFile(fileName, ios::trunc); // Open file in truncate mode to clear content
        outFile.close();
    }

public:
    OrderManagementSystem()
    {
        loadOrdersFromFile(); // Load orders when the system starts
    }

    void addOrder(string name, string phoneNumber, double paymentPaid, double paymentRemaining,
                  string orderDate, string dueDate, string status)
    {
        orders.emplace_back(name, phoneNumber, paymentPaid, paymentRemaining, orderDate, dueDate, status);
        cout << "Order added successfully!" << endl;
        orders.back().displayOrder();
        saveOrdersToFile(); // Save orders to file after adding a new order
    }

    void displayAllOrders() const
    {
        if (orders.empty())
        {
            cout << "No orders to display." << endl;
            return;
        }
        for (const auto &order : orders)
        {
            order.displayOrder();
        }
    }

    void updateOrderPayment(int orderId, double amount)
    {
        for (auto &order : orders)
        {
            if (order.getOrderId() == orderId)
            {
                order.updatePayment(amount);
                saveOrdersToFile(); // Save changes to file
                return;
            }
        }
        cout << "Order ID not found!" << endl;
    }

    void updateOrderStatus(int orderId, string newStatus)
    {
        for (auto &order : orders)
        {
            if (order.getOrderId() == orderId)
            {
                order.updateStatus(newStatus);
                saveOrdersToFile(); // Save changes to file
                return;
            }
        }
        cout << "Order ID not found!" << endl;
    }

    void searchByName(const string &name) const
    {
        bool found = false;
        for (const auto &order : orders)
        {
            if (order.getCustomerName() == name)
            {
                order.displayOrder();
                found = true;
            }
        }
        if (!found)
        {
            cout << "No orders found for customer: " << name << endl;
        }
    }

    void searchByOrderId(int orderId) const
    {
        for (const auto &order : orders)
        {
            if (order.getOrderId() == orderId)
            {
                order.displayOrder();
                return;
            }
        }
        cout << "Order ID not found!" << endl;
    }

    void searchByDate(const string &date) const
    {
        bool found = false;
        ofstream outFile(date + ".txt"); // Create a file named after the date

        outFile << "Orders for Date: " << date << "\n";
        outFile << "========================================\n";

        for (const auto &order : orders)
        {
            if (order.getOrderDate() == date)
            {
                found = true;
                outFile << "Order ID       : " << order.getOrderId() << "\n";
                outFile << "Customer Name  : " << order.getCustomerName() << "\n";
                outFile << "Phone Number   : " << order.getCustomerName() << "\n";
                outFile << "Payment Paid   : " << order.getPaymentPaid() << "\n";
                outFile << "Payment Remaining: " << order.getPaymentRemaining() << "\n";
                outFile << "Due Date       : " << order.getDueDate() << "\n";
                outFile << "Status         : " << order.getStatus() << "\n";
                outFile << "----------------------------------------\n";
            }
        }

        if (!found)
        {
            outFile << "No orders found for the date: " << date << "\n";
            cout << "No orders found for the date: " << date << endl;
        }
        else
        {
            cout << "Orders for the date " << date << " have been written to " << date << ".txt" << endl;
        }

        outFile.close();
    }

    void clearDatabase()
    {
        string enteredPassword;
        cout << "Enter the admin password to clear the database: ";
        cin >> enteredPassword;

        if (enteredPassword == adminPassword)
        {
            orders.clear();        // Clear in-memory orders
            clearOrdersFromFile(); // Clear the file content
            Order::resetOrderId();
            cout << "Database cleared successfully!" << endl;
        }
        else
        {
            cout << "Incorrect password. Database not cleared." << endl;
        }
    }
};

int main()
{
    OrderManagementSystem System;
    atexit(save);
    int choice;
    while (true)
    {
        cout << "\nOrder Management System\n";
        cout << "1. Add Order\n";
        cout << "2. Display All Orders\n";
        cout << "3. Update Payment\n";
        cout << "4. Update Order Status\n";
        cout << "5. Search Orders\n";
        cout << "6. Clear Database\n";
        cout << "7. Total Orders\n";
        cout << "8. Save Database\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            string name, phone, orderDate, dueDate, status;
            double paid, remaining;
            cout << "Enter customer name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter phone number: ";
            cin >> phone;
            cout << "Enter payment paid: ";
            cin >> paid;
            cout << "Enter payment remaining: ";
            cin >> remaining;
            cout << "Enter order date (YYYY-MM-DD): ";
            cin >> orderDate;
            cout << "Enter due date (YYYY-MM-DD): ";
            cin >> dueDate;
            cout << "Enter status (e.g., Pending, Completed): ";
            cin.ignore();
            getline(cin, status);
            System.addOrder(name, phone, paid, remaining, orderDate, dueDate, status);
        }
        else if (choice == 2)
        {
            System.displayAllOrders();
        }
        else if (choice == 3)
        {
            int orderId;
            double amount;
            cout << "Enter order ID: ";
            cin >> orderId;
            cout << "Enter amount to pay: ";
            cin >> amount;
            System.updateOrderPayment(orderId, amount);
        }
        else if (choice == 4)
        {
            int orderId;
            string newStatus;
            cout << "Enter order ID: ";
            cin >> orderId;
            cout << "Enter new status: ";
            cin.ignore();
            getline(cin, newStatus);
            System.updateOrderStatus(orderId, newStatus);
        }
        else if (choice == 5)
        {
            int searchChoice;
            cout << "\nSearch Orders by:\n";
            cout << "1. Name\n";
            cout << "2. Order ID\n";
            cout << "3. Date\n";
            cout << "Enter your choice: ";
            cin >> searchChoice;

            if (searchChoice == 1)
            {
                string name;
                cout << "Enter customer name: ";
                cin.ignore();
                getline(cin, name);
                System.searchByName(name);
            }
            else if (searchChoice == 2)
            {
                int orderId;
                cout << "Enter order ID: ";
                cin >> orderId;
                System.searchByOrderId(orderId);
            }
            else if (searchChoice == 3)
            {
                string date;
                cout << "Enter date (YYYY-MM-DD): ";
                cin >> date;
                System.searchByDate(date);
            }
        }
        else if (choice == 6)
        {
            System.clearDatabase();
        }
        else if (choice == 7)
        {
            Order::total();
        }
        else if (choice == 8)
        {
            system("converter.exe");
        }
        else if (choice == 9)
        {
            cout << "Exiting the system...\n";
            break;
        }
        else
        {
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}