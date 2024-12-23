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
    cout << "3. Comenzi" << endl;

    int alegere;
    cin >> alegere;

    vector<string> headers;
    vector<vector<string>> data;
    string dataString;
    string finalpath;

    // Declare all variables here
    string numeAngajat, functie, locatie;
    int salariu = 0, varsta = 0;
    string oraInceput, oraSfarsit;
    string numeProdus, numeClient, produseStr;
    float pretProdus = 0.0, pretTotal = 0.0;

    switch (alegere)
    {
    case 1:
    {
        finalpath = basePath + cafeLocation + "/" + "Angajati_Functii.csv";
        if (newCSV.readCSV(finalpath).empty())
        {
            headers = {"Nume Angajat", "Varsta", "Salariu", "Funcție", "Locatie", "Ora Început", "Ora Sfârșit"};
        }

        cout << "Se citesc datele in urmatoarea ordine: " << endl;
        cout << "1. Nume Angajat: ";
        cin.ignore();
        std::getline(cin, numeAngajat);
        cout << "2. Varsta: ";
        cin >> varsta;
        cout << "3. Salariu: ";
        cin >> salariu;
        cout << "4. Funcție: ";
        cin >> functie;
        cout << "5. Ora Început: ";
        cin >> oraInceput;
        cout << "6. Ora Sfârșit: ";
        cin >> oraSfarsit;

        locatie = cafeLocation;

        if (functie == "Barista")
        {
            Barista barista(numeAngajat, varsta, salariu, functie, locatie, oraInceput, oraSfarsit);
            barista.displayInfo();
        }
        else if (functie == "Manager")
        {
            Manager manager(numeAngajat, varsta, salariu, functie, locatie, oraInceput, oraSfarsit);
            manager.displayInfo();
        }
        else if (functie == "Ospatar")
        {
            Ospatar ospatar(numeAngajat, varsta, salariu, functie, locatie, oraInceput, oraSfarsit);
            ospatar.displayInfo();
        }

        data.push_back({numeAngajat, to_string(varsta), to_string(salariu), functie, locatie, oraInceput, oraSfarsit});
        break;
    }
    case 2:
    {
        finalpath = basePath + cafeLocation + "/" + "Produse_Preturi.csv";
        if (newCSV.readCSV(finalpath).empty())
        {
            headers = {"Produs", "Preț"};
        }

        cout << "1. Nume Produs: ";
        cin.ignore();
        getline(cin, numeProdus);
        cout << "2. Preț Produs: ";
        cin >> pretProdus;

        data.push_back({numeProdus, to_string(pretProdus)});
        break;
    }
    case 3:
    {
        finalpath = basePath + cafeLocation + "/" + "Comenzi.csv";
        if (newCSV.readCSV(finalpath).empty())
        {
            headers = {"Nume Client", "Produse Comandate", "Preț Total"};
        }

        cout << "1. Nume Client: ";
        cin.ignore();
        getline(cin, numeClient);
        cout << "2. Produse Comandate (separate prin virgulă): ";
        getline(cin, produseStr);
        cout << "3. Preț Total: ";
        cin >> pretTotal;

        data.push_back({numeClient, produseStr, to_string(pretTotal)});
        break;
    }
    default:
        cout << "Optiune invalida!" << endl;
        return;
    }

    newCSV.writeCSV(finalpath, data, headers);
}
