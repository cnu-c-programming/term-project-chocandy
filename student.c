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
    /* TODO:
     * 1. id 중복 검사
     * 2. 새 노드 생성
     * 3. 리스트가 비어 있으면 head에 연결
     * 4. 비어 있지 않으면 마지막 노드까지 이동 후 연결
     *
     * 반환 예시:
     *  0: 성공
     * -1: 중복 ID
     * -2: 메모리 할당 실패
     */
    return 0;
}

int delete_student(Student** head, int id) {
    /* TODO:
     * 1. 삭제할 노드를 찾는다
     * 2. head 노드를 삭제하는 경우와 중간/마지막 노드를 삭제하는 경우 구분
     * 3. free 처리
     *
     * 반환:
     *  0: 성공
     * -1: 학생 없음
     */
    return 0;
}

int update_student(Student* head, int id, int score) {
    /* TODO:
     * 1. find_student로 학생 검색
     * 2. 없으면 -1 반환
     * 3. 있으면 score 수정
     */
    return 0;
}

void print_students(Student* head) {
    /* TODO:
     * 학생이 없으면 "No students found." 출력
     * 있으면:
     * ID Name Score
     * 1 Alice 90
     * 형태로 출력
     */
}

void print_stats(Student* head) {
    /* TODO:
     * 학생이 없으면 "No student data available." 출력
     * 있으면 Count, Average, Max, Min 출력
     */
}

void free_students(Student* head) {
    Student* current = head;

    while (current != NULL) {
        Student* next = current->next;
        free(current);
        current = next;
    }
}

int sort_students(Student** head, const char* key) {
    /* TODO:
     * 보너스 기능
     * key가 "name"이면 이름 오름차순
     * key가 "score"이면 점수 오름차순
     * 잘못된 key면 -1 반환
     *
     * 구현 방식은 버블 정렬처럼 노드 안의 데이터만 swap해도 됨
     */
    return 0;
}