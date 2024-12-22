#include "optiunea6.h"
#include <filesystem>

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

    // Selectare antet și date pe baza alegerii
    vector<string> headers;
    vector<vector<string>> data;
    string finalpath;

    switch (alegere)
    {
    case 1:
        // Antet și date pentru Angajați și Funcții
        headers = {"Nume Angajat", "Funcție", "Ora Început", "Ora Sfârșit"};
        data = {
            {"John Doe", "Manager", "09:00", "17:00"},
            {"Jane Smith", "Barista", "08:00", "16:00"},
            {"Alice Johnson", "Waiter", "10:00", "18:00"}};
        finalpath = basePath + cafeLocation + "/" + "Angajati_Functii.csv";
        break;

    case 2:
        // Antet și date pentru Produse și Prețuri
        headers = {"Produs", "Preț"};
        data = {
            {"Espresso", "5.00"},
            {"Latte", "6.00"},
            {"Cappuccino", "6.50"},
            {"Croissant", "2.50"}};
        finalpath = basePath + cafeLocation + "/" + "Produse_Preturi.csv";
        break;

    case 3:
        // Antet și date pentru Comenzi
        headers = {"Nume Client", "Produse Comandate", "Preț Total"};
        data = {
            {"Maria Popescu", "Espresso, Croissant", "7.50"},
            {"Ion Ionescu", "Latte", "6.00"}};
        finalpath = basePath + cafeLocation + "/" + "Comenzi.csv";
        break;

    default:
        cout << "Optiune invalida!" << endl;
        return;
    }

    newCSV.writeCSV(finalpath, data, headers);

    cout << "Fișierul CSV a fost salvat cu succes la: " << finalpath << endl;
}
