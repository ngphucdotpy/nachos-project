#include "syscall.h"
#define maxlen 32

int main()
{
    int len;
    char filename[maxlen];
    /*Create a file*/
    // Create("Hello.txt");
    int size_buff = 0;
    char *buffer = "owiehbowiebvsoivnview";
    size_buff=ReadConsole(buffer,maxlen);
    PrintConsole(buffer,size_buff);
    Halt();
}