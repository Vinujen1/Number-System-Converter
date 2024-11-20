#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <regex>
using namespace std;


// Function to validate the input number based on the source base
bool ValidateInput(const string &input_number, int source_base) {
    regex pattern;

    // Define patterns for each base
    switch (source_base) {
        case 2: // Binary: Only 0, 1, and an optional decimal point
            pattern = regex("^[-+]?[01]*\\.?[01]+$");
            break;
        case 8: // Octal: Only digits 0-7 and an optional decimal point
            pattern = regex("^[-+]?[0-7]*\\.?[0-7]+$");
            break;
        case 10: // Decimal: Digits 0-9 and an optional decimal point
            pattern = regex("^[-+]?[0-9]*\\.?[0-9]+$");
            break;
        case 16: // Hexadecimal: Digits 0-9, letters A-F (case insensitive), and an optional decimal point
            pattern = regex("^[-+]?[0-9A-Fa-f]*\\.?[0-9A-Fa-f]+$");
            break;
        default: // For unsupported bases, return false
            cout << "Unsupported base entered.\n";
            return false;
    }

    // Check if the input matches the pattern for the source base
    if (regex_match(input_number, pattern)) {
        return true;
    } else {
        cout << "Invalid input for the base " << source_base << ".\n";
        return false;
    }
}

// Function to convert a number from one base to another
int convert_number(const string &input_number, int source_base, int target_base) {
    // Convert the input number from the source base to decimal
    int decimalValue = 0;
    int power = 0;

    // Convert input string to decimal considering the base
    for (int i = input_number.length() - 1; i >= 0; --i) {
        char digit = input_number[i];
        int digitValue;

        if (digit == '.') { // Skip decimal point
            continue;
        }

        // Convert character to its integer value
        if (isdigit(digit)) {
            digitValue = digit - '0';
        } else {
            digitValue = toupper(digit) - 'A' + 10; // For hexadecimal digits
        }

        decimalValue += digitValue * pow(source_base, power);
        power++;
    }

    // Convert decimal to the target base
    string result;
    const char digits[] = "0123456789ABCDEF";

    if (decimalValue == 0) {
        return 0;
    }

    // Convert from decimal to the target base
    while (decimalValue > 0) {
        result += digits[decimalValue % target_base];
        decimalValue /= target_base;
    }

    reverse(result.begin(), result.end());

    // Return result as an integer (only handles integer parts here)
    return stoi(result);
}

int main() {
    string input_number;
    int startBase, endBase;
    char continueChoice;

    do {
        cout << "Please enter the following inputs:\n";
        cout << "The number to convert:\n>> ";
        cin >> input_number;

        cout << "The source base (i.e., the base to convert from, i.e., binary - 2, octal - 8, decimal - 10, hexadecimal - 16):\n>> ";
        cin >> startBase;

        // Validate input before conversion
        if (!ValidateInput(input_number, startBase)) {
            cout << "Invalid number format for the specified base.\n";
            continue;
        }

        cout << "The target base (i.e., the base to convert to, i.e., binary - 2, octal - 8, decimal - 10, hexadecimal - 16):\n>> ";
        cin >> endBase;

        // Perform the conversion
        int result = convert_number(input_number, startBase, endBase);

        // Display the result
        cout << "\nThe result of converting the number " << input_number 
                  << " from base " << startBase << " to base " << endBase << " is:\n>> " << result << "\n";

        // Ask user to continue or quit
        cout << "\nDo you wish to continue with other numbers?\n";
        cout << "Enter (Y) to continue\nEnter (N) to quit\n>> ";
        cin >> continueChoice;
        continueChoice = (continueChoice);

    } while (continueChoice == 'Y');

    cout << "\nQuitting calculator…Thank you!\n";
    return 0;
}
