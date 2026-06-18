# Mini Student Shell

C 언어로 구현한 학생 관리 프로그램이다.

연결 리스트(Linked List)를 사용하여 학생 정보를 관리하며, CSV 파일을 통해 데이터를 저장하고 불러올 수 있다.

## 주요 기능

- 학생 추가 (add)
- 학생 삭제 (delete)
- 학생 정보 수정 (update)
- 학생 검색 (find)
- 전체 목록 조회 (list)
- 통계 조회 (stats)
- CSV 저장 및 다시 불러오기 (save, reload)
- 이름/점수 기준 정렬 (sort)
- 명령어 파일 실행 (-f 옵션)

## 빌드

```bash
make admin
make client
```

## 실행

```bash
./admin_shell students.csv
./client_shell students.csv
```

명령어 파일 실행:

```bash
./admin_shell -f commands.txt students.csv
```

## 파일 구조

```text
main.c
student.c
student.h
file_io.c
file_io.h
command.c
command.h
Makefile
README.md
students.csv
```

## Admin / Client 구분

Admin Program

- add
- delete
- update
- save

Client Program

- list
- find
- stats
- sort
- help
- reload

관리자 전용 명령어는 Client에서 사용할 수 없습니다.

## CSV 형식

```csv
id,name,score
1,Alice,90
2,Bob,85
3,Charlie,95
```

## 개발 환경

- Language: C
- Compiler: GCC
- OS: macOS

## 작성자

조민정