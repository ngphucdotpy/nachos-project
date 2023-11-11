#include "syscall.h"
#define maxlen 32

int main()
{
    int fileid = Open("fileWriteConsole.txt", 3);
    if (fileid != -1)
    {
        // char *buffer = "123456789999";
        char *buffer = "0123456789";
        int size = 10;
        int size_buff = Write(buffer, size, fileid);
    }
    Close(fileid);
    Halt();
}