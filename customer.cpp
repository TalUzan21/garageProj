#define _CRT_SECURE_NO_WARNINGS
#include "customer.h"
#include "car.h"
#include "appointment.h"
#include "maintenance_summary.h"
#include "invoice.h"
#include "date.h"
#include <cstring>
#include <iostream>

int Customer::counter = 0;

Customer::Customer(const char* firstName, const char* lastName) : Person(firstName, lastName)
{
    customerId = ++counter;
    phoneNumber[0] = '\0';
    address = nullptr;
    listOfCars = nullptr;
    listOfAppointments = nullptr;
    numOfCars = 0;
    numOfAppointments = 0;
}

Customer::Customer(const Customer& other) : Person(other)
{
    customerId = other.customerId;
    strncpy(phoneNumber, other.phoneNumber, 11);

    if (other.address)
    {
        address = new char[strlen(other.address) + 1];
        strcpy(address, other.address);
    }
    else
    {
        address = nullptr;
    }

    numOfCars = other.numOfCars;
    listOfCars = new Car * [numOfCars];
    for (int i = 0; i < numOfCars; i++)
    {
        listOfCars[i] = new Car(*other.listOfCars[i]);
    }

    numOfAppointments = other.numOfAppointments;
    listOfAppointments = new Appointment * [numOfAppointments];
    for (int i = 0; i < numOfAppointments; i++)
    {
        listOfAppointments[i] = new Appointment(*other.listOfAppointments[i]);
    }
}

Customer::Customer(Customer&& other) noexcept
    : Person(std::move(other))
{
    customerId = other.customerId;
    std::strncpy(phoneNumber, other.phoneNumber, 11);
    address = other.address;
    listOfCars = other.listOfCars;
    listOfAppointments = other.listOfAppointments;
    numOfCars = other.numOfCars;
    numOfAppointments = other.numOfAppointments;

    other.address = nullptr;
    other.listOfCars = nullptr;
    other.listOfAppointments = nullptr;
    other.numOfCars = 0;
    other.numOfAppointments = 0;
}

Customer::~Customer()
{
    delete[] address;
    for (int i = 0; i < numOfCars; i++)
    {
        delete listOfCars[i];
    }
    delete[] listOfCars;
    for (int i = 0; i < numOfAppointments; i++)
    {
        delete listOfAppointments[i];
    }
    delete[] listOfAppointments;
}

const Customer& Customer::operator=(const Customer& other)
{
    if (this != &other)
    {
        Person::operator=(other);

        customerId = other.customerId;
        strncpy(phoneNumber, other.phoneNumber, 11);

        delete[] address;
        if (other.address)
        {
            address = new char[strlen(other.address) + 1];
            strcpy(address, other.address);
        }
        else
        {
            address = nullptr;
        }

        for (int i = 0; i < numOfCars; i++)
        {
            delete listOfCars[i];
        }
        delete[] listOfCars;

        numOfCars = other.numOfCars;
        listOfCars = new Car * [numOfCars];
        for (int i = 0; i < numOfCars; i++)
        {
            listOfCars[i] = new Car(*other.listOfCars[i]);
        }

        for (int i = 0; i < numOfAppointments; i++)
        {
            delete listOfAppointments[i];
        }
        delete[] listOfAppointments;

        numOfAppointments = other.numOfAppointments;
        listOfAppointments = new Appointment * [numOfAppointments];
        for (int i = 0; i < numOfAppointments; i++)
        {
            listOfAppointments[i] = new Appointment(*other.listOfAppointments[i]);
        }
    }
    return *this;
}

const Customer& Customer::operator=(Customer&& other)
{
    if (this != &other)
    {
        Person::operator=(std::move(other));

        customerId = other.customerId;
        strncpy(phoneNumber, other.phoneNumber, 11);

        delete[] address;
        address = other.address;

        for (int i = 0; i < numOfCars; i++)
        {
            delete listOfCars[i];
        }
        delete[] listOfCars;

        listOfCars = other.listOfCars;
        numOfCars = other.numOfCars;

        for (int i = 0; i < numOfAppointments; i++)
        {
            delete listOfAppointments[i];
        }
        delete[] listOfAppointments;

        listOfAppointments = other.listOfAppointments;
        numOfAppointments = other.numOfAppointments;

        other.address = nullptr;
        other.listOfCars = nullptr;
        other.listOfAppointments = nullptr;
        other.numOfCars = 0;
        other.numOfAppointments = 0;
    }
    return *this;
}

const Customer& Customer::operator+=(const Car& car)
{
    try {
        addCar(car);
    }
    catch (CarException& e) {
        std::cerr << "Error adding car: " << e.what() << std::endl;
    }
    return *this;
}

