#include "syscall.h"

int fileDescriptor[20];

int main()
{
    int sid = SocketTCP();
    char ip[] = "127.0.0.1";
    int port = 1234;
    char buffer[] = "teeepppp";
    int len = strlen(buffer);

    int cn = Connect(sid, ip, port);
    if (cn == 0)
    {
        Send(sid, buffer, len);
    }
    char *bu2;
    Receive(sid, bu2, len);
    
    Close_(sid);

    Halt();
}