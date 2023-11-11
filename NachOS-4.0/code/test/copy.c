#include "syscall.h"
#define maxlen 32

int main()
{
    int len;
    char a[maxlen];
    char b[maxlen];
    int fileid_b;
    int fileid_a;
    /*Create a file*/
    // Create("Hello.txt");
    int stdin;
    int read_a;
    int read_b;
    int length = maxlen;
    stdin = Open("stdin", 2);
    if(stdin==-1)
    {
        Close("stdin");
        Halt();
        return 0;
    }
    read_a = Read(a, length, stdin);
    if (read_a == -1)
    {
        Close("stdin");
        Halt();
        return 0;
    }
    Close("stdin");
    stdin = Open("stdin", 2);
    if(stdin==-1)
    {
        Close("stdin");
        Halt();
        return 0;
    }
    read_b = Read(b, length, stdin);
    if (read_b == -1)
    {
        Close("stdin");
        Halt();
        return 0;
    }
    Close("stdin");
    fileid_b = Create(b);
    Close(fileid_b);
    fileid_a = Open(a, 1);
    if (fileid_a != -1)
    {
        char *buffer = "0123456789";
        int size = 10;
        int size_buff = Read(buffer, size, fileid_a);
        fileid_b = Open(b, 1);
        while (size_buff > 0)
        {
            if (size_buff != size)
            {
                Write(buffer, size_buff, fileid_b);
                break;
            }
            Write(buffer, size, fileid_b);
            size_buff = Read(buffer, size, fileid_a);
        }
        Close(fileid_b);
    }
    Close(fileid_a);
    Halt();
}