#include <iostream>
#include <filesystem>
#include <string>
#include "listareFisiere.h"

namespace fs = std::__fs::filesystem;
using namespace std;

void listFilesInDirectory(const string &directoryPath)
{
    try
    {
        for (const auto &entry : fs::directory_iterator(directoryPath))
        {
            if (fs::is_regular_file(entry))
            {
                cout << entry.path().filename().string() << endl;
            }
        }
    }
    catch (const fs::filesystem_error &e)
    {
        cerr << "Eroare: " << e.what() << endl;
    }
}
