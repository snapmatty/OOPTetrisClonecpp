#include <Windows.h>
#include "game.h"
#include "field.h"
#include <time.h>
#include <fstream>
#include <iostream>
using namespace std;
using std::cout;
using std::endl;

														//Constructor:
Game::Game( const size_t HEIGHT, const size_t WIDTH )
:	isGameOver( false ),
	field( HEIGHT, WIDTH ),
	actualBrick( nullptr ),
	nextBrick( nullptr ),
	intervall( 900 ),
	highscore( 0 )
{
	srand( static_cast<size_t>( time(NULL) ) );
}

														//Getters:
Field& Game::getField()									//getting the bucketfield
{
	return this->field;
}

Tetromino* Game::getActualBrick() const					//getting the tetromino brick
{
	return this->actualBrick;
}

const size_t& Game::getIntervall() const				//getting the time interval
{
	return this->intervall;
}

const size_t& Game::getHighscore() const				//getting the score
{
	return this->highscore;
}



														//Methods:
void Game::action( int key )
{
	switch( key )
	{
		case 224:										 //whenever an arrow key is pressed the function move takes care of the input on the keyboard
			this->movement();
			break;

		case 'x':
		case 'X':																						
			this->actualBrick->rotate( 'x' );
			if( !this->field.isFree( this->actualBrick ) )//when the "x" button is pressed it causes the piece to rotate
			{
				this->actualBrick->rotate( 's' );
			}
			break;
			
																								//the difference between the rotation is that one is clockwise the other is counterclockwise
		case 's':																							//with the addition of the two possible rotations the bug of "wall breaking" has been resolved.
		case 'S':
			this->actualBrick->rotate('s');
			if (!this->field.isFree(this->actualBrick)) //when the "s" button is pressed it causes the piece to rotate
			{
				this->actualBrick->rotate('x');
			}
			break;



		case 'b':
		case 'B':	//whenever the 'B' is pressed the game is going to freeze giving the player a pause
			system( "CLS" );


			cout << "PAUSE" << endl;
			cout << endl;

			cout << "THE GAME HAS BEEN PAUSED, TO CONTINUE, PLEASE PRESS ANY KEY!" << endl;

			system( "PAUSE" );
			system( "CLS" );

			
	}
}




void Game::movement()
{
	int key = _getch();

	switch( key )
	{
	case 75:																										//moving left
		this->field.setCursor( this->field.getCursor().getX(), this->field.getCursor().getY() - 1 );     
		if (!this->field.isFree(this->actualBrick))																	//
		{
			this->field.setCursor(this->field.getCursor().getX(), this->field.getCursor().getY() + 1);				//When the field is indeed free we can be moving left/right, but when 
																													//the field is occupied or there is a wall of the bucket
																													//then we are unable to perform this action.
		}
		break;

	case 77:																										//moving right
		this->field.setCursor( this->field.getCursor().getX(), this->field.getCursor().getY() + 1 );
		if( !this->field.isFree( this->actualBrick ) )
		{
			this->field.setCursor( this->field.getCursor().getX(), this->field.getCursor().getY() - 1 );
		}
		break;

	case 80:																										//moving down
		this->field.setCursor( this->field.getCursor().getX() + 1, this->field.getCursor().getY() );
		if( !this->field.isFree( this->actualBrick ) )
		{
			this->field.setCursor( this->field.getCursor().getX() - 1 , this->field.getCursor().getY() );
		}
		break;
	}
}

bool Game::initializeNewBrick()
{																		//initializiation of the new tetropiece
	if( this->actualBrick != nullptr )
		delete this->actualBrick;

	this->field.setCursor( 0, ( this->field.getting_Wi() / 2 ) - 1 ); 

	if( this->nextBrick != nullptr )
	{
		this->actualBrick = this->nextBrick;
	}
	else
	{
		this->actualBrick = getRandomBrick();
	}
	this->nextBrick = getRandomBrick();

	if( this->field.isFree( this->actualBrick ) )
	{
		return true;
	}
	else
	{
		this->isGameOver = true;				//when the gameover is true the bricks are not initialized anymore 
		return false;
	}
}

bool Game::running()														//running the game until it hits game over
{
	return !this->isGameOver;
}

void Game::print() const												//printing the field
{
	this->field.print();
}

void Game::printNextBrick() const										//printing the next tetropiece
{
	if( this->nextBrick != nullptr )
	{
		this->nextBrick->print();
	}
}

void Game::updateHighscore( const size_t &lines )						//updating the score
{
	switch( lines )
	{
	case 1: this->highscore += 100;
		break;
	case 2: this->highscore += 200;
		break;
	case 3: this->highscore += 300;
		break;
	case 4: this->highscore += 400;										//whenever we have one line or multiple lines (max i did was 8) the highscore/current score of the player is updated depending on the 
		break;															//amount of lines deleted, if its one then only 100+, if its 2 lines then 200 and so on...
	case 5: this->highscore += 500;
		break;
	case 6: this->highscore += 600;
		break;
	case 7: this->highscore += 700;					
		break;
	case 8: this->highscore += 800;
		break;

	}


	if( this->highscore > 5000 )
	{
		this->intervall = 300;
	}
	else if (this->highscore > 2000)
	{
		this->intervall = 350;
	}
	else if( this->highscore > 1500 )									//this is our "interval speed increaser", depending on our current amount of points the speed of falling blocks is increasing.
	{																	//of course this can be changed at will, I chose to have 6 different intervals, with the amount of points increasing...
		this->intervall = 450;											//(the interval of course is in miliseconds as mentioned before.
	}
	else if( this->highscore > 1000 )
	{
		this->intervall = 550;
	}
	else if( this->highscore > 500 )
	{
		this->intervall = 600;
	}
	else if( this->highscore > 300 )
	{
		this->intervall = 700;
	}
}

void Game::displayGameStats() const  //printing the score status of game
{
	cout << "Highscore: " << this->highscore << endl;		//the highscore attained
	cout << "Speed achieved: " << this->intervall << endl;	//the speed of the tetrominos that are falling down 
}


Tetromino* Game::getRandomBrick()    //getting a random tetromino piece onto the game
{
	return new Tetromino( static_cast<Tetromino::TETROMINO>( rand() % 7 ) );    //it chooses one of 7 pieces at random
}