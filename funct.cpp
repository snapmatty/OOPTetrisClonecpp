#include <Windows.h>

void clrScreen()    //method resposible for the clearence of the screen during the playtime
{
	HANDLE hOut; 
	COORD position;

	position.X = 0;
	position.Y = 0;

	hOut = GetStdHandle( STD_OUTPUT_HANDLE );		//more on the GetStdHandle: 
													//The handles returned by this function can be used by various programs, which need to read data from or write data to the console.
													//When a console is created a standard handle input is a handle to the input bufer of the console and the standard handle of output is an active buffer to the creen of the console. 
	SetConsoleCursorPosition( hOut, position );		//These handles are used by functions (like in our case) that need access to the console bufors.
}
													/*SetconsoleCursorPosition is a function which in a manner sets the position of the cursor in our console*/
				
					