#define _CRT_SECURE_NO_WARNINGS
#include "maintenance_summary.h"
#include "car.h"
#include "service.h"
#include "spare_part.h"
#include "employee.h"
#include "invoice.h"
#include <cstring>
#include <iostream>

using namespace std;

MaintenanceSummary::MaintenanceSummary(const Date& dateOfMaintenance, const Car* car, const Service* service)
    : dateOfMaintenance(dateOfMaintenance), car(new Car(*car)), service(new Service(*service)),
    description(nullptr), listOfSpareParts(nullptr), employee(nullptr), invoice(nullptr), numOfSpareParts(0), completed(false) {}


MaintenanceSummary::MaintenanceSummary(const MaintenanceSummary& other)
    : dateOfMaintenance(other.dateOfMaintenance), car(new Car(*other.car)), service(new Service(*other.service)),
    employee(other.employee ? new Employee(*other.employee) : nullptr),
    invoice(other.invoice ? new Invoice(*other.invoice) : nullptr),
    numOfSpareParts(other.numOfSpareParts) {
    if (other.description) {
        description = new char[strlen(other.description) + 1];
        strcpy(description, other.description);
    }
    else {
        description = nullptr;
    }

    if (other.listOfSpareParts) {
        listOfSpareParts = new SparePart * [numOfSpareParts];
        for (int i = 0; i < numOfSpareParts; i++) {
            listOfSpareParts[i] = new SparePart(*other.listOfSpareParts[i]);
        }
    }
    else {
        listOfSpareParts = nullptr;
    }
}

MaintenanceSummary::MaintenanceSummary(MaintenanceSummary&& other)
    : dateOfMaintenance(std::move(other.dateOfMaintenance)), car(other.car), service(other.service),
    description(other.description), listOfSpareParts(other.listOfSpareParts),
    employee(other.employee), invoice(other.invoice), numOfSpareParts(other.numOfSpareParts),
    completed(other.completed)
{
    other.car = nullptr;
    other.service = nullptr;
    other.description = nullptr;
    other.listOfSpareParts = nullptr;
    other.employee = nullptr;
    other.invoice = nullptr;
    other.numOfSpareParts = 0;
    other.completed = false;
}


MaintenanceSummary::~MaintenanceSummary() {
    delete car;
    delete service;
    delete[] description;
    for (int i = 0; i < numOfSpareParts; i++) {
        delete listOfSpareParts[i];
    }
    delete[] listOfSpareParts;
    delete employee;
    delete invoice;
}

const MaintenanceSummary& MaintenanceSummary::operator=(const MaintenanceSummary& other) {
    if (this != &other) {
        delete car;
        delete service;
        delete[] description;
        for (int i = 0; i < numOfSpareParts; i++) {
            delete listOfSpareParts[i];
        }
        delete[] listOfSpareParts;
        delete employee;
        delete invoice;

        dateOfMaintenance = other.dateOfMaintenance;
        car = new Car(*other.car);
        service = new Service(*other.service);

        if (other.description) {
            description = new char[strlen(other.description) + 1];
            strcpy(description, other.description);
        }
        else {
            description = nullptr;
        }

        numOfSpareParts = other.numOfSpareParts;
        if (other.listOfSpareParts) {
            listOfSpareParts = new SparePart * [numOfSpareParts];
            for (int i = 0; i < numOfSpareParts; i++) {
                listOfSpareParts[i] = new SparePart(*other.listOfSpareParts[i]);
            }
        }
        else {
            listOfSpareParts = nullptr;
        }

        employee = other.employee ? new Employee(*other.employee) : nullptr;
        invoice = other.invoice ? new Invoice(*other.invoice) : nullptr;
    }
    return *this;
}

