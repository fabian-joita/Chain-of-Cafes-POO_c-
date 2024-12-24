#include "cafe_chain.h"
#include <iostream>

using namespace std;

// Constructorul clasei Sediu
Sediu::Sediu() : nmb_employees(0), nmb_clients(0) {}

// Adaugarea unui angajat
void Sediu::addEmployee(const Employee &employee)
{
    employees.push_back(employee);
    nmb_employees++;
}

// Setarea locatiei
void Sediu::setLocation(string location)
{
    locatie = location;
}

// Setarea numarului de clienti
void Sediu::setClients(int clients)
{
    nmb_clients = clients;
}

// Returneaza numarul de angajati
int Sediu::getNmbEmployees() const
{
    return nmb_employees;
}

// Returneaza locatia
string Sediu::getLocatie() const
{
    return locatie;
}

// Returneaza numarul de clienti
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

// Adaugarea unei unitati de cafea
void CAFE::addCafeUnit(Sediu *center)
{
    if (center != nullptr) // Verificam daca pointerul este valid
    {
        sedii.push_back(center); // Adaugam sediul in vector
        nmb_sedii++;             // Incrementam numarul de sedii
    }
}

// Afisarea tuturor locatiilor
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
    return sedii[optiune - 1]; // Returneaza pointer la cafeneaua selectata
}

int CAFE::getNmbSedii()
{
    return nmb_sedii;
}
