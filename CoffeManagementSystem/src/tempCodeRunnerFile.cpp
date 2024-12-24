#include "cafe_chain.h"
#include <iostream>

Sediu::Sediu() : nmb_employees(0), nmb_clients(0) {}

void Sediu::addEmployee(const Employee &employee)
{
    employees.push_back(employee);
    nmb_employees++;
}

void Sediu::setClients(int clients)
{
    nmb_clients = clients;
}

void Sediu::getNmbEmployees() const
{
    cout << nmb_employees;
}

void Sediu::getNmbClients() const
{
    cout << nmb_clients;
}

class Display : public Sediu
{
public:
    void update() override
    {
        cout << "Number of employees: ";
        getNmbEmployees();
        cout << endl;

        cout << "Number of clients: ";
        getNmbClients();
        cout << endl;
    }
}

void
CAFE::Notify(Employee *employee)
{
    for (Sediu *sediu : sedii)
    {
        sediu->update();
    }
}

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
