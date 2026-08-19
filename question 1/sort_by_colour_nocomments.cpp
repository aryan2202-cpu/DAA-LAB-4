#include <bits/stdc++.h>
using namespace std;

enum Colour { RED = 0, BLUE = 1, YELLOW = 2 };

struct Item {
    int number;
    Colour colour;
};

const char* colourName(Colour c) {
    switch (c) {
        case RED: return "Red";
        case BLUE: return "Blue";
        case YELLOW: return "Yellow";
    }
    return "?";
}

vector<Item> sortByColour(const vector<Item>& items) {
    int n = items.size();

    int count[3] = {0, 0, 0};
    for (const auto& it : items) count[it.colour]++;

    int offset[3];
    offset[RED] = 0;
    offset[BLUE] = count[RED];
    offset[YELLOW] = count[RED] + count[BLUE];

    vector<Item> result(n);
    for (const auto& it : items) {
        result[offset[it.colour]] = it;
        offset[it.colour]++;
    }

    return result;
}

bool validate(const vector<Item>& out) {
    for (size_t i = 1; i < out.size(); i++) {
        if (out[i].colour < out[i-1].colour) {
            cout << "FAIL: colour order broken at index " << i << "\n";
            return false;
        }
    }
    map<Colour,int> lastNum;
    for (const auto& it : out) {
        if (lastNum.count(it.colour) && it.number < lastNum[it.colour]) {
            cout << "FAIL: numbers not sorted within colour " << colourName(it.colour) << "\n";
            return false;
        }
        lastNum[it.colour] = it.number;
    }
    return true;
}

void printItems(const vector<Item>& items) {
    for (const auto& it : items)
        cout << "(" << it.number << ", " << colourName(it.colour) << ") ";
    cout << "\n";
}

int main() {
    vector<Item> input = {
        {1, YELLOW}, {2, RED}, {4, BLUE}, {5, RED}, {7, YELLOW},
        {9, BLUE}, {10, RED}, {12, YELLOW}, {13, BLUE}, {15, RED},
        {18, YELLOW}, {20, BLUE}
    };

    cout << "Input (sorted by number):\n";
    printItems(input);

    vector<Item> output = sortByColour(input);

    cout << "\nOutput (grouped by colour, numbers stay sorted within colour):\n";
    printItems(output);

    cout << "\nValidation: " << (validate(output) ? "PASSED" : "FAILED") << "\n";

    cout << "\n--- Stress test with random input (n = 20) ---\n";
    srand(42);
    vector<Item> randInput;
    int num = 0;
    for (int i = 0; i < 20; i++) {
        num += rand() % 5 + 1;
        Colour c = static_cast<Colour>(rand() % 3);
        randInput.push_back({num, c});
    }
    cout << "Input:\n";
    printItems(randInput);

    vector<Item> randOutput = sortByColour(randInput);
    cout << "Output:\n";
    printItems(randOutput);
    cout << "Validation: " << (validate(randOutput) ? "PASSED" : "FAILED") << "\n";

    return 0;
}
