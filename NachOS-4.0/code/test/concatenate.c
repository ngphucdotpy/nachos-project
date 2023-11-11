#include "syscall.h"
#define maxlen 32

int main()
{
    int len;
    char a[maxlen];
    char b[maxlen];
    int fileid_b;
    int fileid_a;
    int position;
    char *buffer;
    int size;
    int size_buff;
    /*Create a file*/
    // Create("Hello.txt");
    int read_a;
    int read_b;
    int length = maxlen;
    ReadConsole(a, maxlen);
    ReadConsole(b, maxlen);
    fileid_a = Open(a, 1);
    if (fileid_a == -1)
    {
        Halt();
        return;
    }
    fileid_b = Open(b, 1);
    if (fileid_b == -1)
    {
        Halt();
        return;
    }
    position = Seek(-1, fileid_a);
    if (position == -1)
    {
        Close(fileid_a);
        Close(fileid_b);
        Halt();
        return 0;
    }

    buffer = "0123456789";
    size = 10;
    size_buff = Read(buffer, size, fileid_b);
    while (size_buff > 0)
    {
        if (size_buff != size)
        {
            Write(buffer, size_buff, fileid_a);
            break;
        }
        Write(buffer, size, fileid_a);
        size_buff = Read(buffer, size, fileid_b);
    }
    Close(fileid_a);
    Close(fileid_b);
    Halt();
    return ;
}