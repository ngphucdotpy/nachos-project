#include "syscall.h"
#define maxlen 32

int main()
{
    int len;
    char filename[maxlen];
    /*Create a file*/
    // Create("Hello.txt");
    int fileid = Open("Hello.txt", 3);
    if (fileid != -1)
    {
        char *buffer = "123456789999";
        int size = 10;
        int size_buff = Write(buffer, size, fileid);
    }
    Close(fileid);
    Halt();
}