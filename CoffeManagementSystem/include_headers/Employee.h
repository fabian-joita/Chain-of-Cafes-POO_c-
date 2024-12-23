
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// aici o sa folosim mostenire pt clasele Barista, Manager, Ospătar - care vor mosteni Employee
// de asemenea am folosit si polimorfism in displayInfo()
class Employee
{
protected:
    string name;
    int age;
    double salary;
    string position;
    string location;
    string ora_inceput;
    string ora_sfarsit;

public:
    // Constructor
    Employee(const string &Ename, int Eage, double Esalary, const string &Eposition, const string &Elocation, const string &oraInceput, const string &oraSfarsit);

    // Destructor virtual pentru polimorfism
    virtual ~Employee() {}

    // Metodă virtuală pentru a afisa informațiile angajatului
    virtual void displayInfo() const;

    // Getteri pentru fiecare atribut
    string getName() const;
    int getAge() const;
    double getSalary() const;
    string getPosition() const;
    string getLocation() const;
    string getOraInceput() const;
    string getOraSfarsit() const;
};

// Clasa Barista
class Barista : public Employee
{
public:
    Barista(const string &Ename, int Eage, double Esalary, const string &Eposition, const string &Elocation, const string &oraInceput, const string &oraSfarsit);

    // Suprascrierea metodei displayInfo
    void displayInfo() const override;
};

// Clasa Manager
class Manager : public Employee
{
public:
    Manager(const string &Ename, int Eage, double Esalary, const string &Eposition, const string &Elocation, const string &oraInceput, const string &oraSfarsit);

    // Suprascrierea metodei displayInfo
    void displayInfo() const override;
};

// Clasa Ospatar
class Ospatar : public Employee
{
public:
    Ospatar(const string &Ename, int Eage, double Esalary, const string &Eposition, const string &Elocation, const string &oraInceput, const string &oraSfarsit);

    // Suprascrierea metodei displayInfo
    void displayInfo() const override;
};

#endif // EMPLOYEE_H
