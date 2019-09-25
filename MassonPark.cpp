#include <iostream>
#include <string>

using namespace std;

short n, current, currentSprinkler = 16, activeSprinklers = 16, AX_REGISTER = 0x6A2F; //0110 1010 0010 1111 in binary, 27183 in decimal

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
}

void displayCurrentSprinkler()
{
	cout << ' ' << currentSprinkler;
}

int main()
{
	cout << "AX = ";
	Base2();
	cout << "\nDefective sprinklers:";

	//list the defective sprinklers and display amount of active sprinklers in assembly
	_asm
	{
	ForLoop:
		//If we've gone through all the sprinklers, exit the loop
		cmp currentSprinkler, 1;
		jl ExitLoop;

		mov bx, 1; //will ultimately contain a 1 or 0
		mov cx, currentSprinkler; //used to left-shift bx

		//left-shift bx for later use with and
	NestedForLoop:
		cmp cx, 1;
		je ExitNestedForLoop;

		shl bx, 1;

		dec cx;
		jmp NestedForLoop;
	ExitNestedForLoop:

		//and bx, then use it to determine the state of the sprinkler
		and bx, AX_REGISTER;
		cmp bx, 0;
		jne CurrentIsNot0;
		dec activeSprinklers;
		call displayCurrentSprinkler;
	CurrentIsNot0:
		dec currentSprinkler;
		jmp ForLoop;
	ExitLoop:
	}

	cout << endl << activeSprinklers << " sprinklers are ON";
	
	return 0;
}