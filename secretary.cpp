#include "secretary.h"
#include "invoice.h"
#include "customer.h"
#include "appointment.h"
#include "garage_exception.h"
#include "maintenance_summary.h"

Secretary::Secretary(const char* firstName, const char* lastName) : Employee(firstName, lastName) {}

const char* Secretary::getEmployeeType() const {
    return "Secretary";
}

//Invoice* Secretary::generateInvoice(Customer* customer, Appointment* appointment, const Date& date) {
//    if (!customer || !appointment) {
//        throw InvoiceException("Invalid customer or appointment");
//    }
//    // Implementation of invoice generation
//    MaintenanceSummary* summery = appointment->getMaintenanceSummary();
//    Invoice* invoice = summery->getInvoice();
//    return invoice;
//}

Invoice* Secretary::generateInvoice(Appointment* appointment) {
    /*if (!customer || !appointment) {
        throw InvoiceException("Invalid customer or appointment");
    }*/
    // Implementation of invoice generation
    MaintenanceSummary* summery = appointment->getMaintenanceSummary();
    Invoice* invoice = summery->getInvoice();
    return invoice;
}

void Secretary::print() const {
    cout << "Secretary: ";
    Employee::print();
}