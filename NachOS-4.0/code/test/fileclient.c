#include "syscall.h"
#define MAXLENGTH 128

int strlen(const char *str)
{
    const char *s;
    for (s = str; *s; ++s)
        ;
    return (s - str);
}

int main() {
    char ip[] = "127.0.0.1";
    int port = 1234;
    char bufferIn[MAXLENGTH];
    char bufferOut[MAXLENGTH];
    char fileNameIn[] = "a.txt";
    char fileNameOut[] = "b.txt";

    int fileIn;
    int fileOut;

    int sid = SocketTCP();

    if (sid == -1)
        return;

    fileIn = Open(fileNameIn, 0);
    Create(fileNameOut);
    fileOut = Open(fileNameOut, 1);

    Read(bufferIn, MAXLENGTH, fileIn);

    if (Connect(sid, ip, port) == 0)
    {
        Send(sid, bufferIn, strlen(bufferIn) + 1);
        Receive(sid, bufferOut, strlen(bufferIn) + 1);
    }

    Write(bufferOut, strlen(bufferOut) + 1,fileOut);

    Halt();
}