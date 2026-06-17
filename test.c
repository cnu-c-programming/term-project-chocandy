#include <stdio.h>
#include "student.h"

int main() {
    Student* s1 = create_student(1, "Alice", 90);

    if (s1 == NULL) {
        printf("malloc failed\n");
        return 1;
    }

    printf("ID: %d\n", s1->id);
    printf("Name: %s\n", s1->name);
    printf("Score: %d\n", s1->score);

    free_students(s1);

    printf("free success\n");

    return 0;
}