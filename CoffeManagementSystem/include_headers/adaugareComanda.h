#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "CSVHandler.h"

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
        headers = {"Nume Client", "Produse Comandate", "Pret Total"};
    }

    cout << "1. Nume Client: ";
    cin.ignore();
    getline(cin, numeClient);
    cout << "2. Produse Comandate (unite prin '+'): ";
    getline(cin, produseStr);

    stringstream ss(produseStr);
    string produs;
    bool comandaValida = true;

    string produsePreturiFile = basePath + locatie + "/Produse_Preturi.csv";
    string costPreparareFile = basePath + "costPreparare&Cumparare.csv";
    string compozitieProduseFile = basePath + "compozitieProduse&&produseBrute.csv";
    string stocFile = basePath + locatie + "/stoc.csv";

    vector<vector<string>> produsePreturi = newCSV.readCSV(produsePreturiFile);
    vector<vector<string>> costuriPreparare = newCSV.readCSV(costPreparareFile);
    vector<vector<string>> compozitieProduse = newCSV.readCSV(compozitieProduseFile);
    vector<vector<string>> stoc = newCSV.readCSV(stocFile);

    if (produsePreturi.empty() || costuriPreparare.empty() || compozitieProduse.empty() || stoc.empty())
    {
        cerr << "Eroare la citirea fisierelor necesare!" << endl;
        return;
    }

    // procesam fiecare produs din comanda
    while (getline(ss, produs, '+'))
    {
        bool produsGasit = false;
        float costProdus = 0.0f;

        // verificam daca produsul exista in lista de preturi
        for (const auto &row : produsePreturi)
        {
            if (row[0] == produs)
            {
                produsGasit = true;
                float pretProdus = stof(row[1]);
                pretTotal += pretProdus;
                *vanzari += pretProdus;

                // gasim costul produsului
                for (const auto &costRow : costuriPreparare)
                {
                    if (costRow[0] == produs)
                    {
                        costProdus = stof(costRow[1]);
                        *cheltuieli += costProdus;
                        break;
                    }
                }

                // verificam si actualizam stocul ingredientelor
                for (const auto &compozitieRow : compozitieProduse)
                {
                    if (compozitieRow[0] == produs)
                    {
                        stringstream compozitieSS(compozitieRow[1]); // ingredientele produsului
                        string ingredient;
                        while (getline(compozitieSS, ingredient, '+'))
                        {
                            bool ingredientGasit = false;

                            // cautam ingredientul in stoc
                            for (auto &stocRow : stoc)
                            {
                                if (stocRow[0] == ingredient)
                                {
                                    ingredientGasit = true;
                                    int unitatiNecesare = 1;
                                    int unitatiDisponibile = stoi(stocRow[1]);

                                    // Verificam daca sunt suficiente unitati disponibile in stoc
                                    if (unitatiDisponibile < unitatiNecesare)
                                    {
                                        cout << "Stoc insuficient pentru ingredientul: " << ingredient << endl;
                                        comandaValida = false;
                                        break;
                                    }
                                    else
                                    {
                                        // Scadem o unitate din stoc
                                        unitatiDisponibile -= unitatiNecesare;

                                        // Actualizam stocul
                                        stocRow[1] = to_string(unitatiDisponibile);

                                        // aici facem debugging
                                        cout << "Scazand 1 unitate din stoc. Noul stoc pentru " << ingredient << ": " << unitatiDisponibile << endl;
                                    }
                                }
                            }

                            if (!ingredientGasit)
                            {
                                cout << "Ingredientul '" << ingredient << "' nu exista in stoc!" << endl;
                                comandaValida = false;
                                break;
                            }

                            if (!comandaValida)
                                break;
                        }

                        break;
                    }
                }

                break;
            }
        }

        if (!produsGasit)
        {
            cout << "Produsul '" << produs << "' nu a fost gasit in meniu. Te rugam sa reintroduci comanda." << endl;
            comandaValida = false;
            break;
        }

        if (!comandaValida)
            break;
    }

    if (comandaValida)
    {
        // Adaugam comanda in fisierul CSV
        data.push_back({numeClient, produseStr, to_string(pretTotal)});
        newCSV.writeCSV(finalpath, data, headers);

        // Actualizam fisierul de stoc
        vector<string> headerStoc = {"Ingredient", "Unitati"};
        newCSV.rewriteCSV(stocFile, stoc, headerStoc);

        cout << "Comanda a fost adaugata si stocul a fost actualizat!" << endl;
    }
    else
    {
        cout << "Comanda nu a fost valida si nu a fost adaugata!" << endl;
    }
}
