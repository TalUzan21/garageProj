#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>

using namespace std;

#include "garage.h"
#include "garage_exception.h"
#include "customer.h"
#include "person.h"
#include "car.h"
#include "shift_manager.h"
#include "service.h"
#include "appointment.h"
#include "date.h"
#include "maintenance_summary.h"
#include "spare_part.h"
#include "InputValidator.h"
#include "invoice.h"
#include "mechanic.h"

const int MAX_INPUT_SIZE = 255;
const int CUSTOMER_NUM_OF_OPTIONS = 6;
const int SHIFT_MANAGER_OPTIONS = 5;
const int MECHANIC_OPTIONS = 2;

enum eMenuOptions
{
	PRINT_GARAGE, PRINT_ALL_EMPLOYEES, PRINT_ALL_CUSTOMERS, PRINT_INVENTORY, ADD_EMPLOYEE,
	ADD_CUSTOMER, ADD_SERVICE, EMPLOYEE_OPTIONS, CUSTOMER_OPTIONS, QUIT, NUM_OF_OPTIONS
};
const char* menuOptions[] = { "Print garage", "Print All Employees", "Print All Customers", "Print Inventory", "Add employee",
								"Add customer", "Add service", "Employee Options", "Customer Options", "Quit" };

int menu();
void cleanBuffer();
void addCarToCustomer(Customer& customer) throw (CarException);
void bookNewAppointment(Customer* customer, Garage& garage) throw(GarageExceptions);
void generateNewInvoice(Secretary& secretary, Garage& garage) throw(GarageExceptions);
void repairCustomerCar(Mechanic& mechanic, Garage& garage) throw(GarageExceptions);
void updateExistingMaintenanceSummary(Mechanic& mechanic, Garage& garage) throw(GarageExceptions);
void orderSingleSparePart(ShiftManager& shiftManager, Garage& garage) throw(GarageExceptions);
Customer* getCustomer(Garage& garage) throw(CustomerNullException);
Appointment* getAppointment(Garage& garage, Customer* customer) throw(AppointmentNullException);

