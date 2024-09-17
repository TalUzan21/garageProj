#ifndef __SERVICE_H
#define __SERVICE_H

#include <iostream>
using namespace std;

class Service
{
private:
	char* serviceType;
	int price;

public:
	Service(const char* serviceType, int price);
	Service(const Service& other);
	Service(Service&& other) noexcept;
	~Service();

	const Service& operator=(const Service& other);
	const Service& operator=(Service&& other);
	friend ostream& operator<<(ostream& os, const Service& service);

	int getPrice() const { return price; }

	void print() const;
};

#endif // __SERVICE_