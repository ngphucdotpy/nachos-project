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
    int list[10];
    char ip[] = "127.0.0.1";
    int port = 1234;
    int i = 0;

    char buffer_1[] = "never gonna give you up";
    char buffer_2[] = "never gonna let you down";
    char buffer_3[] = "never gonna run around";
    char buffer_4[] = "and desert you";
    char buffer[MAXLENGTH];

    for (i = 0; i < 4; i++)
    {
        list[i] = SocketTCP();
        if (list[i] == -1)
            return;
    }

    if (Connect(list[0], ip, port) == 0)
    {
        if (Send(list[0], buffer_1, strlen(buffer_1) + 1) > 0)
        {
            Receive(list[0], buffer_1, strlen(buffer_1) + 1);
            PrintConsole(buffer_1, strlen(buffer_1) + 1);
        }
    }

    if (Connect(list[1], ip, port) == 0)
    {
        if (Send(list[1], buffer_2, strlen(buffer_2) + 1) > 0)
        {
            Receive(list[1], buffer_2, strlen(buffer_2) + 1);
            PrintConsole(buffer_2, strlen(buffer_2) + 1);
        }
    }

    if (Connect(list[2], ip, port) == 0)
    {
        if (Send(list[2], buffer_3, strlen(buffer_3) + 1) > 0)
        {
            Receive(list[2], buffer_3, strlen(buffer_3) + 1);
            PrintConsole(buffer_3, strlen(buffer_3) + 1);
        }
    }

    if (Connect(list[3], ip, port) == 0)
    {
        if (Send(list[3], buffer_4, strlen(buffer_4) + 1) > 0)
        {
            Receive(list[3], buffer_4, strlen(buffer_4) + 1);
            PrintConsole(buffer_4, strlen(buffer_4) + 1);
        }
    }

    for (i = 0; i < 4; i++)
        if (Close_(list[i]) == 0)
            list[i] = -1;

    Halt();
}