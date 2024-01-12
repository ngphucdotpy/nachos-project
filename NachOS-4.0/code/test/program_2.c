#include "syscall.h"
#define maxlen 32

int main()
{
    int i;
    char*c;
    i=0;
    while(1)
    {
        i=i+1;
        if(i>=5)
        {
            Signal("pro1");
            return;
        }
        c="b";
        PrintConsole(c,1);
        
    }
    Signal("pro1");

    return 0;
}