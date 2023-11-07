// exception.cc
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "main.h"
#include "syscall.h"
#include "ksyscall.h"
//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2.
//
// If you are handling a system call, don't forget to increment the pc
// before returning. (Or else you'll loop making the same system call forever!)
//
//	"which" is the kind of exception.  The list of possible exceptions
//	is in machine.h.
//----------------------------------------------------------------------
void increasePC()
{
	/* set previous programm counter (debugging only)*/
	kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

	/* set programm counter to next instruction (all Instructions are 4 byte wide)*/
	kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);

	/* set next programm counter for brach execution */
	kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg) + 4);
}

// Input: - User space address (int)
// - Limit of buffer (int)
// Output:- Buffer (char*)
// Purpose: Copy buffer from User memory space to System memory space
char *User2System(int virtAddr, int limit)
{
	int i; // index
	int oneChar;
	char *kernelBuf = NULL;
	kernelBuf = new char[limit + 1]; // need for terminal string
	if (kernelBuf == NULL)
		return kernelBuf;
	memset(kernelBuf, 0, limit + 1);
	// printf("\n Filename u2s:");
	for (i = 0; i < limit; i++)
	{
		kernel->machine->ReadMem(virtAddr + i, 1, &oneChar);
		kernelBuf[i] = (char)oneChar;
		// printf("%c",kernelBuf[i]);
		if (oneChar == 0)
			break;
	}
	return kernelBuf;
}

