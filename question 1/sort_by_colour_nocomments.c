#include <stdio.h>
#include <stdlib.h>

typedef enum { RED = 0, BLUE = 1, YELLOW = 2 } Colour;

typedef struct {
    int number;
    Colour colour;
} Item;

const char* colourName(Colour c) {
    if (c == RED) return "Red";
    if (c == BLUE) return "Blue";
    return "Yellow";
}

void sortByColour(Item items[], int n, Item result[]) {
    int count[3] = {0, 0, 0};
    for (int i = 0; i < n; i++) count[items[i].colour]++;

    int offset[3];
    offset[RED] = 0;
    offset[BLUE] = count[RED];
    offset[YELLOW] = count[RED] + count[BLUE];

    for (int i = 0; i < n; i++) {
        result[offset[items[i].colour]] = items[i];
        offset[items[i].colour]++;
    }
}

int validate(Item out[], int n) {
    for (int i = 1; i < n; i++) {
        if (out[i].colour < out[i-1].colour) {
            printf("FAIL: colour order broken at index %d\n", i);
            return 0;
        }
    }
    int lastNum[3];
    int seen[3] = {0, 0, 0};
    for (int i = 0; i < n; i++) {
        Colour c = out[i].colour;
        if (seen[c] && out[i].number < lastNum[c]) {
            printf("FAIL: numbers not sorted within colour %s\n", colourName(c));
            return 0;
        }
        lastNum[c] = out[i].number;
        seen[c] = 1;
    }
    return 1;
}

void printItems(Item items[], int n) {
    for (int i = 0; i < n; i++)
        printf("(%d, %s) ", items[i].number, colourName(items[i].colour));
    printf("\n");
}

int main() {
    Item input[] = {
        {1, YELLOW}, {2, RED}, {4, BLUE}, {5, RED}, {7, YELLOW},
        {9, BLUE}, {10, RED}, {12, YELLOW}, {13, BLUE}, {15, RED},
        {18, YELLOW}, {20, BLUE}
    };
    int n = sizeof(input) / sizeof(input[0]);
    Item output[n];

    printf("Input (sorted by number):\n");
    printItems(input, n);

    sortByColour(input, n, output);

    printf("\nOutput (grouped by colour, numbers stay sorted within colour):\n");
    printItems(output, n);

    printf("\nValidation: %s\n", validate(output, n) ? "PASSED" : "FAILED");

    printf("\n--- Stress test with random input (n = 20) ---\n");
    srand(42);
    int m = 20;
    Item randInput[20];
    int num = 0;
    for (int i = 0; i < m; i++) {
        num += rand() % 5 + 1;
        Colour c = (Colour)(rand() % 3);
        randInput[i].number = num;
        randInput[i].colour = c;
    }
    printf("Input:\n");
    printItems(randInput, m);

    Item randOutput[20];
    sortByColour(randInput, m, randOutput);
    printf("Output:\n");
    printItems(randOutput, m);
    printf("Validation: %s\n", validate(randOutput, m) ? "PASSED" : "FAILED");

    return 0;
}
