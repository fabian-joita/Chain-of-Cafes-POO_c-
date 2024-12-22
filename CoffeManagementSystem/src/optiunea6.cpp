#include "optiunea6.h"
#include <filesystem>
#include <sstream>
#include <iostream>

using namespace std;

void Optiunea6::writeCSVFile(const string &basePath, const string &cafeLocation)
{
    CSV newCSV;

    // Meniu pentru selecția tipului de fișier CSV
    cout << "Alege tipul de fisier CSV pe care doresti sa-l scrii (1/2/3):" << endl;
    cout << "1. Angajati si Functii" << endl;
    cout << "2. Produse si Preturi" << endl;
    cout << "3. Comenzi" << endl;

    int alegere;
    cin >> alegere;

    // Variables for headers, data, and file path
    vector<string> headers;
    vector<vector<string>> data;
    string dataString;
    string finalpath;

    // Determine file path and headers based on choice
    switch (alegere)
    {
    case 1:
        finalpath = basePath + cafeLocation + "/" + "Angajati_Functii.csv";
        if (newCSV.readCSV(finalpath).empty())
        {
            headers = {"Nume Angajat", "Funcție", "Ora Început", "Ora Sfârșit"};
        }

        cout << "Introduceti datele (format: Nume Angajat, Funcție, Ora Început, Ora Sfârșit):" << endl;
        cin.ignore(); // Clear input buffer
        std::getline(cin, dataString);

        {
            istringstream ss(dataString);
            string field;
            vector<string> row;
            while (getline(ss, field, ','))
            {
                row.push_back(field);
            }
            data.push_back(row);
        }
        break;

    case 2:
        finalpath = basePath + cafeLocation + "/" + "Produse_Preturi.csv";
        if (newCSV.readCSV(finalpath).empty())
        {
            headers = {"Produs", "Preț"};
        }

        cout << "Introduceti datele (format: Produs, Preț):" << endl;
        cin.ignore(); // Clear input buffer
        std::getline(cin, dataString);

        {
            istringstream ss(dataString);
            string field;
            vector<string> row;
            while (getline(ss, field, ','))
            {
                row.push_back(field);
            }
            data.push_back(row);
        }
        break;

    case 3:
        finalpath = basePath + cafeLocation + "/" + "Comenzi.csv";
        if (newCSV.readCSV(finalpath).empty())
        {
            headers = {"Nume Client", "Produse Comandate", "Preț Total"};
        }

        cout << "Introduceti datele (format: Nume Client, Produse Comandate, Preț Total):" << endl;
        cin.ignore(); // Clear input buffer
        std::getline(cin, dataString);

        {
            istringstream ss(dataString);
            string field;
            vector<string> row;
            while (getline(ss, field, ','))
            {
                row.push_back(field);
            }
            data.push_back(row);
        }
        break;

    default:
        cout << "Optiune invalida!" << endl;
        return;
    }

    // Write to CSV
    newCSV.writeCSV(finalpath, data, headers);
}
