#include <stdio.h>
#include <string.h>

#define MAX_BORROW 3
#define STUDENT 1
#define FACULTY 2

/* Reads one integer from a line of input; returns -1 if the input is not a number */
int readInt(void) {
    char buf[100];
    int v;
    if (fgets(buf, sizeof(buf), stdin) == NULL) return -1;
    if (sscanf(buf, "%d", &v) != 1) return -1;
    return v;
}

void displayMenu() {
    printf("\n===== UNIVERSITY LIBRARY MANAGEMENT SYSTEM =====\n");
    printf("1. Member Registration\n");
    printf("2. Display Available Books\n");
    printf("3. Borrow a Book\n");
    printf("4. Return a Book\n");
    printf("5. Display Member Record\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

void registerMember(char name[], int *studentID, int *memberType) {
    int len, id, type;

    printf("Enter member name: ");
    fgets(name, 50, stdin);
    len = strlen(name);
    if (len > 0 && name[len - 1] == '\n') name[len - 1] = '\0';

    do {
        printf("Enter student ID (positive number): ");
        id = readInt();
        if (id <= 0) printf("Invalid ID. Try again.\n");
    } while (id <= 0);
    *studentID = id;

    do {
        printf("Enter membership type (1 = Student, 2 = Faculty): ");
        type = readInt();
        if (type != STUDENT && type != FACULTY)
            printf("Invalid membership type. Try again.\n");
    } while (type != STUDENT && type != FACULTY);
    *memberType = type;

    printf("Registration successful!\n");
}

void displayBooks(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks) {
    printf("\n%-10s %-35s %-10s\n", "Book ID", "Title", "Available");
    printf("---------------------------------------------------------\n");
    for (int i = 0; i < totalBooks; i++) {
        printf("%-10d %-35s %-10d\n", bookIDs[i], bookTitles[i], availableCopies[i]);
    }
}

void borrowBook(int bookIDs[], char bookTitles[][50], int availableCopies[],
                int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType) {
    int id, days, index = -1;
    int allowed = (memberType == STUDENT) ? 14 : 30;

    if (*borrowedCount >= MAX_BORROW) {
        printf("You have already borrowed the maximum of %d books.\n", MAX_BORROW);
        return;
    }

    printf("Enter book ID: ");
    id = readInt();

    for (int i = 0; i < totalBooks; i++) {
        if (bookIDs[i] == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Invalid book ID.\n");
        return;
    }
    if (availableCopies[index] <= 0) {
        printf("Sorry, no copies of \"%s\" are available.\n", bookTitles[index]);
        return;
    }

    printf("Enter number of days you intend to keep the book: ");
    days = readInt();
    if (days <= 0) {
        printf("Number of days must be positive.\n");
        return;
    }

    borrowedBookIDs[*borrowedCount] = id;
    (*borrowedCount)++;
    availableCopies[index]--;

    printf("You have borrowed \"%s\".\n", bookTitles[index]);
    printf("Permitted borrowing period: %d days.\n", allowed);
    if (days > allowed)
        printf("Note: your intended period exceeds the permitted period; late fines apply after %d days.\n", allowed);
}

float returnBook(int bookIDs[], int availableCopies[], int totalBooks,
                 int borrowedBookIDs[], int *borrowedCount, int memberType, float *totalFine) {
    int id, days, pos = -1, index = -1;
    int allowed = (memberType == STUDENT) ? 14 : 30;
    int rate = (memberType == STUDENT) ? 20 : 10;
    float fine = 0.0f;
    char code[50];
    int len;

    if (*borrowedCount == 0) {
        printf("You have no borrowed books to return.\n");
        return 0.0f;
    }

    printf("Enter book ID to return: ");
    id = readInt();

    /* verify the member actually borrowed this book */
    for (int i = 0; i < *borrowedCount; i++) {
        if (borrowedBookIDs[i] == id) {
            pos = i;
            break;
        }
    }
    if (pos == -1) {
        printf("You have not borrowed a book with ID %d.\n", id);
        return 0.0f;
    }

    printf("Enter actual number of days the book was kept: ");
    days = readInt();
    if (days <= 0) {
        printf("Number of days must be positive. Return cancelled.\n");
        return 0.0f;
    }

    /* increase available copies */
    for (int i = 0; i < totalBooks; i++) {
        if (bookIDs[i] == id) {
            index = i;
            break;
        }
    }
    if (index != -1) availableCopies[index]++;

    /* remove book from borrowing list (shift the rest left) */
    for (int i = pos; i < *borrowedCount - 1; i++)
        borrowedBookIDs[i] = borrowedBookIDs[i + 1];
    (*borrowedCount)--;

    /* calculate fine */
    if (days > allowed) {
        int extra = days - allowed;
        fine = (float)(extra * rate);
        printf("Book returned %d day(s) late. Fine charged: Rs. %.2f\n", extra, fine);
        *totalFine += fine;

        printf("Enter membership code for fine waiver: ");
        if (fgets(code, sizeof(code), stdin) != NULL) {
            len = strlen(code);
            if (len > 0 && code[len - 1] == '\n') code[len - 1] = '\0';
        } else {
            code[0] = '\0';
        }

        if (strcmp(code, "LIB2026") == 0) {
            fine = fine * 0.5f;
            printf("Correct code! 50%% waiver applied.\n");
        } else {
            printf("Incorrect code. No waiver applied.\n");
        }
        printf("Fine payable for this return: Rs. %.2f\n", fine);
    } else {
        printf("Book returned on time. No fine.\n");
    }

    return fine;
}

void displayMemberRecord(char name[], int studentID, int memberType, int borrowedBookIDs[],
                         int borrowedCount, float totalFine, float fineAfterWaiver) {
    printf("\n========== MEMBER RECORD ==========\n");
    printf("Name            : %s\n", name);
    printf("Student ID      : %d\n", studentID);
    printf("Membership type : %s\n", (memberType == STUDENT) ? "Student" : "Faculty");

    printf("Borrowed books  : ");
    if (borrowedCount == 0) {
        printf("None");
    } else {
        for (int i = 0; i < borrowedCount; i++)
            printf("%d ", borrowedBookIDs[i]);
    }
    printf("\n");

    printf("Total fine before waiver : Rs. %.2f\n", totalFine);
    printf("Final fine payable       : Rs. %.2f\n", fineAfterWaiver);
}

int main() {
    /* book inventory */
    int totalBooks = 5;
    int bookIDs[5] = {101, 102, 103, 104, 105};
    char bookTitles[5][50] = {
        "Programming in C",
        "Data Structures",
        "Database Systems",
        "Operating Systems",
        "Computer Networks"
    };
    int availableCopies[5] = {3, 2, 4, 1, 2};

    /* member record */
    char name[50] = "";
    int studentID = 0, memberType = 0;
    int borrowedBookIDs[MAX_BORROW];
    int borrowedCount = 0;
    float totalFine = 0.0f, fineAfterWaiver = 0.0f;
    int registered = 0;
    int choice;

    do {
        displayMenu();
        choice = readInt();

        switch (choice) {
            case 1:
                if (registered) {
                    printf("A member is already registered.\n");
                } else {
                    registerMember(name, &studentID, &memberType);
                    registered = 1;
                }
                break;

            case 2:
                displayBooks(bookIDs, bookTitles, availableCopies, totalBooks);
                break;

            case 3:
                if (!registered)
                    printf("Please register first (option 1).\n");
                else
                    borrowBook(bookIDs, bookTitles, availableCopies, totalBooks,
                               borrowedBookIDs, &borrowedCount, memberType);
                break;

            case 4:
                if (!registered)
                    printf("Please register first (option 1).\n");
                else
                    fineAfterWaiver += returnBook(bookIDs, availableCopies, totalBooks,
                                                  borrowedBookIDs, &borrowedCount,
                                                  memberType, &totalFine);
                break;

            case 5:
                if (!registered)
                    printf("Please register first (option 1).\n");
                else
                    displayMemberRecord(name, studentID, memberType, borrowedBookIDs,
                                        borrowedCount, totalFine, fineAfterWaiver);
                break;

            case 6:
                printf("Exiting the program. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please enter a number between 1 and 6.\n");
        }
    } while (choice != 6);

    return 0;
}