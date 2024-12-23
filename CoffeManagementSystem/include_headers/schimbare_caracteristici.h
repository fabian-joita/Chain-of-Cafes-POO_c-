#include <iostream>
#include <string>
#include <vector>
#include "CSVHandler.h" // Asigură-te că ai inclus corect această clasă
#include "Employee.h"   // Presupunând că ai o clasă Employee
#include "Product.h"    // Presupunând că ai o clasă Product

using namespace std;

// Funcție de schimbare a detaliilor
void schimbare_detalii(const string &schimbare, const string &locatie)
{
    string path = "/Users/joitafabian/Facultate_C++_KT/Colocviu_CPP/Chain-of-Cafes-POO_c-/CoffeManagementSystem/CSV_FILES/" + locatie + "/";

    if (schimbare == "angajati")
    {
        string finalpath = path + "Angajati_Functii.csv";
        // Citire și modificare detalii angajat
        string targetName;
        cout << "Introduceți numele angajatului de modificat: ";
        cin.ignore();
        std::getline(cin, targetName); // Folosim std::getline pentru a citi numele întreg

        int age;
        cout << "Introduceți vârsta angajatului de modificat: ";
        cin >> age;

        string newPosition;
        cout << "Introduceți noua poziție: ";
        cin >> newPosition;

        double newSalary;
        cout << "Introduceți noul salariu: ";
        cin >> newSalary;

        string newOraInceput, newOraSfarsit;
        cout << "Introduceți noua oră de început (ex: 08:00): ";
        cin >> newOraInceput;
        cout << "Introduceți noua oră de sfârșit (ex: 16:00): ";
        cin >> newOraSfarsit;

        // Citim angajații din fișierul CSV
        vector<vector<string>> angajati = CSV::readCSV(finalpath);

        for (auto &row : angajati)
        {
            if (row[0] == targetName)
            {
                // Modificăm datele angajatului
                row[1] = to_string(age);       // Modificăm vârsta
                row[3] = newPosition;          // Modificăm poziția
                row[2] = to_string(newSalary); // Modificăm salariul
                row[5] = newOraInceput;        // Modificăm ora de început
                row[6] = newOraSfarsit;        // Modificăm ora de sfârșit

                // Scriem înapoi fișierul
                vector<string> headers = {"Nume Angajat", "Varsta", "Salariu", "Funcție", "Locatie", "Ora Început", "Ora Sfârșit"};
                CSV::rewriteCSV(finalpath, angajati, headers); // Utilizăm CSVHandler
                cout << "Datele angajatului " << targetName << " au fost actualizate!" << endl;
                return;
            }
        }
        cout << "Angajatul nu a fost găsit!" << endl;
    }
    else if (schimbare == "produse")
    {
        string finalpath = path + "Produse_Preturi.csv";
        // Citire și modificare detalii produs
        string targetProduct;
        cout << "Introduceți numele produsului de modificat: ";
        cin >> targetProduct;

        double newPrice;
        cout << "Introduceți noul preț: ";
        cin >> newPrice;

        // Citim produsele din fișierul CSV
        vector<vector<string>> produse = CSV::readCSV(finalpath);

        for (auto &row : produse)
        {
            if (row[0] == targetProduct)
            {
                // Modificăm datele produsului
                row[1] = to_string(newPrice); // Modificăm prețul

                // Scriem înapoi fișierul
                vector<string> headers = {"ProductName", "Price"};
                CSV::rewriteCSV(finalpath, produse, headers); // Utilizăm CSVHandler
                cout << "Datele produsului " << targetProduct << " au fost actualizate!" << endl;
                return;
            }
        }
        cout << "Produsul nu a fost găsit!" << endl;
    }
    else if (schimbare == "stocuri")
    {
        string finalpath = path + "stoc.csv";
        // Citire și modificare stoc
        string targetProduct;
        cout << "Introduceți numele produsului de modificat: ";
        cin >> targetProduct;

        int newStock;
        cout << "Introduceți noul stoc: ";
        cin >> newStock;

        // Citim stocurile din fișierul CSV
        vector<vector<string>> stocuri = CSV::readCSV(finalpath);

        for (auto &row : stocuri)
        {
            if (row[0] == targetProduct)
            {
                // Modificăm stocul produsului
                row[1] = to_string(newStock); // Modificăm stocul

                // Scriem înapoi fișierul
                vector<string> headers = {"ProductName", "Stock"};
                CSV::rewriteCSV(finalpath, stocuri, headers); // Utilizăm CSVHandler
                cout << "Stocul produsului " << targetProduct << " a fost actualizat!" << endl;
                return;
            }
        }
        cout << "Produsul nu a fost găsit!" << endl;
    }
    else
    {
        cout << "Opțiune invalidă!" << endl;
    }
}
