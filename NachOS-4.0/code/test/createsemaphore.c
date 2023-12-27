#include "syscall.h"

int main()
{
    int check=0;
    CreateSemaphore("cat",1);
    CreateSemaphore("copy",2);

    Halt();
    return 0;

}