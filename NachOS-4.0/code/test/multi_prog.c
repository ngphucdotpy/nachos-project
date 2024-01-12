#include "syscall.h"

int main()
{
    SpaceId newProc1;
    SpaceId newProc3;

    newProc3 = Exec("copy");
    newProc1 = Exec("cat");
    Join(newProc1);
    Join(newProc3);

    Halt();
}
