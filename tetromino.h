#ifndef TETROMINO_H
#define TETROMINO_H

#include <vector>
using std::vector;

class Tetromino
{
public:

	enum TETROMINO{ I, J, L, O, S, T, Z };  //the tetromino pieces in enum

																					//Constructor:
	Tetromino( const TETROMINO type, char brickfrom = 'A', char emptyspace = ' ' ); //the kind of tetromino/it's "format" means how each block of the corresponding piece is appearing on the screen/emptyspace is the "empty" space in our 4x4 array for tetrominos

																					//Getters:
	const char** getActualBrickTemplate() const;   //getting the template of each tetromino
	const char getFormat() const;				   //getting the format for each tetromino

																					//Methods:
	void print() const;							//printing the tetromino
	//void printAllTemplates() const;				//printing the templates
	void rotate( int key );						//the roatation of the tetromino

												//Destructor:
	~Tetromino();

private:

	const char brickform;
	const char emptyspace;
	TETROMINO type;
	char **actualBrickTemplate;
	size_t actualBrickIndex;
	vector<char**> brickFormTemplate;

												//Method:
	void generatingTemplate( const char t[4][4] );//generating the template for the 4x4 tetromino marix
};

#endif
