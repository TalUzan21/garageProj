#include "garage_exception.h"

void EmployeeException::show() const {
    std::cout << "Employee Exception: " << what() << std::endl;
}

void CustomerException::show() const {
    std::cout << "Customer Exception: " << what() << std::endl;
}

void CarException::show() const {
    std::cout << "Car Exception: " << what() << std::endl;
}

void CarNullException::show() const {
    std::cout << "Car Null Exception: " << message << std::endl;
}

void CustomerNullException::show() const {
    std::cout << "Customer Null Exception" << std::endl;
}

void AppointmentNullException::show() const {
    std::cout << "Appointment Null Exception" << std::endl;
}

void AppointmentException::show() const {
    std::cout << "Appointment Exception" << std::endl;
}

void SummaryNullException::show() const {
    std::cout << "Summary Null Exception: " << what() << std::endl;
}

void InvoiceException::show() const {
    std::cout << "Invoice Exception: " << message << std::endl;
}

void RepairCarException::show() const {
    std::cout << "Repair Car Exception: " << message << std::endl;
}

void SparePartNullException::show() const {
    std::cout << "Spare Part Null Exception" << std::endl;
}

void SparePartException::show() const {
    std::cout << "Spare Part Exception" << std::endl;
}

void ServiceNullException::show() const {
    std::cout << "Service Null Exception" << std::endl;
}

void InvalidDateException::show() const {
    std::cout << "Invalid Date Exception: " << what() << std::endl;
}