#include <stdio.h>
#include <setjmp.h>

static jmp_buf jumpbuffer;
static int jump_count;

void f3()
{
    printf("call function f3\n");
    longjmp(jumpbuffer, ++jump_count);
    printf("f3 after call longjump\n");
}
void f2()
{
    printf("f2 before call f3\n");
    f3();
    printf("f2 after call f3\n");
}
void f1()
{
    printf("f1 before call f2\n");
    f2();
    printf("f1 after call f2\n");
}


int main()
{
    jump_count = 0;
    if(setjmp(jumpbuffer) >= 5) return 0;
    printf("main before call f1\n");
    f1();

}
