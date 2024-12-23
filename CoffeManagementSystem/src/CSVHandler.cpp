#include "CSVHandler.h"
using namespace std;

vector<vector<string>> CSV::readCSV(const string &filename)
{
    vector<vector<string>> data;
    string line;
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Eroare la deschiderea fisierului " << filename << endl;
        return data;
    }

    // sar peste prima linie la citire
    getline(file, line);

    while (getline(file, line))
    {
        stringstream ss(line);
        string cell;
        vector<string> row;

        while (getline(ss, cell, ','))
        {
            row.push_back(cell);
        }
        data.push_back(row);
    }

    file.close();
    return data;
}

void CSV::writeCSV(const string &filename, const vector<vector<string>> &data, const vector<string> &headers)
{
    ofstream file(filename, ios::app);
    if (!file.is_open())
    {
        cerr << "Eroare la deschiderea fisierului pentru scriere: " << filename << endl;
        cerr << strerror(errno) << endl; // afișează mesajul de eroare detaliat
        return;
    }

    // aici se scriu titlurile coloanelor, pe prima linie
    if (!headers.empty())
    {
        for (size_t i = 0; i < headers.size(); ++i)
        {
            file << headers[i];
            if (i != headers.size() - 1)
            {
                file << ",";
            }
        }
        file << endl;
    }

    // scrierea datelor
    for (const auto &row : data)
    {
        for (size_t i = 0; i < row.size(); ++i)
        {
            file << row[i];
            if (i != row.size() - 1)
            {
                file << ",";
            }
        }
        file << endl;
    }

    file.close();
}