int main()
{
	cout << "Please enter the garage name: " << endl;
	char garageName[MAX_INPUT_SIZE];
	cin.getline(garageName, MAX_INPUT_SIZE);
	Garage garage(garageName, 100);

	garage.generateEmployees(10);
	garage.generateCustomers(10);
	garage.generateService(5);
	garage.generateAppointments(2);

	int option;
	bool stop = false;

	do
	{
		option = menu();
		cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;
		switch (option)
		{
		case eMenuOptions::PRINT_GARAGE:
			cout << "Name: " << garage.getName() << endl;
			cout << "\nProvided Services:" << endl;
			garage.printAllServices();
			cout << "\nThe Garage's Employees:" << endl;
			garage.printAllEmployees();
			cout << "\nThe Garage's Customers:" << endl;
			garage.printAllCustomers();
			cout << "\nInventory:" << endl;
			garage.printInventory();
			break;

		case eMenuOptions::PRINT_ALL_EMPLOYEES:
			cout << "The Garage's Employees:" << endl;
			garage.printAllEmployees();
			break;

		case eMenuOptions::PRINT_ALL_CUSTOMERS:
			cout << "The Garage's Customers:" << endl;
			garage.printAllCustomers();
			break;

		case eMenuOptions::PRINT_INVENTORY:
		{
			cout << "Inventory:" << endl;
			garage.printInventory();
			break;
		}

		case eMenuOptions::ADD_EMPLOYEE:
		{
			char firstName[MAX_INPUT_SIZE];
			char lastName[MAX_INPUT_SIZE];

			InputValidator::getValidStringInput("Please enter first name: ", firstName, MAX_INPUT_SIZE, InputValidator::isValidName);
			InputValidator::getValidStringInput("Please enter last name: ", lastName, MAX_INPUT_SIZE, InputValidator::isValidName);

			int answer;
			do
			{
				answer = InputValidator::getValidIntInput("Which type of employee?\n1 - secretary, 2 - mechanic, 3 - shift manager\n", 1, 3);
				try
				{
					if (answer == 1)
						garage.addEmployee(new Secretary(firstName, lastName));
					else if (answer == 2)
						garage.addEmployee(new Mechanic(firstName, lastName));
					else if (answer == 3)
						garage.addEmployee(new ShiftManager(firstName, lastName));
				}
				catch (EmployeeException& e)
				{
					e.show();
				}
				catch (...)
				{
					cout << "unknown error!" << endl;
				}
			} while (answer < 1 || answer > 3);
			break;
		}

		case eMenuOptions::ADD_CUSTOMER:
		{
			char firstName[MAX_INPUT_SIZE];
			char lastName[MAX_INPUT_SIZE];
			char phoneNumber[MAX_INPUT_SIZE];
			char address[MAX_INPUT_SIZE];

			InputValidator::getValidStringInput("Please enter first name: ", firstName, MAX_INPUT_SIZE, InputValidator::isValidName);
			InputValidator::getValidStringInput("Please enter last name: ", lastName, MAX_INPUT_SIZE, InputValidator::isValidName);
			InputValidator::getValidStringInput("Please enter phone number (10 digits): ", phoneNumber, MAX_INPUT_SIZE,
				[](const char* s) { return strlen(s) == 10 && InputValidator::isValidNumber(s); });
			InputValidator::getValidStringInput("Please enter address: ", address, MAX_INPUT_SIZE, [](const char* s) { return strlen(s) > 0; });

			Customer customer(firstName, lastName);
			customer.setAddress(address);
			try
			{
				customer.setPhoneNumber(phoneNumber);
			}
			catch (CustomerException& e)
			{
				e.show();
			}
			catch (...)
			{
				cout << "unknown error!" << endl;
			}

			try
			{
				addCarToCustomer(customer);
				garage.addCustomer(customer);
			}
			catch (CarException& e)
			{
				e.show();
			}
			catch (CustomerException& e)
			{
				e.show();
			}
			catch (...)
			{
				cout << "unknown error!" << endl;
			}
			break;
		}

		case eMenuOptions::ADD_SERVICE:
		{
			char serviceType[MAX_INPUT_SIZE];
			int price;

			InputValidator::getValidStringInput("Please enter a new service type for the garage: ", serviceType, MAX_INPUT_SIZE,
				[](const char* s) { return strlen(s) > 0; });
			price = InputValidator::getValidIntInput("Please enter its price: ", 0, INT_MAX);

			garage.addService(Service(serviceType, price));
			break;
		}

		case eMenuOptions::EMPLOYEE_OPTIONS:
		{
			cout << "\nThe Garage's Employees:" << endl;
			garage.printAllEmployees();
			int id = InputValidator::getValidIntInput("Please enter employee id: ", 1, INT_MAX);
			Employee* employee = garage.getEmployeeById(id);

			if (typeid(*employee) == typeid(Secretary))
			{
				bool answer = InputValidator::getYesNoInput("Do you want to generate a new invoice? (y/n): ");
				if (answer)
				{
					Secretary* secretary = dynamic_cast<Secretary*>(employee);
					try
					{
						generateNewInvoice(*secretary, garage);
					}
					catch (GarageExceptions& e)
					{
						e.show();
					}
					catch (...)
					{
						cout << "unknown error!" << endl;
					}
				}
			}
			else if (typeid(*employee) == typeid(Mechanic))
			{
				Mechanic* mechanic = dynamic_cast<Mechanic*>(employee);
				int choice;
				do
				{
					cout << "Please choose what to do:" << endl;
					cout << "1. Repair a car" << endl;
					cout << "2. Update maintnance summary" << endl;
					choice = InputValidator::getValidIntInput("Enter your choice: ", 1, MECHANIC_OPTIONS);
				} while (choice != 1 && choice != 2);

				try
				{
					if (choice == 1)
						repairCustomerCar(*mechanic, garage);
					else
						updateExistingMaintenanceSummary(*mechanic, garage);
				}
				catch (GarageExceptions& e)
				{
					e.show();
				}
				catch (...)
				{
					cout << "unknown error!" << endl;
				}

			}
			else if (typeid(*employee) == typeid(ShiftManager))
			{
				ShiftManager* shiftManager = dynamic_cast<ShiftManager*>(employee);
				int choice;
				do
				{
					cout << "Please choose what to do:" << endl;
					cout << "1. Generate a new invoice" << endl;
					cout << "2. Repair a car" << endl;
					cout << "3. Update maintnance summary" << endl;
					cout << "4. Do inventory count" << endl;
					cout << "5. Order a spare part" << endl;
					choice = InputValidator::getValidIntInput("Enter your choice: ", 1, SHIFT_MANAGER_OPTIONS);

				} while (choice < 1 || choice > 5);

				try
				{
					switch (choice)
					{
					case 1:
						generateNewInvoice(*shiftManager, garage);
						break;

					case 2:
						repairCustomerCar(*shiftManager, garage);
						break;

					case 3:
						updateExistingMaintenanceSummary(*shiftManager, garage);
						break;

					case 4:
						shiftManager->doInventoryCount();
						break;
					case 5:
						orderSingleSparePart(*shiftManager, garage);
						break;

					default:
						break;
					}
				}
				catch (GarageExceptions& e)
				{
					e.show();
				}
				catch (...)
				{
					cout << "unknown error!" << endl;
				}
			}
			break;
		}

		case eMenuOptions::CUSTOMER_OPTIONS:
		{
			try
			{
				Customer* customer = getCustomer(garage);
				int choice;
				do
				{
					cout << "Hello " << customer->getFirstName() << ", what do you want to do?" << endl;
					cout << "1. Book a new appointment" << endl;
					cout << "2. Add a car to your cars' list" << endl;
					cout << "3. Update your phone number" << endl;
					cout << "4. Get maintenance summeries of a car" << endl;
					cout << "5. Get an appointment by date" << endl;
					cout << "6. Get all your invoices" << endl;
					choice = InputValidator::getValidIntInput("Enter your choice: ", 1, CUSTOMER_NUM_OF_OPTIONS);
				} while (choice < 1 || choice > 7);

				try
				{
					switch (choice)
					{
					case 1:
						bookNewAppointment(customer, garage);
						break;

					case 2:
						addCarToCustomer(*customer);
						break;

					case 3:
						char phoneNumber[MAX_INPUT_SIZE];
						InputValidator::getValidStringInput("Please enter phone number (10 digits): ", phoneNumber, MAX_INPUT_SIZE,
							[](const char* s) { return strlen(s) == 10 && InputValidator::isValidNumber(s); });
						customer->setPhoneNumber(phoneNumber);
						break;

					case 4:
					{
						int carIndex;
						const Car** allCars = customer->getListOfCars();
						cout << "Please choose the index of a car from the list below:" << endl;
						for (int i = 0; i < customer->getNumOfCars(); i++)
							cout << i + 1 << " - " << *allCars[i] << endl;
						carIndex = InputValidator::getValidIntInput("Enter your choice: ", 1, customer->getNumOfCars());

						customer->printMaintenanceSummary(customer->getCar(carIndex - 1));
						break;
					}

					case 5:
					{
						int day = InputValidator::getValidIntInput("Please enter day (1-31): ", 1, 31);
						int month = InputValidator::getValidIntInput("Please enter month (1-12): ", 1, 12);
						int year = InputValidator::getValidIntInput("Please enter year: ", 1000, 2100);

						customer->printAppointment(Date(day, month, year));
						break;
					}
					case 6:
						customer->printAllInvoices();
						break;

					default:
						break;
					}
				}
				catch (GarageExceptions& e)
				{
					e.show();
				}
				catch (...)
				{
					cout << "unknown error!" << endl;
				}
			}
			catch (CustomerNullException& e)
			{
				e.show();
			}
			catch (...)
			{
				cout << "unknown error!" << endl;
			}
			break;
		}

		case eMenuOptions::QUIT:
			cout << "Thank You bye" << endl;
			stop = true;
			break;

		default:
			cout << "Wrong option" << endl;
			break;
		}
		cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;
	} while (!stop);
}

