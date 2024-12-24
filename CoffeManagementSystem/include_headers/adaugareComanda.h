#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "CSVHandler.h" // Presupun că ai această clasă pentru citire/scriere CSV

using namespace std;

void adaugareComanda(const string &locatie, float *vanzari, float *cheltuieli)
{
    CSV newCSV;

    vector<string> headers;
    vector<vector<string>> data;
    string basePath = "/Users/joitafabian/Facultate_C++_KT/Colocviu_CPP/Chain-of-Cafes-POO_c-/CoffeManagementSystem/CSV_FILES/";
    string finalpath = basePath + locatie + "/" + "Comenzi.csv";
    string numeClient, produseStr;
    float pretTotal = 0.0f;

    if (newCSV.readCSV(finalpath).empty())
    {
        headers = {"Nume Client", "Produse Comandate", "Preț Total"};
    }

    cout << "1. Nume Client: ";
    cin.ignore();
    getline(cin, numeClient);
    cout << "2. Produse Comandate (unite prin '+'): ";
    getline(cin, produseStr);

    // Divid produsele comandate în elemente separate
    stringstream ss(produseStr);
    string produs;
    bool comandaValida = true;

    // Citim fișierul cu produsele și prețurile
    string filename = basePath + locatie + "/Produse_Preturi.csv";
    ifstream file(filename);
    vector<vector<string>> produsePreturi;
    string line;

    if (!file.is_open())
    {
        cerr << "Eroare la deschiderea fisierului " << filename << endl;
        return;
    }

    // Sarim peste header-ul fișierului
    getline(file, line);

    // Citim restul fișierului
    while (getline(file, line))
    {
        stringstream ss(line);
        string cell;
        vector<string> row;
        while (getline(ss, cell, ','))
        {
            row.push_back(cell);
        }
        produsePreturi.push_back(row);
    }

    file.close();

    // Citim fișierul cu costurile de preparare și cumpărare
    string costFilename = basePath + locatie + "/costPreparare&Cumparare.csv";
    ifstream costFile(costFilename);
    vector<vector<string>> costuriPreparare;
    if (!costFile.is_open())
    {
        cerr << "Eroare la deschiderea fisierului de costuri " << costFilename << endl;
        return;
    }

    // Sarim peste header-ul fișierului cu costuri
    getline(costFile, line);

    // Citim costurile produselor
    while (getline(costFile, line))
    {
        stringstream ss(line);
        string cell;
        vector<string> row;
        while (getline(ss, cell, ','))
        {
            row.push_back(cell);
        }
        costuriPreparare.push_back(row);
    }

    costFile.close();

    // Procesăm produsele comandate
    while (getline(ss, produs, '+'))
    {
        bool produsGasit = false;
        float costProdus = 0.0f;
        for (const auto &row : produsePreturi)
        {
            if (row[0] == produs) // Dacă produsul este găsit în fișier
            {
                produsGasit = true;
                float pretProdus = stof(row[1]); // Conversia prețului în float
                pretTotal += pretProdus;         // Adăugăm la prețul total
                *vanzari += pretProdus;          // Adăugăm la vanzări

                // Căutăm costul de preparare al produsului
                for (const auto &costRow : costuriPreparare)
                {
                    if (costRow[0] == produs)
                    {
                        costProdus = stof(costRow[1]); // Conversia costului în float
                        *cheltuieli += costProdus;     // Adăugăm la cheltuieli
                        break;
                    }
                }

                break;
            }
        }

        if (!produsGasit)
        {
            cout << "Produsul '" << produs << "' nu a fost găsit în meniu. Te rugăm să reintroduci comanda." << endl;
            comandaValida = false;
            break;
        }
    }

    if (comandaValida)
    {
        // Adăugăm comanda în fișierul CSV
        data.push_back({numeClient, produseStr, to_string(pretTotal)});
        newCSV.writeCSV(finalpath, data, headers);
        cout << "Comanda a fost adăugată cu succes!" << endl;
    }
    else
    {
        cout << "Comanda nu a fost validă și nu a fost adăugată!" << endl;
    }
}
