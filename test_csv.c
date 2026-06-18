#include <stdio.h>
#include "student.h"
#include "file_io.h"

int main(void) {
    Student* head = NULL;
    int result;

    result = load_students_from_csv("student.csv", &head);

    printf("load result: %d\n", result);

    if (result == 0) {
        print_students(head);
        print_stats(head);
    }

    free_students(head);

    return 0;
}