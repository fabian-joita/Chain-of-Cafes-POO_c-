#include "optiunea7.h"
#include "CSVHandler.h"
#include <filesystem>
#include <vector>

using namespace std;

void Optiunea7::readCSVFile(const string &basePath)
{
    CSV newCSV;

    vector<vector<string>> dataFromCSV = newCSV.readCSV(basePath);
    cout << "Datele din fisierul csv ales sunt : " << endl;

    for (const auto &row : dataFromCSV)
    {
        for (const auto &cell : row)
        {
            cout << cell << " ";
        }
        cout << endl;
    }
}
