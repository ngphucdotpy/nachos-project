#include "syscall.h"
#define maxlen 32

int main()
{
    int len;
    char filename[maxlen];
    /*Create a file*/
    int temp = Create("Hello.txt");
    int fileid = Open("Hello.txt",1);
    Remove("Hello.txt");
    Halt();
}