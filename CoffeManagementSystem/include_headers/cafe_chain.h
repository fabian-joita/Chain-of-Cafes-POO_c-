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
    Sediu();
    virtual ~Sediu() = default;

    void addEmployee(const Employee &employee);
    void setLocation(string location);
    void setClients(int clients);

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
    vector<Sediu *> sedii;
    int nmb_sedii = 0;

public:
    void addCafeUnit(Sediu *center);
    void displayAllSedii();
    void displayCafeLocations();
    int getNmbSedii();

    Sediu *getPtrUnit(int optiune);
};

#endif
