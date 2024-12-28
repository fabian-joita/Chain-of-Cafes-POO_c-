#include "cafe_chain.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

Sediu::Sediu() : nmb_employees(0), nmb_clients(0) {}

void Sediu::loadEmployeesFromFile(const string &fileName, const string &locatie)
{
    string basePath = "/Users/joitafabian/Facultate_C++_KT/Colocviu_CPP/Chain-of-Cafes-POO_c-/CoffeManagementSystem/CSV_FILES/";
    string finalPath = basePath + locatie + "/" + fileName;

    ifstream file(finalPath);
    if (!file.is_open())
    {
        cout << "Eroare la deschiderea fisierului " << finalPath << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string nume, functie;
        int varsta;
        double salariu;
        string locatie, oraInceput, oraSfarsit;

        getline(ss, nume, ',');
        getline(ss, functie, ',');
        ss >> varsta;
        ss.ignore();
        ss >> salariu;
        ss.ignore();
        getline(ss, locatie, ',');
        getline(ss, oraInceput, ',');
        getline(ss, oraSfarsit);

        Employee newEmployee(nume, varsta, salariu, functie, locatie, oraInceput, oraSfarsit);
        addEmployee(newEmployee);
    }

    file.close();
}

void Sediu::addEmployee(const Employee &employee)
{
    employees.push_back(employee);
    nmb_employees++;
}

void Sediu::setLocation(string location)
{
    locatie = location;
}

void Sediu::setClients(int clients)
{
    nmb_clients = clients;
}

int Sediu::getNmbEmployees() const
{
    return nmb_employees;
}

string Sediu::getLocatie() const
{
    return locatie;
}

int Sediu::getNmbClients() const
{
    return nmb_clients;
}

void Display::update()
{
    cout << "Number of employees: " << getNmbEmployees() << endl;
    cout << "Number of clients: " << getNmbClients() << endl;
}

void Display::display() const
{
    cout << "Displaying information for the cafe: " << locatie << endl;
    cout << "Number of employees: " << getNmbEmployees() << endl;
    cout << "Number of clients: " << getNmbClients() << endl;
}

void CAFE::addCafeUnit(Sediu *center)
{
    if (center != nullptr)
    {
        sedii.push_back(center);
        nmb_sedii++;
    }
}

void CAFE::displayAllSedii()
{
    int i = 0;
    for (Sediu *sediu : sedii)
    {
        i++;
        cout << "Cafe nmb: " << i << endl;
        cout << "Number of employees: " << sediu->getNmbEmployees() << endl;
        cout << "Number of clients: " << sediu->getNmbClients() << endl;
        cout << "Location: " << sediu->getLocatie() << endl;
    }
}

void CAFE::displayCafeLocations()
{
    int i = 0;
    for (Sediu *sediu : sedii)
    {
        i++;
        cout << "Cafe number " << i << " in " << sediu->getLocatie() << endl;
    }
}

Sediu *CAFE::getPtrUnit(int optiune)
{
    if (optiune < 1 || optiune > sedii.size())
    {
        cout << "Invalid option. Please choose a valid option." << endl;
        return nullptr;
    }
    return sedii[optiune - 1];
}

int CAFE::getNmbSedii()
{
    return nmb_sedii;
}
