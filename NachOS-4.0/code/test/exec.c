#include "syscall.h"
#define stdin 0
#define stdout 1

int main() {
    int pid,pid2;
    pid = Exec("createfile");
    pid2 = Exec("delete");
    
    Join(pid);
    Join(pid2);
}