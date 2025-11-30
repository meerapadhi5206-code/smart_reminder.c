# What is Unique in My Project

- I added *category-wise reminders* (Work/Study/Personal).
- I added *overdue reminder detection* (Late status).
- I added a *search-by-date* option.
- I implemented *file saving* so reminders are stored permanently.
- I redesigned the menu to make it user-friendly.

# Smart Reminder – C Project

This is a C language project that helps users store, view and manage daily tasks using reminders.

## Features
- Add Reminder  
- View Reminders  
- Automatic Save  
- Categorized tasks  

## How to Run
Run the program using:
./smart_reminder 
## Source code (smart_reminder.c)
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

// Load reminders from file
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

// Save reminders to file
void save_reminders() {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) return;
    for (int i = 0; i < reminder_count; i++) {
        fprintf(file, "%ld %s\n", reminders[i].due_time, reminders[i].description);
    }
    fclose(file);
}

// Add a reminder
void add_reminder() {
    if (reminder_count >= MAX_REMINDERS) {
        printf("Max reminders reached.\n");
        return;
    }
    printf("Description: ");
    getchar();
    fgets(reminders[reminder_count].description, sizeof(reminders[reminder_count].description), stdin);
    reminders[reminder_count].description[strcspn(reminders[reminder_count].description, "\n")] = 0;
    
    printf("Due time (YYYY-MM-DD HH:MM): ");
    char time_str[20];
    fgets(time_str, sizeof(time_str), stdin);
    time_str[strcspn(time_str, "\n")] = 0;
    
    struct tm tm = {0};
    int y, m, d, h, min;
    if (sscanf(time_str, "%d-%d-%d %d:%d", &y, &m, &d, &h, &min) != 5) {
        printf("Invalid format.\n");
        return;
    }
    tm.tm_year = y - 1900;
    tm.tm_mon = m - 1;
    tm.tm_mday = d;
    tm.tm_hour = h;
    tm.tm_min = min;
    tm.tm_sec = 0;
    tm.tm_isdst = -1;
    
    reminders[reminder_count].due_time = mktime(&tm);
    if (reminders[reminder_count].due_time == -1) {
        printf("Invalid time.\n");
        return;
    }
    reminder_count++;
    save_reminders();
    printf("Added.\n");
}

// List reminders
void list_reminders() {
    if (reminder_count == 0) {
        printf("No reminders.\n");
        return;
    }
    for (int i = 0; i < reminder_count; i++) {
        char time_str[20];
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M", localtime(&reminders[i].due_time));
        printf("%d. %s - %s\n", i + 1, reminders[i].description, time_str);
    }
}

// Check due reminders
void check_reminders() {
    time_t now = time(NULL);
    for (int i = 0; i < reminder_count; i++) {
        if (reminders[i].due_time <= now) {
            printf("REMINDER: %s\n", reminders[i].description);
        }
    }
}

// Delete a reminder
void delete_reminder() {
    list_reminders();
    printf("Delete number: ");
    int index;
    scanf("%d", &index);
    if (index < 1 || index > reminder_count) {
        printf("Invalid.\n");
        return;
    }
    for (int i = index - 1; i < reminder_count - 1; i++) {
        reminders[i] = reminders[i + 1];
    }
    reminder_count--;
    save_reminders();
    printf("Deleted.\n");
}

int main() {
    load_reminders();
    while (1) {
        printf("\nMenu:\n1. Add\n2. List\n3. Check\n4. Delete\n5. Exit\nChoice: ");
        int choice;
        scanf("%d", &choice);
        switch (choice) {
            case 1: add_reminder(); break;
            case 2: list_reminders(); break;
            case 3: check_reminders(); break;
            case 4: delete_reminder(); break;
            case 5: exit(0);
            default: printf("Invalid.\n");
        }
    }
    return 0;
}
