#ifndef __DATE_H
#define __DATE_H

#include <iostream>

using namespace std;

class Date
{
private:
	int day;
	int month;
	int year;

public:
	Date();
	Date(int day, int month, int year);

	bool operator==(const Date& other) const;
	bool operator<(const Date& other) const;
	bool operator>(const Date& other) const;
	bool operator<=(const Date& other) const;
	bool operator>=(const Date& other) const;
	friend std::ostream& operator<<(std::ostream& os, const Date& obj);

	void print() const;
};

#endif // __DATE_H