#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Order
{
private:
    string clientName;
    vector<string> orderedProducts;
    double totalPrice;

public:
    Order() : clientName(""), totalPrice(0.0) {}

    Order(const string &client, const vector<string> &products, double price)
        : clientName(client), orderedProducts(products), totalPrice(price) {}

    void displayInfo() const
    {
        cout << "Client: " << clientName << ", Ordered Products: ";
        for (const auto &product : orderedProducts)
        {
            cout << product << " ";
        }
        cout << ", Total Price: " << totalPrice << " RON" << endl;
    }

    // Getter and Setter pt clientName
    string getClientName() const { return clientName; }
    void setClientName(const string &client) { clientName = client; }

    // Getter and Setter pt orderedProducts
    vector<string> getOrderedProducts() const { return orderedProducts; }
    void setOrderedProducts(const vector<string> &products) { orderedProducts = products; }

    // Getter and Setter pt totalPrice
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