const MaintenanceSummary& MaintenanceSummary::operator=(MaintenanceSummary&& other) {
    if (this != &other) {
        delete car;
        delete service;
        delete[] description;
        for (int i = 0; i < numOfSpareParts; i++) {
            delete listOfSpareParts[i];
        }
        delete[] listOfSpareParts;
        delete employee;
        delete invoice;

        dateOfMaintenance = other.dateOfMaintenance;
        car = other.car;
        service = other.service;
        description = other.description;
        listOfSpareParts = other.listOfSpareParts;
        numOfSpareParts = other.numOfSpareParts;
        employee = other.employee;
        invoice = other.invoice;

        other.car = nullptr;
        other.service = nullptr;
        other.description = nullptr;
        other.listOfSpareParts = nullptr;
        other.numOfSpareParts = 0;
        other.employee = nullptr;
        other.invoice = nullptr;
    }
    return *this;
}

ostream& operator<<(ostream& os, const MaintenanceSummary& summary) {
    if (summary.description) {
        os << "\nDescription: " << summary.description;
    }

    if (summary.employee) {
        os << "\nMechanic: " << summary.employee->getEmployeeType() << ": " << summary.employee->getFirstName() << " " << summary.employee->getLastName();
    }

    os << "\nDate: " << summary.dateOfMaintenance
        << "\n" << *summary.car
        << "\n" << *summary.service;
    if (summary.numOfSpareParts != 0) 
        os << "\nSpare Parts Used:";
    

        int j = 1;
        for (int i = 0; i < summary.numOfSpareParts; ++i) {
            os << "\n" << j << " - " << summary.listOfSpareParts[i]->getName()
                << " (Price: $" << summary.listOfSpareParts[i]->getPrice() << ")";
            //cout << j << " - " << summary.listOfSpareParts[i] << endl;
            j++;
        }

    if (summary.invoice) {
        os << "\nInvoice: " << *summary.invoice;
    }


    return os;
}

void MaintenanceSummary::setDescription(const char* newDescription) {
    delete[] description;
    description = new char[strlen(newDescription) + 1];
    strcpy(description, newDescription);
}

void MaintenanceSummary::addSparePart(const SparePart& sparePart) {
    SparePart** newList = new SparePart * [numOfSpareParts + 1];
    for (int i = 0; i < numOfSpareParts; i++) {
        newList[i] = listOfSpareParts[i];
    }
    newList[numOfSpareParts] = new SparePart(sparePart);
    delete[] listOfSpareParts;
    listOfSpareParts = newList;
    numOfSpareParts++;
}

void MaintenanceSummary::addSparePart(const SparePart** newListOfSpareParts) {
    // Assuming newListOfSpareParts is null-terminated
    int count = 0;
    while (newListOfSpareParts[count] != nullptr) {
        count++;
    }

    SparePart** newList = new SparePart * [numOfSpareParts + count];
    for (int i = 0; i < numOfSpareParts; i++) {
        newList[i] = listOfSpareParts[i];
    }
    for (int i = 0; i < count; i++) {
        newList[numOfSpareParts + i] = new SparePart(*newListOfSpareParts[i]);
    }
    delete[] listOfSpareParts;
    listOfSpareParts = newList;
    numOfSpareParts += count;
}

void MaintenanceSummary::setEmployee(const Employee* newEmployee) {
    delete employee;
    employee = new Employee(*newEmployee);
}


void MaintenanceSummary::setInvoice(const Invoice* newInvoice) {
    delete invoice;
    invoice = new Invoice(*newInvoice);
}

bool MaintenanceSummary::isCompleted() const {
    return completed;
}

void MaintenanceSummary::setCompleted(bool completed) {
    this->completed = completed;
}

void MaintenanceSummary::addDescription(const char* additionalDescription) {
    if (description == nullptr) {
        setDescription(additionalDescription);
    }
    else {
        char* newDescription = new char[strlen(description) + strlen(additionalDescription) + 2];
        strcpy(newDescription, description);
        strcat(newDescription, "\n");
        strcat(newDescription, additionalDescription);
        delete[] description;
        description = newDescription;
    }
}

void MaintenanceSummary::print() const {
    cout << *this;
}

const SparePart** MaintenanceSummary::getListOfSpareParts() const {
    return const_cast<const SparePart**>(listOfSpareParts);
}

int MaintenanceSummary::getNumOfSpareParts() const {
    return numOfSpareParts;
}