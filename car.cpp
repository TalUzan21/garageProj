#include "car.h"
#include <cstring>

Car::Car(const char* carNumber, const char* manufacturer, const char* model, int year)
    : year(year)
{
    strncpy(this->carNumber, carNumber, 8);
    this->carNumber[8] = '\0';

    this->manufacturer = new char[strlen(manufacturer) + 1];
    strcpy(this->manufacturer, manufacturer);

    this->model = new char[strlen(model) + 1];
    strcpy(this->model, model);
}

Car::Car(const Car& other)
    : year(other.year)
{
    strncpy(this->carNumber, other.carNumber, 9);

    this->manufacturer = new char[strlen(other.manufacturer) + 1];
    strcpy(this->manufacturer, other.manufacturer);

    this->model = new char[strlen(other.model) + 1];
    strcpy(this->model, other.model);
}

Car::Car(Car&& other) noexcept
    : year(other.year)
{
    strncpy(this->carNumber, other.carNumber, 9);
    manufacturer = other.manufacturer;
    model = other.model;

    other.manufacturer = nullptr;
    other.model = nullptr;
}

Car::~Car()
{
    delete[] manufacturer;
    delete[] model;
}

Car& Car::operator=(const Car& other)
{
    if (this != &other)
    {
        strncpy(this->carNumber, other.carNumber, 9);

        delete[] manufacturer;
        this->manufacturer = new char[strlen(other.manufacturer) + 1];
        strcpy(this->manufacturer, other.manufacturer);

        delete[] model;
        this->model = new char[strlen(other.model) + 1];
        strcpy(this->model, other.model);

        year = other.year;
    }
    return *this;
}

Car& Car::operator=(Car&& other) noexcept
{
    if (this != &other)
    {
        strncpy(this->carNumber, other.carNumber, 9);
        delete[] manufacturer;
        manufacturer = other.manufacturer;
        delete[] model;
        model = other.model;
        year = other.year;

        other.manufacturer = nullptr;
        other.model = nullptr;
    }
    return *this;
}

bool Car::isEqual(const Car* other) const {
    if (other == nullptr) return false;
    return strcmp(this->carNumber, other->carNumber) == 0 &&
        strcmp(this->manufacturer, other->manufacturer) == 0 &&
        strcmp(this->model, other->model) == 0 &&
        this->year == other->year;
}

bool Car::operator==(const Car& other) const 
{
    return strcmp(this->carNumber, other.carNumber) == 0 &&
        strcmp(this->manufacturer, other.manufacturer) == 0 &&
        strcmp(this->model, other.model) == 0 &&
        this->year == other.year;
}

std::ostream& operator<<(std::ostream& os, const Car& car)
{
    os << "Car Number: " << car.carNumber << ", Manufacturer: " << car.manufacturer
        << ", Model: " << car.model << ", Year: " << car.year;
    return os;
}

const char* Car::getCarNumber() const
{
    return carNumber;
}

const char* Car::getManufacturer() const
{
    return manufacturer;
}

const char* Car::getModel() const
{
    return model;
}

int Car::getYear() const
{
    return year;
}

void Car::print() const
{
    std::cout << *this;
}