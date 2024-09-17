#define _CRT_SECURE_NO_WARNINGS
#include "date.h"
#include <iomanip>
#include <ctime>


Date::Date() {
    time_t now = time(0);
    tm* ltm = localtime(&now);

    year = 1900 + ltm->tm_year;
    month = 1 + ltm->tm_mon;
    day = ltm->tm_mday;
}

Date::Date(int day, int month, int year)
    : day(day), month(month), year(year) {}

bool Date::operator==(const Date& other) const
{
    return (day == other.day && month == other.month && year == other.year);
}

bool Date::operator<(const Date& other) const
{
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    return day < other.day;
}

bool Date::operator>(const Date& other) const
{
    return other < *this;
}

bool Date::operator<=(const Date& other) const
{
    return !(other < *this);
}

bool Date::operator>=(const Date& other) const
{
    return !(*this < other);
}

ostream& operator<<(ostream& os, const Date& date)
{
    os << std::setfill('0')
        << std::setw(2) << date.day << '/'
        << std::setw(2) << date.month << '/'
        << std::setw(4) << date.year;
    return os;
}

void Date::print() const
{
    std::cout << *this;
}