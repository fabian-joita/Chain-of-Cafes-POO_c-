#include "inchidereZi.h"

using namespace std;

float inchidereZi::getVenituri(const string &locatie)
{
    string basePath = "/Users/joitafabian/Facultate_C++_KT/Colocviu_CPP/Chain-of-Cafes-POO_c-/CoffeManagementSystem/CSV_FILES/";
    string finalPath = basePath + locatie + "/Comenzi.csv";

    float venituri = 0.0f;
    CSV newCSV;

    ifstream file(finalPath);

    if (!file.is_open())
    {
        cout << "Eroare la deschiderea fisierului " << finalPath << endl;
        return 0.0f;
    }

    vector<vector<string>> comenzi = newCSV.readCSV(finalPath);

    if (comenzi.empty())
    {
        cout << "Nu au fost gasite comenzi in fisier." << endl;
        return 0.0f;
    }

    for (auto &row : comenzi)
    {
        venituri += stof(row[2]);
    }

    return venituri;
}

float inchidereZi::getCosturi(const string &locatie)
{
    string basePath = "/Users/joitafabian/Facultate_C++_KT/Colocviu_CPP/Chain-of-Cafes-POO_c-/CoffeManagementSystem/CSV_FILES/";
    string comenziPath = basePath + locatie + "/Comenzi.csv";
    string costPreparareFile = basePath + "costPreparare&Cumparare.csv";

    float costuri = 0.0f;
    CSV newCSV;

    vector<vector<string>> comenzi = newCSV.readCSV(comenziPath);
    vector<vector<string>> costuriPreparare = newCSV.readCSV(costPreparareFile);

    if (comenzi.empty() || costuriPreparare.empty())
    {
        cout << "Eroare: Nu exista date in fisierele necesare pentru calcularea cheltuielilor." << endl;
        return 0.0f;
    }

    for (const auto &comanda : comenzi)
    {
        if (comanda.size() < 2)
        {
            cerr << "Eroare la interpretarea unei comenzi." << endl;
            continue;
        }

        stringstream produseStream(comanda[1]);
        string produs;

        while (getline(produseStream, produs, '+'))
        {
            bool costGasit = false;

            for (const auto &costRow : costuriPreparare)
            {
                if (costRow[0] == produs)
                {
                    costuri += stof(costRow[1]);
                    costGasit = true;
                    break;
                }
            }

            if (!costGasit)
            {
                cout << "Eroare: Nu exista cost de preparare pentru produsul '" << produs << "'." << endl;
            }
        }
    }

    return costuri;
}

float inchidereZi::getProfit()
{
    profit = venituri - cheltuieli;
    return profit;
}

void inchidereZi::inchidereZiCalcul(const string &locatie)
{
    venituri = getVenituri(locatie);
    cheltuieli = getCosturi(locatie);
    profit = getProfit();

    cout << "Venituri totale: " << venituri << " RON" << endl;
    cout << "Cheltuieli totale: " << cheltuieli << " RON" << endl;
    cout << "Profitul zilei: " << profit << " RON" << endl;

    string basePath = "/Users/joitafabian/Facultate_C++_KT/Colocviu_CPP/Chain-of-Cafes-POO_c-/CoffeManagementSystem/CSV_FILES/";
    string finalPath = basePath + locatie + "/Comenzi.csv";

    ofstream file(finalPath, ofstream::trunc);
    if (file.is_open())
    {
        cout << "Comenzile au fost sterse pentru ziua curenta." << endl;
        file.close();
    }
    else
    {
        cout << "Eroare la deschiderea fisierului pentru stergere." << endl;
    }
}
