#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>

using namespace std;

class Produs
{
private:
    string nume;
    double pret;

public:
    // Constructor
    Produs(const string &numeProdus, double pretProdus) : nume(numeProdus), pret(pretProdus) {}

    // Metoda de afisare
    void displayInfo() const
    {
        cout << "Produs: " << nume << ", Pret: " << pret << " RON" << endl;
    }

    // Getter pentru date
    string getNume() const { return nume; }
    double getPret() const { return pret; }
};

#endif // PRODUCT_H
