#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Doctor {
    int id;
    char name[50];
    char dept[50];
};

struct Patient {
    int id;
    char name[50];
    char disease[50];
};

struct Node {
    struct Patient p;
    struct Node *next;
};

struct Doctor doctors[] = {
    {1, "Dr. Rahat", "Heart"},
    {2, "Dr. Apon", "Brain"},
    {3, "Dr. Safin", "Child"},
    {4, "Dr. Faija", "Bone"},
    {5, "Dr. Sabiha", "Skin"}
};
int doctorCount = 5;

struct Node *admitted = NULL;

struct Patient appQueue[20];
int front = -1, rear = -1;

struct Patient discharged[20];
int top = -1;

void showDoctors() {
    printf("\n--- Doctors List ---\n");
    for (int i = 0; i < doctorCount; i++) {
        printf("%d - %s (%s)\n", doctors[i].id, doctors[i].name, doctors[i].dept);
    }
}

void addAppointment(struct Patient p) {
    if (rear < 19) {
        if (front == -1) front = 0;
        appQueue[++rear] = p;
    }
}

struct Patient getAppointment() {
    struct Patient temp = appQueue[front];
    if (front == rear) front = rear = -1;
    else front++;
    return temp;
}

void admitPatient(struct Patient p) {
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->p = p;
    newNode->next = admitted;
    admitted = newNode;
}

void dischargePatient() {
    if (admitted == NULL) {
        printf("No admitted patients.\n");
        return;
    }
    struct Node *temp = admitted;
    admitted = admitted->next;
    discharged[++top] = temp->p;
    printf("Discharged: %s\n", temp->p.name);
    free(temp);
}

void showAdmitted() {
    if (admitted == NULL) {
        printf("No admitted patients.\n");
        return;
    }
    printf("\n--- Admitted Patients ---\n");
    struct Node *t = admitted;
    while (t != NULL) {
        printf("%d - %s (%s)\n", t->p.id, t->p.name, t->p.disease);
        t = t->next;
    }
}

void showAppointments() {
    if (front == -1) {
        printf("No appointments.\n");
        return;
    }
    printf("\n--- Appointment Queue ---\n");
    for (int i = front; i <= rear; i++) {
        printf("%d - %s (%s)\n", appQueue[i].id, appQueue[i].name, appQueue[i].disease);
    }
}

void showDischarged() {
    if (top == -1) {
        printf("No discharged patients.\n");
        return;
    }
    printf("\n--- Discharged Patients ---\n");
    for (int i = top; i >= 0; i--) {
        printf("%d - %s (%s)\n", discharged[i].id, discharged[i].name, discharged[i].disease);
    }
}

int main() {
    int choice;
    struct Patient p;
    while (1) {
        printf("\n--- Hospital Menu ---\n");
        printf("1. Show Doctors\n");
        printf("2. Book Appointment\n");
        printf("3. Admit Patient\n");
        printf("4. Discharge Patient\n");
        printf("5. Show Admitted Patients\n");
        printf("6. Show Appointments\n");
        printf("7. Show Discharged Patients\n");
        printf("8. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                showDoctors();
                break;
            case 2:
                printf("Enter ID: "); scanf("%d", &p.id);
                printf("Enter Name: "); scanf(" %[^\n]", p.name);
                printf("Enter Disease: "); scanf(" %[^\n]", p.disease);
                addAppointment(p);
                printf("Appointment booked.\n");
                break;
            case 3:
                if (front != -1) {
                    p = getAppointment();
                    admitPatient(p);
                    printf("Admitted: %s\n", p.name);
                } else {
                    printf("No appointments.\n");
                }
                break;
            case 4:
                dischargePatient();
                break;
            case 5:
                showAdmitted();
                break;
            case 6:
                showAppointments();
                break;
            case 7:
                showDischarged();
                break;
            case 8:
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }
}