ostream& operator<<(ostream& os, const Customer& customer)
{
    os << "Customer ID: " << customer.customerId << ", Name: " << customer.getFirstName() << " " << customer.getLastName()
        << ", Phone: " << customer.phoneNumber << ", Address: " << (customer.address ? customer.address : "N/A");
    return os;
}

void Customer::bookAppointment(const Appointment& appointment)
{
    Appointment** newList = new Appointment * [numOfAppointments + 1];
    for (int i = 0; i < numOfAppointments; i++)
    {
        newList[i] = listOfAppointments[i];
    }
    newList[numOfAppointments] = new Appointment(appointment);

    delete[] listOfAppointments;
    listOfAppointments = newList;
    numOfAppointments++;
}

void Customer::addCar(const Car& car)
{
    for (int i = 0; i < numOfCars; i++)
    {
        if (strcmp(listOfCars[i]->getCarNumber(), car.getCarNumber()) == 0)
        {
            throw CarException("Car with this number already exists");
        }
    }

    Car** newList = new Car * [numOfCars + 1];
    for (int i = 0; i < numOfCars; i++)
    {
        newList[i] = listOfCars[i];
    }
    newList[numOfCars] = new Car(car);  // Create a new Car object

    delete[] listOfCars;
    listOfCars = newList;
    numOfCars++;
}

const char* Customer::getAddress() const
{
    return address;
}

const char* Customer::getPhoneNumber() const
{
    return phoneNumber;
}

const Car** Customer::getListOfCars() const
{
    return const_cast<const Car**>(listOfCars);
}

const Car* Customer::getCar(int index) const
{
    if (index >= 0 && index < numOfCars)
    {
        return listOfCars[index];
    }
    return nullptr;
}

const char* Customer::getCustomerId() const
{
    static char idStr[20];
    snprintf(idStr, sizeof(idStr), "%d", customerId);
    return idStr;
}

int Customer::getNumOfCars() const
{
    return numOfCars;
}

Appointment** Customer::getAllAppointments() const
{
    return listOfAppointments;
}

int Customer::getNumOfAppiontments() const
{
    return numOfAppointments;
}

Appointment* Customer::getAppointmentByIndex(int index) const
{
    if (index >= 0 && index < numOfAppointments)
    {
        return listOfAppointments[index];
    }
    return nullptr;
}

void Customer::setPhoneNumber(const char* number)
{
    if (strlen(number) != 10)
    {
        throw CustomerException("Phone number must be 10 digits");
    }
    strncpy(phoneNumber, number, 11);
}

void Customer::setAddress(const char* newAddress)
{
    delete[] address;
    address = new char[strlen(newAddress) + 1];
    strcpy(address, newAddress);
}

void Customer::printAppointment(const Date& date)
{
    bool found = false;
    for (int i = 0; i < numOfAppointments; i++)
    {
        if (listOfAppointments[i]->getDate() == date)
        {
            cout << *listOfAppointments[i] << endl;
            found = true;
        }
    }
    if (!found)
    {
        throw InvalidDateException("No appointment found for the given date");
    }
}

void Customer::printMaintenanceSummary(const Car* car) const
{
    if (!car) {
        throw CarNullException("Car pointer is null");
    }
    bool found = false;
    cout << "Maintenance summaries for the car " << car->getCarNumber() << ":" << endl;
    for (int i = 0; i < numOfAppointments; i++) {
        const Car* appointmentCar = listOfAppointments[i]->getCar();
        if (appointmentCar && strcmp(appointmentCar->getCarNumber(), car->getCarNumber()) == 0) {
            MaintenanceSummary* summary = listOfAppointments[i]->getMaintenanceSummary();
            if (summary) {
                cout << "Appointment Date: " << listOfAppointments[i]->getDate() << endl;
                cout << *summary << endl;
                found = true;
            }
        }
        cout << endl;
    }
    if (!found) {
        cout << "No maintenance summaries found for the given car." << endl;
    }
}

void Customer::printAllInvoices() const

{
    bool found = false;
    for (int i = 0; i < numOfAppointments; i++)
    {
        Invoice* invoice = listOfAppointments[i]->getInvoice();
        if (invoice)
        {
            cout << *invoice << endl;
            found = true;
        }
    }
    if (!found)
    {
        cout << "No invoices found for this customer." << endl;
    }
}

void Customer::printCars() const
{
    cout << "Cars:" << endl;
    for (int i = 0; i < numOfCars; i++)
    {
        cout << i + 1 << " - " << *listOfCars[i] << endl;
    }
}

void Customer::printAppointments() const
{
    cout << "Appointments:" << endl;
    for (int i = 0; i < numOfAppointments; i++)
    {
        cout << i + 1 << " - " << *listOfAppointments[i] << endl;
    }
}

void Customer::print() const
{
    cout << *this << endl;
    printCars();
    printAppointments();
}
