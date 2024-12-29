#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>
#include "Globals.h"

using namespace std;

class Product
{
private:
    string name;
    double price;

public:
    Product(const string &productName, double productPrice) : name(productName), price(productPrice) {}

    void displayInfo() const
    {
        cout << "Product: " << name << ", Price: " << price << " RON" << endl;
    }

    string getName() const { return name; }
    void setName(const string &productName) { name = productName; }

    double getPrice() const { return price; }
    void setPrice(double productPrice) { price = productPrice; }
};

#endif
