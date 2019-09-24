#include <iostream>
#include <string>

using namespace std;

unsigned short current = 78, currentIndex = 16, activeSprinklers = 0;
unsigned short a, b, c, d;
string defectiveSprinklers = " sprinklers are ON\nDefective sprinklers:";

void displayCurrent()
{
	if (!(currentIndex % 4))
		cout << ' ';

	cout << current;
}

void defectiveSprinkler()
{
	defectiveSprinklers += ' ' + currentIndex;
}

int main()
{
	//_asm
	//{
	//	mov ax, 54366;
	//	mov a, ax;
	//	shl ax, 1;
	//	mov b, ax;
	//	shl ax, 1;
	//	mov c, ax;
	//	shl ax, 1;
	//	mov d, ax;
	//}
	//cout << a << endl << b << endl << c << endl << d << endl;


	_asm
	{
		mov ax, 6A2Fh;

	ForLoop:
		cmp currentIndex, 0;
		je ExitLoop;

		mov bx, 1000000000000000b;
		and bx, ax;
		cmp bx, 0;
		je CurrentIs0;
		mov current, 1;
		jmp DisplayCurrent;
	CurrentIs0:
		mov current, 0;
	DisplayCurrent:
		call displayCurrent;
		shl ax, 1;

		dec currentIndex;
		jmp ForLoop;
	ExitLoop:

	}



	/*cout << "AX =";
	_asm
	{
		mov ax, 6A2Fh;

	ForLoop:
		cmp currentIndex, 0;
		je ExitLoop;

		mov bx, 1000000000000000b;
		and bx, ax;
		cmp bx, 0;
		je currentIs0;
		mov current, 1;
		jmp DisplayCurrent;
	currentIs0:
		mov current, 0;
		call defectiveSprinkler;
	DisplayCurrent:
		call displayCurrent;

		shl ax, 1;
		dec currentIndex;
		jmp ForLoop;
	ExitLoop:

	}

	cout << '\n' << activeSprinklers << defectiveSprinklers;*/

	return 0;
}