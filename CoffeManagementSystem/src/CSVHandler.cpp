#include "CSVHandler.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>

using namespace std;

vector<vector<string>> CSV::readCSV(const string &filename)
{
    vector<vector<string>> data;
    string line;
    ifstream file(filename);

    if (!file.is_open())
    {
        if (languageOption == "EN")
        {
            cerr << "Error opening file " << filename << endl;
        }
        else
        {
            cerr << "Eroare la deschiderea fisierului " << filename << endl;
        }
        return data;
    }

    // Sarim peste prima linie (header)
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
    ofstream file(filename, ios::app); // Deschidem fisierul in mod de adaugare
    if (!file.is_open())
    {
        if (languageOption == "EN")
        {
            cerr << "Error opening file for writing: " << filename << endl;
            cerr << strerror(errno) << endl;
        }
        else
        {
            cerr << "Eroare la deschiderea fisierului pentru scriere: " << filename << endl;
            cerr << strerror(errno) << endl;
        }
        return;
    }

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

void CSV::rewriteCSV(const string &filename, const vector<vector<string>> &data, const vector<string> &headers)
{
    ofstream file(filename); // Deschidem fisierul in mod de rescriere
    if (!file.is_open())
    {
        if (languageOption == "EN")
        {
            cerr << "Error opening file for rewriting: " << filename << endl;
            cerr << strerror(errno) << endl;
        }
        else
        {
            cerr << "Eroare la deschiderea fisierului pentru rescriere: " << filename << endl;
            cerr << strerror(errno) << endl;
        }
        return;
    }

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
