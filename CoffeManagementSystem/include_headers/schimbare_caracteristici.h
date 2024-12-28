#include <iostream>
#include <string>
#include <vector>
#include "CSVHandler.h"
#include "Employee.h"
#include "Product.h"

using namespace std;

void schimbare_detalii(const string &schimbare, const string &locatie)
{
    string path = "/Users/joitafabian/Facultate_C++_KT/Colocviu_CPP/Chain-of-Cafes-POO_c-/CoffeManagementSystem/CSV_FILES/" + locatie + "/";

    if (schimbare == "angajati")
    {
        string finalpath = path + "Angajati_Functii.csv";
        string targetName;
        cout << "Introduceti numele angajatului de modificat: ";
        cin.ignore();
        std::getline(cin, targetName);

        int age;
        cout << "Introduceti varsta angajatului de modificat: ";
        cin >> age;

        string newPosition;
        cout << "Introduceti noua pozitie: ";
        cin >> newPosition;

        double newSalary;
        cout << "Introduceti noul salariu: ";
        cin >> newSalary;

        string newOraInceput, newOraSfarsit;
        cout << "Introduceti noua ora de inceput (ex: 08:00): ";
        cin >> newOraInceput;
        cout << "Introduceti noua ora de sfarsit (ex: 16:00): ";
        cin >> newOraSfarsit;

        vector<vector<string>> angajati = CSV::readCSV(finalpath);

        for (auto &row : angajati)
        {
            if (row[0] == targetName)
            {
                row[1] = to_string(age);       // Modificam varsta
                row[3] = newPosition;          // Modificam pozitia
                row[2] = to_string(newSalary); // Modificam salariul
                row[5] = newOraInceput;        // Modificam ora de inceput
                row[6] = newOraSfarsit;        // Modificam ora de sfarsit

                vector<string> headers = {"Nume Angajat", "Varsta", "Salariu", "Functie", "Locatie", "Ora Inceput", "Ora Sfarsit"};
                CSV::rewriteCSV(finalpath, angajati, headers);
                cout << "Datele angajatului " << targetName << " au fost actualizate!" << endl;
                return;
            }
        }
        cout << "Angajatul nu a fost gasit!" << endl;
    }
    else if (schimbare == "produse")
    {
        string finalpath = path + "Produse_Preturi.csv";
        string targetProduct;
        cout << "Introduceti numele produsului de modificat: ";
        cin >> targetProduct;

        double newPrice;
        cout << "Introduceti noul pret: ";
        cin >> newPrice;

        // Citim produsele din fisierul CSV
        vector<vector<string>> produse = CSV::readCSV(finalpath);

        for (auto &row : produse)
        {
            if (row[0] == targetProduct)
            {
                // Modificam datele produsului
                row[1] = to_string(newPrice);

                vector<string> headers = {"ProductName", "Price"};
                CSV::rewriteCSV(finalpath, produse, headers);
                cout << "Datele produsului " << targetProduct << " au fost actualizate!" << endl;
                return;
            }
        }
        cout << "Produsul nu a fost gasit!" << endl;
    }
    else if (schimbare == "stocuri")
    {
        string finalpath = path + "stoc.csv";
        string targetProduct;
        cout << "Introduceti numele produsului de modificat: ";
        cin >> targetProduct;

        int newStock;
        cout << "Introduceti noul stoc: ";
        cin >> newStock;

        vector<vector<string>> stocuri = CSV::readCSV(finalpath);

        for (auto &row : stocuri)
        {
            if (row[0] == targetProduct)
            {
                // Modificam stocul produsului
                row[1] = to_string(newStock);

                vector<string> headers = {"ProductName", "Stock"};
                CSV::rewriteCSV(finalpath, stocuri, headers);
                cout << "Stocul produsului " << targetProduct << " a fost actualizat!" << endl;
                return;
            }
        }
        cout << "Produsul nu a fost gasit!" << endl;
    }
    else
    {
        cout << "Optiune invalida!" << endl;
    }
}
