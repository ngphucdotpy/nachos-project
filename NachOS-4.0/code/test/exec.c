#include "syscall.h"
#define stdin 0
#define stdout 1

int main() {
    int pid;
    pid = Exec("createfile");
    if (pid < 0) {
        Write("Exec failed: ", 14, stdout);
    } else
        Join(pid);
}