#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to convert a single Roman numeral character to its decimal value
int roman_to_value(char roman_char) {
    // Array mapping Roman numerals to their decimal values
    switch (roman_char) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return 0; // Return 0 for invalid characters
    }
}

// Function to convert a Roman numeral string to its decimal equivalent
int roman_to_decimal(const char *roman) {
    int total = 0; // Initialize total to 0
    int length = strlen(roman); // Get the length of the Roman numeral string

    // Iterate through the Roman numeral string
    for (int i = 0; i < length; i++) {
        int current_value = roman_to_value(roman[i]); // Get the value of the current symbol
        int next_value = (i + 1 < length) ? roman_to_value(roman[i + 1]) : 0; // Get the value of the next symbol

        // If the current value is less than the next value, subtract it from total
        if (current_value < next_value) {
            total -= current_value;
        } else { // Otherwise, add it to total
            total += current_value;
        }
    }
    return total; // Return the total decimal value
}

// Function to perform arithmetic operations on two integers
int perform_operation(int num1, int num2, char operator) {
    switch (operator) {
        case '+': return num1 + num2; // Addition
        case '-': return num1 - num2; // Subtraction
        case '*': return num1 * num2; // Multiplication
        default: return 0; // Return 0 for invalid operators
    }
}

// Function to convert a number to its English words representation
void number_to_words(int num, char *result) {
    const char *ones[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    const char *teens[] = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    const char *tens[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    const char *thousands[] = {"", "Thousand", "Million", "Billion"};

    if (num == 0) {
        strcpy(result, "Zero");
        return;
    }

    result[0] = '\0'; // Initialize result string

    // Process thousands, hundreds, tens, and ones
    for (int i = 0; num > 0; i++) {
        int part = num % 1000; // Get the last three digits
        num /= 1000; // Remove the last three digits

        if (part > 0) {
            char buffer[100] = ""; // Buffer to hold the current part's words

            // Handle hundreds
            if (part >= 100) {
                strcat(buffer, ones[part / 100]);
                strcat(buffer, " Hundred ");
                part %= 100; // Remove hundreds
            }

            // Handle tens and ones
            if (part >= 20) {
                strcat(buffer, tens[part / 10]);
                strcat(buffer, " ");
                part %= 10; // Remove tens
            } else if (part >= 10) {
                strcat(buffer, teens[part - 10]);
                strcat(buffer, " ");
                part = 0; // Set part to 0 as we've handled it
            }

            // Handle ones
            if (part > 0) {
                strcat(buffer, ones[part]);
                strcat(buffer, " ");
            }

            // Add the thousands place
            if (i > 0) {
                strcat(buffer, thousands[i]);
                strcat(buffer, " ");
            }

            // Append the current part to the result
            strcat(result, buffer);
        }
    }
}

// Main function to read input, process it, and write output
int main() {
    FILE *input_file = fopen("input.txt", "r"); // Open input file for reading
    FILE *output_file = fopen("output.txt", "w"); // Open output file for writing
    char line[256]; // Buffer to hold each line from the input file

    // Check if files opened successfully
    if (input_file == NULL || output_file == NULL) {
        printf("Error opening files.\n");
        return 1; // Exit with error code
    }

    // Read each line from the input file
    while (fgets(line, sizeof(line), input_file)) {
        char roman1[20], roman2[20], operator; // Variables to hold Roman numerals and operator
        sscanf(line, "%s %c %s", roman1, &operator, roman2); // Parse the line

        // Convert Roman numerals to decimal
        int decimal1 = roman_to_decimal(roman1);
        int decimal2 = roman_to_decimal(roman2);

        // Perform the arithmetic operation
        int result = perform_operation(decimal1, decimal2, operator);

        // Convert the result to words
        char result_in_words[100];
        number_to_words(result, result_in_words);

        // Write the result to the output file
        fprintf(output_file, "%s %c %s = %d\n%s\n", roman1, operator, roman2, result, result_in_words);
    }

    // Close the files
    fclose(input_file);
    fclose(output_file);

    return 0; // Exit successfully
}