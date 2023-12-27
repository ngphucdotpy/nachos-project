#include "syscall.h"

int main()
{
    int i;
    char*c;
    i=0;
    while(1)
    {
        i=i+1;
        Wait("m_vn");
        if(i>=1000)
        {
            Signal("program_1");
            return;
        }
        c="b";
        PrintConsole(c,1);
        
        Signal("program_1");
    }
    Halt();
    return 0;
}