#include "syscall.h"

int main()
{
    int i;
    char*c;
    i=0;
    Wait("m_vn");
    while(1)
    {
        i=i+1;
        if(i>=10)
        {
            Signal("program_1");
            return;
        }
        c="b";
        PrintConsole(c,1);
        
    }
    Signal("program_1");
    Halt();
    return 0;
}