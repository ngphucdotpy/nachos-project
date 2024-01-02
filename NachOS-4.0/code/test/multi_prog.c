#include "syscall.h"

int main()
{
    SpaceId newProc1;
    SpaceId newProc2;

    newProc1 = Exec("copy");
    newProc2 = Exec("cat");

    Join(newProc1);
    Join(newProc2);

    Halt();
}
