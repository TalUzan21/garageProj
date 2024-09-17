#include "shift_manager.h"
#include "spare_part.h"
#include "garage_exception.h"
#include <iostream>
#include <cstring>

using namespace std;

ShiftManager::ShiftManager(const char* firstName, const char* lastName)
    : Employee(firstName, lastName), Secretary(firstName, lastName), Mechanic(firstName, lastName) {}

void ShiftManager::doInventoryCount() const {
    cout << "Performing inventory count..." << endl;
    // Implementation of inventory count
}

void ShiftManager::orderSparePart(const SparePart& sparePart, int amount) {
    cout << "Ordering " << amount << " of " << sparePart.getName() << endl;
    // Update the quantity
    const_cast<SparePart&>(sparePart).setUnitsInStock(sparePart.getUnitsInStock() + amount);
}

void ShiftManager::addNewSparePart(const SparePart& sparePart, Garage& garage) {
    int numSpareParts = garage.getNumOfSpareParts();
    int maxSpareParts = garage.getMaxSpareParts();  // Assume this method exists

    // Check if the spare part already exists
    for (int i = 0; i < numSpareParts; i++) {
        if (strcmp(garage.getSparePartByIndex(i)->getName(), sparePart.getName()) == 0) {
            throw SparePartException("Spare part already exists");
        }
    }

    // Check if there's room for a new spare part
    if (numSpareParts >= maxSpareParts) {
        throw SparePartException("Maximum number of spare parts reached");
    }

    // Add the new spare part using a method in the Garage class
    garage.addSparePart(new SparePart(sparePart));

    cout << "New spare part added: " << sparePart.getName() << endl;
}

//void ShiftManager::addNewSparePart(const SparePart& sparePart, SparePart** listOfSpareParts, int& numSpareParts, int maxSpareParts) {
//    // Check if the spare part already exists
//    for (int i = 0; i < numSpareParts; i++) {
//        if (strcmp(listOfSpareParts[i]->getName(), sparePart.getName()) == 0) {
//            throw SparePartException("Spare part already exists");
//        }
//    }
//
//    // Check if there's room for a new spare part
//    if (numSpareParts >= maxSpareParts) {
//        throw SparePartException("Maximum number of spare parts reached");
//    }
//
//    // Add the new spare part
//    listOfSpareParts[numSpareParts] = new SparePart(sparePart);
//    numSpareParts++;  // Update the count
//    cout << "New spare part added: " << sparePart.getName() << endl;
//}

const char* ShiftManager::getEmployeeType() const {
    return "Shift Manager";
}

void ShiftManager::print() const {
    cout << "Shift Manager: ";
    Employee::print();
}