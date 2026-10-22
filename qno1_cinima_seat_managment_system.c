#include <stdio.h>

int main() {
    int r = 5, c = 5, k = 0;
    int seats_available_hall = 0;
    int seats[r][c];
    char seat[r][c];

    // input
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            int val;
            do {
                printf("enter 0 for available and 1 for unavailable for row(%d) and seat(%d): ", i, j);
                if (scanf("%d", &val) != 1) {
                    while (getchar() != '\n');   // clear bad input
                    val = -1;
                }
            } while (val != 0 && val != 1);
            seats[i][j] = val;
        }
    }

    // count free seats and build the display array
    printf("number of free seats per row are: ");
    for (int i = 0; i < r; i++) {
        int seats_available_row = 0;
        for (int j = 0; j < c; j++) {
            if (seats[i][j] == 1) {
                seat[i][j] = 'x';
            } else {
                seat[i][j] = '-';
                seats_available_row++;       // FIX: count FREE seats
                seats_available_hall++;
            }
        }
        printf("%d ", seats_available_row);
    }
    printf("\ntotal free: %d\n", seats_available_hall);

    // display
    printf("\n");
    for (int j = 0; j < c; j++) {
        printf("   %d", j);
    }
    for (int i = 0; i < r; i++) {
        printf("\nR%d ", i);
        for (int j = 0; j < c; j++) {
            printf("%c   ", seat[i][j]);
        }
    }

    // input group
    printf("\n\nenter number of customers: ");
    scanf("%d", &k);
    if (k <= 0 || k > c) {
        printf("invalid group size, customers should be between (1-%d)\n", c);
        return 0;
    }

    // search (middle row first, then by distance, smaller row first)
    int mid = r / 2;
    int found = 0, foundrow = -1, startseat = -1;
    for (int d = 0; d < r && !found; d++) {
        for (int t = 0; t < 2 && !found; t++) {
            if (d == 0 && t == 1) continue;
            int row = (t == 0) ? mid - d : mid + d;
            if (row < 0 || row >= r) continue;

            int count = 0;
            for (int j = 0; j < c; j++) {
                if (seat[row][j] == '-') {   // FIX: compare with '-'
                    count++;
                    if (count == k) {
                        found = 1;
                        foundrow = row;
                        startseat = j - k + 1;
                        break;
                    }
                } else {
                    count = 0;
                }
            }
        }
    }

    // booking
    if (found) {
        for (int j = startseat; j < startseat + k; j++) {
            seats[foundrow][j] = 1;          // FIX: mark as taken
            seat[foundrow][j] = 'x';         // FIX: show as taken
        }
        seats_available_hall -= k;

        printf("\nbooking successful");
        printf("\nallocated row: %d", foundrow);
        printf("\nallocated seats: ");
        for (int j = startseat; j < startseat + k; j++) {
            printf("%d ", j);
        }

        // updated display
        printf("\n\nupdated seating arrangement:\n");
        for (int j = 0; j < c; j++) {
            printf("   %d", j);
        }
        for (int i = 0; i < r; i++) {
            printf("\nR%d ", i);
            for (int j = 0; j < c; j++) {
                printf("%c   ", seat[i][j]);
            }
        }
        printf("\nremaining free seats: %d\n", seats_available_hall);
    } else {
        printf("\nsorry, no row has %d consecutive available seats", k);
        printf("\nseating plan is unchanged\n");
    }

    return 0;
}