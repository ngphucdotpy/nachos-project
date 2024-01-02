#include "syscall.h"
#define maxlen 32

int main()
{
    // int i;
    // char*c;
    // // Wait("program_1");
    // i=0;
    // while(1)
    // {
    //     i=i+1;
    //     if(i>=10)
    //     {
    //         Signal("main");
    //         return;
    //     }
    //     c="a";
    //     PrintConsole(c,1);
    //     if(i==5)
    //     {
    //         Signal("program_2");
    //         Wait("program_1");
    //     }
    // }
    // Signal("main");

    //program cat

 int fileid;
    int index;
    int idConsole;
    int len;

    char filename[]="demo.txt";
    fileid=Open(filename,1);

    if (fileid != -1)
    {
        char *buffer = "0123456789";
        int size = 10;
        int size_buff = Read(buffer, size, fileid);
        int idConsole = Open("fileWriteConsole", 3);
        if (idConsole == -1)
        {
            Close(fileid);
            Halt();
            return;
        }
        while (size_buff > 0)
        {
            if (size_buff != size)
            {
                PrintConsole(buffer,size_buff);
                break;
            }
            PrintConsole(buffer,size);
            size_buff = Read(buffer, size, fileid);
            Signal("program_2");
            Wait("program_1");
        }
        
        Close(idConsole);
    }
    Close(fileid);
    Signal("main");

    Halt();
    return 0;
}