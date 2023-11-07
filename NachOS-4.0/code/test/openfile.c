#include "syscall.h"
#define maxlen 32

int main()
{
    int len;
    char filename[maxlen];
    /*Create a file*/
    int fileid = Open("Hello.txt",0);

    Open("Hello2.txt",0);
    Halt();
}