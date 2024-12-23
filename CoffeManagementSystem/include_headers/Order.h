#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Comanda
{
private:
    string numeClient;
    vector<string> produseComandate;
    double pretTotal;

public:
    // Constructor
    Comanda(const string &nume, const vector<string> &produse, double pret)
        : numeClient(nume), produseComandate(produse), pretTotal(pret) {}

    // Metoda de afisare
    void displayInfo() const
    {
        cout << "Client: " << numeClient << ", Produse Comandate: ";
        for (const auto &produs : produseComandate)
        {
            cout << produs << " ";
        }
        cout << ", Pret Total: " << pretTotal << " RON" << endl;
    }

    // Getter pentru date
    string getNumeClient() const { return numeClient; }
    vector<string> getProduseComandate() const { return produseComandate; }
    double getPretTotal() const { return pretTotal; }
};

#endif // ORDER_H
