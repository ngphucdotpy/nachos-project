#include "syscall.h"
#define MAXLENGTH 128

int strlen(const char *str)
{
    const char *s;
    for (s = str; *s; ++s)
        ;
    return (s - str);
}

int main(int argc, char *argv[])
{
    char ip[] = "127.0.0.1";
    int port = 1234;
    char bufferIn[MAXLENGTH];
    char bufferOut[MAXLENGTH];
    char fileNameIn[] = "a.txt";
    char fileNameOut[] = "b.txt";

    int fileIn;
    int fileOut;
    int size;

    int sid = SocketTCP();

    if (sid == -1)
        return;

    fileIn = Open(fileNameIn, 0);
    Create(fileNameOut);
    fileOut = Open(fileNameOut, 1);

    size = Read(bufferIn, MAXLENGTH, fileIn);

    if (Connect(sid, ip, port) == 0)
    {
        if (Send(sid, bufferIn, size) > 0)
            Receive(sid, bufferOut, size);
    }

    Write(bufferOut, size, fileOut);

    Close_(sid);

    Halt();
}