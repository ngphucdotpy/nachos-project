#include "syscall.h"
#define maxlen 32

int main()
{
    int len;
    char filename[maxlen];
    int fileid;
    int fileid_write;
    /*Create a file*/
    // Create("Hello.txt");
    int size_buff = 0;
    char *buffer = "owiehbowiebvsoivnview";
    size_buff = ReadConsole(filename, maxlen);
    fileid = Open(filename, 1);
    if (fileid != 1)
    {
        size_buff = Read(buffer, 10, fileid);
        Close(fileid);
        fileid_write = Open("fileWriteConsole.txt", 3);
        if (fileid_write != -1)
        {
            size_buff = Write(buffer, size_buff, fileid_write);
        }
        Close(fileid_write);
    }
    Halt();
}