 #include <stdio.h>

struct event {
    int id;
    char name[50];
    char date[20];
    char venue[50];
};

void addevent();
void viewevents();
void searchevent();
void deleteevent();

int main() {
    int choice;

    while (1) {
        printf("\n----- EVENT MANAGEMENT SYSTEM -----\n");
        printf("1. Add Event\n");
        printf("2. View All Events\n");
        printf("3. Search Event by ID\n");
        printf("4. Delete Event by ID\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addevent();
                break;
            case 2:
                viewevents();
                break;
            case 3:
                 searchevent();
                 break;
            case 4:
                deleteevent();
                break;
            case 5:
                 return 0;
            default: printf("Invalid choice.\n");
        }
    }
}


void addevent() {
    struct event e;
    FILE *fp = fopen("events.txt", "a");

    if (!fp) {
        printf("File error.\n");
        return;
    }

    printf("Enter Event ID: ");
    scanf("%d", &e.id);

    printf("Enter Event Name (single word): ");
    scanf("%s", e.name);

    printf("Enter Event Date (single word): ");
    scanf("%s", e.date);

    printf("Enter Event Venue (single word): ");
    scanf("%s", e.venue);

    fprintf(fp, "%d %s %s %s\n", e.id, e.name, e.date, e.venue);

    fclose(fp);
    printf("Event Added Successfully!\n");
}


void viewevents() {
    struct event e;
    FILE *fp = fopen("events.txt", "r");

    if (!fp) {
        printf("No events available.\n");
        return;
    }

    printf("\n------ All Events ------\n");

    while (fscanf(fp, "%d %s %s %s", &e.id, e.name, e.date, e.venue) == 4) {
        printf("ID    : %d\n", e.id);
        printf("Name  : %s\n", e.name);
        printf("Date  : %s\n", e.date);
        printf("Venue : %s\n", e.venue);
        printf("------------------------\n");
    }

    fclose(fp);
}


void searchevent() {
    struct event e;
    int id, found = 0;
    FILE *fp = fopen("events.txt", "r");

    if (!fp) {
        printf("No events available.\n");
        return;
    }

    printf("Enter Event ID to search: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %s %s", &e.id, e.name, e.date, e.venue) == 4) {
        if (e.id == id) {
            printf("\nEvent Found:\n");
            printf("ID    : %d\n", e.id);
            printf("Name  : %s\n", e.name);
            printf("Date  : %s\n", e.date);
            printf("Venue : %s\n", e.venue);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Event not found!\n");

    fclose(fp);
}


void deleteevent() {
    struct event list[1000], e;
    int id, count = 0, i, found = 0;

    FILE *fp = fopen("events.txt", "r");

    if (!fp) {
        printf("No events available.\n");
        return;
    }


    while (fscanf(fp, "%d %s %s %s", &e.id, e.name, e.date, e.venue) == 4) {
        list[count++] = e;
    }

    fclose(fp);

    printf("Enter Event ID to delete: ");
    scanf("%d", &id);


    fp = fopen("events.txt", "w");

    for (i = 0; i < count; i++) {
        if (list[i].id == id) {
            found = 1;
            continue;
        }

        fprintf(fp, "%d %s %s %s\n",
                list[i].id, list[i].name, list[i].date, list[i].venue);
    }

    fclose(fp);

    if (found)
        printf("Event deleted successfully!\n");
    else
        printf("Event ID not found.\n");
}

