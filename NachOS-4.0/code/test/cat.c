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
    ReadConsole(filename, maxlen);
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