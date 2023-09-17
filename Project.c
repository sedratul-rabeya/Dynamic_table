#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char* id;
    int age;
    char* name;
} ;

struct DynamicTable {
    struct Student* data;
    int size;
    int capacity;
} ;

void search_by_age(struct DynamicTable* table, int age);
void sort(struct DynamicTable* table);
void editTable(struct DynamicTable* table, int index);
void displayTable(struct DynamicTable* table);
void removeTable(struct DynamicTable* table);
void search_by_id(struct DynamicTable* table, const char* id);

struct DynamicTable* createDynamicTable(int capacity) {
    struct DynamicTable* table = (struct DynamicTable*)malloc(sizeof(struct DynamicTable));
    table->data = (struct Student*)malloc(capacity * sizeof(struct Student));
    table->size = 0;
    table->capacity = capacity;
    return table;
}

void removeTable(struct DynamicTable* table) {
    for (int i = 0; i < table->size; i++) {
        free(table->data[i].name);
        free(table->data[i].id);
        free(table->data[i].age);
    }
    free(table->data);
    free(table);
}

void resizeCapacity(struct DynamicTable* table, int newCapacity) {
    struct Student* newData = (struct Student*)realloc(table->data, newCapacity * sizeof(struct Student));
    table->data = newData;
    table->capacity = newCapacity;
}

void insertStudent(struct DynamicTable* table, char* name, int age, char* id) {
    if (table->size == table->capacity) {
        resizeCapacity(table, table->capacity * 2);
    }

    table->data[table->size].name = (char*)malloc((strlen(name) + 1) * sizeof(char));
    table->data[table->size].id = (char*)malloc((strlen(id) + 1) * sizeof(char));

    strcpy(table->data[table->size].name, name);
    strcpy(table->data[table->size].id, id);
    table->data[table->size].age = age;
    table->size++;
}

void removeStudent(struct DynamicTable* table, int index) {
    if (index >= table->size) {
        printf("    Invalid index. Cannot remove Student.\n");
        return;
    }

    free(table->data[index].name);
    free(table->data[index].id);

    for (int i = index; i < table->size - 1; i++) {
        table->data[i] = table->data[i + 1];
    }

    table->size--;

    if (table->size <= table->capacity / 4 && table->capacity > 1) {
        resizeCapacity(table, table->capacity / 2);
    }
    printf("    Student removed successfully.\n");
    displayTable(table);
}

void search_by_age(struct DynamicTable* table, int age) {
        printf("    Results:\n");
        printf("    -------------------------------------------------------------------\n");
        printf("    |   SL.  |         ID            |        NAME           |   AGE  |\n");
        printf("    -------------------------------------------------------------------\n");
    for (int i = 0; i < table->size; i++) {
        if (table->data[i].age == age) {
        printf("    |  %-3d   |   %-20s|   %-20s|  %-3d   |\n",i+1, table->data[i].id, table->data[i].name, table->data[i].age);
        printf("    -------------------------------------------------------------------\n");
        }
    }
}

int compare(int* a, int* b) {
    struct Student* i =a;
    struct Student* j=b;
    int d;
    d = i->age - j->age;
    return d;
}

void sort(struct DynamicTable* table) {
    qsort(table->data, table->size, sizeof(struct Student), compare);
}

void editTable(struct DynamicTable* table, int index) {
    if (index >= table->size) {
        printf("    Invalid index. Cannot edit Student.\n");
        return;
    }

    printf("    Enter new struct Student name: ");
    scanf("%s", table->data[index].name);
    printf("    Enter new struct Student age: ");
    scanf("%d", &table->data[index].age);
    printf("    Enter new struct Student ID: ");
    scanf("%s", table->data[index].id);
    printf("    Student edited successfully.\n");
    displayTable(table);
}

