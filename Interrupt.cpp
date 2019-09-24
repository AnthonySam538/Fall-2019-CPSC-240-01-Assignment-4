#include <iostream>

using namespace std;

short ram = 1, floppyDrives = 1, printers = 0;

//void readBits()
//{
//	_asm
//	{
//		mov cx, ax; //store a copy of the data in cx to avoid overwriting ax when using "and"
//		and cx, one; //cx = ax & 0000 0000 0000 0001
//		mov printers, cx;
//		cmp cx, 0;
//		je BitIs0; //skips over the next line
//		inc bx; //increment by 1
//	BitIs0:
//		shr ax, 1;
//		mov cx, ax;
//		and cx, one;
//		cmp cx, 0;
//		je NextBitIs0;
//		add bx, 2; //increment by 2
//	NextBitIs0:
//	}
//}

int main()
{
	_asm
	{
		mov ax, 1100111010011100b; //store the data in ax

		// 1. check the size of the RAM using bits 3 & 4
		mov bx, ram; //move ram into bx for modification
		shr ax, 2; //remove the last 2 digits
		mov cx, ax; //store a copy of the data in cx to avoid overwriting ax when using "and"
		and cx, 1; //cx = ax & 0000 0000 0000 0001
		cmp cx, 0;
		je Bit3Is0; //skips over the next line
		inc bx; //increment by 1
	Bit3Is0:
		shr ax, 1;
		mov cx, ax;
		and cx, 1;
		cmp cx, 0;
		je Bit4Is0;
		add bx, 2; //increment by 2
	Bit4Is0:
		mov ram, bx;

		// 2. check the number of floppy drives using bits 7 & 8
		mov bx, floppyDrives; //move floppyDrives into bx for modification
		shr ax, 3; //remove the last 3 digits
		mov cx, ax; //store a copy of the data in cx to avoid overwriting ax when using "and"
		and cx, 1; //cx = ax & 0000 0000 0000 0001
		cmp cx, 0;
		je Bit7Is0; //skips over the next line
		inc bx; //increment by 1
	Bit7Is0:
		shr ax, 1;
		mov cx, ax;
		and cx, 1;
		cmp cx, 0;
		je Bit8Is0;
		add bx, 2; //increment by 2
	Bit8Is0:
		mov floppyDrives, bx;

		// 3. check the amount of printers connected using bits 15 & 16
		mov bx, printers; //move printers into bx for modification
		shr ax, 7; //remove the last 7 digits
		mov cx, ax; //store a copy of the data in cx to avoid overwriting ax when using "and"
		and cx, 1; //cx = ax & 0000 0000 0000 0001
		cmp cx, 0;
		je Bit1Is0; //skips over the next line
		inc bx; //increment by 1
	Bit1Is0:
		shr ax, 1;
		mov cx, ax;
		and cx, 1;
		cmp cx, 0;
		je Bit16Is0;
		add bx, 2; //increment by 2
	Bit16Is0:
		mov printers, bx;
	}

	cout << "Printers connected: " << printers << "\nFloppy drives: " << floppyDrives << "\nSize of the RAM: " << ram*16;

	return 0;
}