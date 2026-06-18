// CSV 파일 입출력 구현
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_io.h"
#include "student.h"

#define LINE_SIZE 256

int load_students_from_csv(const char* filename, Student** head) {
    FILE* fp;
    char line[LINE_SIZE];

    /* 기존 데이터 제거 */
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
        if (token == NULL) {
            fclose(fp);
            return -3;
        }
        id = atoi(token);

        token = strtok(NULL, ",");
        if (token == NULL) {
            fclose(fp);
            return -3;
        }
        strcpy(name, token);

        token = strtok(NULL, ",");
        if (token == NULL) {
            fclose(fp);
            return -3;
        }
        score = atoi(token);

        /* 점수 범위 검사 */
        if (score < 0 || score > 100) {
            fclose(fp);
            return -3;
        }

        /* 학생 추가 */
        if (add_student(head, id, name, score) != 0) {
            fclose(fp);
            return -3;
        }
    }

    fclose(fp);
    return 0;
}

int save_students_to_csv(const char* filename, Student* head) {
    (void)filename;
    (void)head;

    return 0;
}