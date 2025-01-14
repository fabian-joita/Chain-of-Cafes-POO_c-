#include "schimbare_caracteristici.h"
#include <iostream>
#include <string>
#include "CSVHandler.h"
#include "Employee.h"
#include "Product.h"

using namespace std;

void schimbare_detalii(const string &schimbare, const string &locatie)
{
    string path = (languageOption == "EN") ? "/Users/joitafabian/Facultate_C++_KT/Colocviu_CPP/Chain-of-Cafes-POO_c-/CoffeManagementSystem/CSV_FILES_ENGLISH/" + locatie + "/"
                                           : "/Users/joitafabian/Facultate_C++_KT/Colocviu_CPP/Chain-of-Cafes-POO_c-/CoffeManagementSystem/CSV_FILES/" + locatie + "/";

    if (schimbare == "angajati" || schimbare == "employees")
    {
        string finalpath = (languageOption == "EN") ? path + "Employees_Roles.csv" : path + "Angajati_Functii.csv";
        string targetName;

        cout << ((languageOption == "EN") ? "Enter the name of the employee to modify: " : "Introduceti numele angajatului de modificat: ");
        cin.ignore();
        std::getline(cin, targetName);

        int age;
        cout << ((languageOption == "EN") ? "Enter the employee's age: " : "Introduceti varsta angajatului de modificat: ");
        cin >> age;

        string newPosition;
        cout << ((languageOption == "EN") ? "Enter the new position: " : "Introduceti noua pozitie: ");
        cin >> newPosition;

        double newSalary;
        cout << ((languageOption == "EN") ? "Enter the new salary: " : "Introduceti noul salariu: ");
        cin >> newSalary;

        string newOraInceput, newOraSfarsit;
        cout << ((languageOption == "EN") ? "Enter the new start time (e.g., 08:00): " : "Introduceti noua ora de inceput (ex: 08:00): ");
        cin >> newOraInceput;
        cout << ((languageOption == "EN") ? "Enter the new end time (e.g., 16:00): " : "Introduceti noua ora de sfarsit (ex: 16:00): ");
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

                vector<string> headers;
                if (languageOption == "EN")
                {
                    headers = {"Employee Name", "Age", "Salary", "Position", "Location", "Start Time", "End Time"};
                }
                else
                {
                    headers = {"Nume Angajat", "Varsta", "Salariu", "Functie", "Locatie", "Ora Inceput", "Ora Sfarsit"};
                }

                CSV::rewriteCSV(finalpath, angajati, headers);

                cout << ((languageOption == "EN") ? "Employee data for " : "Datele angajatului ") << targetName
                     << ((languageOption == "EN") ? " has been updated!" : " au fost actualizate!") << endl;
                return;
            }
        }

        cout << ((languageOption == "EN") ? "Employee not found!" : "Angajatul nu a fost gasit!") << endl;
    }
    else if (schimbare == "produse" || schimbare == "products")
    {
        string finalpath = (languageOption == "EN") ? path + "Products_Prices.csv" : path + "Produse_Preturi.csv";
        string targetProduct;
        cout << ((languageOption == "EN") ? "Enter the name of the product to modify: " : "Introduceti numele produsului de modificat: ");
        cin.ignore();
        getline(cin, targetProduct);

        double newPrice;
        cout << ((languageOption == "EN") ? "Enter the new price: " : "Introduceti noul pret: ");
        cin >> newPrice;

        vector<vector<string>> produse = CSV::readCSV(finalpath);

        for (auto &row : produse)
        {
            cout << "Checking product: " << row[0] << endl; // Debug
            if (row[0] == targetProduct)
            {
                cout << "Product found! Modifying..." << endl; // Debug
                row[1] = to_string(newPrice);
                vector<string> headers = {"ProductName", "Price"};
                CSV::rewriteCSV(finalpath, produse, headers);
                cout << ((languageOption == "EN") ? "Product data for " : "Datele produsului ") << targetProduct << ((languageOption == "EN") ? " has been updated!" : " au fost actualizate!") << endl;
                return;
            }
        }

        cout << ((languageOption == "EN") ? "Product not found!" : "Produsul nu a fost gasit!") << endl;
    }
    else if (schimbare == "stocuri" || schimbare == "stock")
    {
        string finalpath = (languageOption == "EN") ? path + "stock.csv" : path + "stoc.csv";
        string targetProduct;
        cout << ((languageOption == "EN") ? "Enter the name of the product to modify: " : "Introduceti numele produsului de modificat: ");
        cin >> targetProduct;

        int newStock;
        cout << ((languageOption == "EN") ? "Enter the new stock: " : "Introduceti noul stoc: ");
        cin >> newStock;

        vector<vector<string>> stocuri = CSV::readCSV(finalpath);

        for (auto &row : stocuri)
        {
            if (row[0] == targetProduct)
            {
                row[1] = to_string(newStock);

                vector<string> headers;
                if (languageOption == "EN")
                {
                    headers = {"ProductName", "Stock"};
                }
                else
                {
                    headers = {"Produs", "Stoc"};
                }

                CSV::rewriteCSV(finalpath, stocuri, headers);

                cout << ((languageOption == "EN") ? "Stock data for " : "Stocul produsului ")
                     << targetProduct
                     << ((languageOption == "EN") ? " has been updated!" : " a fost actualizat!")
                     << endl;
                return;
            }
        }
        cout << ((languageOption == "EN") ? "Product not found!" : "Produsul nu a fost gasit!") << endl;
    }
    else
    {
        cout << ((languageOption == "EN") ? "Invalid option!" : "Optiune invalida!") << endl;
    }
}
