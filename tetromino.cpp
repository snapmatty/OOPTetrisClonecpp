#include "tetromino.h"
#include <iostream>
using std::endl;
using std::cout;

																						//Construcor:
Tetromino::Tetromino( const Tetromino::TETROMINO type, char brickform, char emptyspace )			//the type of tetroblock/the format of the brickform/ the empty space field from the 4x4 array
: brickform( brickform),																			//the shape of every tetromino is determined by the brickform, it is the "filled" block in the 4x4 array 
  emptyspace( emptyspace ),																			//emptyspace is the empty part of the 4x4 array of  tetrominos
  type( type ),																						//the type is obviously the type of the brick (it's initial and final shape for eg. "staright line-shape", "square shape" etc).
  actualBrickTemplate( nullptr )																	//the template of each brick of the tetromino
{
	this->brickFormTemplate.resize( 0 );

	switch( type )
	{
		case I:																							//each tetropiece is stored ina a 4x4 matrix, to quickly solve the rotation part of each piece different placements for each tetropiece have been made 
			{																							//in each matrix, for example the "I" shaped tetromino when rotating it's actually switching between "lying" and "standing" which in turn means
				const char t1[4][4] = {																	//that we have only two matrices for it's movement on the fieldbucket
					this->emptyspace, this->brickform, this->emptyspace, this->emptyspace,
					this->emptyspace, this->brickform, this->emptyspace, this->emptyspace,			//this method is again used for the corresponding pieces accordingly and with taken into account their ability of rotation, if some shape can have 4 different
					this->emptyspace, this->brickform, this->emptyspace, this->emptyspace,			//positions when rotating then it has 4 matrices and so on.
					this->emptyspace, this->brickform, this->emptyspace, this->emptyspace			//depending on the rotation the program selects the correct matrix and the piece then is switched on the screen to another postition of rotation.
				};
				this->generatingTemplate( t1 );   //generating the template of a tetropiece, this follows for each iteration and each segment of tetrominos
		
				const char t2[4][4] = {
					this->emptyspace, this->emptyspace, this->emptyspace, this->emptyspace,
					this->brickform, this->brickform, this->brickform, this->brickform,
					this->emptyspace, this->emptyspace, this->emptyspace, this->emptyspace,
					this->emptyspace, this->emptyspace, this->emptyspace, this->emptyspace
				};
				this->generatingTemplate( t2 );
			}
			break;

		case J:
		{	
				const char t1[4][4] = {
					this->emptyspace,	this->brickform,		this->emptyspace,	this->emptyspace,
					this->emptyspace,	this->brickform,		this->emptyspace,	this->emptyspace,                                //the reverse L shaped tetromino
					this->brickform,		this->brickform,		this->emptyspace,	this->emptyspace,
					this->emptyspace,	this->emptyspace,	this->emptyspace,	this->emptyspace
				};
				this->generatingTemplate( t1 );

				const char t2[4][4] = {
					this->brickform,		this->emptyspace,	this->emptyspace,	this->emptyspace,
					this->brickform,		this->brickform,		this->brickform,		this->emptyspace,
					this->emptyspace,	this->emptyspace,	this->emptyspace,	this->emptyspace,
					this->emptyspace,	this->emptyspace,	this->emptyspace,	this->emptyspace
				};
				this->generatingTemplate( t2 );

				const char t3[4][4] = {
					this->emptyspace,	this->brickform,		this->brickform,		this->emptyspace,
					this->emptyspace,	this->brickform,		this->emptyspace,	this->emptyspace,
					this->emptyspace,	this->brickform,		this->emptyspace,	this->emptyspace,
					this->emptyspace,	this->emptyspace,	this->emptyspace,	this->emptyspace
				};
				this->generatingTemplate( t3 );

				const char t4[4][4] = {
					this->emptyspace,	this->emptyspace,	this->emptyspace,	this->emptyspace,
					this->brickform,		this->brickform,		this->brickform,		this->emptyspace,
					this->emptyspace,	this->emptyspace,	this->brickform,		this->emptyspace,
					this->emptyspace,	this->emptyspace,	this->emptyspace,	this->emptyspace
				};
				this->generatingTemplate( t4 );
			}
			break;

		case L:
			{
				const char t1[4][4] = {
					this->emptyspace,	this->brickform,		this->emptyspace,	this->emptyspace,
					this->emptyspace,	this->brickform,		this->emptyspace,	this->emptyspace,
					this->emptyspace,	this->brickform,		this->brickform,		this->emptyspace,						//the L shaped tetromino
					this->emptyspace,	this->emptyspace,	this->emptyspace,	this->emptyspace
				};
				this->generatingTemplate( t1 );

				const char t2[4][4] = {
					this->emptyspace,	this->emptyspace,	this->emptyspace,	this->emptyspace,
					this->brickform,		this->brickform,		this->brickform,		this->emptyspace,
					this->brickform,		this->emptyspace,	this->emptyspace,	this->emptyspace,
					this->emptyspace,	this->emptyspace,	this->emptyspace,	this->emptyspace
				};
				this->generatingTemplate( t2 );

				const char t3[4][4] = {
					this->brickform,		this->brickform,		this->emptyspace,	this->emptyspace,
					this->emptyspace,	this->brickform,		this->emptyspace,	this->emptyspace,
					this->emptyspace,	this->brickform,		this->emptyspace,	this->emptyspace,
					this->emptyspace,	this->emptyspace,	this->emptyspace,	this->emptyspace
				};
				this->generatingTemplate( t3 );

				const char t4[4][4] = {
					this->emptyspace,	this->emptyspace,	this->brickform,		this->emptyspace,
					this->brickform,		this->brickform,		this->brickform,		this->emptyspace,
					this->emptyspace,	this->emptyspace,	this->emptyspace,	this->emptyspace,
					this->emptyspace,	this->emptyspace,	this->emptyspace,	this->emptyspace
				};
				this->generatingTemplate( t4 );
			}
			break;

		case O:
			{
				const char t1[4][4] = {
					this->emptyspace,	this->emptyspace,	this->emptyspace,	this->emptyspace,
					this->emptyspace,	this->brickform,		this->brickform,		this->emptyspace,
					this->emptyspace,	this->brickform,		this->brickform,		this->emptyspace,   //the squareshape tetromino, as you can see it has only one way of rotation thus it has only 1 matrix 
					this->emptyspace,	this->emptyspace,	this->emptyspace,	this->emptyspace
				};
				this->generatingTemplate( t1 );
			}
			break;

		case S:
			{
				const char t1[4][4] = {
					this->emptyspace,	this->emptyspace,	this->emptyspace,	this->emptyspace,
					this->emptyspace,	this->brickform,		this->brickform,		this->emptyspace,				//the "staircase" shaped tetromino
					this->brickform,		this->brickform,		this->emptyspace,	this->emptyspace,
					this->emptyspace,	this->emptyspace,	this->emptyspace,	this->emptyspace
				};
				this->generatingTemplate( t1 );

				const char t2[4][4] = {
					this->brickform,		this->emptyspace,	this->emptyspace,	this->emptyspace,
					this->brickform,		this->brickform,		this->emptyspace,	this->emptyspace,
					this->emptyspace,	this->brickform,		this->emptyspace,	this->emptyspace,
					this->emptyspace,	this->emptyspace,	this->emptyspace,	this->emptyspace
				};
				this->generatingTemplate( t2 );
			}
			break;

		case Z:
		{
			const char t1[4][4] = {
				this->emptyspace,	this->emptyspace,	this->emptyspace,	this->emptyspace,
				this->brickform,		this->brickform,		this->emptyspace,	this->emptyspace,
				this->emptyspace,	this->brickform,		this->brickform,		this->emptyspace,				//the reversed "staircase" shaped tetromino
				this->emptyspace,	this->emptyspace,	this->emptyspace,	this->emptyspace
			};
			this->generatingTemplate(t1);

			const char t2[4][4] = {
				this->emptyspace,	this->brickform,		this->emptyspace,	this->emptyspace,
				this->brickform,		this->brickform,		this->emptyspace,	this->emptyspace,
				this->brickform,		this->emptyspace,	this->emptyspace,	this->emptyspace,
				this->emptyspace,	this->emptyspace,	this->emptyspace,	this->emptyspace
			};
			this->generatingTemplate(t2);
		}
		break;

		case T:
			{
				const char t1[4][4] = {
					this->emptyspace,	this->brickform,		this->emptyspace,	this->emptyspace,
					this->brickform,		this->brickform,		this->brickform,		this->emptyspace,
					this->emptyspace,	this->emptyspace,	this->emptyspace,	this->emptyspace,
					this->emptyspace,	this->emptyspace,	this->emptyspace,	this->emptyspace
				};
				this->generatingTemplate( t1 );

				const char t2[4][4] = {
					this->emptyspace,	this->brickform,		this->emptyspace,	this->emptyspace,
					this->emptyspace,	this->brickform,		this->brickform,		this->emptyspace,			//the T shaped tetromino piece
					this->emptyspace,	this->brickform,		this->emptyspace,	this->emptyspace,
					this->emptyspace,	this->emptyspace,	this->emptyspace,	this->emptyspace
				};
				this->generatingTemplate( t2 );

				const char t3[4][4] = {
					this->emptyspace,	this->emptyspace,	this->emptyspace,	this->emptyspace,
					this->brickform,		this->brickform,		this->brickform,		this->emptyspace,
					this->emptyspace,	this->brickform,		this->emptyspace,	this->emptyspace,
					this->emptyspace,	this->emptyspace,	this->emptyspace,	this->emptyspace
				};
				this->generatingTemplate( t3 );

				const char t4[4][4] = {
					this->emptyspace,	this->brickform,		this->emptyspace,	this->emptyspace,
					this->brickform,		this->brickform,		this->emptyspace,	this->emptyspace,
					this->emptyspace,	this->brickform,		this->emptyspace,	this->emptyspace,
					this->emptyspace,	this->emptyspace,	this->emptyspace,	this->emptyspace
				};
				this->generatingTemplate( t4 );
			}
			break;

		
	}

	this->actualBrickIndex = 0;
	this->actualBrickTemplate = this->brickFormTemplate[0];
}

																	//Getters:
