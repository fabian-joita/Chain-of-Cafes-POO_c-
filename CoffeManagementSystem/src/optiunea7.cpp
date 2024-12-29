#include "optiunea7.h"
#include "CSVHandler.h"
#include <filesystem>
#include <vector>
#include <iostream>

using namespace std;

void Optiunea7::readCSVFile(const string &basePath)
{
    CSV newCSV;

    vector<vector<string>> dataFromCSV = newCSV.readCSV(basePath);

    if (languageOption == "EN")
    {
        cout << "The data from the selected CSV file are: " << endl;
    }
    else
    {
        cout << "Datele din fisierul csv ales sunt : " << endl;
    }

    for (const auto &row : dataFromCSV)
    {
        for (const auto &cell : row)
        {
            cout << cell << " ";
        }
        cout << endl;
    }
}
