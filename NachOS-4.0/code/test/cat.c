#include "syscall.h"
#define maxlen 32

int main(int argc, char *argv[])
{
    int fileid;
    int index;
    int idConsole;
    char filename[maxlen];
    int len;
    /*Create a file*/
    // Create("Hello.txt");
    int stdin;
    int stdout;
    stdin = Open("stdin", 2);
    if (stdin != -1)
    {
        len = Read(filename, maxlen, stdin);
        if (len <= 1)
        {
            Close("stdin");
            Halt();
            return -1;
        }
    }
    Close("stdin");
    fileid = Open(filename, 0);
    if (fileid != -1)
    {
        char *buffer = "0123456789";
        int size = 10;
        int size_buff = Read(buffer, size, fileid);
        int idConsole = Open("stdout", 3);
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
                Write(buffer, size_buff, idConsole);
                break;
            }
            Write(buffer, size, idConsole);
            size_buff = Read(buffer, size, fileid);
        }
        Close(idConsole);
    }
    Close(fileid);
    Halt();
}