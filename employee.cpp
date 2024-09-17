#include "employee.h"
#include <iostream>
#include <cstring>
using namespace std;


int Employee::counter = 0;

Employee::Employee(const char* firstName, const char* lastName)
    : Person(firstName, lastName)
{
    employeeId = ++counter;
}

Employee::~Employee() = default;


const char* Employee::getEmployeeId() const {
    static char idStr[20];
    snprintf(idStr, sizeof(idStr), "%d", employeeId);
    return idStr;
}


void Employee::print() const {
    cout << "Employee ID: " << employeeId
        << ", Name: " << getFirstName() << " " << getLastName()
        << ", Employee type: " << getEmployeeType() << endl;
}

const char* Employee::getEmployeeType() const {
    return "Unknown";
}

ostream& operator<<(std::ostream& os, const Employee& employee)
{
    os << "Employee ID: " << employee.getEmployeeId()
        << ", Name: " << employee.getFirstName() << " " << employee.getLastName();
    return os;
}