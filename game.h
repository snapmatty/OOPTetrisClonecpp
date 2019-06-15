#ifndef GAME_H
#define GAME_H

#include "field.h"
#include <conio.h>

class Game
{
public:
												//Constructor:
	Game( const size_t HEIGHT, const size_t WIDTH );

												//Getters:
	Field& getField();							//getting the bucketfield where the game is held
	Tetromino* getActualBrick() const;			//getting the tetromino piece
	const size_t& getIntervall() const;			//getting the time interval for how fast the piece is falling
	const size_t& getHighscore() const;			//getting the score that the player is achieving during play-time

												//Methods:
	void action( int key );						//using the key on the keyboard to perform an action
	void movement();								//movement of the tetromino
	bool initializeNewBrick();					//initialization of a new tetromino piece
	bool running();									//running the game
	void print() const;							//printing the bucketfield
	void printNextBrick() const;				//printing the next tetropiece
	void updateHighscore( const size_t &lines );//updating the score
	void displayGameStats() const;				//printing the status of the performed game
	void setHighScore(const size_t& h);
	int h = highscore;

private:

	bool isGameOver;
	Field field;
	Tetromino *actualBrick;
	Tetromino *nextBrick;
	size_t intervall;							//the interval is expressed in miliseconds
	size_t highscore;

												//Method:
	Tetromino* getRandomBrick();				//gettig a random tetromino piece
	
};

#endif