int menu()
{
	cout << "\n\n" << "Please choose one of the following options:" << endl;
	for (int i = 0; i < eMenuOptions::NUM_OF_OPTIONS; i++)
		cout << i + 1 << "\t- " << menuOptions[i] << endl;

	int option = InputValidator::getValidIntInput("Enter your choice: ", 1, eMenuOptions::NUM_OF_OPTIONS);
	return option - 1;
}


void cleanBuffer()
{
	int c;
	do
	{
		c = getchar();
	} while (c != EOF && c != '\n');
}

void addCarToCustomer(Customer& customer) throw (CarException)
{
	char carNumber[MAX_INPUT_SIZE];
	char manufacturer[MAX_INPUT_SIZE];
	char model[MAX_INPUT_SIZE];
	int year;

	InputValidator::getValidStringInput("Please enter car number: ", carNumber, MAX_INPUT_SIZE, InputValidator::isValidCarNumber);
	InputValidator::getValidStringInput("Please enter manufacturer: ", manufacturer, MAX_INPUT_SIZE, InputValidator::isValidName);
	InputValidator::getValidStringInput("Please enter model name: ", model, MAX_INPUT_SIZE, [](const char* s) { return strlen(s) > 0; });
	year = InputValidator::getValidIntInput("Please enter year: ", 1000, 2100);

	try
	{
		Car car(carNumber, manufacturer, model, year);
		customer.addCar(car);
	}
	catch (CarException& e)
	{
		throw e;
	}
	catch (...)
	{
		cout << "unknown error!" << endl;
	}
}

