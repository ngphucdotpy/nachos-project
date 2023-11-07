#include <stdio.h>
#include "syscall.h"

int main() {
    int a = SocketTCP();
    printf('%d', a);
    Halt();
}