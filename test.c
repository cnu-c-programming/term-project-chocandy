#include <stdio.h>
#include "student.h"

int main() {
    Student* head = NULL;

    print_students(head);
    print_stats(head);

    add_student(&head, 1001, "Kim", 90);
    add_student(&head, 1002, "Lee", 80);
    add_student(&head, 1003, "Park", 70);

    print_students(head);
    print_stats(head);

    free_students(head);

    return 0;
}