#ifndef __MAINTENANCE_SUMARRY_H
#define __MAINTENANCE_SUMARRY_H

#include "date.h"

class Car;
class Service;
class SparePart;
class Employee;
class Invoice;

class MaintenanceSummary
{
private:
	Date dateOfMaintenance;
	Car* car;
	Service* service;
	char* description;
	SparePart** listOfSpareParts;
	Employee* employee;
	Invoice* invoice;
	int numOfSpareParts;
	bool completed = false;

public:
	MaintenanceSummary(const Date& dateOfMaintenance, const Car* car, const Service* service);
	MaintenanceSummary(const MaintenanceSummary& other);
	MaintenanceSummary(MaintenanceSummary&& other);
	~MaintenanceSummary();

	const MaintenanceSummary& operator=(const MaintenanceSummary& other);
	const MaintenanceSummary& operator=(MaintenanceSummary&& other);
	friend ostream& operator<<(ostream& os, const MaintenanceSummary& summary);

	void setDescription(const char* description);
	void addSparePart(const SparePart& sparePart);
	void addSparePart(const SparePart** listOfSpareParts);
	void setEmployee(const Employee* employee);
	void setInvoice(const Invoice* invoice);
	bool isCompleted() const;
	void setCompleted(bool completed);
	void addDescription(const char* additionalDescription);
	const SparePart** getListOfSpareParts() const;
	void print() const;
	int getNumOfSpareParts() const;

	const Service* getService() const { return service; }
	Invoice* getInvoice() const { return invoice; }
	const Date& getDateOfMaintenance() const { return dateOfMaintenance; }

};

#endif // __MAINTENANCE_SUMARRY_H