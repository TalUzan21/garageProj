#ifndef __APPOINTMENT_H
#define __APPOINTMENT_H

#include "date.h"
#include "garage_exception.h"

class Car;
class Service;
class MaintenanceSummary;
class Invoice;

class Appointment
{
private:
    Date date;
    const Car* car;
    const Service* service;
    MaintenanceSummary* summary;
    Invoice* invoice;

public:
    Appointment(const Date& date, const Car* car, const Service* service);
    Appointment(const Appointment& other);
    Appointment(Appointment&& other);
    ~Appointment();

    const Appointment& operator=(const Appointment& other);
    const Appointment& operator=(Appointment&& other);

    void createMaintenanceSummary();
    void setInvoice(Invoice* invoice);

    MaintenanceSummary* getMaintenanceSummary() const;
    Invoice* getInvoice() const;
    const Date& getDate() const;
    const Car* getCar() const;
    const Service* getService() const;

    friend ostream& operator<<(ostream& os, const Appointment& appointment);
    void print() const;
};

#endif // __APPOINTMENT_H