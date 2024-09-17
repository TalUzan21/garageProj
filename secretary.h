#ifndef __SECRETARY_H
#define __SECRETARY_H

#include <ctime>
#include "employee.h"

class Invoice;
class Customer;
class Appointment;
class Garage;
class Date;  // Add this forward declaration


class Secretary : virtual public Employee
{
public:
	Secretary(const char* firstName, const char* lastName);

	const char* getEmployeeType() const override;
//	Invoice* generateInvoice(Customer* customer, Appointment* appointment, const Date& date);
	Invoice* generateInvoice(Appointment* appointment);

	//void createInvoice(Customer* customer, Employee* mechanic, const Date& date);
	void print() const override;
};

#endif // __SECRETARY_H