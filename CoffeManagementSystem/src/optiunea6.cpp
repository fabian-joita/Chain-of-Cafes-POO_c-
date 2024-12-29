#include "optiunea6.h"
#include "Employee.h"
#include "Order.h"
#include "Product.h"
#include <filesystem>
#include <sstream>
#include <iostream>

using namespace std;

void Optiunea6::writeCSVFile(const string &basePath, const string &cafeLocation)
{
    CSV newCSV;

    if (languageOption == "EN")
    {
        cout << "Choose the type of CSV file you want to write (1/2/3):" << endl;
        cout << "1. Employees and Roles" << endl;
        cout << "2. Products and Prices" << endl;
        cout << "3. Ingredient Stock" << endl;
    }
    else
    {
        cout << "Alege tipul de fisier CSV pe care doresti sa-l scrii (1/2/3):" << endl;
        cout << "1. Angajati si Functii" << endl;
        cout << "2. Produse si Preturi" << endl;
        cout << "3. Stoc Ingrediente" << endl;
    }

    int alegere;
    cin >> alegere;

    vector<string> headers;
    vector<vector<string>> data;
    string dataString;
    string finalpath;

    string numeAngajat, functie, locatie;
    int salariu = 0, varsta = 0;
    string oraInceput, oraSfarsit;
    string numeProdus, numeClient, produseStr;
    float pretProdus = 0.0, pretTotal = 0.0;
    string ingredientName;
    int ingredientGramaj = 0;

    switch (alegere)
    {
    case 1:
    {
        finalpath = basePath + "/" + cafeLocation + "/" + ((languageOption == "EN") ? "Employees_Roles.csv" : "Angajati_Functii.csv");
        if (newCSV.readCSV(finalpath).empty())
        {
            headers = {(languageOption == "EN") ? "Employee Name" : "Nume Angajat",
                       (languageOption == "EN") ? "Age" : "Varsta",
                       (languageOption == "EN") ? "Salary" : "Salariu",
                       (languageOption == "EN") ? "Role" : "Functie",
                       (languageOption == "EN") ? "Location" : "Locatie",
                       (languageOption == "EN") ? "Start Time" : "Ora Inceput",
                       (languageOption == "EN") ? "End Time" : "Ora Sfarsit"};
        }

        cout << ((languageOption == "EN") ? "Enter employee details in the following order:" : "Se citesc datele in urmatoarea ordine:") << endl;
        cout << ((languageOption == "EN") ? "1. Employee Name: " : "1. Nume Angajat: ");
        cin.ignore();
        std::getline(cin, numeAngajat);
        cout << ((languageOption == "EN") ? "2. Age: " : "2. Varsta: ");
        cin >> varsta;
        cout << ((languageOption == "EN") ? "3. Salary: " : "3. Salariu: ");
        cin >> salariu;
        cout << ((languageOption == "EN") ? "4. Role: " : "4. Functie: ");
        cin >> functie;
        cout << ((languageOption == "EN") ? "5. Start Time: " : "5. Ora Inceput: ");
        cin >> oraInceput;
        cout << ((languageOption == "EN") ? "6. End Time: " : "6. Ora Sfarsit: ");
        cin >> oraSfarsit;

        locatie = cafeLocation;

        // Adaugam angajatul la date
        data.push_back({numeAngajat, to_string(varsta), to_string(salariu), functie, locatie, oraInceput, oraSfarsit});
        break;
    }
    case 2:
    {
        finalpath = basePath + "/" + cafeLocation + "/" + ((languageOption == "EN") ? "Products_Prices.csv" : "Produse_Preturi.csv");
        if (newCSV.readCSV(finalpath).empty())
        {
            headers = {(languageOption == "EN") ? "Product" : "Produs", (languageOption == "EN") ? "Price" : "Pret"};
        }

        cout << ((languageOption == "EN") ? "1. Product Name: " : "1. Nume Produs: ");
        cin.ignore();
        getline(cin, numeProdus);
        cout << ((languageOption == "EN") ? "2. Product Price: " : "2. Pret Produs: ");
        cin >> pretProdus;

        // Adaugam produsul la date
        data.push_back({numeProdus, to_string(pretProdus)});
        break;
    }
    case 3:
    {
        finalpath = basePath + "/" + cafeLocation + "/" + ((languageOption == "EN") ? "stock.csv" : "stoc.csv");
        if (newCSV.readCSV(finalpath).empty())
        {
            headers = {(languageOption == "EN") ? "Ingredient" : "Ingredient",
                       (languageOption == "EN") ? "Units" : "Unitati"};
        }

        cout << ((languageOption == "EN") ? "1. Ingredient Name (e.g., water) or product (e.g., ground coffee): " : "1. Nume prodBrut(ex:apa)/ingredient(cafeaMacinata): ");
        cin.ignore();
        getline(cin, ingredientName);
        cout << ((languageOption == "EN") ? "2. Ingredient/Raw product units (number of units): " : "2. Unitati Ingredient/produsBrut (numarul de unitati): ");
        cin >> ingredientGramaj;

        // Adaugam ingredientul la date
        data.push_back({ingredientName, to_string(ingredientGramaj)});
        break;
    }
    default:
        cout << ((languageOption == "EN") ? "Invalid option!" : "Optiune invalida!") << endl;
        return;
    }

    newCSV.writeCSV(finalpath, data, headers);
}
