#include <stdio.h>
#include "student.h"
#include "file_io.h"

int main(void) {
    Student* head = NULL;
    int result;

    add_student(&head, 1001, "Kim", 90);
    add_student(&head, 1002, "Lee", 80);
    add_student(&head, 1003, "Park", 70);

    result = save_students_to_csv("saved.csv", head);
    printf("save result: %d\n", result);

    free_students(head);

    return 0;
}