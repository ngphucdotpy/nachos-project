#include "syscall.h"

int main()
{
    int i;
    char*c;
    Signal("m_vn");	
    i=0;
    while(1)
    {
        i=i+1;
        Wait("program_1");
        if(i>=1000)
        {
            Signal("main");
            return;
        }
        c="a";
        PrintConsole(c,1);
        if(i==500)
        {
            Signal("program_2");
            Wait("program_1");
        }
        Signal("main");
    }
    Halt();
    return 0;
}