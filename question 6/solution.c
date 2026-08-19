#include <stdio.h>
#include <stdlib.h>

// Event structure representing start/end points
typedef struct {
    int point;
    int type; // +1 for start point (l_i), -1 for end point (r_i)
} Event;

// Comparator to sort events by coordinate
int compareEvents(const void *a, const void *b) {
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;
    
    if (e1->point != e2->point) {
        return e1->point - e2->point;
    }
    // Tie-breaker: Process start points (+1) before end points (-1)
    return e2->type - e1->type; 
}

void findMaxOverlapPoint(int L[], int R[], int n) {
    Event events[2 * n];

    // Build event array
    for (int i = 0; i < n; i++) {
        events[2 * i].point = L[i];
        events[2 * i].type = 1;

        events[2 * i + 1].point = R[i];
        events[2 * i + 1].type = -1;
    }

    // Step 1: Sort all events in O(n log n)
    qsort(events, 2 * n, sizeof(Event), compareEvents);

    // Step 2: Sweep line in O(n)
    int current_overlap = 0;
    int max_overlap = 0;
    int best_point = -1;

    for (int i = 0; i < 2 * n; i++) {
        current_overlap += events[i].type;

        if (current_overlap > max_overlap) {
            max_overlap = current_overlap;
            best_point = events[i].point;
        }
    }

    printf("Point in maximum number of intervals: p = %d\n", best_point);
    printf("Number of intervals containing p: %d\n", max_overlap);
}

int main() {
    // Input set S = {(10, 40), (20, 60), (50, 90), (15, 70)}
    int L[] = {10, 20, 50, 15};
    int R[] = {40, 60, 90, 70};
    int n = sizeof(L) / sizeof(L[0]);

    printf("Intervals:\n");
    for (int i = 0; i < n; i++) {
        printf("Interval %d: [%d, %d]\n", i + 1, L[i], R[i]);
    }
    printf("\n");

    findMaxOverlapPoint(L, R, n);

    return 0;
}