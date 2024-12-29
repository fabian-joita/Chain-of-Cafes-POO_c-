#ifndef CSV_H
#define CSV_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Globals.h"

using namespace std;

class CSV
{
public:
    // citesc fisierele sarind prima linie deoarece reprezinta un header
    static vector<vector<string>> readCSV(const string &filename);

    // scriere in fis csv, inclusiv titlurile coloanelor pe prima linie
    static void writeCSV(const string &filename, const vector<vector<string>> &data, const vector<string> &headers);

    static void rewriteCSV(const string &filename, const vector<vector<string>> &data, const vector<string> &headers);
};

#endif