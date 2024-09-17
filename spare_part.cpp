#define _CRT_SECURE_NO_WARNINGS
#include "spare_part.h"
#include <cstring>

SparePart::SparePart(const char* name, int unitsInStock, double price)
    : unitsInStock(unitsInStock), price(price) {
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

SparePart::SparePart(const SparePart& other)
    : unitsInStock(other.unitsInStock), price(other.price) {
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
}

SparePart::SparePart(SparePart&& other) noexcept
    : name(other.name), unitsInStock(other.unitsInStock), price(other.price) {
    const_cast<SparePart&>(other).name = nullptr;
}

SparePart::~SparePart() {
    delete[] name;
}

const SparePart& SparePart::operator=(const SparePart& other) {
    if (this != &other) {
        delete[] name;
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        unitsInStock = other.unitsInStock;
        price = other.price;
    }
    return *this;
}

const SparePart& SparePart::operator=(SparePart&& other) noexcept {
    if (this != &other) {
        delete[] name;
        name = other.name;
        unitsInStock = other.unitsInStock;
        price = other.price;
        other.name = nullptr;
    }
    return *this;
}

const SparePart& SparePart::operator+=(int units) {
    unitsInStock += units;
    return *this;
}

const SparePart& SparePart::operator-=(int units) {
    unitsInStock = max(0, unitsInStock - units);
    return *this;
}

ostream& operator<<(ostream& os, const SparePart& sparePart) {
    os << "Spare Part: " << sparePart.name << ", Units in Stock: " << sparePart.unitsInStock
        << ", Price: " << sparePart.price;
    return os;
}

const char* SparePart::getName() const {
    return name;
}

double SparePart::getPrice() const {
    return price;
}

int SparePart::getUnitsInStock() const {
    return unitsInStock;
}

void SparePart::setUnitsInStock(int unitsInStock) {
    this->unitsInStock = max(0, unitsInStock);
}

void SparePart::setPrice(double price) {
    this->price = max(0.0, price);
}

void SparePart::print() const {
    cout << *this;
}