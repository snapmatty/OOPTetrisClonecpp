#ifndef FIELD_H
#define FIELD_H

#include "tetromino.h"

class Field
{
public:

	struct Point
	{	
		unsigned short x;
		unsigned short y;

		Point() : x(0), y(0){}

		unsigned short getX() const //getter for the X position 
		{
			return this->x;
		}

		unsigned short getY() const		//getter for the Y position
		{
			return this->y;
		}

		void setX( const unsigned short x )		//setter for the X position
		{
			this->x = x;
		}

		void setY( const unsigned short y )	//setter for the Y position
		{
			this->y = y;
		}
	};

														// Construcor
	Field( const size_t HEIGHT, const size_t WIDTH );

														//Getters:
	size_t getting_Hi() const; //getting the height of our bucketfield
	size_t getting_Wi() const;	//getting the width of our bucketfield
	const Point& getCursor() const;	//getting the cursor for our bucket field

														//Methods:
	void clear( const char brickform = 'A' );
	void setCursor( const unsigned short x, const unsigned short y ); //setting the position of the cursor
	void print() const;												  //printing the field
	bool isFree( const Tetromino *brick );							  //checking if a certain position on the field is free and there can be a block placed
	bool drawBrick( const Tetromino *brick, const char brickform = 'A' );//drawing the tetromino bricks on the bucketboard
	size_t clearCompleteLines();									  //clearing the completed lines once the row is "filled"


														// Destructor:
	~Field();

private:

	Point cursor;
	char **field;
	const size_t HEIGHT;
	const size_t WIDTH;
};

#endif