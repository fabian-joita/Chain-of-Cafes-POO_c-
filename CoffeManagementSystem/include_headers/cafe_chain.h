#ifndef CAFE_CHAIN_H
#define CAFE_CHAIN_H

#include <vector>
#include <string>
#include "Employee.h"
#include "Globals.h"

using namespace std;

// aici s a folosit polimorfism, functii virtuale, mostenirea, incapsulare

// am utilizat desing patternul OBSERVER
class Sediu
{
protected:
    int nmb_employees;
    int nmb_clients;
    string locatie;
    vector<Employee> employees;

public:
    Sediu();                    // Constructorul clasei Sediu
    virtual ~Sediu() = default; // Destructorul virtual pentru clasele derivate

    // Metode de acces (gettere/settere) pentru a obtine sau modifica atributele
    void addEmployee(const Employee &employee);
    void setLocation(string location);
    void setClients(int clients);

    // Metode pentru a obtine datele interne
    int getNmbEmployees() const;
    int getNmbClients() const;
    string getLocatie() const;
    void loadEmployeesFromFile(const string &fileName, const string &locatie);

    virtual void update() = 0;
    virtual void display() const = 0;
};

class Display : public Sediu
{
public:
    void update() override;
    void display() const override;
};

class CAFE
{
private:
    vector<Sediu *> sedii; // Stocarea pointerilor catre obiecte de tip Sediu
    int nmb_sedii = 0;     // Incapsularea numarului de unitati cafea

public:
    // Metode pentru gestionarea sedii-urilor
    void addCafeUnit(Sediu *center);
    void displayAllSedii();
    void displayCafeLocations();
    int getNmbSedii();

    Sediu *getPtrUnit(int optiune);
};

#endif
