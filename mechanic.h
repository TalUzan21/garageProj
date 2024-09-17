#ifndef __MECHANIC_H
#define __MECHANIC_H

#include "employee.h"
#include "maintenance_summary.h"

class Garage;

class Mechanic : virtual public Employee
{
public:
    Mechanic(const char* firstName, const char* lastName);

    void repairCar(MaintenanceSummary& summary, Garage& garage);
    void updateMaintenanceSummary(MaintenanceSummary& summary);
    const char* getEmployeeType() const override;
    void print() const override;

  //  int getId() const { return Employee::getEmployeeId(); } // Assuming Employee has getEmployeeId()

};

#endif // __MECHANIC_H