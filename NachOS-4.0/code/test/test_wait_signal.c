#include "syscall.h"

int main()
{
    // KHAI BAO
	int check_Success; // Bien co dung de kiem tra thanh cong

    // Khoi tao 4 Semaphore de quan ly 3 tien trinh
	check_Success = CreateSemaphore("main",0);
	if(check_Success == -1)
		return 1;
	check_Success = CreateSemaphore("pro1", 0);
	if(check_Success == -1)
		return 1;
	check_Success = CreateSemaphore("pro2", 0);
	if(check_Success == -1)
		return 1;

    check_Success= Exec("program_1");
		check_Success= Exec("program_2");
    // Signal("pro1");

    Wait("main");
    Halt();
    return 0;
}