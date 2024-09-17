#ifndef INPUT_VALIDATOR_H
#define INPUT_VALIDATOR_H

#include "appointment.h"
#include "customer.h"


class InputValidator {
public:
    static bool isValidNumber(const char* input, int expectedLength = -1, bool positiveOnly = true);
    static bool isValidName(const char* input);
    static bool isValidCarNumber(const char* input);
    static bool isAppointmentAvailable(const Customer* customer, const Date& date);
    static bool getYesNoInput(const char* prompt);
    static int getValidIntInput(const char* prompt, int min, int max);
    static void getValidStringInput(const char* prompt, char* output, int maxLength, bool (*validationFunc)(const char*));

private:
    static bool isAlpha(char c);
    static int stringToInt(const char* str);
};

#endif // INPUT_VALIDATOR_H