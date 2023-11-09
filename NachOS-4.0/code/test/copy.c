#include "syscall.h"
#define maxlen 32

int main()
{
    int len;
    char *a;
    char*b;
    int fileid_b;
    int fileid_a;
    /*Create a file*/
    // Create("Hello.txt");
    int readfilename = Open("stdin", 2);
    int length = maxlen;
    
    int read = Read(a, length, readfilename);
    fileid_a = Open(a, 0);
    read = Read(b, length, readfilename);
    fileid_b= Create(b);
    Close(fileid_b);
    fileid_a = Open(a, 0);
    if (fileid_a != -1)
    {
        char *buffer = "0123456789";
        int size = 10;
        int size_buff = Read(buffer, size, fileid_a);
        fileid_b=Open(b,1);
        while (size_buff > 0)
        {

            Write(buffer, size, fileid_b);
            size_buff = Read(buffer, size, fileid_a);
        }
        Close(fileid_b);
    }
    Close(fileid_a);
    Halt();
}