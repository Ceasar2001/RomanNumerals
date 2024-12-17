#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to convert a single Roman numeral character to its decimal value
int romanCharToDecimal(char c) {
    switch (c) {
        case 'I': return 1;    // I = 1
        case 'V': return 5;    // V = 5
        case 'X': return 10;   // X = 10
        case 'L': return 50;   // L = 50
        case 'C': return 100;  // C = 100
        case 'D': return 500;  // D = 500
        case 'M': return 1000; // M = 1000
        default: return 0;     // Invalid character
    }
}

// Function to convert a Roman numeral string to its decimal equivalent
int romanToDecimal(const char *roman) {
    int total = 0; // Initialize total to 0
    int length = strlen(roman); // Get the length of the Roman numeral string

    for (int i = 0; i < length; i++) {
        // If the current value is less than the next value, subtract it
        if (i + 1 < length && romanCharToDecimal(roman[i]) < romanCharToDecimal(roman[i + 1])) {
            total -= romanCharToDecimal(roman[i]);
        } else {
            total += romanCharToDecimal(roman[i]);
        }
    }
    return total; // Return the total decimal value
}

// Function to read Roman numerals from a file
void readRomanNumerals(const char *filename, char romanNumerals[][20], int *count) {
    FILE *file = fopen(filename, "r"); // Open the input file
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    *count = 0; // Initialize count to 0
    while (fgets(romanNumerals[*count], 20, file) != NULL) {
        romanNumerals[*count][strcspn(romanNumerals[*count], "\n")] = 0; // Remove newline character
        (*count)++; // Increment count
    }
    fclose(file); // Close the file
}

// Function to write the results to a file
void writeResultsToFile(const char *filename, int results[], int count) {
    FILE *file = fopen(filename, "w"); // Open the output file
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d\n", results[i]); // Write each result to the file
    }
    fclose(file); // Close the file
}

// Main function to execute the program
int main() {
    char romanNumerals[100][20]; // Array to store Roman numeral strings
    int count = 0; // Variable to store the count of Roman numerals
    int results[100]; // Array to store decimal results

    readRomanNumerals("input.txt", romanNumerals, &count); // Read Roman numerals from file

    for (int i = 0; i < count; i++) {
        results[i] = romanToDecimal(romanNumerals[i]); // Convert each Roman numeral to decimal
    }

    writeResultsToFile("output.txt", results, count); // Write results to output file

    return 0; // Return success
}
