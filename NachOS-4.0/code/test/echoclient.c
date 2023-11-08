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
    // int sid = SocketTCP();
    // char ip[] = "127.0.0.1";
    // int port = 1234;

    // char buffer[] = "never gonna give you up.";
    // char buffer2[MAXLENGTH];
    // int len = strlen(buffer);

    // if (sid == -1)
    // {
    //     return;
    // }

    // if (Connect(sid, ip, port) == 0)
    // {
    //     Send(sid, buffer, len + 1);
    //     Receive(sid, buffer2, len + 1);
    // }

    // Close_(sid);

    int fd[20];
    char ip[] = "127.0.0.1";
    int port = 1234;
    int i = 0;

    char buffer_1[] = "never gonna give you up";
    char buffer_2[] = "never gonna let you down";
    char buffer_3[] = "never gonna run around";
    char buffer_4[] = "and desert you";
    char buffer[MAXLENGTH];

    for (i = 0; i < 4; i++)
        fd[i] = SocketTCP();

    for (i = 0; i < 4; i++)
        if (fd[i] == -1)
            return;


    if (Connect(fd[0], ip, port) == 0)
    {
        Send(fd[0], buffer_1, strlen(buffer_1) + 1);
        Receive(fd[0], buffer_1, strlen(buffer_1) + 1);
    }

    if (Connect(fd[1], ip, port) == 0)
    {
        Send(fd[1], buffer_2, strlen(buffer_2) + 1);
        Receive(fd[1], buffer_2, strlen(buffer_2) + 1);
    }

    if (Connect(fd[2], ip, port) == 0)
    {
        Send(fd[2], buffer_3, strlen(buffer_3) + 1);
        Receive(fd[2], buffer_3, strlen(buffer_3) + 1);
    }

    if (Connect(fd[3], ip, port) == 0)
    {
        Send(fd[3], buffer_4, strlen(buffer_4) + 1);
        Receive(fd[3], buffer_4, strlen(buffer_4) + 1);
    }

    for (i = 0; i < 4; i++)
        Close_(fd[i]);

    Halt();
}