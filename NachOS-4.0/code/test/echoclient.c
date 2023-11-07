#include "syscall.h"

int fileDescriptor[20];

int main()
{
    int sid = SocketTCP();
    char ip[] = "127.0.0.1";
    int port = 1234;
    char buffer[] = "testtest";
    int len = 8;

    Connect(sid, ip, port);
    Send(sid, buffer, len);
    Close(sid);

    Halt();
}