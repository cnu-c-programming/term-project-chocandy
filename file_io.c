// CSV 파일 입출력 구현
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_io.h"
#include "student.h"

#define LINE_SIZE 256

static int is_number(const char* str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return 0;
        }
    }

    return 1;
}

int load_students_from_csv(const char* filename, Student** head) {
    FILE* fp;
    char line[LINE_SIZE];
    int count = 0;

    if (*head != NULL) {
        free_students(*head);
        *head = NULL;
    }

    fp = fopen(filename, "r");

    /* 파일 없으면 빈 리스트 시작 */
    if (fp == NULL) {
        return 0;
    }

    /* header 읽기 */
    if (fgets(line, sizeof(line), fp) == NULL) {
        fclose(fp);
        return -2;
    }

    line[strcspn(line, "\r\n")] = '\0';

    if (strcmp(line, "id,name,score") != 0) {
        fclose(fp);
        return -2;
    }

    /* 데이터 읽기 */
    while (fgets(line, sizeof(line), fp) != NULL) {
        char* token;
        int id;
        int score;
        char name[100];

        line[strcspn(line, "\r\n")] = '\0';

        token = strtok(line, ",");
        if (token == NULL || !is_number(token)) {
            fclose(fp);
            return -3;
        }
        id = atoi(token);

        if (id <= 0) {
            fclose(fp);
            return -3;
        }

        token = strtok(NULL, ",");
        if (token == NULL || strlen(token) == 0) {
            fclose(fp);
            return -3;
        }

        strncpy(name, token, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';

        token = strtok(NULL, ",");
        if (token == NULL || !is_number(token)) {
            fclose(fp);
            return -3;
        }
        score = atoi(token);

        if (score < 0 || score > 100) {
            fclose(fp);
            return -3;
        }

        if (add_student(head, id, name, score) != 0) {
            fclose(fp);
            return -3;
        }
        count++;
    }

    fclose(fp);
    return count;
}

int save_students_to_csv(const char* filename, Student* head) {
    FILE* fp = fopen(filename, "w");

    if (fp == NULL) {
        return -1;
    }

    fprintf(fp, "id,name,score\n");

    Student* current = head;
    while (current != NULL) {
        fprintf(fp, "%d,%s,%d\n",
                current->id,
                current->name,
                current->score);

        current = current->next;
    }

    fclose(fp);
    return 0;
}