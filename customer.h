#ifndef __CUSTOMER_H
#define __CUSTOMER_H

#include "person.h"

#include <iostream>
using namespace std;

#include "garage_exception.h"

class Car;
class Appointment;
class MaintenanceSummary;
class Invoice;
class Date;

class Customer : public Person
{
private:
	static int counter; // for customerId
	int customerId;
	char phoneNumber[11] = {};
	char* address;
	Car** listOfCars;
	Appointment** listOfAppointments;
	int numOfCars;
	int numOfAppointments;

public:
	Customer(const char* firstName, const char* lastName);
	Customer(const Customer& other);
	Customer(Customer&& other) noexcept;
	~Customer();

	const Customer& operator=(const Customer& other);
	const Customer& operator=(Customer&& other);
	const Customer& operator+=(const Car& car);
	friend std::ostream& operator<<(std::ostream& os, const Customer& obj);

	void bookAppointment(const Appointment& appointment) throw(GarageExceptions);
	void addCar(const Car& car) throw(CarException);
	int getId() const { return customerId; }
	const char* getAddress() const;
	const char* getPhoneNumber() const;
	const Car** getListOfCars() const;
	const Car* getCar(int index) const;
	const char* getCustomerId() const;
	int getNumOfCars() const;
	Appointment** getAllAppointments() const;
	int getNumOfAppiontments() const;
	Appointment* getAppointmentByIndex(int index) const;
	void setPhoneNumber(const char* number) throw(CustomerException);
	void setAddress(const char* address);
	void printAppointment(const Date& date) throw(InvalidDateException);
	void printMaintenanceSummary(const Car* car) const throw(CarNullException);
	void printAllInvoices() const;
	void printCars() const;
	void printAppointments() const;
	void print() const override;
};

#endif // __CUSTOMER_H