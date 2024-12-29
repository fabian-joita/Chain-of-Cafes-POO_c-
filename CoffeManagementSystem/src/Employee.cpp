#include "Employee.h"
#include <iostream>
#include <string>

using namespace std;

Employee::Employee(const string &Ename, int Eage, double Esalary, const string &Eposition, const string &Elocation, const string &oraInceput, const string &oraSfarsit)
{
    name = Ename;
    age = Eage;
    salary = Esalary;
    position = Eposition;
    location = Elocation;
    ora_inceput = oraInceput;
    ora_sfarsit = oraSfarsit;
}

Barista::Barista(const string &Ename, int Eage, double Esalary, const string &Eposition, const string &Elocation, const string &oraInceput, const string &oraSfarsit)
    : Employee(Ename, Eage, Esalary, Eposition, Elocation, oraInceput, oraSfarsit) {}

Manager::Manager(const string &Ename, int Eage, double Esalary, const string &Eposition, const string &Elocation, const string &oraInceput, const string &oraSfarsit)
    : Employee(Ename, Eage, Esalary, Eposition, Elocation, oraInceput, oraSfarsit) {}

Ospatar::Ospatar(const string &Ename, int Eage, double Esalary, const string &Eposition, const string &Elocation, const string &oraInceput, const string &oraSfarsit)
    : Employee(Ename, Eage, Esalary, Eposition, Elocation, oraInceput, oraSfarsit) {}

string Employee::getName() const { return name; }
int Employee::getAge() const { return age; }
double Employee::getSalary() const { return salary; }
string Employee::getPosition() const { return position; }
string Employee::getLocation() const { return location; }
string Employee::getOraInceput() const { return ora_inceput; }
string Employee::getOraSfarsit() const { return ora_sfarsit; }

void Employee::displayInfo() const
{
    if (languageOption == "EN")
    {
        cout << "Name: " << name << ", Age: " << age << ", Salary: " << salary
             << ", Position: " << position << ", Location: " << location << endl;
    }
    else
    {
        cout << "Nume: " << name << ", Varsta: " << age << ", Salariu: " << salary
             << ", Functie: " << position << ", Locatie: " << location << endl;
    }
}

void Barista::displayInfo() const
{
    if (languageOption == "EN")
    {
        cout << "Barista - Name: " << name << ", Age: " << age << ", Salary: " << salary
             << ", Position: " << position << ", Location: " << location << endl;
    }
    else
    {
        cout << "Barista - Nume: " << name << ", Varsta: " << age << ", Salariu: " << salary
             << ", Functie: " << position << ", Locatie: " << location << endl;
    }
}

void Manager::displayInfo() const
{
    if (languageOption == "EN")
    {
        cout << "Manager - Name: " << name << ", Age: " << age << ", Salary: " << salary
             << ", Position: " << position << ", Location: " << location << endl;
    }
    else
    {
        cout << "Manager - Nume: " << name << ", Varsta: " << age << ", Salariu: " << salary
             << ", Functie: " << position << ", Locatie: " << location << endl;
    }
}

void Ospatar::displayInfo() const
{
    if (languageOption == "EN")
    {
        cout << "Waiter - Name: " << name << ", Age: " << age << ", Salary: " << salary
             << ", Position: " << position << ", Location: " << location << endl;
    }
    else
    {
        cout << "Ospatar - Nume: " << name << ", Varsta: " << age << ", Salariu: " << salary
             << ", Functie: " << position << ", Locatie: " << location << endl;
    }
}
