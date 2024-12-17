#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function prototypes
int romanToDecimal(char roman[]);
int calculateResult(int num1, int num2, char operator);
void numberToWords(int num, char result[]);
void processInputFile(const char *inputFile, const char *outputFile);
int getRomanValue(char ch);

// Roman numeral to decimal value
int getRomanValue(char ch) {
    switch (ch) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return 0;
    }
}

// Convert Roman numeral to decimal
int romanToDecimal(char roman[]) {
    int total = 0;
    int i = 0;
    while (roman[i] != '\0') {
        int current = getRomanValue(roman[i]);
        int next = getRomanValue(roman[i + 1]);
        if (current < next) {
            total += next - current;
            i += 2;
        } else {
            total += current;
            i++;
        }
    }
    return total;
}

// Perform arithmetic operations
int calculateResult(int num1, int num2, char operator) {
    switch (operator) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        default: return 0;
    }
}

// Convert numbers to words
void numberToWords(int num, char result[]) {
    const char *ones[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    const char *teens[] = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    const char *tens[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    const char *thousands[] = {"", "Thousand", "Million"};

    if (num == 0) {
        strcpy(result, "Zero");
        return;
    }

    int parts[4] = {0};
    int index = 0;

    // Split number into groups of 3 digits
    while (num > 0) {
        parts[index++] = num % 1000;
        num /= 1000;
    }

    strcpy(result, "");

    for (int i = index - 1; i >= 0; i--) {
        int current = parts[i];
        if (current == 0) continue;

        char buffer[100] = "";

        if (current / 100 > 0) {
            sprintf(buffer, "%s Hundred ", ones[current / 100]);
            strcat(result, buffer);
        }

        int lastTwo = current % 100;
        if (lastTwo >= 10 && lastTwo < 20) {
            strcat(result, teens[lastTwo - 10]);
        } else {
            if (lastTwo / 10 > 0) {
                strcat(result, tens[lastTwo / 10]);
                strcat(result, " ");
            }
            if (lastTwo % 10 > 0) {
                strcat(result, ones[lastTwo % 10]);
            }
        }

        if (i > 0) {
            strcat(result, " ");
            strcat(result, thousands[i]);
            strcat(result, " ");
        }
    }
}

// Process input file and write output
void processInputFile(const char *inputFile, const char *outputFile) {
    FILE *inFile = fopen(inputFile, "r");
    FILE *outFile = fopen(outputFile, "w");

    if (!inFile || !outFile) {
        printf("Error opening file.\n");
        return;
    }

    char line[100], roman1[50], roman2[50], operator;
    while (fgets(line, sizeof(line), inFile)) {
        sscanf(line, "%s %c %s", roman1, &operator, roman2);

        int num1 = romanToDecimal(roman1);
        int num2 = romanToDecimal(roman2);
        int result = calculateResult(num1, num2, operator);

        char resultInWords[200];
        numberToWords(result, resultInWords);

        fprintf(outFile, "%s\n", resultInWords);
    }

    fclose(inFile);
    fclose(outFile);
}

// Main function
int main() {
    processInputFile("input.txt", "output.txt");
    printf("Conversion complete. Check output.txt for results.\n");
    return 0;
}
