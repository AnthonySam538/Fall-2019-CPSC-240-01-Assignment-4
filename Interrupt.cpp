#include <iostream>

using namespace std;

short printers = 0, floppyDrives = 1, ram = 16, thirtyTwo = 32;

int main()
{
	_asm
	{
		mov ax, 1100111010011100b;

		// check the size of the RAM
		mov bx, ram;
		shr ax, 2;
		and ax, 1b;
		jne Bit3Is0;
		add bx, ram;
	Bit3Is0:
		//do nothing
		shr ax, 1;
		and ax, 1b;
		jne Bit4Is0;
		add bx, thirtyTwo;
	Bit4Is0:
		//do nothing
		mov ram, bx;
	}

	cout << "Printers connected: " << printers << "\nFloppy drives: " << floppyDrives << "\nSize of the RAM: " << ram;

	return 0;
}