const char** Tetromino::getActualBrickTemplate() const              //getting the brick template for tetromino
{
	return const_cast<const char**>( this->actualBrickTemplate );
}

const char Tetromino::getFormat() const								//getting the format of each brickform for the tetromino
{
	return this->brickform;
}

																	//Methods:
void Tetromino::print() const										//printing the tetromino
{
	for( size_t i=0; i<4; i++ )
	{
		for( size_t j=0; j<4; j++ )
		{
			cout << this->actualBrickTemplate[i][j];
		}
		cout << endl;
	}
}

/*void Tetromino::printAllTemplates() const							
{
	for( size_t i=0; i<this->brickFormTemplate.size(); i++ )			//needs improvement, unnecessary for the program to function in a playable state...
	{
		for( size_t j=0; j<4; j++ )
		{
			for( size_t k=0; k<4; k++ )
			{
				cout << this->brickFormTemplate[i][j][k];
			}
			cout << endl;
		}
		cout << "\n" << endl;
	}
}*/

void Tetromino::rotate( int key )											//the rotation portion of the tetrominos
{
	int index = this->actualBrickIndex;

	switch( key )
	{
	case 'x':
	case 'X':
		index = ( (index-1) + this->brickFormTemplate.size() ) % this->brickFormTemplate.size();
		this->actualBrickIndex = index;
		this->actualBrickTemplate = this->brickFormTemplate[index];
		break;
		
	case 's':
	case 'S':
		index = ((index + 1) + this->brickFormTemplate.size()) % this->brickFormTemplate.size();
		this->actualBrickIndex = index;
		this->actualBrickTemplate = this->brickFormTemplate[index];
		break;
	
	}
}

void Tetromino::generatingTemplate( const char t[4][4] )             
{
	this->brickFormTemplate.push_back( new char*[4] );      

	for( size_t i=0; i<4; i++ )
	{
		this->brickFormTemplate[this->brickFormTemplate.size()-1][i] = new char[4];
	}

	for( size_t i=0; i<4; i++ )
	{
		for( size_t j=0; j<4; j++ )
		{	
			this->brickFormTemplate[this->brickFormTemplate.size()-1][i][j] = t[i][j];
		}
	}
}

														//Destructor:
Tetromino::~Tetromino()
{
	for( size_t i=0; i<this->brickFormTemplate.size(); i++ )
	{
		for( size_t j=0; j<4; j++ )
		{
			delete [] ( this->brickFormTemplate[i][j] );
		}

		delete [] ( this->brickFormTemplate[i] );
	}
}