#include "syscall.h"
#define maxlen 32

int main()
{
    // int i;
    // char*c;
    // i=0;
    // while(1)
    // {
    //     i=i+1;
    //     if(i>=5)
    //     {
    //         Signal("program_1");
    //         return;
    //     }
    //     c="b";
    //     PrintConsole(c,1);
        
    // }
    // Signal("program_1");

    // Program copy

    int len;
    char a[] = "demo.txt";
    char b[] = "demo_copy.txt";
    int fileid_b;
    int fileid_a;
    int length = maxlen;
    fileid_b = Create(b);
    if (fileid_b == 1)
    {
        Signal("main");
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
            Signal("program_1");

        }
        Close(fileid_b);
    }
    Close(fileid_a);
    Signal("program_1");
    Halt();
    return 0;
}