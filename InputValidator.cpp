#include "InputValidator.h"
#include <iostream>

using namespace std;

// Custom strlen function
size_t myStrlen(const char* str) {
    size_t len = 0;
    while (str[len] != '\0') {
        ++len;
    }
    return len;
}

bool InputValidator::isValidNumber(const char* input, int expectedLength, bool positiveOnly) {
    int length = myStrlen(input);
    if (expectedLength != -1 && length != expectedLength) {
        return false;
    }

    for (int i = 0; i < length; i++) {
        if (input[i] < '0' || input[i] > '9') {
            return false;
        }
    }

    // Now, 0 is considered positive
    if (positiveOnly && input[0] == '-') {
        return false;
    }

    return true;
}

bool InputValidator::isValidName(const char* input) {
    int length = myStrlen(input);
    if (length == 0) {
        return false;
    }

    for (int i = 0; i < length; i++) {
        if (!isAlpha(input[i]) && input[i] != ' ' && input[i] != '-') {
            return false;
        }
    }

    return true;
}

bool InputValidator::isValidCarNumber(const char* input) {
    int length = myStrlen(input);
    return length > 0 && length <= 8;
}

bool InputValidator::isAppointmentAvailable(const Customer* customer, const Date& date) {
    if (!customer) {
        return false;
    }

    int numAppointments = customer->getNumOfAppiontments();
    Appointment** appointments = customer->getAllAppointments();

    for (int i = 0; i < numAppointments; ++i) {
        if (appointments[i]->getDate() == date) {
            return false; // Conflict found
        }
    }

    return true; // No conflict
}

int InputValidator::getValidIntInput(const char* prompt, int min, int max) {
    char input[256];
    int result;

    do {
        cout << prompt;
        cin.getline(input, sizeof(input));
        if (!isValidNumber(input) || (result = stringToInt(input)) < min || result > max) {
            cout << "Invalid input. Please enter a number between " << min << " and " << max << "." << endl;
        }
        else {
            break;
        }
    } while (true);

    return result;
}

void InputValidator::getValidStringInput(const char* prompt, char* output, int maxLength, bool (*validationFunc)(const char*)) {
    do {
        cout << prompt;
        cin.getline(output, maxLength);

        if (!validationFunc(output)) {
            cout << "Invalid input. Please try again." << endl;
        }
        else {
            break;
        }
    } while (true);
}

bool InputValidator::isAlpha(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int InputValidator::stringToInt(const char* str) {
    int result = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '-') {
        sign = -1;
        i = 1;
    }

    for (; str[i] != '\0'; ++i) {
        result = result * 10 + (str[i] - '0');
    }

    return sign * result;
}

bool InputValidator::getYesNoInput(const char* prompt) {
    char input;
    bool validInput = false;

    do {
        cout << prompt;
        cin >> input;

        // Clear the input buffer
        while (cin.get() != '\n')
            continue;

        input = tolower(input);
        if (input == 'y' || input == 'n') {
            validInput = true;
        }
        else {
            cout << "Invalid input. Please enter 'y' for yes or 'n' for no." << endl;
        }
    } while (!validInput);

    return (input == 'y');
}