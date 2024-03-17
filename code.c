#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_SAVE_PATH "C:/Users/vinit/dsa/.vscode/mydirectory/contacts/contacts.txt"

struct Contact {
    char name[50];
    char number[15];
    struct Contact* next;
};

struct Contact *head = NULL;
struct Contact *temp = NULL;

void cont(const char* name, const char* number) {
    if (head == NULL) {
        head = (struct Contact*)malloc(sizeof(struct Contact));
        if (head == NULL) {
            printf("Memory allocation failed.\n");
            return;
        }
        strcpy(head->name, name);
        strcpy(head->number, number);
        head->next = NULL;
        temp = head;
        printf("Contact added successfully!\n");
        return;
    }

    struct Contact* new_contact = (struct Contact*)malloc(sizeof(struct Contact));
    if (new_contact == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    strcpy(new_contact->name, name);
    strcpy(new_contact->number, number);
    new_contact->next = NULL;
    temp->next = new_contact;
    temp = new_contact;
    printf("Contact added successfully!\n");
}

void searching(const char* name) {
    struct Contact* save = head;
    while (save != NULL) {
        if (strcmp(save->name, name) == 0) {
            printf("Contact found:\nName: %s\nNumber: %s\n", save->name, save->number);
            return;
        }
        save = save->next;
    }
    printf("Contact not found.\n");
}

void delete(const char* name) {
    struct Contact* save = head;
    struct Contact* previous = NULL;
    while (save != NULL) {
        if (strcmp(save->name, name) == 0) {
            if (previous == NULL) {
                head = save->next;
            } else {
                previous->next = save->next;
            }
            free(save);
            printf("Contact deleted successfully!\n");
            return;
        }
        previous = save;
        save = save->next;
    }
    printf("Contact not found. Deletion failed.\n");
}

void update(const char* name, const char* new_number) {
    struct Contact* save = head;
    while (save != NULL) {
        if (strcmp(save->name, name) == 0) {
            strcpy(save->number, new_number);
            printf("Contact updated successfully!\n");
            return;
        }
        save = save->next;
    }
    printf("Contact not found. Update failed.\n");
}

void display() {
    struct Contact* save = head;
    printf("Contact List:\n");
    while (save != NULL) {
        printf("Name: %s\nNumber: %s\n\n", save->name, save->number);
        save = save->next;
    }
}

void saving(const char* filename) {
    FILE* f = fopen(filename, "w");
    if (f == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    struct Contact* save = head;
    while (save != NULL) {
        fprintf(f, "Name: %s\nNumber: %s\n\n", save->name, save->number);
        save = save->next;
    }
    fclose(f);
    printf("Contacts saved successfully!\n");
}

int main() {
    while (1) {
        printf("\nContact List\n");
        printf("1. Add Contact\n");
        printf("2. Search \n");
        printf("3. Update \n");
        printf("4. Delete \n");
        printf("5. Display \n");
        printf("6. Save (%s)\n", DEFAULT_SAVE_PATH);
        printf("7. Exit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);
        fflush(stdin);

        switch (choice) {
            case 1: {
                char name[50], number[15];
                printf("Enter Name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                printf("Enter Number: ");
                fgets(number, sizeof(number), stdin);
                number[strcspn(number, "\n")] = '\0';
                cont(name, number);
                break;
            }
            case 2: {
                char name[50];
                printf("Enter Name to Search: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                searching(name);
                break;
            }
            case 3: {
                char name[50], new_number[15];
                printf("Enter Name to Update: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                printf("Enter New Number: ");
                fgets(new_number, sizeof(new_number), stdin);
                new_number[strcspn(new_number, "\n")] = '\0';
                update(name, new_number);
                break;
            }
            case 4: {
                char name[50];
                printf("Enter Name to Delete: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                delete(name);
                break;
            }
            case 5:
                display();
                break;
            case 6:
                saving(DEFAULT_SAVE_PATH);
                break;
            case 7:
                printf("Exiting....\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}
