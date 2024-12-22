#include "Employee.h"

Employee::Employee(const string &Ename, int Eage, double Esalary, const string &Eposition, const string &Elocation)
{
    name = Ename;
    age = Eage;
    salary = Esalary;
    position = Eposition;
    location = Elocation;
}

string Employee::getName() const { return name; }
int Employee::getAge() const { return age; }
double Employee::getSalary() const { return salary; }
string Employee::getPosition() const { return position; }
string Employee::getLocation() const { return location; }
