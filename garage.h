#ifndef __GARAGE_H
#define __GARAGE_H

#include "garage_exception.h"

class Service;
class Employee;
class Customer;
class SparePart;
class Person;

class Garage
{
private:
	char* name;
	Service** allServices;
	Employee** allEmployees;
	Customer** allCustomers;
	SparePart** allSpareParts;
	int numOfServiecs;
	int numOfEmployees;
	int numOfCustomers;
	int numOfSpareParts;
	int maxSpareParts;
	int maxEmployees;

	// Helper functions for generating random data
	static const char* getRandomName();
	static const char* getRandomLastName();
	static const char* getRandomPhoneNumber();
	static const char* getRandomAddress();
	static const char* getRandomCarModel();
	static const char* getRandomCarNumber();

public:
	Garage(const char* name, int maxEmployees = 100);
	Garage(const Garage& other);
	Garage(Garage&& other) noexcept;
	~Garage();

	const Garage& operator=(const Garage& other);
	const Garage& operator=(Garage&& other);
	const Garage& operator+=(const Customer& customer);
	const Garage& operator+=(const Employee& employee);
	const Garage& operator+=(const SparePart& sparePart);

	void printAllServices() const;
	void printAllEmployees() const;
	void printAllCustomers() const;
	void printInventory() const;
	const char* getName() const;
	void addCustomer(const Customer& customer) throw(CustomerException);
	void addEmployee(const Employee& employee) throw(EmployeeException);
	void addEmployee(Employee* employee);
	void addService(const Service& service);
	void addSparePart(SparePart* newPart);
	Employee* getEmployeeById(int id) const;
	Customer* getCustomerById(int id) const;
	const Service** getListOfServices() const;
	const Customer** getListOfCustomers() const;
	const Employee** getListOfEmployees() const;
	SparePart** getListOfSpareParts() const;
	int getNumOfServices() const;
	int getNumOfCustomers() const;
	int getNumOfEmployees() const;
	int getNumOfSpareParts() const;
	int getMaxSpareParts() const;
	SparePart* getSparePartByIndex(int index) const;
	const Service* getService(int index) const throw(ServiceNullException);	


	// ... (existing methods)

	void generateEmployees(int count);
	void generateCustomers(int count);
	void generateService(int count);
	void generateAppointments(int count);

	// Helper method to get a random customer
	Customer* getRandomCustomer() const;
	// Helper method to get a random service
	const Service* getRandomService() const;


};

#endif // __GARAGE_H