void bookNewAppointment(Customer* customer, Garage& garage) throw(GarageExceptions)
{
	if (customer->getNumOfCars() == 0) {
		cout << "Customer has no cars. Cannot book appointment." << endl;
		return;
	}
	if (garage.getNumOfServices() == 0) {
		cout << "No services available. Cannot book appointment." << endl;
		return;
	}
	
	Date appointmentDate;
	bool isDateValid = false;

	while (!isDateValid) {
		int day = InputValidator::getValidIntInput("Please enter day (1-31): ", 1, 31);
		int month = InputValidator::getValidIntInput("Please enter month (1-12): ", 1, 12);
		int year = InputValidator::getValidIntInput("Please enter year: ", 1000, 2100);

		try {
			appointmentDate = Date(day, month, year);

			if (!InputValidator::isAppointmentAvailable(customer, appointmentDate)) {
				cout << "An appointment already exists on this date. Please choose another date." << endl;
				continue;
			}

			isDateValid = true;
		}
		catch (InvalidDateException& e) {
			cout << "Invalid date: " << e.what() << ". Please try again." << endl;
		}
	}

	const Car** allCars = customer->getListOfCars();
	cout << "Available cars:" << endl;
	for (int i = 0; i < customer->getNumOfCars(); i++) {
		cout << i + 1 << ". ";
		allCars[i]->print();
		cout << endl;
	}
	int carIndex = InputValidator::getValidIntInput("Please choose the index of a car: ", 1, customer->getNumOfCars()) - 1;

	const Service** allServices = garage.getListOfServices();
	cout << "Available services:" << endl;
	for (int i = 0; i < garage.getNumOfServices(); i++) {
		cout << i + 1 << ". ";
		allServices[i]->print();
		cout << endl;
	}
	int serviceIndex = InputValidator::getValidIntInput("Please choose the index of the desired service: ", 1, garage.getNumOfServices());

	try
	{
		const Car* selectedCar = customer->getCar(carIndex);
		const Service* selectedService = garage.getService(serviceIndex - 1);

		if (selectedCar == nullptr || selectedService == nullptr) {
			throw ConcreteGarageException("Invalid car or service selection");
		}

		Appointment newAppointment(appointmentDate, selectedCar, selectedService);
		// No need to call createMaintenanceSummary() here, it's called in the constructor
		newAppointment.createMaintenanceSummary();
		customer->bookAppointment(newAppointment);
		cout << "Appointment booked successfully." << endl;
	}
	catch (InvalidDateException& e)
	{
		throw e;
	}
	catch (CarNullException& e)
	{
		throw e;
	}
	catch (ServiceNullException& e)
	{
		throw e;
	}
	catch (AppointmentException& e)
	{
		throw e;
	}
}


