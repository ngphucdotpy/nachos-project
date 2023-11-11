#include "syscall.h"
#define maxlen 32

int main()
{
    int len;
    char filename[maxlen];
    /*Create a file*/
    // Create("Hello.txt");
    int fileid = Open("Hello.txt", 2);
    int size_buff = 0;
    char *buffer = "owiehbowiebvsoivnview";
    int size = 5;
    if (fileid != -1)
    {
        size_buff = Read(buffer, size, fileid);
        // if (size_buff != -1)
        // {
        //     size_buff = Read(buffer, size_buff, fileid);
        // }
    }
    Close(fileid);
    fileid = Open("Hello.txt", 3);
    if (size_buff > 0)
    {
        size_buff = Write(buffer, size,fileid);
    }
    Close(fileid);
    Halt();
}