#include "optiunea6.h"
#include "Employee.h"
#include "Order.h"
#include "Product.h"
#include <filesystem>
#include <sstream>
#include <iostream>

using namespace std;

// o sa adaugam datele in fisiere dupa ce verificam data angajatul produsul sau ingredietul nu mai exista
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
    string finalpath;

    string numeAngajat, functie, locatie;
    int salariu = 0, varsta = 0;
    string oraInceput, oraSfarsit;
    string numeProdus;
    float pretProdus = 0.0;
    string ingredientName;
    int ingredientGramaj = 0;

    switch (alegere)
    {
    case 1:
    {
        finalpath = basePath + "/" + cafeLocation + "/" + ((languageOption == "EN") ? "Employees_Roles.csv" : "Angajati_Functii.csv");
        auto csvData = newCSV.readCSV(finalpath);

        if (csvData.empty())
        {
            headers = {(languageOption == "EN") ? "Employee Name" : "Nume Angajat",
                       (languageOption == "EN") ? "Age" : "Varsta",
                       (languageOption == "EN") ? "Salary" : "Salariu",
                       (languageOption == "EN") ? "Role" : "Functie",
                       (languageOption == "EN") ? "Location" : "Locatie",
                       (languageOption == "EN") ? "Start Time" : "Ora Inceput",
                       (languageOption == "EN") ? "End Time" : "Ora Sfarsit"};
        }

        cout << ((languageOption == "EN") ? "1. Employee Name: " : "1. Nume Angajat: ");
        cin.ignore();
        std::getline(cin, numeAngajat);

        bool alreadyExists = false;
        for (const auto &row : csvData)
        {
            if (!row.empty() && row[0] == numeAngajat)
            {
                alreadyExists = true;
                break;
            }
        }

        if (alreadyExists)
        {
            cout << ((languageOption == "EN") ? "Employee already exists with this name: " : "Angajatul cu acest nume exista deja: ") << numeAngajat << endl;
            break;
        }

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
        auto csvData = newCSV.readCSV(finalpath);

        if (csvData.empty())
        {
            headers = {(languageOption == "EN") ? "Product" : "Produs", (languageOption == "EN") ? "Price" : "Pret"};
        }

        cout << ((languageOption == "EN") ? "1. Product Name: " : "1. Nume Produs: ");
        cin.ignore();
        getline(cin, numeProdus);

        bool alreadyExists = false;
        for (const auto &row : csvData)
        {
            if (!row.empty() && row[0] == numeProdus)
            {
                alreadyExists = true;
                break;
            }
        }

        if (alreadyExists)
        {
            cout << ((languageOption == "EN") ? "Product already exists with this name: " : "Produsul cu acest nume exista deja: ") << numeProdus << endl;
            break;
        }

        cout << ((languageOption == "EN") ? "2. Product Price: " : "2. Pret Produs: ");
        cin >> pretProdus;
        // Adaugam produsul la date
        data.push_back({numeProdus, to_string(pretProdus)});
        break;
    }
    case 3:
    {
        finalpath = basePath + "/" + cafeLocation + "/" + ((languageOption == "EN") ? "stock.csv" : "stoc.csv");
        auto csvData = newCSV.readCSV(finalpath);

        if (csvData.empty())
        {
            headers = {(languageOption == "EN") ? "Ingredient" : "Ingredient",
                       (languageOption == "EN") ? "Units" : "Unitati"};
        }

        cout << ((languageOption == "EN") ? "1. Ingredient Name: " : "1. Nume Ingredient: ");
        cin.ignore();
        getline(cin, ingredientName);

        bool alreadyExists = false;
        for (const auto &row : csvData)
        {
            if (!row.empty() && row[0] == ingredientName)
            {
                alreadyExists = true;
                break;
            }
        }

        if (alreadyExists)
        {
            cout << ((languageOption == "EN") ? "Ingredient already exists with this name: " : "Ingredientul cu acest nume exista deja: ") << ingredientName << endl;
            break;
        }

        cout << ((languageOption == "EN") ? "2. Ingredient Units: " : "2. Unitati Ingredient: ");
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
