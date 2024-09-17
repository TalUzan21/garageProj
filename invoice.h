#ifndef __INVOICE_H
#define __INVOICE_H

#include <iostream>
#include <ctime>
#include "customer.h"
#include "appointment.h"
#include "date.h"
#include "employee.h"


using namespace std;

class Customer;
class Appointment;
class Employee;
class SparePart;

class Invoice
{
private:
	double totalPrice;
	Customer* customer;
	Employee* mechanic;
	Appointment* appointment;
	Date invoiceDate;
	MaintenanceSummary* maintenanceSummary;



public:
	Invoice(Customer* customer, Appointment* appointment, const Date& date);
	//Invoice(double totalPrice, const Date& date);
	//Invoice(const Date& date, Customer* customer, Employee* mechanic);

	//double calculateTotalPrice(const SparePart** listOfSparePart);
	void setMaintenanceSummary(MaintenanceSummary* summary);
	void calculateTotalPrice();
	double getTotalPrice() const;
	//void addCharge(const char* itemName, double price);
	void print() const;

	friend ostream& operator<<(ostream& os, const Invoice& invoice);
};

#endif // __INVOICE_H