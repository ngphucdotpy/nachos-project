#include "networktable.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

NetworkTable::NetworkTable()
{
    fd = new int[MAXSIZE];
    isUse = new bool[MAXSIZE];
    for (int i = RESERVED; i < MAXSIZE; i++)
    {
        fd[i] = -1;
        isUse[i] = false;
    }
}

NetworkTable::~NetworkTable()
{
    for (int i = RESERVED; i < MAXSIZE; i++)
    {
        fd[i] = -1;
        isUse[i] = false;
    }
    delete[] fd;
    delete[] isUse;
}

int NetworkTable::SocketTCP()
{
    int freeSlot = -1;
    for (int i = RESERVED; i < MAXSIZE; i++)
    {
        if (isUse[i] == false)
        {
            freeSlot = i;
            break;
        }
    }
    if (freeSlot != -1)
    {
        fd[freeSlot] = socket(AF_INET, SOCK_STREAM, 0);
        isUse[freeSlot] = true;
        return fd[freeSlot];
    }
    return -1;
}

int NetworkTable::Close(int sid)
{
    close(sid);
    for (int i = RESERVED; i < MAXSIZE; i++)
    {
        if (fd[i] == sid && isUse[i] == true)
        {
            fd[i] = -1;
            isUse[i] = false;
            return 0;
        }
    }
    return -1;
}

// bool NetworkTable::isAlive(int sid)
// {
//     for (int i = RESERVED; i < MAXSIZE; i++)
//         if (fd[i] == sid && isUse[i] == true)
//             return true;
//     return false;
// }