void generateNewInvoice(Secretary& secretary, Garage& garage) throw(GarageExceptions)
{
	try
	{
		Customer* customer = getCustomer(garage);
		if (customer == nullptr) {
			cout << "No customer selected. Returning to main menu." << endl;
			return;
		}
		Appointment* appointment = getAppointment(garage, customer);
		if (appointment == nullptr) {
			cout << "No appointment selected. Returning to main menu." << endl;
			return;
		}

		time_t now = time(0);
		tm* ltm = localtime(&now);
		Date currentDate(ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);

		//Invoice* invoice = secretary.generateInvoice(customer, appointment, currentDate);
		Invoice* invoice = secretary.generateInvoice(appointment);
		if (invoice != nullptr) {
			cout << "Invoice generated successfully:" << endl;
			invoice->print();
			//delete invoice; // Assuming the Invoice is dynamically allocated
		}
		else {
			cout << "Failed to generate invoice." << endl;
		}
	}
	catch (CustomerNullException& e)
	{
		throw e;
	}
	catch (AppointmentNullException& e)
	{
		throw e;
	}
	catch (InvoiceException& e)
	{
		throw e;
	}
}


void repairCustomerCar(Mechanic& mechanic, Garage& garage) throw(GarageExceptions)
{
	try
	{
		Customer* customer = getCustomer(garage);
		Appointment* appointment = getAppointment(garage, customer);
		MaintenanceSummary* summary = appointment->getMaintenanceSummary();
		if (summary == nullptr) {
			cout << "Creating a new maintenance summary for this appointment." << endl;
			appointment->createMaintenanceSummary();
			summary = appointment->getMaintenanceSummary();
		}
		mechanic.repairCar(*summary, garage); // Pass the garage to the repairCar method
		cout << "Car repaired successfully." << endl;

		// Update the invoice with the used spare parts
        Invoice* invoice = summary->getInvoice();
        if (invoice == nullptr) {
            invoice = new Invoice(customer, appointment, summary->getDateOfMaintenance());
            invoice->setMaintenanceSummary(summary);
            summary->setInvoice(invoice);
			appointment->setInvoice(invoice); // i did
        }
        else {
            invoice->setMaintenanceSummary(summary);
        }

        cout << "Invoice generated successfully:" << endl;
        invoice->print();

	}
	catch (CustomerNullException& e)
	{
		throw e;
	}
	catch (AppointmentNullException& e)
	{
		throw e;
	}
	catch (SummaryNullException& e)
	{
		cout << e.what() << endl;
		cout << "Unable to repair car without a maintenance summary." << endl;
	}
	catch (RepairCarException& e)
	{
		throw e;
	}
}

void updateExistingMaintenanceSummary(Mechanic& mechanic, Garage& garage) throw(GarageExceptions)
{
	try
	{
		Customer* customer = getCustomer(garage);
		Appointment* appointment = getAppointment(garage, customer);
		MaintenanceSummary* summary = appointment->getMaintenanceSummary();
		if (summary == nullptr) {
			cout << "Creating a new maintenance summary for this appointment." << endl;
			appointment->createMaintenanceSummary();
			summary = appointment->getMaintenanceSummary();
		}
		char description[MAX_INPUT_SIZE];
		InputValidator::getValidStringInput("Please enter description: ", description, MAX_INPUT_SIZE,
			[](const char* s) { return strlen(s) > 0; });
		summary->setDescription(description);
	}
	catch (CustomerNullException& e)
	{
		throw e;
	}
	catch (AppointmentNullException& e)
	{
		throw e;
	}
	catch (SummaryNullException& e)
	{
		throw e;
	}
	catch (...)
	{
		cout << "unknown error!" << endl;
	}
}


