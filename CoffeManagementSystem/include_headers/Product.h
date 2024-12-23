#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>

using namespace std;

class Product
{
private:
    string name;  // Product name
    double price; // Product price

public:
    // Constructor
    Product(const string &productName, double productPrice) : name(productName), price(productPrice) {}

    // Method to display product information
    void displayInfo() const
    {
        cout << "Product: " << name << ", Price: " << price << " RON" << endl;
    }

    // Getter and Setter for name
    string getName() const { return name; }
    void setName(const string &productName) { name = productName; }

    // Getter and Setter for price
    double getPrice() const { return price; }
    void setPrice(double productPrice) { price = productPrice; }
};

#endif // PRODUCT_H
