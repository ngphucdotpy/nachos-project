#include "syscall.h"
#define maxlen 32

int main()
{
    int i;
    char*c;
    Wait("pro1");
    i=0;
    while(1)
    {
        i=i+1;
        if(i>=10)
        {
            Signal("main");
            return;
        }
        c="a";
        PrintConsole(c,1);
        if(i==5)
        {
            Signal("pro2");
            Wait("pro1");
        }
    }
    Signal("main");


    return 0;
}