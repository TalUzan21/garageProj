#ifndef __EMPLOYEE_H
#define __EMPLOYEE_H

#include "person.h"
#include <iostream>

class Employee : public Person
{
private:
	static int counter; // for employeeId

protected:
	int employeeId;


public:
	Employee(const char* firstName, const char* lastName);
	virtual ~Employee();


	const char* getEmployeeId() const;
	virtual const char* getEmployeeType() const;
	virtual void print() const override;
	friend std::ostream& operator<<(std::ostream& os, const Employee& obj);
};

#endif // __EMPLOYEE_H