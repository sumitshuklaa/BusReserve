#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEATS 40

// Structure to hold passenger details
typedef struct Passenger {
    int seatNumber;
    char name[50];
    struct Passenger* next;
} Passenger;

// Functions
void initializeSeats(int seats[]);
void displayAvailableSeats(int seats[]);
void bookTicket(Passenger** head, int seats[]);
void cancelTicket(Passenger** head, int seats[]);
void displayPassengerList(Passenger* head);

int main() {
    int seats[MAX_SEATS];
    Passenger* head = NULL;
    int choice;

    initializeSeats(seats);
    while (1) {
        printf("\n--- Bus Reservation System ---\n");
        printf("1. Display Available Seats\n");
        printf("2. Book Ticket\n");
        printf("3. Cancel Ticket\n");
        printf("4. Display Passenger List\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayAvailableSeats(seats);
                break;
            case 2:
                bookTicket(&head, seats);
                break;
            case 3:
                cancelTicket(&head, seats);
                break;
            case 4:
                displayPassengerList(head);
                break;
            case 5:
                printf("Exiting system.\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

// Initialize all seats to available (0)
void initializeSeats(int seats[]) {
    for (int i = 0; i < MAX_SEATS; i++) {
        seats[i] = 0;
    }
}

// Display available seats
void displayAvailableSeats(int seats[]) {
    printf("\nAvailable Seats:\n");
    for (int i = 0; i < MAX_SEATS; i++) {
        if (seats[i] == 0) {
            printf("%d ", i + 1);
        }
    }
    printf("\n");
}

// Book a ticket
void bookTicket(Passenger** head, int seats[]) {
    int seatNumber;
    char name[50];

    printf("\nEnter seat number to book (1-%d): ", MAX_SEATS);
    scanf("%d", &seatNumber);

    if (seatNumber < 1 || seatNumber > MAX_SEATS || seats[seatNumber - 1] == 1) {
        printf("Invalid or already booked seat number.\n");
        return;
    }

    printf("Enter passenger name: ");
    scanf(" %[^\n]", name);

    // Update seat status
    seats[seatNumber - 1] = 1;

    // Add passenger details to linked list
    Passenger* newPassenger = (Passenger*)malloc(sizeof(Passenger));
    newPassenger->seatNumber = seatNumber;
    strcpy(newPassenger->name, name);
    newPassenger->next = *head;
    *head = newPassenger;

    printf("Ticket booked successfully for %s (Seat %d).\n", name, seatNumber);
}

// Cancel a ticket
void cancelTicket(Passenger** head, int seats[]) {
    int seatNumber;
    printf("\nEnter seat number to cancel (1-%d): ", MAX_SEATS);
    scanf("%d", &seatNumber);

    if (seatNumber < 1 || seatNumber > MAX_SEATS || seats[seatNumber - 1] == 0) {
        printf("Invalid or not booked seat number.\n");
        return;
    }

    // Update seat status
    seats[seatNumber - 1] = 0;

    // Remove passenger from linked list
    Passenger *current = *head, *prev = NULL;
    while (current != NULL && current->seatNumber != seatNumber) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Passenger not found.\n");
        return;
    }

    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    printf("Ticket for Seat %d canceled successfully.\n", seatNumber);
}

// Display passenger list
void displayPassengerList(Passenger* head) {
    if (head == NULL) {
        printf("\nNo passengers booked.\n");
        return;
    }

    printf("\nPassenger List:\n");
    Passenger* temp = head;
    while (temp != NULL) {
        printf("Seat %d: %s\n", temp->seatNumber, temp->name);
        temp = temp->next;
    }
}
