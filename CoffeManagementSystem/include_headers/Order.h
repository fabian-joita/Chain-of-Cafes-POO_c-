#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Order
{
private:
    string clientName;              // Name of the client
    vector<string> orderedProducts; // List of ordered products
    double totalPrice;              // Total price of the order

public:
    // Default constructor
    Order() : clientName(""), totalPrice(0.0) {}

    // Parameterized constructor
    Order(const string &client, const vector<string> &products, double price)
        : clientName(client), orderedProducts(products), totalPrice(price) {}

    // Method to display order information
    void displayInfo() const
    {
        cout << "Client: " << clientName << ", Ordered Products: ";
        for (const auto &product : orderedProducts)
        {
            cout << product << " ";
        }
        cout << ", Total Price: " << totalPrice << " RON" << endl;
    }

    // Getter and Setter for clientName
    string getClientName() const { return clientName; }
    void setClientName(const string &client) { clientName = client; }

    // Getter and Setter for orderedProducts
    vector<string> getOrderedProducts() const { return orderedProducts; }
    void setOrderedProducts(const vector<string> &products) { orderedProducts = products; }

    // Getter and Setter for totalPrice
    double getTotalPrice() const { return totalPrice; }
    void setTotalPrice(double price) { totalPrice = price; }

    // Operator<< for easy printing of the order
    friend ostream &operator<<(ostream &os, const Order &order)
    {
        os << "Client: " << order.clientName << ", Ordered Products: ";
        for (const auto &product : order.orderedProducts)
        {
            os << product << " ";
        }
        os << ", Total Price: " << order.totalPrice << " RON";
        return os;
    }
};

#endif // ORDER_H
