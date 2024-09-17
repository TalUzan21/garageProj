#define _CRT_SECURE_NO_WARNINGS
#include "garage.h"
#include "service.h"
#include "employee.h"
#include "mechanic.h"
#include "shift_manager.h"
#include "secretary.h"
#include "customer.h"
#include "spare_part.h"
#include <cstring>
#include <string>
#include "car.h"
#include "appointment.h"
#include "InputValidator.h"
#include <cstdlib>
#include <ctime>

Garage::Garage(const char* name, int maxEmployees)
    : numOfServiecs(0), numOfEmployees(0), numOfCustomers(0), numOfSpareParts(0), maxEmployees(maxEmployees), maxSpareParts(100)
{
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);

    allServices = nullptr;
    allCustomers = nullptr;
    allSpareParts = nullptr;

    allEmployees = new Employee * [maxEmployees];

    allSpareParts = new SparePart * [maxSpareParts];
    for (int i = 0; i < maxSpareParts; i++) {
        allSpareParts[i] = nullptr;
    }
}

Garage::Garage(const Garage& other) : numOfServiecs(other.numOfServiecs), numOfEmployees(other.numOfEmployees),
numOfCustomers(other.numOfCustomers), numOfSpareParts(other.numOfSpareParts), maxSpareParts(other.maxSpareParts){
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);

    allServices = new Service * [numOfServiecs];
    for (int i = 0; i < numOfServiecs; i++) {
        allServices[i] = new Service(*other.allServices[i]);
    }

    allEmployees = new Employee * [numOfEmployees];
    for (int i = 0; i < numOfEmployees; i++) {
        allEmployees[i] = new Employee(*other.allEmployees[i]);
    }

    allCustomers = new Customer * [numOfCustomers];
    for (int i = 0; i < numOfCustomers; i++) {
        allCustomers[i] = new Customer(*other.allCustomers[i]);
    }

    allSpareParts = new SparePart * [numOfSpareParts];
    for (int i = 0; i < numOfSpareParts; i++) {
        allSpareParts[i] = new SparePart(*other.allSpareParts[i]);
    }
}

Garage::Garage(Garage&& other) noexcept
    : name(other.name), allServices(other.allServices), allEmployees(other.allEmployees),
    allCustomers(other.allCustomers), allSpareParts(other.allSpareParts),
    numOfServiecs(other.numOfServiecs), numOfEmployees(other.numOfEmployees),
    numOfCustomers(other.numOfCustomers), numOfSpareParts(other.numOfSpareParts), 
    maxSpareParts(other.maxSpareParts)
{
    other.name = nullptr;
    other.allServices = nullptr;
    other.allEmployees = nullptr;
    other.allCustomers = nullptr;
    other.allSpareParts = nullptr;
    other.numOfServiecs = 0;
    other.numOfEmployees = 0;
    other.numOfCustomers = 0;
    other.numOfSpareParts = 0;
}

Garage::~Garage() {
    delete[] name;

    for (int i = 0; i < numOfServiecs; i++)
        delete allServices[i];
    delete[] allServices;

    for (int i = 0; i < numOfEmployees; i++)
        delete allEmployees[i];
    delete[] allEmployees;

    for (int i = 0; i < numOfCustomers; i++)
        delete allCustomers[i];
    delete[] allCustomers;

    for (int i = 0; i < numOfSpareParts; i++)
        delete allSpareParts[i];
    delete[] allSpareParts;

    for (int i = 0; i < numOfSpareParts; i++) {
        delete allSpareParts[i];
    }
    delete[] allSpareParts;
}

