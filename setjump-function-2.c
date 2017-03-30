#include <stdio.h>
#include <setjmp.h>

static jmp_buf jumpbuffer;

void f3() {
    printf("call function f3\n");
    longjmp(jumpbuffer, 1);
    printf("f3 after call longjump\n");
}
void f2() {
    printf("f2 before call f3\n");
    f3();
    printf("f2 after call f3\n");
}
void f1() {
    printf("f1 before call f2\n");
    f2();
    printf("f1 after call f2\n");
}


int main() {
        if(setjmp(jumpbuffer)) {
            return 0;
        }
        printf("main before call f1\n");
        f1();
        printf("After f1()\n");
        //setjmp(jumpbuffer);
    
    return 0;
}
