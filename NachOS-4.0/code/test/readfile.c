#include "syscall.h"
#define maxlen 32

int main()
{
    int len;
    char filename[maxlen];
    /*Create a file*/
    // Create("Hello.txt");
    int fileid = Open("Hello.txt", 0);
    if (fileid != -1)
    {
        char *buffer = "owiehbowiebvsoivnview";
        int size = 5;
        int size_buff = Read(buffer, size, fileid);
        if (size_buff != -1)
        {
            size_buff = Read(buffer, size_buff, fileid);
        }
    }
    Close(fileid);
    Halt();
}