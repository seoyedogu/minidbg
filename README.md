# minidbg — 나만의 작은 디버거

ptrace 시스템콜 기반으로 직접 구현한 미니 디버거입니다.

## 빌드

```bash
make
```

## 사용법

```
./minidbg
(minidbg) run ./target
(minidbg) break main
(minidbg) regs
(minidbg) mem 0x7fffffffe000
(minidbg) step
(minidbg) continue
(minidbg) quit
```

## 명령어

| 명령어 | 설명 |
|--------|------|
| `run <prog>` | 프로그램 실행 |
| `regs` | 레지스터 출력 |
| `mem <addr> [len]` | 메모리 덤프 |
| `break <addr/func>` | 브레이크포인트 설정 |
| `info b` | BP 목록 출력 |
| `delete <n>` | BP 삭제 |
| `continue` | 실행 재개 |
| `step` | 한 명령어 실행 |
| `quit` | 종료 |

## 기술 스택

- Language: C (gcc)
- OS: Ubuntu / Kali Linux
- Core: `ptrace(2)`, ELF, x86-64
