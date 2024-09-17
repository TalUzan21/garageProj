#include "appointment.h"
#include "car.h"
#include "service.h"
#include "maintenance_summary.h"
#include "invoice.h"
#include "garage_exception.h"
#include <iostream>

Appointment::Appointment(const Date& date, const Car* car, const Service* service)
    : date(date), car(new Car(*car)), service(new Service(*service)), summary(nullptr), invoice(nullptr) 
{
    //createMaintenanceSummary();
}

Appointment::Appointment(const Appointment& other)
    : date(other.date), car(new Car(*other.car)), service(new Service(*other.service)),
    summary(other.summary ? new MaintenanceSummary(*other.summary) : nullptr),
    invoice(other.invoice ? new Invoice(*other.invoice) : nullptr) {}

Appointment::Appointment(Appointment&& other) 
    : date(std::move(other.date)), car(other.car), service(other.service),
    summary(other.summary), invoice(other.invoice)
{
    other.car = nullptr;
    other.service = nullptr;
    other.summary = nullptr;
    other.invoice = nullptr;
}

Appointment::~Appointment() {
    delete summary;
    delete invoice;
}

const Appointment& Appointment::operator=(const Appointment& other) {
    if (this != &other) {
        date = other.date;
        delete car;
        delete service;
        delete summary;
        delete invoice;
        car = new Car(*other.car);
        service = new Service(*other.service);
        summary = other.summary ? new MaintenanceSummary(*other.summary) : nullptr;
        invoice = other.invoice ? new Invoice(*other.invoice) : nullptr;
    }
    return *this;
}

const Appointment& Appointment::operator=(Appointment&& other) {
    if (this != &other) {
        date = std::move(other.date);
        delete car;
        delete service;
        delete summary;
        delete invoice;
        car = other.car;
        service = other.service;
        summary = other.summary;
        invoice = other.invoice;
        other.car = nullptr;
        other.service = nullptr;
        other.summary = nullptr;
        other.invoice = nullptr;
    }
    return *this;
}


void Appointment::createMaintenanceSummary()
{
    if (summary == nullptr) {
        summary = new MaintenanceSummary(date, car, service);
    }
}

void Appointment::setInvoice(Invoice* invoice) {
    this->invoice = invoice;
}

MaintenanceSummary* Appointment::getMaintenanceSummary() const {
    if (!summary) {
        throw SummaryNullException(); //
    }
    return summary;
}

Invoice* Appointment::getInvoice() const {
    return invoice;
}

const Date& Appointment::getDate() const {
    return date;
}

const Car* Appointment::getCar() const {
    return car;
}

const Service* Appointment::getService() const {
    return service;
}

ostream& operator<<(ostream& os, const Appointment& appointment) {
    os << "Date: " << appointment.date 
        << ", Car: " << *appointment.car
        << ", Service: " << *appointment.service;
    return os;
}


void Appointment::print() const {
    std::cout << *this;
    if (summary) {
        std::cout << "\nMaintenance Summary: ";
        summary->print();
    }
}