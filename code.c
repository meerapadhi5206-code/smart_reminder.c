#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_REMINDERS 100
#define FILENAME "reminders.txt"

typedef struct {
    char description[256];
    time_t due_time;
} Reminder;

Reminder reminders[MAX_REMINDERS];
int reminder_count = 0;

// Function to load reminders from file
void load_reminders() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) return;
    
    reminder_count = 0;
    while (fscanf(file, "%ld %[^\n]", &reminders[reminder_count].due_time, reminders[reminder_count].description) != EOF) {
        reminder_count++;
        if (reminder_count >= MAX_REMINDERS) break;
    }
    fclose(file);
}

// Function to save reminders to file
void save_reminders() {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error saving reminders.\n");
        return;
    }
    
    for (int i = 0; i < reminder_count; i++) {
        fprintf(file, "%ld %s\n", reminders[i].due_time, reminders[i].description);
    }
    fclose(file);
}

// Function to add a reminder
void add_reminder() {
    if (reminder_count >= MAX_REMINDERS) {
        printf("Maximum reminders reached.\n");
        return;
    }
    
    printf("Enter reminder description: ");
    getchar(); // Consume newline
    fgets(reminders[reminder_count].description, sizeof(reminders[reminder_count].description), stdin);
    reminders[reminder_count].description[strcspn(reminders[reminder_count].description, "\n")] = 0; // Remove newline
    
    printf("Enter due time (YYYY-MM-DD HH:MM): ");
    char time_str[20];
    fgets(time_str, sizeof(time_str), stdin);
    time_str[strcspn(time_str, "\n")] = 0;
    
    struct tm tm = {0};
    if (strptime(time_str, "%Y-%m-%d %H:%M", &tm) == NULL) {
        printf("Invalid time format.\n");
        return;
    }
    reminders[reminder_count].due_time = mktime(&tm);
    
    reminder_count++;
    save_reminders();
    printf("Reminder added.\n");
}

// Function to list reminders
void list_reminders() {
    if (reminder_count == 0) {
        printf("No reminders.\n");
        return;
    }
    
    for (int i = 0; i < reminder_count; i++) {
        char time_str[20];
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M", localtime(&reminders[i].due_time));
        printf("%d. %s - Due: %s\n", i + 1, reminders[i].description, time_str);
    }
}

// Function to check for due reminders
void check_reminders() {
    time_t now = time(NULL);
    for (int i = 0; i < reminder_count; i++) {
        if (reminders[i].due_time <= now) {
            printf("REMINDER: %s\n", reminders[i].description);
        }
    }
}

// Function to delete a reminder
void delete_reminder() {
    list_reminders();
    printf("Enter reminder number to delete: ");
    int index;
    scanf("%d", &index);
    if (index < 1 || index > reminder_count) {
        printf("Invalid index.\n");
        return;
    }
    
    for (int i = index - 1; i < reminder_count - 1; i++) {
        reminders[i] = reminders[i + 1];
    }
    reminder_count--;
    save_reminders();
    printf("Reminder deleted.\n");
}

int main() {
    load_reminders();
    
    while (1) {
        printf("\nSmart Reminder Menu:\n");
        printf("1. Add Reminder\n");
        printf("2. List Reminders\n");
        printf("3. Check Due Reminders\n");
        printf("4. Delete Reminder\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        
        int choice;
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: add_reminder(); break;
            case 2: list_reminders(); break;
            case 3: check_reminders(); break;
            case 4: delete_reminder(); break;
            case 5: exit(0);
            default: printf("Invalid choice.\n");
        }
    }
    
    return 0;
}
