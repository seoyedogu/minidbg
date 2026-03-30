# ptrace 학습 노트

## 참고 링크
- man page: https://man7.org/linux/man-pages/man2/ptrace.2.html

## 핵심 요청 타입

| 요청 | 설명 |
|------|------|
| PTRACE_TRACEME   | 자식이 추적 허용 선언 |
| PTRACE_ATTACH    | 실행 중인 프로세스에 붙기 |
| PTRACE_DETACH    | 추적 해제 |
| PTRACE_GETREGS   | 레지스터 읽기 |
| PTRACE_SETREGS   | 레지스터 쓰기 |
| PTRACE_PEEKDATA  | 메모리 읽기 (8바이트) |
| PTRACE_POKEDATA  | 메모리 쓰기 (8바이트) |
| PTRACE_CONT      | 실행 재개 |
| PTRACE_SINGLESTEP| 한 명령어 실행 |

## waitpid 상태 플래그

| 매크로 | 설명 |
|--------|------|
| WIFEXITED(s)  | 정상 종료 여부 |
| WIFSTOPPED(s) | 시그널로 멈춤 여부 |
| WSTOPSIG(s)   | 멈춘 시그널 번호 |
