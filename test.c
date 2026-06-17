#include <stdio.h>
#include "student.h"

int main() {
    Student* head = NULL;

    printf("add 1 = %d\n",
           add_student(&head, 1, "Alice", 90));

    printf("add 2 = %d\n",
           add_student(&head, 2, "Bob", 80));

    printf("duplicate = %d\n",
           add_student(&head, 1, "Tom", 70));

    Student* s = find_student(head, 2);

    if (s != NULL) {
        printf("found: %s %d\n",
               s->name,
               s->score);
    }

    free_students(head);

    return 0;
}