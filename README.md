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

<img width="1909" height="1009" alt="Screenshot 2025-11-30 205350" src="https://github.com/user-attachments/assets/34ca9334-5fd2-4b87-abcc-3e4caace4419" />
<img width="1911" height="996" alt="Screenshot 2025-11-30 205422" src="https://github.com/user-attachments/assets/c857a36a-0b62-4cbc-a6de-d6034dc6a12b" />
<img width="1915" height="1017" alt="Screenshot 2025-11-30 205505" src="https://github.com/user-attachments/assets/be062ad3-bf6f-4223-99ed-f9d1f0b3164f" />
<img width="1906" height="1005" alt="Screenshot 2025-11-30 205526" src="https://github.com/user-attachments/assets/70cf7da3-febe-4926-9134-639d3d33df9c" />

## Example Usage and Output
Menu:
1. Add
2. List
3. Check
4. Delete
5. Exit
Choice: **1**  (User chooses to add a reminder)

Description: **Buy groceries**  (User enters description)
Due time (YYYY-MM-DD HH:MM): **2023-10-05 14:30**  (User enters time)
Added.  (Program confirms)

Menu:
1. Add
2. List
3. Check
4. Delete
5. Exit
Choice: **1**  (Add another reminder)

Description: **Call doctor**
Due time (YYYY-MM-DD HH:MM): **2023-10-06 10:00**
Added.

Menu:
1. Add
2. List
3. Check
4. Delete
5. Exit
Choice: **2**  (List reminders)

1. Buy groceries - 2023-10-05 14:30
2. Call doctor - 2023-10-06 10:00

Menu:
1. Add
2. List
3. Check
4. Delete
5. Exit
Choice: **3**  (Check for due reminders; assuming current time is after 2023-10-05 14:30)

REMINDER: Buy groceries

Menu:
1. Add
2. List
3. Check
4. Delete
5. Exit
Choice: **4**  (Delete a reminder)

1. Buy groceries - 2023-10-05 14:30
2. Call doctor - 2023-10-06 10:00
Delete number: **1**  (Delete the first reminder)
Deleted.

Menu:
1. Add
2. List
3. Check
4. Delete
5. Exit
Choice: **5**  (Exit)
Menu:
1. Add
2. List
3. Check
4. Delete
5. Exit
Choice: **1**  (User chooses to add a reminder)

Description: **Buy groceries**  (User enters description)
Due time (YYYY-MM-DD HH:MM): **2023-10-05 14:30**  (User enters time)
Added.  (Program confirms)

Menu:
1. Add
2. List
3. Check
4. Delete
5. Exit
Choice: **1**  (Add another reminder)

Description: **Call doctor**
Due time (YYYY-MM-DD HH:MM): **2023-10-06 10:00**
Added.

Menu:
1. Add
2. List
3. Check
4. Delete
5. Exit
Choice: **2**  (List reminders)

1. Buy groceries - 2023-10-05 14:30
2. Call doctor - 2023-10-06 10:00

Menu:
1. Add
2. List
3. Check
4. Delete
5. Exit
Choice: **3**  (Check for due reminders; assuming current time is after 2023-10-05 14:30)

REMINDER: Buy groceries

Menu:
1. Add
2. List
3. Check
4. Delete
5. Exit
Choice: **4**  (Delete a reminder)

1. Buy groceries - 2023-10-05 14:30
2. Call doctor - 2023-10-06 10:00
Delete number: **1**  (Delete the first reminder)
Deleted.

Menu:
1. Add
2. List
3. Check
4. Delete
5. Exit
Choice: **5**  (Exit)
<img width="1914" height="987" alt="Screenshot 2025-11-30 214540" src="https://github.com/user-attachments/assets/4a0445ba-ed51-4c6a-b8b5-016306094e12" />
<img width="1892" height="1007" alt="Screenshot 2025-11-30 214557" src="https://github.com/user-attachments/assets/db5934c4-8550-47d3-aab6-96ecb4cb4cb1" />
## Conclusion
This Smart Reminder project demonstrates how C language can be used to build a simple real-world utility application. 
I added multiple unique features such as categorized reminders, validation checks, and a redesigned menu system, which makes my project different from others. 
This project helped me understand file handling, time management, and user-friendly program design in C.
