#ifndef CAFE_CHAIN_H
#define CAFE_CHAIN_H

#include <vector>
#include <string>
#include "Employee.h"

using namespace std;

class Sediu
{
protected:
    int nmb_employees;
    int nmb_clients;
    string locatie;
    vector<Employee> employees;

public:
    Sediu();                    // Constructorul declarat
    virtual ~Sediu() = default; // Destructor virtual

    void addEmployee(const Employee &employee);
    void setLocation(string location);
    void setClients(int clients);

    int getNmbEmployees() const;
    int getNmbClients() const;
    string getLocatie() const;

    virtual void update() = 0;        // Metodă virtuală pură
    virtual void display() const = 0; // Metodă virtuală pură pentru display
};

class Display : public Sediu
{
public:
    void update() override;        // Marcare const
    void display() const override; // Implementarea metodei display
};

class CAFE
{
private:
    vector<Sediu *> sedii;
    int nmb_sedii = 0;

public:
    void addCafeUnit(Sediu *center); // Modificăm funcția să nu mai primească un pointer pentru nmb_sedii
    void displayAllSedii();
    void displayCafeLocations();
    int getNmbSedii();

    Sediu *getPtrUnit(int optiune); // Metoda pentru a obține pointer la o cafenea
};

#endif
