/* 디버거 테스트용 바이너리 */
#include <stdio.h>

void greet(void) {
    printf("Hello from greet()\n");
}

int main(void) {
    printf("Start\n");
    greet();
    printf("End\n");
    return 0;
}
