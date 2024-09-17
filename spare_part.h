#ifndef __SPARE_PART_H
#define __SPARE_PART_H

#include <iostream>
using namespace std;

class SparePart
{
private:
	char* name;
	int unitsInStock;
	double price;

public:
	SparePart(const char* name, int unitsInStock = 0, double price = 0.0);
	SparePart(const SparePart& other);
	SparePart(SparePart&& other) noexcept;
	~SparePart();

	const SparePart& operator=(const SparePart& other);
	const SparePart& operator=(SparePart&& other) noexcept;
	const SparePart& operator+=(int units);
	const SparePart& operator-=(int units);

	friend std::ostream& operator<<(std::ostream& os, const SparePart& obj);

	const char* getName() const;
	double getPrice() const;
	int getUnitsInStock() const;
	void setUnitsInStock(int unitsInStock);
	void setPrice(double price);
	void print() const;
};

#endif // __SPARE_PART_H