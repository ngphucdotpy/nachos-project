#include "syscall.h"

int main()
{
    int check;
    int i;
    char *c;

    check = CreateSemaphore("main", 0);
    if (check == -1)
    {
        return 1;
    }
    check = CreateSemaphore("Thread_1", 0);
    if (check == -1)
    {
        return 1;
    }
    check = CreateSemaphore("Thread_2", 0);
    if (check == -1)
    {
        return 1;
    }
    while (i<10)
    {
        // Wait("Thread_1");
        c= "a";
        PrintConsole(c,1);
        i=i+1;
        // Signal("Thread_1");
    }
    i=0;
    // Wait("Thread_2");

    while (i<10)
    {
        c= "b";
        PrintConsole(c,1);
        i=i+1;
    }
    // Signal("Thread_2");
    
    Halt();
    return 0;
}