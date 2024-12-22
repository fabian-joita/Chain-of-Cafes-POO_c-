#include "cafe_chain.h"
#include <iostream>

using namespace std;

// Constructorul clasei Sediu
Sediu::Sediu() : nmb_employees(0), nmb_clients(0) {} // Inițializare membri

// Adăugarea unui angajat
void Sediu::addEmployee(const Employee &employee)
{
    employees.push_back(employee);
    nmb_employees++;
}

// Setarea locației
void Sediu::setLocation(string location)
{
    locatie = location;
}

// Setarea numărului de clienți
void Sediu::setClients(int clients)
{
    nmb_clients = clients;
}

// Returnează numărul de angajați
int Sediu::getNmbEmployees() const
{
    return nmb_employees;
}

// Returnează locația
string Sediu::getLocatie() const
{
    return locatie;
}

// Returnează numărul de clienți
int Sediu::getNmbClients() const
{
    return nmb_clients;
}

// Implementarea metodei update din clasa Display
void Display::update()
{
    cout << "Number of employees: " << getNmbEmployees() << endl;
    cout << "Number of clients: " << getNmbClients() << endl;
}

// Implementarea metodei display din clasa Display
void Display::display() const
{
    cout << "Displaying information for the cafe: " << locatie << endl;
    cout << "Number of employees: " << getNmbEmployees() << endl;
    cout << "Number of clients: " << getNmbClients() << endl;
}

// Adăugarea unei unități de cafea
void CAFE::addCafeUnit(Sediu *center)
{
    if (center != nullptr) // Verificăm dacă pointerul este valid
    {
        sedii.push_back(center); // Adăugăm sediul în vector
        nmb_sedii++;             // Incrementăm numărul de sedii
    }
}

// Afișarea tuturor locațiilor
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

// Afișarea locațiilor
void CAFE::displayCafeLocations()
{
    int i = 0;
    for (Sediu *sediu : sedii)
    {
        i++;
        cout << "Cafe number " << i << " in " << sediu->getLocatie() << endl;
    }
}

// Implementarea metodei getPtrUnit
Sediu *CAFE::getPtrUnit(int optiune)
{
    if (optiune < 1 || optiune > sedii.size())
    {
        cout << "Invalid option. Please choose a valid option." << endl;
        return nullptr; // Returnează nullptr dacă opțiunea este invalidă
    }
    return sedii[optiune - 1]; // Returnează pointer la cafeneaua selectată
}

int CAFE::getNmbSedii()
{
    return nmb_sedii;
}
