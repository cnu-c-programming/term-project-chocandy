// linked list 기본 함수 구현
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

Student* create_student(int id, const char* name, int score) {
    Student* new_student = (Student*)malloc(sizeof(Student));

    if (new_student == NULL) {
        return NULL;
    }

    new_student->id = id;
    strncpy(new_student->name, name, 31);
    new_student->name[31] = '\0';
    new_student->score = score;
    new_student->next = NULL;

    return new_student;
}

Student* find_student(Student* head, int id) {
    Student* current = head;

    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

int add_student(Student** head, int id, const char* name, int score) {
    if (head == NULL || id <= 0 || score < 0 || score > 100 || name == NULL) {
        return -3;
    }
    /* 중복 ID 검사 */
    if (find_student(*head, id) != NULL) {
        return -1;
    }
    /* 새 노드 생성 */
    Student* new_student = create_student(id, name, score);
    if (new_student == NULL) {
        return -2;
    }
    /* 빈 리스트인 경우 */
    if (*head == NULL) {
        *head = new_student;
        return 0;
    }
    /* 마지막 노드까지 이동 */
    Student* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_student;

    return 0;
}

int delete_student(Student** head, int id) {
    Student* current = *head;
    Student* prev = NULL;

    while (current != NULL) {
        if (current->id == id) {
            if (prev == NULL) { // head 노드를 삭제하는 경우
                *head = current->next;
            }else {  // 중간 또는 마지막 노드를 삭제하는 경우
                prev->next = current->next;
            }
            free(current);
            return 0;
        }

        prev = current;
        current = current->next;
    }

    return -1;
}

int update_student(Student* head, int id, int score) {
    Student* student = find_student(head, id);

    if (student == NULL) {
        return -1;
    }
    student->score = score;

    return 0;
}

void print_students(Student* head) {
    if (head == NULL) {
        printf("No students found.\n");
        return;
    }

    printf("ID Name Score\n");

    Student* current = head;
    while (current != NULL) {
        printf("%d %s %d\n", current->id, current->name, current->score);
        current = current->next;
    }
}

void print_stats(Student* head) {
    if (head == NULL) {
        printf("No student data available.\n");
        return;
    }

    int count = 0;
    int sum = 0;
    int max = head->score;
    int min = head->score;

    Student* current = head;
    while (current != NULL) {
        count++;
        sum += current->score;

        if (current->score > max) {
            max = current->score;
        }

        if (current->score < min) {
            min = current->score;
        }

        current = current->next;
    }

    printf("Count: %d\n", count);
    printf("Average: %.2f\n", (double)sum / count);
    printf("Max: %d\n", max);
    printf("Min: %d\n", min);
}

void free_students(Student* head) {
    Student* current = head;

    while (current != NULL) {
        Student* next = current->next;
        free(current);
        current = next;
    }
}

int count_students(Student* head) {
    int count = 0;

    while (head != NULL) {
        count++;
        head = head->next;
    }

    return count;
}

int sort_students(Student** head, const char* key) {
    Student* i;
    Student* j;

    if (head == NULL || *head == NULL || key == NULL) {
        return -1;
    }

    if (strcmp(key, "id") != 0 &&
        strcmp(key, "name") != 0 &&
        strcmp(key, "score") != 0) {
        return -1;
    }

    for (i = *head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            int should_swap = 0;

            if (strcmp(key, "id") == 0 && i->id > j->id) {
                should_swap = 1;
            } else if (strcmp(key, "name") == 0 &&
                       strcmp(i->name, j->name) > 0) {
                should_swap = 1;
            } else if (strcmp(key, "score") == 0 &&
                       i->score > j->score) {
                should_swap = 1;
            }

            if (should_swap) {
                int temp_id = i->id;
                int temp_score = i->score;
                char temp_name[32];

                strcpy(temp_name, i->name);

                i->id = j->id;
                i->score = j->score;
                strcpy(i->name, j->name);

                j->id = temp_id;
                j->score = temp_score;
                strcpy(j->name, temp_name);
            }
        }
    }

    return 0;
}