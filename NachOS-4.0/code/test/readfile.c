#include "syscall.h"
#define maxlen 32

int main()
{
    int len;
    char filename[maxlen];
    /*Create a file*/
    // Create("Hello.txt");
    int fileid = Open("Hello.txt",2);
    char*buffer="owiehbowiebvsoivnview";
    int size=25;
    Read(buffer, size, fileid);
    Close(fileid);
    Halt();
}