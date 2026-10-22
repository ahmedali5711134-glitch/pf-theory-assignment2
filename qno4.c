#include <stdio.h>

#define MAX_DAYS 7

/* Reads an integer; returns -1 if the input is not a number */
int readInt(void) {
    int v;
    if (scanf("%d", &v) != 1) {
        while (getchar() != '\n');   /* clear bad input */
        return -1;
    }
    return v;
}

/* Reads a float; returns -1 if the input is not a number */
float readFloat(void) {
    float v;
    if (scanf("%f", &v) != 1) {
        while (getchar() != '\n');   /* clear bad input */
        return -1.0f;
    }
    return v;
}

int getValidDays() {
    int days;
    do {
        printf("Enter number of festival days (1-7): ");
        days = readInt();
        if (days < 1 || days > MAX_DAYS)
            printf("Invalid input. Days must be between 1 and 7.\n");
    } while (days < 1 || days > MAX_DAYS);
    return days;
}

float calculateDailySales(int dayNumber) {
    int orders;
    float amount, total = 0.0f, highest = 0.0f;

    printf("\n--- Day %d ---\n", dayNumber);

    do {
        printf("Enter number of orders for Day %d: ", dayNumber);
        orders = readInt();
        if (orders < 1)
            printf("There must be at least one order.\n");
    } while (orders < 1);

    for (int i = 1; i <= orders; i++) {
        do {
            printf("Enter amount for order %d: Rs. ", i);
            amount = readFloat();
            if (amount <= 0)
                printf("Invalid amount. It must be greater than zero.\n");
        } while (amount <= 0);

        total += amount;
        if (amount > highest) highest = amount;
    }

    printf("Total sales: Rs. %.2f\n", total);
    printf("Average order: Rs. %.2f\n", total / orders);
    printf("Highest order: Rs. %.2f\n", highest);

    return total;
}

int findHighestSalesDay(float dailySales[], int numberOfDays) {
    int best = 0;
    for (int i = 1; i < numberOfDays; i++) {
        if (dailySales[i] > dailySales[best])   /* strict > keeps the earliest day on ties */
            best = i;
    }
    return best + 1;   /* day numbers start from 1 */
}

void displayBarChart(float dailySales[], int numberOfDays) {
    printf("\n===== DAILY SALES BAR CHART =====\n");
    for (int i = 0; i < numberOfDays; i++) {
        int stars = (int)(dailySales[i] / 100.0f);   /* one * per complete Rs. 100 */
        printf("Day %d: ", i + 1);
        for (int j = 0; j < stars; j++)
            printf("*");
        printf(" (Rs. %.2f)\n", dailySales[i]);
    }
}

int main() {
    float dailySales[MAX_DAYS];
    float festivalTotal = 0.0f;
    int days, bestDay;

    days = getValidDays();

    for (int i = 0; i < days; i++) {
        dailySales[i] = calculateDailySales(i + 1);
        festivalTotal += dailySales[i];
    }

    bestDay = findHighestSalesDay(dailySales, days);

    printf("\n===== FESTIVAL SUMMARY =====\n");
    printf("Total festival sales: Rs. %.2f\n", festivalTotal);
    printf("Day with highest sales: Day %d\n", bestDay);
    printf("Highest daily sales: Rs. %.2f\n", dailySales[bestDay - 1]);

    displayBarChart(dailySales, days);

    return 0;
}