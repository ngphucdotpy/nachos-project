#include "syscall.h"
#define maxlen 32

int main()
{
    int len;
    char *filename;
    
    int readfilename = Open("stdin", 2);
    int length = maxlen;
    
    int read = Read(filename, length, readfilename);
    int fileid = Open(filename, 0);
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

            Write(buffer, size, idConsole);
            size_buff = Read(buffer, size, fileid);
        }
        Close(idConsole);
    }
    Close(fileid);
    Halt();
}