#include "syscall.h"
#define MAXLENGTH 128

int strlen(const char *str)
{
    const char *s;
    for (s = str; *s; ++s)
        ;
    return (s - str);
}

int main()
{
    int sid = SocketTCP();
    char ip[] = "127.0.0.1";
    int port = 1234;

    char buffer[] = "never gonna give you up.";
    char buffer2[MAXLENGTH];
    int len = strlen(buffer);

    if (sid == -1)
    {
        return;
    }

    if (Connect(sid, ip, port) == 0)
    {
        Send(sid, buffer, len + 1);
        Receive(sid, buffer2, len + 1);
    }

    Close_(sid);

    Halt();
}