const Garage& Garage::operator=(const Garage& other) {
    if (this != &other) {
        delete[] name;
        for (int i = 0; i < numOfServiecs; i++) {
            delete allServices[i];
        }
        delete[] allServices;
        for (int i = 0; i < numOfEmployees; i++) {
            delete allEmployees[i];
        }
        delete[] allEmployees;
        for (int i = 0; i < numOfCustomers; i++) {
            delete allCustomers[i];
        }
        delete[] allCustomers;
        for (int i = 0; i < numOfSpareParts; i++) {
            delete allSpareParts[i];
        }
        delete[] allSpareParts;

        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);

        numOfServiecs = other.numOfServiecs;
        numOfEmployees = other.numOfEmployees;
        numOfCustomers = other.numOfCustomers;
        numOfSpareParts = other.numOfSpareParts;

        allServices = new Service * [numOfServiecs];
        for (int i = 0; i < numOfServiecs; i++) {
            allServices[i] = new Service(*other.allServices[i]);
        }

        allEmployees = new Employee * [numOfEmployees];
        for (int i = 0; i < numOfEmployees; i++) {
            allEmployees[i] = new Employee(*other.allEmployees[i]);
        }

        allCustomers = new Customer * [numOfCustomers];
        for (int i = 0; i < numOfCustomers; i++) {
            allCustomers[i] = new Customer(*other.allCustomers[i]);
        }

        allSpareParts = new SparePart * [numOfSpareParts];
        for (int i = 0; i < numOfSpareParts; i++) {
            allSpareParts[i] = new SparePart(*other.allSpareParts[i]);
        }
    }
    return *this;
}

const Garage& Garage::operator=(Garage&& other) {
    if (this != &other) {
        // Delete current resources
        delete[] name;
        for (int i = 0; i < numOfServiecs; i++) {
            delete allServices[i];
        }
        delete[] allServices;
        for (int i = 0; i < numOfEmployees; i++) {
            delete allEmployees[i];
        }
        delete[] allEmployees;
        for (int i = 0; i < numOfCustomers; i++) {
            delete allCustomers[i];
        }
        delete[] allCustomers;
        for (int i = 0; i < numOfSpareParts; i++) {
            delete allSpareParts[i];
        }
        delete[] allSpareParts;

        // Move resources from other
        name = other.name;
        allServices = other.allServices;
        allEmployees = other.allEmployees;
        allCustomers = other.allCustomers;
        allSpareParts = other.allSpareParts;
        numOfServiecs = other.numOfServiecs;
        numOfEmployees = other.numOfEmployees;
        numOfCustomers = other.numOfCustomers;
        numOfSpareParts = other.numOfSpareParts;

        // Reset other's resources
        other.name = nullptr;
        other.allServices = nullptr;
        other.allEmployees = nullptr;
        other.allCustomers = nullptr;
        other.allSpareParts = nullptr;
        other.numOfServiecs = 0;
        other.numOfEmployees = 0;
        other.numOfCustomers = 0;
        other.numOfSpareParts = 0;
    }
    return *this;
}

const Garage& Garage::operator+=(const Customer & customer) {
    Customer** newCustomers = new Customer * [numOfCustomers + 1];
    for (int i = 0; i < numOfCustomers; i++) {
        newCustomers[i] = allCustomers[i];
    }
    newCustomers[numOfCustomers] = new Customer(customer);
    delete[] allCustomers;
    allCustomers = newCustomers;
    numOfCustomers++;
    return *this;
}

const Garage& Garage::operator+=(const Employee & employee) {
    Employee** newEmployees = new Employee * [numOfEmployees + 1];
    for (int i = 0; i < numOfEmployees; i++) {
        newEmployees[i] = allEmployees[i];
    }
    newEmployees[numOfEmployees] = new Employee(employee);
    delete[] allEmployees;
    allEmployees = newEmployees;
    numOfEmployees++;
    return *this;
}

const Garage& Garage::operator+=(const SparePart & sparePart) {
    SparePart** newSpareParts = new SparePart * [numOfSpareParts + 1];
    for (int i = 0; i < numOfSpareParts; i++) {
        newSpareParts[i] = allSpareParts[i];
    }
    newSpareParts[numOfSpareParts] = new SparePart(sparePart);
    delete[] allSpareParts;
    allSpareParts = newSpareParts;
    numOfSpareParts++;
    return *this;
}

void Garage::printAllServices() const {
    for (int i = 0; i < numOfServiecs; i++) {
        allServices[i]->print();
        cout << endl;
    }
}

void Garage::printAllEmployees() const {
    for (int i = 0; i < numOfEmployees; i++) {
        allEmployees[i]->print();
        cout << endl;
    }
}

void Garage::printAllCustomers() const {
    for (int i = 0; i < numOfCustomers; i++) {
        cout << (i+1) << " - ";
        allCustomers[i]->print();
        cout << endl;
    }
}

void Garage::printInventory() const {
    for (int i = 0; i < numOfSpareParts; i++) {
        allSpareParts[i]->print();
        cout << endl;
    }
}

