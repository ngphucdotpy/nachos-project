#include "syscall.h"
#define maxlen 32

int main()
{
    int len;
    char filename[maxlen + 1];
    int id = Create("Hello.txt");
    Open(id);
    Close(id);
    Remove("Hello.txt");
    Halt();
}