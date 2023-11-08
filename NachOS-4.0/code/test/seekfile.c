#include "syscall.h"
#define maxlen 32

int main()
{
    int len;
    char filename[maxlen];
    /*Create a file*/
    // Create("Hello.txt");
    int fileid = Open("Hello.txt", 1);
    if (fileid != -1)
    {
        int position=-1;
        int index_seek=Seek(position,fileid);
        char *buffer = "123456";
        int size = 3;
        int size_buff = Write(buffer, size, fileid);
    }
    Close(fileid);
    Halt();
}