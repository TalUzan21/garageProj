#ifndef __GARAGE_EXCEPTIONS_H_
#define __GARAGE_EXCEPTIONS_H_

#include <iostream>
#include <string>
#include <stdexcept>

class GarageExceptions : public std::exception {
public:
    virtual void show() const = 0;
};

class ConcreteGarageException : public GarageExceptions {
private:
    std::string message;

public:
    ConcreteGarageException(const char* msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }

    void show() const override {
        std::cout << "Garage Exception: " << message << std::endl;
    }
};

class EmployeeException : public GarageExceptions {
private:
    std::string msg;
public:
    EmployeeException(const char* msg) : msg(msg) {}
    const char* what() const noexcept override { return msg.c_str(); }
    void show() const override;
};

class CustomerException : public GarageExceptions {
private:
    std::string msg;
public:
    CustomerException(const char* msg) : msg(msg) {}
    const char* what() const noexcept override { return msg.c_str(); }
    void show() const override;
};

class CarException : public GarageExceptions {
private:
    std::string msg;
public:
    CarException(const char* msg) : msg(msg) {}
    const char* what() const noexcept override { return msg.c_str(); }
    void show() const override;
};

class CarNullException : public GarageExceptions {
public:
    CarNullException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
    void show() const override; // Remove the implementation here
private:
    std::string message;
};

class CustomerNullException : public GarageExceptions {
public:
    const char* what() const noexcept override { return "Customer Null Exception"; }
    void show() const override;
};

class AppointmentNullException : public GarageExceptions {
public:
    const char* what() const noexcept override { return "Appointment Null Exception"; }
    void show() const override;
};

class AppointmentException : public GarageExceptions {
public:
    const char* what() const noexcept override { return "Appointment Exception"; }
    void show() const override;
};

class SummaryNullException : public GarageExceptions {
public:
    const char* what() const noexcept override { return "Summary is null"; }
    void show() const override;  // Just declare it here, don't define
};

class InvoiceException : public GarageExceptions {
public:
    InvoiceException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
    void show() const override; // Remove the implementation here
private:
    std::string message;
};

class RepairCarException : public GarageExceptions {
public:
    RepairCarException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
    void show() const override; // Remove the implementation here
private:
    std::string message;
};

class SparePartNullException : public GarageExceptions {
public:
    const char* what() const noexcept override { return "Spare Part Null Exception"; }
    void show() const override;
};

class SparePartException : public GarageExceptions {
private:
    std::string message;
public:
    SparePartException(const char* msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
    void show() const override;
};

class ServiceNullException : public GarageExceptions {
private:
    std::string message;
public:
    ServiceNullException(const char* msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
    void show() const override;
};
class InvalidDateException : public GarageExceptions {
private:
    std::string msg;
public:
    InvalidDateException(const char* msg) : msg(msg) {}
    const char* what() const noexcept override { return msg.c_str(); }
    void show() const override;
};

#endif // __GARAGE_EXCEPTIONS_H_