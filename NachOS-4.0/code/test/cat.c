#include "syscall.h"
#define maxlen 32

int main(int argc, char *argv[])
{
    int fileid;
    int len = maxlen;
    int index;
    int idConsole ;
    char *filename;
    filename=argv[1];
    // while (argv[0][index] != '\0' && len != 0)
    // {
    //     filename[index] = argv[0][index];
    //     ++index;
    //     --len;
    // }
    // if(argv[0][index]!= '\0')
    // {
    //     filename[index]!= '\0';
    // }
    /*Create a file*/
    // Create("Hello.txt");
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