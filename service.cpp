#define _CRT_SECURE_NO_WARNINGS
#include "service.h"
#include <cstring>

Service::Service(const char* serviceType, int price) : price(price) {
    this->serviceType = new char[strlen(serviceType) + 1];
    strcpy(this->serviceType, serviceType);
}

Service::Service(const Service& other) : price(other.price) {
    serviceType = new char[strlen(other.serviceType) + 1];
    strcpy(serviceType, other.serviceType);
}

Service::Service(Service&& other) noexcept : serviceType(other.serviceType), price(other.price) {
    const_cast<Service&>(other).serviceType = nullptr;
}

Service::~Service() {
    delete[] serviceType;
}

const Service& Service::operator=(const Service& other) {
    if (this != &other) {
        delete[] serviceType;
        serviceType = new char[strlen(other.serviceType) + 1];
        strcpy(serviceType, other.serviceType);
        price = other.price;
    }
    return *this;
}

const Service& Service::operator=(Service&& other) {
    if (this != &other) {
        delete[] serviceType;
        serviceType = other.serviceType;
        price = other.price;
        other.serviceType = nullptr;
    }
    return *this;
}

ostream& operator<<(ostream& os, const Service& service) {
    os << "Service Type: " << service.serviceType << ", Price: " << service.price;
    return os;
}

void Service::print() const {
    cout << *this;
}