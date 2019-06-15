#include "field.h"

#include <iostream>
using std::endl;
using std::cout;

																	//Construcor:
Field::Field( const size_t HEIGHT, const size_t WIDTH )
: HEIGHT( HEIGHT ),
  WIDTH( WIDTH ),
  field( nullptr )
{
	this->field = new char*[this->HEIGHT];				

	for( size_t i=0; i<this->HEIGHT; i++ )
	{																//creating the empty space in our bucket field
		this->field[i] = new char[this->WIDTH];

		for( size_t j=0; j<this->WIDTH; j++ )
			this->field[i][j] = ' ';
	}

	for( size_t i=0; i<this->HEIGHT-1; i++ )						//creating the diagonal border of the bucket field aka "the walls"
	{
		this->field[i][0] = '|';
		this->field[i][this->WIDTH-1] = '|';
	}

	for( size_t i=0; i<this->WIDTH; i++ )							//creating the "floor" of our bucket field
		this->field[this->HEIGHT-1][i] = '-';
}

																	//Getters:
size_t Field::getting_Hi() const
{
	return this->HEIGHT;											//getting the height of our bucketfield
}

size_t Field::getting_Wi() const										//getting the width of our bucketfield
{
	return this->WIDTH;
}

const Field::Point& Field::getCursor() const						//getting the cursor 
{
	return this->cursor;
}

																	//Methods:
void Field::clear( const char format )											
{
	for( size_t i=0; i<this->HEIGHT; i++ )
	{															 
		for( size_t j=0; j<this->WIDTH; j++ )
		{
			if( this->field[i][j] == format )
				this->field[i][j] = ' ';
		}
	}
}


void Field::setCursor( const unsigned short x, const unsigned short y )
{
	this->cursor.setX( x );                                        //setting the position of our cursor in the fieldbucket
	this->cursor.setY( y );
}

void Field::print() const
{
	for( size_t i=0; i<this->HEIGHT; i++ )
	{																		//printing the field
		for( size_t j=0; j<this->WIDTH; j++ )
			cout << this->field[i][j];

		cout << endl;
	}
}

bool Field::isFree( const Tetromino *brick )											
{
	const char **tmp = brick->getActualBrickTemplate();

	const size_t x = this->cursor.getX();
	const size_t y = this->cursor.getY();

	if( x < 0 || x >= this->HEIGHT || y < 0 || y >= this->WIDTH )			//if the x and y coordinates of the brick are exceeding the size of bucket it returns false
		return false;

	for( size_t i=0; i<4; i++ )
	{
		for( size_t j=0; j<4; j++ )
		{
			if( tmp[i][j] == brick->getFormat() )                         //it also returns false when we have the placed piece marked with "X" and meet the border and floor of our bucketfield "|" and "-"
			{
				if( this->field[x+i][y+j] == 'X'
					|| this->field[x+i][y+j] == '|'
					|| this->field[x+i][y+j] == '-' )	
					return false;
			}
		}
	}
	return true;
}

bool Field::drawBrick( const Tetromino *brick, const char brickform )				//drawing the tetromino piece spawned
{
	const char **tmp = brick->getActualBrickTemplate();  
	
	for( size_t i=0; i<4; i++ )
	{
		for( size_t j=0; j<4; j++ )
		{
			if( tmp[i][j] == brick->getFormat() )
				this->field[this->cursor.getX()+i][this->cursor.getY()+j] = brickform;
		}
	}

	return true;
}

size_t Field::clearCompleteLines()  //after we complete one full line on the playing field it gets deleted/cleared by the game
{
	size_t lines = 0;				//more on the size_t:  unsigned integer type, can store the maximum size of a theoretically possible object of any type (including array),

	vector<int> connectedLines;    

	for( int i = this->HEIGHT - 2; i>=0; i-- )
	{
		if( this->field[i][1] == 'X' )                   //when the row is full of the "X" symbols, meaning that we indeed have a full line then 'found' is set to true thus performing the push_back, deleting the complete line
		{
			bool found = true;

			for( int j = 1; j < this->WIDTH - 1; j++ )				
			{
				if( this->field[i][j] != 'X' )
				{												//if the row in the field is however not filled with the "X" then it means that there is no completed line, thus making 'found' false, there i no need to delete the line
					found = false;
					break;
				}
			}

			if( found )
			{
				connectedLines.push_back( i );         //more on the push_back: increases the container size by one, which causes an automatic reallocation of the allocated storage space only if the new vector size surpasses the current vector capacity.

				
			}
		}
	}

	if( connectedLines.size() < 1 )
	{
		return 0;										
	}
	else
	{
		lines = connectedLines.size();                                   

		for( int i = connectedLines.size() - 1; i >= 0; i-- )
		{
			
			char **tmp = new char*[this->HEIGHT];					//allocating the memory for a new field
			for( int j = 0; j < this->HEIGHT; j++ )
			{
				tmp[j] = new char[this->WIDTH];
			}
			

			for( int j = this->HEIGHT - 1; j > connectedLines[i]; j-- )
			{
				for( int k = 0; k < this->WIDTH; k++ )
				{
					tmp[j][k] = this->field[j][k];
				}
			}
			for( int j = connectedLines[i] - 1; j >= 0; j-- )
			{
				for( int k = 0; k < this->WIDTH; k++ )
				{
					tmp[j + 1][k] = this->field[j][k];
				}
			}
			for( int i = 1; i < this->WIDTH - 1; i++ )
			{
				tmp[0][i] = ' ';
			}
			tmp[0][0] = '|';
			tmp[0][this->WIDTH - 1] = '|';

			
			char **del = this->field;					//switching the fields
			this->field = tmp;

			for( int i = 0; i < this->WIDTH; i++ )
			{
				delete [] ( del[i] );                //deleting 
			}
			delete [] del;
		}
	}

	return lines;
}


													// Destructor:
Field::~Field()
{
	for( size_t i=0; i<this->HEIGHT; i++ )
		delete [] this->field[i];

	delete [] this->field;
}