void displayTable(struct DynamicTable* table) {
    printf("    -------------------------------------------------------------------\n");
    printf("    |   Table Capacity    |   %-5d   |     Table Size      |   %-5d |\n", table->capacity, table->size);
    printf("    -------------------------------------------------------------------\n");
    printf("                                 TABLE:\n");
    printf("    -------------------------------------------------------------------\n");
    printf("    |   SL.  |         ID            |        NAME           |   AGE  |\n");
    printf("    -------------------------------------------------------------------\n");
    for (int i = 0; i < table->size; i++) {
    printf("    |  %-3d   |   %-20s|   %-20s|  %-3d   |\n",i+1, table->data[i].id, table->data[i].name, table->data[i].age);
    printf("    -------------------------------------------------------------------\n");
    }
}
void search_by_id(struct DynamicTable* table, const char* id) {
        printf("    Search Results:\n");
        printf("    -------------------------------------------------------------------\n");
        printf("    |   SL.  |         ID            |        NAME           |   AGE  |\n");
        printf("    -------------------------------------------------------------------\n");
    for (int i = 0; i < table->size; i++) {
        if (strcmp(table->data[i].id, id) == 0) {
        printf("    |  %-3d   |   %-20s|   %-20s|  %-3d   |\n", i + 1, table->data[i].id, table->data[i].name, table->data[i].age);
        printf("    -------------------------------------------------------------------\n");
        }
    }
}


int main() {
    int initialCapacity = 1;
    struct DynamicTable* table = createDynamicTable(initialCapacity);

    char name[50];
    char id[20];
    int age;
    int index;

    while (1) {
        printf("\n\n              DYNAMIC TABLE     \n\n");
        printf("        -------------------------\n");
        printf("        |         Menu:         |\n");
        printf("        -------------------------\n");
        printf("        |1. |   Add Student     |\n");
        printf("        -------------------------\n");
        printf("        |2. |   Remove Student  |\n");
        printf("        -------------------------\n");
        printf("        |3. |   Search by Age   |\n");
        printf("        -------------------------\n");
        printf("        |4. |   Search by ID     |\n");
        printf("        -------------------------\n");
        printf("        |5. |   Sort by Age     |\n");
        printf("        -------------------------\n");
        printf("        |6. |   Edit Student    |\n");
        printf("        -------------------------\n");
        printf("        |7. |   Print Table     |\n");
        printf("        -------------------------\n");
        printf("        |8. |   Exit            |\n");
        printf("        -------------------------\n");
        printf("    Enter your choice: ");
        int choice;
        while (1) {
            if (scanf("%d", &choice) != 1) {
                printf("    Invalid input. Please enter a valid number: ");
                while (getchar() != '\n');
                continue;
            }
            if (choice < 0) {
                printf("    Invalid input. Please enter a non-negative number: ");
                while (getchar() != '\n');
                continue;
            }
            break;
        }

        switch (choice) {
            case 1: {
                printf("    Enter Student name: ");
                scanf("%s", name);
                printf("    Enter Student age: ");
                scanf("%d", &age);
                printf("    Enter Student ID: ");
                scanf("%s", id);
                insertStudent(table, name, age, id);
                printf("    Student added successfully.\n");
                displayTable(table);
                break;
            }
            case 2:
                printf("    Enter the index to remove: ");
                scanf("%d", &index);
                removeStudent(table, index - 1);
                break;

            case 3: {
                printf("    Enter the age to search: ");
                scanf("%d", &age);
                search_by_age(table, age);
                break;
            }
            case 4:
                printf("    Enter the ID to search: ");
                scanf("%s", id);
                search_by_id(table,id);
                break;

            case 5: {
                sort(table);
                printf("    Table sorted by age.\n");
                displayTable(table);
                break;
            }
            case 6: {
                int index;
                printf("    Enter the index to edit: ");
                scanf("%d", &index);
                editTable(table, index - 1);
                break;
            }
            case 7: {
                displayTable(table);
                break;
            }
            case 8: {
                removeTable(table);
                return 0;
            }
            default:
                printf("    Invalid choice. Please try again.\n");
                break;
        }
    }
}
