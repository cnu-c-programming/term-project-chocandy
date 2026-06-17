// CSV 파일 입출력 구현
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_io.h"
#include "student.h"

int load_students_from_csv(const char* filename, Student** head) {
    /* TODO:
     * 1. 기존 linked list가 있으면 free_students로 비우기
     * 2. fopen(filename, "r")
     * 3. 파일이 없으면 빈 리스트로 시작해도 됨
     * 4. 첫 줄 header 읽기
     * 5. header가 "id,name,score"인지 확인
     * 6. 이후 한 줄씩 읽기
     * 7. strtok 또는 sscanf로 id, name, score 파싱
     * 8. 유효한 데이터면 add_student 호출
     *
     * 반환 예시:
     *  0: 성공
     * -1: 파일 열기 실패
     * -2: 잘못된 header
     * -3: 잘못된 CSV 데이터
     */
    return 0;
}

int save_students_to_csv(const char* filename, Student* head) {
    /* TODO:
     * 1. fopen(filename, "w")
     * 2. header 출력: id,name,score
     * 3. linked list 순회하면서 각 학생 출력
     * 4. fclose
     *
     * 반환:
     *  0: 성공
     * -1: 파일 쓰기 실패
     */
    return 0;
}