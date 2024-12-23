#include "Employee.h"

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
    cout << "Name: " << name << ", Age: " << age << ", Salary: " << salary
         << ", Position: " << position << ", Location: " << location << endl;
}

void Barista::displayInfo() const
{
    cout << "Barista - Name: " << name << ", Age: " << age << ", Salary: " << salary
         << ", Position: " << position << ", Location: " << location << endl;
}
void Manager::displayInfo() const
{
    cout << "Manager - Name: " << name << ", Age: " << age << ", Salary: " << salary
         << ", Position: " << position << ", Location: " << location << endl;
}
void Ospatar::displayInfo() const
{
    cout << "Ospatar - Name: " << name << ", Age: " << age << ", Salary: " << salary
         << ", Position: " << position << ", Location: " << location << endl;
}