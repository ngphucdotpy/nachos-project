#ifndef NT_H
#define NT_H

#include "copyright.h"
#include "sysdep.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXSIZE 20
#define RESERVED 2

class NetworkTable
{
private:
    int *fd;
    bool *mask;

public:
    NetworkTable()
    {
        fd = new int[MAXSIZE];
        mask = new bool[MAXSIZE];
    }
    ~NetworkTable()
    {
        delete[] fd;
        delete[] mask;
    }

    int SocketTCP()
    {
        int freeSlot = -1;
        for (int i = RESERVED; i < MAXSIZE; i++)
        {
            if (mask[i] == 0)
            {
                freeSlot = i;
                break;
            }
        }
        if (freeSlot != -1)
        {
            fd[freeSlot] = socket(AF_INET, SOCK_STREAM, 0);
            mask[freeSlot] = true;
        }
        else
            return -1;
        return fd[freeSlot];
    }
    int Close(int sid)
    {
        close(sid);
        for (int i = RESERVED; i < MAXSIZE; i++)
        {
            if (fd[i] == sid && mask[i] == true)
            {
                fd[i] = 0;
                mask[i] = false;
                return 1;
            }
        }
        return 0;
    }
    // bool isAlive(int sid) {
    //     for (int i = RESERVED; i < MAXSIZE; i++)
    //         if (fd[i] == sid && mask[i] == true)
    //             return true;
    //     return false;
    // }
};

#endif