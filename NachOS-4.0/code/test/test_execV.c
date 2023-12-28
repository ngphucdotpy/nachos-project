#include "syscall.h"
#define stdin 0
#define stdout 1

int main()
{

    int pid;
    char* str[]={"createfile","paramenter_1","parameter_2"};
    pid = ExecV(3,str);
    if (pid < 0) {
        Write("Exec failed: ", 14, stdout);
    } else
        Join(pid);
    Halt();
    return 0;
}