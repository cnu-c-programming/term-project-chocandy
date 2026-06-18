// Student 구조체와 linked list 함수 선언
#ifndef STUDENT_H
#define STUDENT_H

typedef struct Student {
    int id;
    char name[32];
    int score;
    struct Student* next;
} Student;

/* linked list 기본 기능 */
Student* create_student(int id, const char* name, int score);
Student* find_student(Student* head, int id);

int add_student(Student** head, int id, const char* name, int score);
int delete_student(Student** head, int id);
int update_student(Student* head, int id, int score);

void print_students(Student* head);
void print_stats(Student* head);
void free_students(Student* head);

int count_students(Student* head);

/* 보너스 기능 */
int sort_students(Student** head, const char* key);

#endif