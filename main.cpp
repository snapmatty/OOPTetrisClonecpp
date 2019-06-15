#include <Windows.h>
#include "funct.h"
#include "game.h"
#include <cstdlib>
#include <conio.h>
#include <iostream>
using std::cout;
using std::endl;
#include <time.h>
#include <fstream>
using namespace std;

int main()
{	
	std::cout << "                            Tetris clone created by: Mateusz Drygiel for the OOP Lab of 2019, group of Thursday." << std::endl;

	Tetromino ted( Tetromino::T );
	Game tetris( 18, 12 );         //the height and width of our playing field

	tetris.initializeNewBrick();                                //initialization of the brick, bucketfield and the printing/spawning of the elements
	tetris.getField().drawBrick( tetris.getActualBrick() );
	tetris.print();
	 
	

	int key;
	char inputs[] = { 's', 'S', 'x', 'X','b','B'};



	Field &feld = tetris.getField();
	int i=0;

	size_t actualTime = GetTickCount();								//more on the GetTickCount: retrieves the number of milliseconds that have elapsed since the system was started, but only until around 49 days. 
																	//it can be replaced by the GetTickCount64 for more longevity but since this is a short game I decided to stick with this one instead.
	long actualPlaytime = static_cast<size_t>( time( nullptr ) );   //nullptr denotes the pointer literal. Static Cast: simplest type of cast which can be used. It is a compile time cast.It does things like implicit conversions between types (such as int to float, or pointer to void*), and it can also call explicit conversion functions (or implicit ones).

	while( tetris.running() )                                           //Main game loop:
	{	
		
		if( _kbhit() )												//_kbhit  checks if there is something in the input buffer, if there is nothing it retruns false.
		{
			key = _getch();											//_getch returns the read character.

			tetris.action( key );												
			key = ' ';

			feld.clear( tetris.getActualBrick()->getFormat() );      
			feld.drawBrick( tetris.getActualBrick() );
			clrScreen();
			tetris.print();

	

		}

		++i;

		bool bump = false;

		if( bump || actualTime + tetris.getIntervall() < GetTickCount() )
		{
			

			actualTime = GetTickCount();

			feld.setCursor( feld.getCursor().getX()+1, feld.getCursor().getY() );
			
			if( feld.isFree( tetris.getActualBrick() ) )                              //as long as the condition of a free bucketfield is maintained
			{		
				bump = false;

				feld.clear( tetris.getActualBrick()->getFormat() );
				feld.drawBrick( tetris.getActualBrick() );
				i=0;
				clrScreen();		
				tetris.print();
			}
			else																			//after the game has been paused and we resume we would like to continue from the previous state, 
			{																				////with the implementation of the "else" portion we are able to play where we left before pausing.
																							//all the previous postiions of the cursor, the tetropieces on the bucketfield as well as the 
																							//previous functions like clrScreen and printing/spawning the next tetropiece are still available.
				bump = true;

				feld.setCursor( feld.getCursor().getX()-1, feld.getCursor().getY() );
				feld.drawBrick( tetris.getActualBrick(), 'X' );			

				size_t lines = feld.clearCompleteLines();
				tetris.updateHighscore( lines );

				tetris.initializeNewBrick();
				clrScreen();		
				tetris.print();
			}

			std::cout << std::endl;
			std::cout << "Next Tetromino:";                     //information for the player which block is going to spawn next
			std::cout << std::endl;
			tetris.printNextBrick();

			std::cout << std::endl;								//information for the player what is his/her score
			std::cout << "Your score:\t";
			std::cout << tetris.getHighscore() << std::endl;
			
		}
		
	}

	system( "CLS" );
	ofstream myfile;
	myfile.open("logging.txt");
	if (myfile.is_open())
	{
			myfile << "THE PLAYER STATISTICS: \n";
			myfile <<"Playtime:  "<< static_cast<size_t>(time(nullptr)) - actualPlaytime << "\n";
			myfile << "Highscore:  " << tetris.getHighscore() << "\n";
			myfile << "Speed achieved (interval):  " << tetris.getIntervall();
		

	}
	else cout << "Unable to open file";
	myfile.close();

	std::cout << "This game has been created as a part of the OOP labs." << std::endl;
	std::cout << "Game created by: Mateusz Drygiel" << std::endl;

	tetris.displayGameStats();
	cout << "Playtime: " << static_cast<size_t>( time( nullptr ) ) - actualPlaytime << " Sec" << endl;    
	
	system( "PAUSE" );

	
	return 0;
}