#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string>

using namespace std;

class Employee
{
private:
    string name;
    int age;
    double salary;
    string position;
    string location;

public:
    Employee(const string &Ename, int Eage, double Esalary, const string &Eposition, const string &Elocation);
    string getName() const;
    int getAge() const;
    double getSalary() const;
    string getPosition() const;
    string getLocation() const;
};

#endif