void orderSingleSparePart(ShiftManager& shiftManager, Garage& garage) throw(GarageExceptions)
{
	int numSpareParts = garage.getNumOfSpareParts();
	bool addNewPart = false;

	if (numSpareParts == 0) {
		cout << "No spare parts available. You will need to add a new spare part." << endl;
		addNewPart = true;
	}
	else {
		cout << "Available spare parts:" << endl;
		SparePart** allSpareParts = garage.getListOfSpareParts();
		for (int i = 0; i < numSpareParts; i++) {
			cout << i + 1 << ". " << allSpareParts[i]->getName() << " - In stock: " << allSpareParts[i]->getUnitsInStock() << endl;
		}

		int choice = InputValidator::getValidIntInput("Enter the number of the spare part to update, or 0 to add a new part: ", 0, numSpareParts);

		if (choice == 0) {
			addNewPart = true;
		}
		else {
			SparePart* sp = garage.getSparePartByIndex(choice - 1);
			if (sp == nullptr)
				throw SparePartNullException();

			int amount = InputValidator::getValidIntInput("Enter the quantity to add to stock: ", 1, INT_MAX);
			shiftManager.orderSparePart(*sp, amount);
			cout << "Updated stock for " << sp->getName() << ". New stock: " << sp->getUnitsInStock() << endl;
		}
	}

	if (addNewPart) {
		char sparePartName[MAX_INPUT_SIZE];
		int unitsInStock;
		double price;

		InputValidator::getValidStringInput("Enter the new spare part name: ", sparePartName, MAX_INPUT_SIZE,
			[](const char* s) { return strlen(s) > 0; });
		unitsInStock = InputValidator::getValidIntInput("Enter the initial stock quantity: ", 0, INT_MAX);
		price = InputValidator::getValidIntInput("Enter the price: ", 0, INT_MAX);

		try {
			SparePart newPart(sparePartName, unitsInStock, price);
			shiftManager.addNewSparePart(newPart, garage);
			cout << "New spare part added successfully." << endl;
		}
		catch (SparePartException& e) {
			cout << "Failed to add new spare part: " << e.what() << endl;
		}
	}
}

Customer* getCustomer(Garage& garage) throw(CustomerNullException)
{
	const Customer** allCustomers = garage.getListOfCustomers();
	int numCustomers = garage.getNumOfCustomers();

	if (numCustomers == 0) {
		cout << "No customers available." << endl;
		return nullptr;
	}

	cout << "Available customers:" << endl;
	for (int i = 0; i < numCustomers; i++) {
		cout << i + 1 << ". " << *allCustomers[i] << endl;
	}

	int customerId = InputValidator::getValidIntInput("Please choose the index of the desired customer: ", 1, numCustomers);
	Customer* theCustomer = garage.getCustomerById(customerId);

	if (theCustomer == nullptr)
		throw CustomerNullException();

	return theCustomer;
}


Appointment* getAppointment(Garage& garage, Customer* customer) throw(AppointmentNullException)
{
	if (customer->getNumOfAppiontments() == 0) {
		cout << "This customer has no appointments." << endl;
		return nullptr;
	}

	cout << "Customer's appointments:" << endl;
	customer->printAppointments();

	int index = InputValidator::getValidIntInput("Please choose the desired appointment: ", 1, customer->getNumOfAppiontments());
	Appointment* appointment = customer->getAppointmentByIndex(index - 1);  // Adjust for 0-based indexing

	if (appointment == nullptr)
		throw AppointmentNullException();

	return appointment;
}