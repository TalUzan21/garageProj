#define _CRT_SECURE_NO_WARNINGS
#ifndef __CAR_H
#define __CAR_H

#include <iostream>

class Car
{
private:
    char carNumber[9];
    char* manufacturer;
    char* model;
    int year;

public:
    Car(const char* carNumber, const char* manufacturer, const char* model, int year);
    Car(const Car& other);
    Car(Car&& other) noexcept;
    ~Car();

    Car& operator=(const Car& other);
    Car& operator=(Car&& other) noexcept;
    bool operator==(const Car& other) const;

    bool isEqual(const Car* other) const;


    friend std::ostream& operator<<(std::ostream& os, const Car& car);

    const char* getCarNumber() const;
    const char* getManufacturer() const;
    const char* getModel() const;
    int getYear() const;
    void print() const;
};

#endif // __CAR_H