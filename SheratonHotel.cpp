#include <iostream>

using namespace std;

const short AX_REGISTER = 37132; // 1001 0001 0000 1100 in binary
short current, currentFloor = 16, n;

void Base2()
{
	short x = 1 << 15, t;
	n = AX_REGISTER;

	for (int i = 1; i <= 16; ++i)
	{
		t = n & x;

		if (t == 0)
			cout << 0;
		else
			cout << 1;

		if (i % 4 == 0)
			cout << ' ';

		n = n << 1;
	}
	cout << endl;
}

void displayCurrentFloor()
{
	cout << ' ' << currentFloor;
}

int main()
{
	cout << "AX = ";
	Base2();
	cout << "\nThe elevator will stop at these floors:";

	//Determine and list the floors the elevator will stop at in assembly
	_asm
	{
	ForLoop:
		//If we've gone through all 16 floors, exit the loop
		cmp currentFloor, 1;
		jl ExitLoop;

		mov bx, 1; //bx will be left-shifted by cx
		mov cx, currentFloor; //currentFloor controls the for loop & cx controls the nested for loop

		//Shift over bx for later use with and
	NestedForLoop:
		cmp cx, 1;
		je ExitNestedForLoop;

		shl bx, 1;

		dec cx;
		jmp NestedForLoop;
	ExitNestedForLoop:

		//and bx with ax, then use it to determine if we're stopping at this floor
		and bx, AX_REGISTER; //On the first run, bx = 1000000000000000 & 1001 0001 0000 1100 = 1 != 0
		cmp bx, 0;
		je FloorIs0;
		call displayCurrentFloor;
	FloorIs0:
		dec currentFloor;
		jmp ForLoop;

	ExitLoop:
	}
	
	return 0;
}