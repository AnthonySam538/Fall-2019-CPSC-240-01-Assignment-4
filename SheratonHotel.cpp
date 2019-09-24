#include <iostream>

using namespace std;

short current, currentFloor = 16;

void displayCurrent()
{
	cout << "Current is: " << current << endl;
}

int main()
{
	_asm
	{
		mov cx, 1001000100001100b;

	WhileLoop:
		cmp cx, 0;
		je ExitLoop;

		mov current, cx;
		call displayCurrent;

		shl cx, 1;
		dec currentFloor;
		jmp WhileLoop;

	ExitLoop:
	}
	
	return 0;
}