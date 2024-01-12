#include "syscall.h"
#define maxlen 32

int main()
{
    int len;
    char a[] = "demo.txt";
    char b[] = "demo_copy.txt";
    int fileid_b;
    int fileid_a;
    /*Create a file*/
    // Create("Hello.txt");
    int read_a;
    int read_b;
    int length = maxlen;
    // ReadConsole(a, maxlen);
    // ReadConsole(b, maxlen);
    fileid_b = Create(b);
    if (fileid_b == 1)
    {
        Halt();
        return 0;
    }
    Close(fileid_b);
    fileid_a = Open(a, 1);
    fileid_b = Open(b, 1);
    if (fileid_a != -1 &&fileid_b!=-1)
    {
        char *buffer = "0123456789";
        int size = 10;
        int size_buff = Read(buffer, size, fileid_a);
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
    // Halt();
    return 0;
}