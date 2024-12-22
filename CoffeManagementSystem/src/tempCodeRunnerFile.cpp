#include "cafe_chain.h"
#include <iostream>

// Implementarea metodei constructorului pentru Sediu
Sediu::Sediu() : nmb_employees(0), nmb_clients(0) {}

// Implementarea metodei pentru adăugarea unui angajat
void Sediu::addEmployee(const Employee &employee)
{
    employees.push_back(employee);
    nmb_employees++;
}

// Implementarea metodei pentru setarea numărului de clienți
void Sediu::setClients(int clients)
{
    nmb_clients = clients;
}

// Implementarea metodei pentru obținerea numărului de angajați
void Sediu::getNmbEmployees() const
{
    cout << nmb_employees;
}

// Implementarea metodei pentru obținerea numărului de clienți
void Sediu::getNmbClients() const
{
    cout << nmb_clients;
}

// Implementarea metodei 'update' pentru clasa derivată Display
class Display : public Sediu
{
public:
    void update() override
    {
        // Exemplu de implementare a metodei update
        cout << "Number of employees: ";
        getNmbEmployees();
        cout << endl;

        cout << "Number of clients: ";
        getNmbClients();
        cout << endl;
    }
}

// Implementarea metodei 'Notify' din CAFE
void
CAFE::Notify(Employee *employee)
{
    for (Sediu *sediu : sedii)
    {
        sediu->update();
    }
}

// Implementarea metodei 'displayAllSedii' din CAFE
void CAFE::displayAllSedii()
{
    for (Sediu *sediu : sedii)
    {
        cout << "Number of employees: ";
        sediu->getNmbEmployees();
        cout << endl;

        cout << "Number of clients: ";
        sediu->getNmbClients();
        cout << endl;
    }
}
