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

    cout << "Alege tipul de fisier CSV pe care doresti sa-l scrii (1/2/3):" << endl;
    cout << "1. Angajati si Functii" << endl;
    cout << "2. Produse si Preturi" << endl;
    cout << "3. Stoc Ingrediente" << endl;

    int alegere;
    cin >> alegere;

    vector<string> headers;
    vector<vector<string>> data;
    string dataString;
    string finalpath;

    // Declarati toate variabilele aici
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
        finalpath = basePath + cafeLocation + "/" + "Angajati_Functii.csv";
        if (newCSV.readCSV(finalpath).empty())
        {
            headers = {"Nume Angajat", "Varsta", "Salariu", "Functie", "Locatie", "Ora Inceput", "Ora Sfarsit"};
        }

        cout << "Se citesc datele in urmatoarea ordine: " << endl;
        cout << "1. Nume Angajat: ";
        cin.ignore();
        std::getline(cin, numeAngajat);
        cout << "2. Varsta: ";
        cin >> varsta;
        cout << "3. Salariu: ";
        cin >> salariu;
        cout << "4. Functie: ";
        cin >> functie;
        cout << "5. Ora Inceput: ";
        cin >> oraInceput;
        cout << "6. Ora Sfarsit: ";
        cin >> oraSfarsit;

        locatie = cafeLocation;

        // Adaugam angajatul la date
        data.push_back({numeAngajat, to_string(varsta), to_string(salariu), functie, locatie, oraInceput, oraSfarsit});
        break;
    }
    case 2:
    {
        finalpath = basePath + cafeLocation + "/" + "Produse_Preturi.csv";
        if (newCSV.readCSV(finalpath).empty())
        {
            headers = {"Produs", "Pret"};
        }

        cout << "1. Nume Produs: ";
        cin.ignore();
        getline(cin, numeProdus);
        cout << "2. Pret Produs: ";
        cin >> pretProdus;

        // Adaugam produsul la date
        data.push_back({numeProdus, to_string(pretProdus)});
        break;
    }
    case 3:
    {
        finalpath = basePath + cafeLocation + "/" + "stoc.csv";
        if (newCSV.readCSV(finalpath).empty())
        {
            headers = {"Ingredient", "Unitati"};
        }

        cout << "1. Nume prodBrut(ex:apa)/ingredient(cafeaMacinata): ";
        cin.ignore();
        getline(cin, ingredientName);
        cout << "2. Unitati Ingredient/produsBrut (numarul de unitati): ";
        cin >> ingredientGramaj;

        // Adaugam ingredientul la date
        data.push_back({ingredientName, to_string(ingredientGramaj)});
        break;
    }
    default:
        cout << "Optiune invalida!" << endl;
        return;
    }

    // Scriem datele in fisierul CSV corespunzator
    newCSV.writeCSV(finalpath, data, headers);
}