// Input: - User space address (int)
// - Limit of buffer (int)
// - Buffer (char[])
// Output:- Number of bytes copied (int)
// Purpose: Copy buffer from System memory space to User memory space
int System2User(int virtAddr, int len, char *buffer)
{
	if (len < 0)
		return -1;
	if (len == 0)
		return len;
	int i = 0;
	int oneChar = 0;
	do
	{
		oneChar = (int)buffer[i];
		kernel->machine->WriteMem(virtAddr + i, 1, oneChar);
		i++;
	} while (i < len && oneChar != 0);
	return i;
}
int MaxFileLength = 32;
void ExceptionHandler(ExceptionType which)
{
	int type = kernel->machine->ReadRegister(2);

	DEBUG(dbgSys, "Received Exception " << which << " type: " << type << "\n");

	switch (which)
	{
	case SyscallException:
		switch (type)
		{
		case SC_Halt:
			DEBUG(dbgSys, "Shutdown, initiated by user program.\n");

			SysHalt();

			ASSERTNOTREACHED();
			break;

		case SC_Add:
			DEBUG(dbgSys, "Add " << kernel->machine->ReadRegister(4) << " + " << kernel->machine->ReadRegister(5) << "\n");

			/* Process SysAdd Systemcall*/
			int result;
			result = SysAdd(/* int op1 */ (int)kernel->machine->ReadRegister(4),
							/* int op2 */ (int)kernel->machine->ReadRegister(5));

			DEBUG(dbgSys, "Add returning with " << result << "\n");
			/* Prepare Result */
			kernel->machine->WriteRegister(2, (int)result);

			/* Modify return point */
			{
				/* set previous programm counter (debugging only)*/
				kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

				/* set programm counter to next instruction (all Instructions are 4 byte wide)*/
				kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);

				/* set next programm counter for brach execution */
				kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg) + 4);
			}

			return;

			ASSERTNOTREACHED();

			break;
		case SC_Create:
		{
			int virtAddr;
			char *filename;
			DEBUG(dbgSys, "\n SC_Create call ...");
			DEBUG(dbgSys, "\n Reading virtual address of filename");
			// Lấy tham số tên tập tin từ thanh ghi r4
			virtAddr = kernel->machine->ReadRegister(4);
			DEBUG(dbgSys, "\n Reading filename.");
			// MaxFileLength là = 32
			filename = User2System(virtAddr, MaxFileLength + 1);
			if (filename == NULL)
			{
				printf("\n Not enough memory in system");
				DEBUG(dbgSys, "\n Not enough memory in system");
				kernel->machine->WriteRegister(2, -1); // trả về lỗi cho chương
				// trình người dùng
				delete filename;
				return;
			}
			DEBUG(dbgSys, "\n Finish reading filename.");
			// DEBUG(‘a’,"\n File name : '"<<filename<<"'");
			//  Create file with size = 0
			//  Dùng đối tượng fileSystem của lớp OpenFile để tạo file,
			//  việc tạo file này là sử dụng các thủ tục tạo file của hệ điều
			//  hành Linux, chúng ta không quản ly trực tiếp các block trên
			//  đĩa cứng cấp phát cho file, việc quản ly các block của file
			//  trên ổ đĩa là một đồ án khác
			if (!kernel->fileSystem->Create(filename, 0))
			{
				printf("\n Error create file '%s'", filename);
				DEBUG(dbgSys, "\n Error:Cannot create file.");
				kernel->machine->WriteRegister(2, -1);
				increasePC();
				delete filename;
				return;
			}

			kernel->machine->WriteRegister(2, 0); // trả về cho chương trình
												  // người dùng thành công
			increasePC();
			delete filename;

			return;
			ASSERTNOTREACHED();
			break;
		}

		case SC_Open:
		{
			DEBUG(dbgSys, "Vao case SC_Open. ");
			int virtAddr = kernel->machine->ReadRegister(4);
			int type = kernel->machine->ReadRegister(5);
			char *filename;
			filename = User2System(virtAddr, MaxFileLength);
			DEBUG(dbgSys, "Mo file " << filename << ". Type: " << type << "\n");
			int freeSlot = kernel->fileSystem->FindFreeSlot();
			if (freeSlot != -1)
			{
				if (type == 0 || type == 1)
				{ // 0: read and write 	1: read only
					if ((kernel->fileSystem->fileDes[freeSlot] = kernel->fileSystem->Open(filename, type)) != NULL)
					{
						DEBUG(dbgSys, "Mo File Thanh Cong. FileID: " << freeSlot << "\n");
						kernel->machine->WriteRegister(2, freeSlot);
					}
					else
					{
						DEBUG(dbgSys, "Khong the mo file."
										  << "\n");
						kernel->machine->WriteRegister(2, -1);
					}
				}
				else if (type == 2)
				{
					kernel->machine->WriteRegister(2, 0); // Vi tri ID 0 stdin
				}
				else if (type == 3)
				{
					kernel->machine->WriteRegister(2, 1); // Vi tri ID 1 stdout
				}
				else
				{
					// Neu khong mo duoc file
					DEBUG(dbgSys, "Khong the mo file."
									  << "\n");
					kernel->machine->WriteRegister(2, -1);
				}
			}
			else
			{
				DEBUG(dbgSys, "Khong the mo file."
								  << "\n");
				kernel->machine->WriteRegister(2, -1);
			}
			DEBUG(dbgSys, "Tang bien PC "
							  << "\n");
			increasePC();
			delete[] filename;
			return;
			ASSERTNOTREACHED();
			break;
		}
		case SC_Close:
		{
			DEBUG(dbgSys, "Vao case SC_Close. ");

			// Doc id cua file(OpenFileID)
			int id = kernel->machine->ReadRegister(4);
			if (id >= 0 && id <= 19)
			{
				if (kernel->fileSystem->fileDes[id]) // neu co mo file
				{
					delete kernel->fileSystem->fileDes[id];
					kernel->fileSystem->fileDes[id] = NULL;
					kernel->machine->WriteRegister(2, 0);
					DEBUG(dbgSys, "Dong file so " << id << " thanh cong "
												  << "\n");
				}
			}
			kernel->machine->WriteRegister(2, -1);
			increasePC();
			DEBUG(dbgSys, "Tang bien PC "
							  << "\n");
			return;
			ASSERTNOTREACHED();
			break;
		}
		case SC_Read:
		{
			// Doc id cua file(OpenFileID)
			// int id = kernel->machine->ReadRegister(4);
			DEBUG(dbgSys, "Vao case SC_Read. ");
			int virtAddr = kernel->machine->ReadRegister(4);
			int size = kernel->machine->ReadRegister(5);
			int id = kernel->machine->ReadRegister(6);
			char *buffer;
			buffer = User2System(virtAddr, size);
			OpenFile *fileopen = kernel->fileSystem->fileDes[id];
			DEBUG(dbgSys, "Read file " << buffer << ". Size: " << size << ", ID:" << id << ", Type:" << fileopen->type << "\n");

			if (id < 0 || id > 19)
			{
				printf("Khong the mo file.\n");
				DEBUG(dbgSys, "Khong the read file do id file khong thuoc file descriptor table.\n");
				kernel->machine->WriteRegister(2, -1);
				increasePC();

				return;
			}
			if (kernel->fileSystem->fileDes[id] == NULL)
			{
				printf("Khong the mo file khong ton tai.\n");
				DEBUG(dbgSys, "Khong the read file KHONG ton tai.\n");
				kernel->machine->WriteRegister(2, -1);
				increasePC();

				return;
			}
			if (kernel->fileSystem->fileDes[id]->type == 3)
			{
				printf("Khong the mo file Console output.\n");
				DEBUG(dbgSys, "Khong the read file Console output..\n");
				kernel->machine->WriteRegister(2, -1);
				increasePC();

				return;
			}

			char ch;
			
			// Read file bang stdin
			if (kernel->fileSystem->fileDes[id]->type == 2)
			{
				printf("Read file Console input.\n");
				DEBUG(dbgSys, "Read file Console input.\n");
				// Convert data in buffer to 0
				for (int i = 0; i < size; i++)
				{
					buffer[i] = 0;
				}

				// Use class SynchConsoleInput to get data from console
				int loop = 0;
				// char *filename = NULL;
				// kernel->synchConsoleIn;
				// SynchConsoleInput* conslInput = new SynchConsoleInput(NULL);
					DEBUG(dbgSys, "Vao Loop-----------------------------------------\n");
					DEBUG(dbgSys, "Nhap Buffer: ");
				while (loop < size)
				{
					// Create class SynchConsoleInput

					do
					{						
						ch = kernel->GetChar();
						
					} while (ch == EOF);

					if ((ch == '\012') || (ch == '\001'))
					{
						break;
					}
					else
					{
						buffer[loop] = ch;
						++loop;
					}
					
				}
					DEBUG(dbgSys, "Buffer: "<<buffer<<"\n");

					DEBUG(dbgSys, "Xong Loop-----------------------------------------\n");

				int size_buff = 0;
				if (ch == '\001')
				{
					size_buff = -1;
				}
				else
				{
					size_buff = loop;
				}
				DEBUG(dbgSys, " Byte read: "<<size_buff<<"\n");
				System2User(virtAddr, size_buff, buffer);

				kernel->machine->WriteRegister(2, size_buff);
				delete buffer;
				DEBUG(dbgSys, "Read file thanh cong\n");
				increasePC();
				return;
			}
			// truong hop Read file binh thuong
			int OldPosition = kernel->fileSystem->fileDes[id]->GetPosition();
			if (kernel->fileSystem->fileDes[id]->Read(buffer, size) > 0)
			{
				int NewPosition = kernel->fileSystem->fileDes[id]->GetPosition();
				
				
				System2User(virtAddr, NewPosition - OldPosition, buffer);
				kernel->machine->WriteRegister(2, NewPosition - OldPosition);

				DEBUG(dbgSys, "Read file thanh cong, So byte: "<<NewPosition - OldPosition<<", Buffer: "<<buffer<<"\n");
			}
			else
			{
				DEBUG(dbgSys, "Read file Rong\n");
				kernel->machine->WriteRegister(2, -1);
			}
			increasePC();
			DEBUG(dbgSys, "Tang bien PC "<< "\n");
			return;
			ASSERTNOTREACHED();
			break;
		}
		case SC_Write:
		{
			// Doc id cua file(OpenFileID)
			// int id = kernel->machine->ReadRegister(4);
			DEBUG(dbgSys, "Vao case SC_Write. ");
			DEBUG(dbgSys, "Write file thanh cong\n");
			// if (id >= 0 && id <= 19)
			// {
			// 	if (kernel->fileSystem->fileDes[id]) // neu co mo file
			// 	{
			// 		delete kernel->fileSystem->fileDes[id];
			// 		kernel->fileSystem->fileDes[id] = NULL;
			// 		kernel->machine->WriteRegister(2, 0);
			// 		DEBUG(dbgSys, "Dong file so " << id << " thanh cong "
			// 									  << "\n");
			// 	}
			// }
			kernel->machine->WriteRegister(2, -1);
			increasePC();
			DEBUG(dbgSys, "Tang bien PC "
							  << "\n");
			return;
			ASSERTNOTREACHED();
			break;
		}
		case SC_Seek:
		{
			// Doc id cua file(OpenFileID)
			// int id = kernel->machine->ReadRegister(4);
			DEBUG(dbgSys, "Vao case SC_Seek. \n");
			DEBUG(dbgSys, "Seek file thanh cong\n");

			// if (id >= 0 && id <= 19)
			// {
			// 	if (kernel->fileSystem->fileDes[id]) // neu co mo file
			// 	{
			// 		delete kernel->fileSystem->fileDes[id];
			// 		kernel->fileSystem->fileDes[id] = NULL;
			// 		kernel->machine->WriteRegister(2, 0);
			// 		DEBUG(dbgSys, "Dong file so " << id << " thanh cong "
			// 									  << "\n");
			// 	}
			// }
			kernel->machine->WriteRegister(2, -1);
			increasePC();
			DEBUG(dbgSys, "Tang bien PC "
							  << "\n");
			return;
			ASSERTNOTREACHED();
			break;
		}

		// network
		case SC_SocketTCP:
		{
			int sid = OpenSocket();
			if (sid != -1)
			{
				DEBUG(dbgSys, "Socked created. SocID: " << sid << "\n");
				kernel->machine->WriteRegister(2, sid);
			}
			else
			{
				DEBUG(dbgSys, "Failed. SocID: " << sid << "\n");
				kernel->machine->WriteRegister(2, -1);
			}

			increasePC();

			return;
			ASSERTNOTREACHED();
			break;
		}

		case SC_Connect:
		{
			int socket_id = kernel->machine->ReadRegister(4);
			int virtAddr = kernel->machine->ReadRegister(5);
			int port = kernel->machine->ReadRegister(6);

			char *ip = User2System(virtAddr, 16);

			result = ConnectToSocket(socket_id, ip, port);

			kernel->machine->WriteRegister(2, result);

			increasePC();
			delete ip;

			return;
			ASSERTNOTREACHED();
			break;
		}

		case SC_Send:
		{
			int socket_id = kernel->machine->ReadRegister(4);
			int virtAddr = kernel->machine->ReadRegister(5);
			int len = kernel->machine->ReadRegister(6);

			char *buffer = User2System(virtAddr, len + 1);

			char sockName[32];
			sprintf(sockName, "SOCKET_%d", kernel->hostName);
			result = SendToSocket(socket_id, buffer, len, sockName);
			kernel->machine->WriteRegister(2, result);

			increasePC();
			delete buffer;

			return;
			ASSERTNOTREACHED();
			break;
		}

		case SC_Receive:
		{
			int socket_id = kernel->machine->ReadRegister(4);
			int virtAddr = kernel->machine->ReadRegister(5);
			int len = kernel->machine->ReadRegister(6);

			char *buffer = new char[len + 1];
			result = ReadFromSocket(socket_id, buffer, len);
			System2User(virtAddr, len, buffer);
			kernel->machine->WriteRegister(2, result);

			increasePC();

			return;
			ASSERTNOTREACHED();
			break;
		}

		case SC_Close_soc:
		{
			int fd = kernel->machine->ReadRegister(4);

			if (fd != -1)
				kernel->machine->WriteRegister(2, 0);
			else
				kernel->machine->WriteRegister(2, -1);

			CloseSocket(fd);
			increasePC();

			return;
			ASSERTNOTREACHED();
			break;
		}

		default:
			cerr << "Unexpected system call " << type << "\n";
			break;
		}
		break;
	default:
		cerr << "Unexpected user mode exception" << (int)which << "\n";
		break;
	}
}
