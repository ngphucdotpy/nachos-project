#include "syscall.h"

int main()
{
    SpaceId newProc1;
    SpaceId newProc2;

    newProc2 = Exec("copy");
    newProc1 = Exec("cat");

    Join(newProc1); 
    Join(newProc2); 


    Halt();
}