const char* Garage::getName() const {
    return name;
}

void Garage::addCustomer(const Customer & customer) {
    for (int i = 0; i < numOfCustomers; i++) {
        if (strcmp(allCustomers[i]->getFirstName(), customer.getFirstName()) == 0 &&
            strcmp(allCustomers[i]->getLastName(), customer.getLastName()) == 0) {
            throw CustomerException("Customer already exists");
        }
    }
    *this += customer;
}

void Garage::addEmployee(const Employee & employee) {
    for (int i = 0; i < numOfEmployees; i++) {
        if (strcmp(allEmployees[i]->getFirstName(), employee.getFirstName()) == 0 &&
            strcmp(allEmployees[i]->getLastName(), employee.getLastName()) == 0) {
            throw EmployeeException("Employee already exists");
        }
    }
    *this += employee;
}

void Garage::addEmployee(Employee* employee) {
    if (numOfEmployees < maxEmployees) {
        allEmployees[numOfEmployees++] = employee;
    }
    else {
        // Handle the case when the employee array is full
        cout << "Error: Maximum number of employees reached." << endl;
        delete employee;  // Avoid memory leak
    }
}

void Garage::addService(const Service & service) {
    Service** newServices = new Service * [numOfServiecs + 1];
    for (int i = 0; i < numOfServiecs; i++) {
        newServices[i] = allServices[i];
    }
    newServices[numOfServiecs] = new Service(service);
    delete[] allServices;
    allServices = newServices;
    numOfServiecs++;
}

Employee* Garage::getEmployeeById(int id) const {
    for (int i = 0; i < numOfEmployees; i++) {
        if (std::stoi(allEmployees[i]->getEmployeeId()) == id) {
            return allEmployees[i];
        }
    }
    return nullptr;
}

Customer* Garage::getCustomerById(int id) const {
    for (int i = 0; i < numOfCustomers; i++) {
        if (atoi(allCustomers[i]->getCustomerId()) == id) {
            return allCustomers[i];
        }
    }
    return nullptr;
}

const Service** Garage::getListOfServices() const {
    return const_cast<const Service**>(allServices);
}

const Customer** Garage::getListOfCustomers() const {
    return const_cast<const Customer**>(allCustomers);
}

const Employee** Garage::getListOfEmployees() const {
    return const_cast<const Employee**>(allEmployees);
}

SparePart** Garage::getListOfSpareParts() const {
    return allSpareParts;
}

int Garage::getNumOfServices() const {
    return numOfServiecs;
}

int Garage::getNumOfCustomers() const {
    return numOfCustomers;
}

int Garage::getNumOfEmployees() const {
    return numOfEmployees;
}

int Garage::getNumOfSpareParts() const {
    return numOfSpareParts;
}

int Garage::getMaxSpareParts() const
{ 
    return maxSpareParts; 
}


SparePart* Garage::getSparePartByIndex(int index) const {
    if (index >= 0 && index < numOfSpareParts) {
        return allSpareParts[index];
    }
    return nullptr;
}

void Garage::addSparePart(SparePart* newPart) {
    if (numOfSpareParts < maxSpareParts) {
        allSpareParts[numOfSpareParts] = newPart;
        numOfSpareParts++;
    }
    else {
        throw SparePartException("Maximum number of spare parts reached");
    }
}

const Service* Garage::getService(int index) const {
    if (index >= 0 && index <= numOfServiecs) {
        return allServices[index];
    }
    throw ServiceNullException("Service not found");
}




// ... (existing implementation)

const char* Garage::getRandomName() {
    static const char* names[] = { "John", "Jane", "Michael", "Emily", "David", "Sarah", "Daniel", "Emma", "Christopher", "Olivia" };
    return names[rand() % (sizeof(names) / sizeof(names[0]))];
}

const char* Garage::getRandomLastName() {
    static const char* lastNames[] = { "Smith", "Johnson", "Williams", "Brown", "Jones", "Garcia", "Miller", "Davis", "Rodriguez", "Martinez" };
    return lastNames[rand() % (sizeof(lastNames) / sizeof(lastNames[0]))];
}

