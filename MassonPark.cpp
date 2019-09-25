#include <iostream>
#include <string>

using namespace std;

const short AX_REGISTER = 0x6A2F; //27183 in decimal
short current, currentSprinkler = 16, activeSprinklers = 16;

//void Base2()
//{
//	short n = 1 << 15, t;
//	n = AX_REGISTER;
//
//	for (int i = 1; i <= 16; ++i)
//	{
//		t = n & x;
//
//		if (t == 0)
//			cout << 0;
//		else
//			cout << 1;
//
//		if (i % 4 == 0)
//			cout << ' ';
//		n = n << 1;
//	}
//	cout << endl;
//}

void displayCurrent()
{
	if (!(currentSprinkler % 4))
		cout << ' ';

	cout << current;
}

void displayCurrentSprinkler()
{
	cout << ' ' << currentSprinkler;
}

int main()
{

	cout << "AX =";

	//display the AX register and the amount of activeSprinklers in assembly
	_asm
	{
	ForLoop:
		cmp currentSprinkler, 1;
		jl ExitLoop;

		mov ax, AX_REGISTER; //a copy of AX_REGISTER (calling functions messes with registers)
		mov bx, 1; //will ultimately contain a 1 or 0
		mov cx, currentSprinkler; //used to left-shift bx

	NestedForLoop:
		cmp cx, 1;
		je ExitNestedForLoop;

		shl bx, 1;

		dec cx;
		jmp NestedForLoop;
	ExitNestedForLoop:

		and bx, ax;
		cmp bx, 0;
		je CurrentIs0;
		mov current, 1;
		jmp DisplayCurrent;
	CurrentIs0:
		mov current, 0;
		dec activeSprinklers;
	DisplayCurrent:
		call displayCurrent;
		dec currentSprinkler;
		jmp ForLoop;
	ExitLoop:
	}
	cout << endl << activeSprinklers << " sprinklers are ON\nDefective sprinklers:";

	//list the defective sprinklers in assembly
	_asm
	{
		mov currentSprinkler, 16;
	ForLoop2:
		cmp currentSprinkler, 1;
		jl ExitLoop2;

		mov ax, AX_REGISTER;
		mov bx, 1;
		mov cx, currentSprinkler;

	NestedForLoop2:
		cmp cx, 1;
		je ExitNestedForLoop2;

		shl bx, 1;

		dec cx;
		jmp NestedForLoop2;
	ExitNestedForLoop2:

		and bx, AX_REGISTER;
		cmp bx, 0;
		jne SkipOver;
		call displayCurrentSprinkler;
	SkipOver:
		dec currentSprinkler;
		jmp ForLoop2;
	ExitLoop2:
	}

	return 0;
}