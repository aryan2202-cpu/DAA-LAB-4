#include <stdio.h>
#include <stdlib.h>

// Structure to represent an event
typedef struct {
    int time;
    int type; // +1 for entry (a_i), -1 for exit (b_i)
} Event;

// Comparator function to sort events by time
int compareEvents(const void *a, const void *b) {
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;
    return e1->time - e2->time;
}

void findPeakPartyTime(int entry[], int exit[], int n) {
    // Total 2n events (n entries, n exits)
    Event events[2 * n];

    for (int i = 0; i < n; i++) {
        events[2 * i].time = entry[i];
        events[2 * i].type = 1;     // Entry event

        events[2 * i + 1].time = exit[i];
        events[2 * i + 1].type = -1;  // Exit event
    }

    // Step 1: Sort all events by time in O(n log n)
    qsort(events, 2 * n, sizeof(Event), compareEvents);

    // Step 2: Sweep line technique in O(n)
    int current_people = 0;
    int max_people = 0;
    int peak_time = -1;

    for (int i = 0; i < 2 * n; i++) {
        current_people += events[i].type;

        if (current_people > max_people) {
            max_people = current_people;
            peak_time = events[i].time;
        }
    }

    printf("Maximum number of people present simultaneously: %d\n", max_people);
    printf("Time when peak attendance was reached: %d\n", peak_time);
}

int main() {
    // Sample inputs: entry times (a_i) and exit times (b_i)
    int entry[] = {1, 2, 9, 5, 8};
    int exit[]  = {4, 5, 12, 10, 11};
    int n = sizeof(entry) / sizeof(entry[0]);

    printf("Person Logs (Entry, Exit):\n");
    for (int i = 0; i < n; i++) {
        printf("Person %d: Entry = %d, Exit = %d\n", i + 1, entry[i], exit[i]);
    }
    printf("\n");

    findPeakPartyTime(entry, exit, n);

    return 0;
}