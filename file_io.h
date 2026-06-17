// CSV load/save 함수 선언
#ifndef FILE_IO_H
#define FILE_IO_H

#include "student.h"

int load_students_from_csv(const char* filename, Student** head);
int save_students_to_csv(const char* filename, Student* head);

#endif