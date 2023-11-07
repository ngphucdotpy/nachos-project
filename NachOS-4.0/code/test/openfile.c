#include "syscall.h"
#define maxlen 32

int main()
{
    int len;
    char filename[maxlen];
    int fileid;
    /*Create a file*/
    Create("Hello.txt");
    fileid = Open("Hello.txt",1);
    Close(fileid);
    Remove("Hello.txt");
    Halt();
}