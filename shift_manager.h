#ifndef __SHIFT_MANAGER_H
#define __SHIFT_MANAGER_H

#include "secretary.h"
#include "mechanic.h"
#include "garage.h"

class SparePart;

class ShiftManager : public Secretary, public Mechanic
{
public:
    ShiftManager(const char* firstName, const char* lastName);

    const char* getEmployeeType() const override;
    void doInventoryCount() const;
    void orderSparePart(const SparePart& sparePart, int amount);
    //void addNewSparePart(const SparePart& sparePart, SparePart** listOfSpareParts);
    void addNewSparePart(const SparePart& sparePart, Garage& garage);
    //void addNewSparePart(const SparePart& sparePart, SparePart** listOfSpareParts, int& numSpareParts, int maxSpareParts);
    void print() const override;
};

#endif // __SHIFT_MANAGER_H