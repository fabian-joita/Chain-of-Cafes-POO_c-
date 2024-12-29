#include "inchidereZi.h"
#include "evenimenteSpeciale.h"
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

string getCurrentDate()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    ostringstream dateStream;
    dateStream << 1900 + ltm->tm_year << "-"
               << setw(2) << setfill('0') << 1 + ltm->tm_mon << "-"
               << setw(2) << setfill('0') << ltm->tm_mday;

    return dateStream.str();
}

float inchidereZi::getVenituri(const string &locatie)
{
    string basePath = (languageOption == "EN") ? "/Users/joitafabian/Facultate_C++_KT/Colocviu_CPP/Chain-of-Cafes-POO_c-/CoffeManagementSystem/CSV_FILES_ENGLISH"
                                               : "/Users/joitafabian/Facultate_C++_KT/Colocviu_CPP/Chain-of-Cafes-POO_c-/CoffeManagementSystem/CSV_FILES/";
    string finalPath = (languageOption == "EN") ? basePath + locatie + "/Orders.csv" : basePath + locatie + "/Comenzi.csv";

    float venituri = 0.0f;
    CSV newCSV;

    ifstream file(finalPath);

    if (!file.is_open())
    {
        cout << ((languageOption == "EN") ? "Error opening file " : "Eroare la deschiderea fisierului ") << finalPath << endl;
        return 0.0f;
    }

    vector<vector<string>> comenzi = newCSV.readCSV(finalPath);

    if (comenzi.empty())
    {
        cout << ((languageOption == "EN") ? "No orders found in the file." : "Nu au fost gasite comenzi in fisier.") << endl;
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
    string basePath = (languageOption == "EN") ? "/Users/joitafabian/Facultate_C++_KT/Colocviu_CPP/Chain-of-Cafes-POO_c-/CoffeManagementSystem/CSV_FILES_ENGLISH"
                                               : "/Users/joitafabian/Facultate_C++_KT/Colocviu_CPP/Chain-of-Cafes-POO_c-/CoffeManagementSystem/CSV_FILES/";
    string comenziPath = (languageOption == "EN") ? basePath + locatie + "/Orders.csv" : basePath + locatie + "/Comenzi.csv";
    string costPreparareFile = (languageOption == "EN") ? basePath + "costPreparation&Purchase.csv" : basePath + "costPreparare&Cumparare.csv";

    float costuri = 0.0f;
    CSV newCSV;

    vector<vector<string>> comenzi = newCSV.readCSV(comenziPath);
    vector<vector<string>> costuriPreparare = newCSV.readCSV(costPreparareFile);

    if (comenzi.empty() || costuriPreparare.empty())
    {
        cout << ((languageOption == "EN") ? "Error: No data in the required files for calculating costs." : "Eroare: Nu exista date in fisierele necesare pentru calcularea cheltuielilor.") << endl;
        return 0.0f;
    }

    for (const auto &comanda : comenzi)
    {
        if (comanda.size() < 2)
        {
            cerr << ((languageOption == "EN") ? "Error interpreting an order." : "Eroare la interpretarea unei comenzi.") << endl;
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
                cout << ((languageOption == "EN") ? "Error: No preparation cost found for product '" : "Eroare: Nu exista cost de preparare pentru produsul '") << produs << "'" << endl;
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

    string currentDate = getCurrentDate();

    float venituriEvenimente = 0.0f;
    float costuriEvenimente = 0.0f;

    auto &evenimente = ManagerEvenimente::getInstance()->getGestionare().getToateEvenimentele();

    for (const auto &eveniment : evenimente)
    {
        if (eveniment.getDataEveniment() == currentDate)
        {
            venituriEvenimente += eveniment.calculVenitEveniment();
            costuriEvenimente += eveniment.getCostOrganizare();
        }
    }

    venituri += venituriEvenimente;
    cheltuieli += costuriEvenimente;

    profit = getProfit();

    cout << ((languageOption == "EN") ? "Order revenues: " : "Venituri din comenzi: ") << venituri - venituriEvenimente << " RON" << endl;
    cout << ((languageOption == "EN") ? "Order costs: " : "Costuri din comenzi: ") << cheltuieli - costuriEvenimente << " RON" << endl;

    cout << ((languageOption == "EN") ? "Total revenues (including events): " : "Venituri totale (inclusiv evenimente): ") << venituri << " RON" << endl;
    cout << ((languageOption == "EN") ? "Total costs (including events): " : "Cheltuieli totale (inclusiv evenimente): ") << cheltuieli << " RON" << endl;
    cout << ((languageOption == "EN") ? "Profit of the day: " : "Profitul zilei: ") << profit << " RON" << endl;

    if (venituriEvenimente > 0 || costuriEvenimente > 0)
    {
        cout << ((languageOption == "EN") ? "Special event revenues: " : "Venituri din evenimente speciale: ") << venituriEvenimente << " RON" << endl;
        cout << ((languageOption == "EN") ? "Special event costs: " : "Costuri din evenimente speciale: ") << costuriEvenimente << " RON" << endl;
    }

    string basePath = (languageOption == "EN") ? "/Users/joitafabian/Facultate_C++_KT/Colocviu_CPP/Chain-of-Cafes-POO_c-/CoffeManagementSystem/CSV_FILES_ENGLISH"
                                               : "/Users/joitafabian/Facultate_C++_KT/Colocviu_CPP/Chain-of-Cafes-POO_c-/CoffeManagementSystem/CSV_FILES/";
    string raportPath = (languageOption == "EN") ? basePath + locatie + "/ZReport.csv" : basePath + locatie + "/raportZ.csv";

    ifstream checkFile(raportPath);
    bool isFileEmpty = checkFile.peek() == ifstream::traits_type::eof();
    checkFile.close();

    ofstream raportFile(raportPath, ios::app);

    if (raportFile.is_open())
    {
        if (isFileEmpty)
        {
            raportFile << ((languageOption == "EN") ? "Date,Location,Order revenues,Order costs,Total revenues,Total costs,Profit,Special event revenues,Special event costs\n" : "Data,Locatie,Venituri din comenzi,Costuri din comenzi,Venituri totale,Cheltuieli totale,Profit,Venituri din evenimente speciale,Costuri din evenimente speciale\n");
        }

        raportFile << currentDate << ","
                   << locatie << ","
                   << venituri - venituriEvenimente << ","
                   << cheltuieli - costuriEvenimente << ","
                   << venituri << ","
                   << cheltuieli << ","
                   << profit << ","
                   << venituriEvenimente << ","
                   << costuriEvenimente << "\n";

        cout << ((languageOption == "EN") ? "The details have been saved in the raportZ.csv file." : "Detaliile au fost salvate in fisierul raportZ.csv.") << endl;
        raportFile.close();
    }
    else
    {
        cout << ((languageOption == "EN") ? "Error opening the raportZ.csv file for saving." : "Eroare la deschiderea fisierului raportZ.csv pentru salvare.") << endl;
    }

    string finalPath = (languageOption == "EN") ? basePath + locatie + "/Orders.csv" : basePath + locatie + "/Comenzi.csv";

    ofstream file(finalPath, ofstream::trunc);
    if (file.is_open())
    {
        cout << ((languageOption == "EN") ? "The orders have been deleted for the current day." : "Comenzile au fost sterse pentru ziua curenta.") << endl;
        file.close();
    }
    else
    {
        cout << ((languageOption == "EN") ? "Error opening the file for deletion." : "Eroare la deschiderea fisierului pentru stergere.") << endl;
    }
}
