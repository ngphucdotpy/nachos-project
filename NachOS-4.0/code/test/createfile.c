#include "syscall.h"
#define maxlen 32

int main()
{
    int len;
    char filename[maxlen + 1];
    int temp = Create("Xin_Chao_Cac_Ban.txt");
    Halt();
}