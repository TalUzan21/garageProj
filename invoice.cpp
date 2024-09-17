#include "invoice.h"
#include "spare_part.h"
#include "service.h"
#include "maintenance_summary.h"


Invoice::Invoice(Customer* customer, Appointment* appointment, const Date& date)
    : customer(customer),mechanic(nullptr) ,appointment(appointment) , totalPrice(0), invoiceDate(date), maintenanceSummary(nullptr) {
    // Calculate total price based on the appointment and customer details
    // This is a placeholder, implement the actual logic
    //totalPrice = appointment->getService()->getPrice();
}

ostream& operator<<(ostream& os, const Invoice& invoice) {
    os << "Invoice Date: " << invoice.invoiceDate << endl;
    os << "Customer: " << invoice.customer->getFirstName() << " " << invoice.customer->getLastName() << endl;
    if (invoice.mechanic) {
        os << "Mechanic: " << invoice.mechanic->getFirstName() << " " << invoice.mechanic->getLastName() << endl;
    }
    os << "Total Price: $" << invoice.totalPrice;
    return os;
}

void Invoice::calculateTotalPrice() {
    totalPrice = 0;
    if (appointment) {
        totalPrice += appointment->getService()->getPrice();
    }
    if (maintenanceSummary) {
        const SparePart** parts = maintenanceSummary->getListOfSpareParts();
        int numParts = maintenanceSummary->getNumOfSpareParts();
        for (int i = 0; i < numParts; ++i) {
            totalPrice += parts[i]->getPrice();
        }
    }
}



double Invoice::getTotalPrice() const {
    return totalPrice;
}

void Invoice::print() const {
    cout << *this;
}

//void Invoice::addCharge(const char* itemName, double price) {
//    // Implement the logic to add a charge to the invoice
//    totalPrice += price;
//    // You might want to store the item name and price for later use
//}

void Invoice::setMaintenanceSummary(MaintenanceSummary* summary) {
    maintenanceSummary = summary;
    calculateTotalPrice();
}