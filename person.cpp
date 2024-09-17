#define _CRT_SECURE_NO_WARNINGS
#include "person.h"
#include <cstring>
#include <iostream>

Person::Person(const char* firstName, const char* lastName)
{
    this->firstName = new char[strlen(firstName) + 1];
    strcpy(this->firstName, firstName);
    this->lastName = new char[strlen(lastName) + 1];
    strcpy(this->lastName, lastName);
}

Person::Person(const Person& other)
{
    this->firstName = new char[strlen(other.firstName) + 1];
    strcpy(this->firstName, other.firstName);
    this->lastName = new char[strlen(other.lastName) + 1];
    strcpy(this->lastName, other.lastName);
}

Person::Person(const Person&& other)
{
    this->firstName = other.firstName;
    this->lastName = other.lastName;
    const_cast<Person&>(other).firstName = nullptr;
    const_cast<Person&>(other).lastName = nullptr;
}

Person::~Person()
{
    delete[] firstName;
    delete[] lastName;
}

const Person& Person::operator=(const Person& other)
{
    if (this != &other)
    {
        delete[] firstName;
        delete[] lastName;
        this->firstName = new char[strlen(other.firstName) + 1];
        strcpy(this->firstName, other.firstName);
        this->lastName = new char[strlen(other.lastName) + 1];
        strcpy(this->lastName, other.lastName);
    }
    return *this;
}

const Person& Person::operator=(Person&& other) noexcept
{
    if (this != &other)
    {
        delete[] firstName;
        delete[] lastName;
        this->firstName = other.firstName;
        this->lastName = other.lastName;
        other.firstName = nullptr;
        other.lastName = nullptr;
    }
    return *this;
}

const char* Person::getFirstName() const
{
    return firstName;
}

void Person::setFirstName(const char* firstName)
{
    delete[] this->firstName;
    this->firstName = new char[strlen(firstName) + 1];
    strcpy(this->firstName, firstName);
}

const char* Person::getLastName() const
{
    return lastName;
}

void Person::setLastName(const char* lastName)
{
    delete[] this->lastName;
    this->lastName = new char[strlen(lastName) + 1];
    strcpy(this->lastName, lastName);
}