const char* Garage::getRandomPhoneNumber() {
    static char phoneNumber[11];
    for (int i = 0; i < 10; ++i) {
        phoneNumber[i] = '0' + (rand() % 10);
    }
    phoneNumber[10] = '\0';
    return phoneNumber;
}

const char* Garage::getRandomAddress() {
    static const char* addresses[] = { "123 Main St", "456 Elm St", "789 Oak St", "321 Pine St", "654 Maple St" };
    return addresses[rand() % (sizeof(addresses) / sizeof(addresses[0]))];
}

const char* Garage::getRandomCarModel() {
    static const char* models[] = { "Toyota Camry", "Honda Civic", "Ford F-150", "Chevrolet Malibu", "Nissan Altima" };
    return models[rand() % (sizeof(models) / sizeof(models[0]))];
}

const char* Garage::getRandomCarNumber() {
    const int numberLength = 9;
    char* carNumber = new char[numberLength + 1]; // Allocate memory for the car number string

    std::srand(std::time(0)); // Seed the random number generator

    for (int i = 0; i < numberLength; ++i) {
        int digit = std::rand() % 10; // Generate a random digit between 0 and 9
        carNumber[i] = '0' + digit;   // Convert digit to corresponding char
    }

    carNumber[numberLength] = '\0'; // Null-terminate the string

    return carNumber;
}

void Garage::generateEmployees(int count) {
    for (int i = 0; i < count; ++i) {
        const char* firstName = getRandomName();
        const char* lastName = getRandomLastName();
        int type = rand() % 3;  // 0: Mechanic, 1: Secretary, 2: ShiftManager

        Employee* newEmployee = nullptr;
        switch (type) {
        case 0:
            newEmployee = new Mechanic(firstName, lastName);
            break;
        case 1:
            newEmployee = new Secretary(firstName, lastName);
            break;
        case 2:
            newEmployee = new ShiftManager(firstName, lastName);
            break;
        }

        try {
            this->addEmployee(newEmployee);
        }
        catch (EmployeeException& e) {
            delete newEmployee;
            cout << "Failed to add employee: " << e.what() << endl;
        }
    }
}

void Garage::generateCustomers(int count) {
    for (int i = 0; i < count; ++i) {
        const char* firstName = getRandomName();
        const char* lastName = getRandomLastName();
        Customer* newCustomer = new Customer(firstName, lastName);

        newCustomer->setPhoneNumber(getRandomPhoneNumber());
        newCustomer->setAddress(getRandomAddress());

        // Add a random car to the customer
        Car* newCar = new Car(getRandomCarNumber(), getRandomCarModel(), getRandomCarModel(), rand() % 10000 + 2010);
        newCustomer->addCar(*newCar);
        delete newCar;

        try {
            this->addCustomer(*newCustomer);
        }
        catch (CustomerException& e) {
            delete newCustomer;
            cout << "Failed to add customer: " << e.what() << endl;
        }
    }
}

void Garage::generateService(int count) {
    for (int i = 0; i < count; ++i) {
        const char* firstName = getRandomName();
        int price = (rand() % 10) + 1;  // 0: Mechanic, 1: Secretary, 2: ShiftManager
        Service* newService = new Service(firstName, price);

        try {
            this->addService(*newService);
        }
        catch (CustomerException& e) {
            delete newService;
            cout << "Failed to add customer: " << e.what() << endl;
        }
    }
}

void Garage::generateAppointments(int count) {
    for (int i = 0; i < count; ++i) {
        Customer* customer = getRandomCustomer();
        if (!customer) continue;  // Skip if no customers available

        const Car* car = customer->getCar(0);  // Assume customer has at least one car
        if (!car) continue;  // Skip if customer has no cars

        const Service* service = getRandomService();
        if (!service) continue;  // Skip if no services available


        Appointment* newAppointment = new Appointment(Date(1 + (rand() % 28), 1 + (rand() % 12),2023 + (rand() % 2)), car, service);
        newAppointment->createMaintenanceSummary();
        customer->bookAppointment(*newAppointment);
        delete newAppointment;
    }
}

Customer* Garage::getRandomCustomer() const {
    if (numOfCustomers == 0) return nullptr;
    return allCustomers[rand() % numOfCustomers];
}

const Service* Garage::getRandomService() const {
    if (numOfServiecs == 0) return nullptr;
    return allServices[rand() % numOfServiecs];
}