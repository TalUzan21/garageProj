#define _CRT_SECURE_NO_WARNINGS
#include "mechanic.h"
#include "maintenance_summary.h"
#include "garage_exception.h"

#include "spare_part.h"
#include "garage.h"
#include "InputValidator.h"
#include <iostream>

using namespace std;

Mechanic::Mechanic(const char* firstName, const char* lastName) : Employee(firstName, lastName) {}

void Mechanic::repairCar(MaintenanceSummary& summary, Garage& garage) {
    if (summary.isCompleted()) {
        throw RepairCarException("Car has already been repaired");
    }

    cout << "Starting repair process..." << endl;

     // Ask if the repair requires spare parts
    SparePart** availableParts = garage.getListOfSpareParts();
    int numOfParts = garage.getNumOfSpareParts();

    if (numOfParts == 0) {
        cout << "There are no spare parts available in the garage." << endl;
        cout << "Proceeding with repair without spare parts." << endl;
    }
    else {
        // Ask if the repair requires spare parts
        bool requiresParts = InputValidator::getYesNoInput("Does this repair require spare parts? (y/n): ");

        if (requiresParts) {
            cout << "Available spare parts:" << endl;
            for (int i = 0; i < numOfParts; ++i) {
                cout << i + 1 << ". " << availableParts[i]->getName()
                    << " (Price: $" << availableParts[i]->getPrice()
                    << ", Quantity: " << availableParts[i]->getUnitsInStock() << ")" << endl;
            }

            // Allow mechanic to choose parts
            while (true) {
                int choice = InputValidator::getValidIntInput("Enter the number of the part to use (0 to finish): ", 0, numOfParts);
                if (choice == 0) break;

                SparePart* chosenPart = garage.getSparePartByIndex(choice - 1);
                if (chosenPart->getUnitsInStock() > 0) {
                    summary.addSparePart(*chosenPart);
                    *chosenPart -= 1; // Decrease the quantity by 1
                    cout << "Added " << chosenPart->getName() << " to the repair." << endl;
                }
                else {
                    cout << "This part is out of stock. Please choose another." << endl;
                }
            }
        }
        else {
            cout << "No spare parts will be used for this repair." << endl;
        }
    }

    // Update maintenance summary
    this->updateMaintenanceSummary(summary);

    // Set repair as completed
    summary.setCompleted(true);

    cout << "Repair completed successfully." << endl;
}

void Mechanic::updateMaintenanceSummary(MaintenanceSummary& summary) {
    char description[256];
    sprintf(description, "Maintenance performed by mechanic %s %s", this->getFirstName(), this->getLastName());
    summary.addDescription(description);
    summary.setEmployee(this);
}

const char* Mechanic::getEmployeeType() const {
    return "Mechanic";
}

void Mechanic::print() const {
    cout << "Mechanic: ";
    Employee::print();
}
