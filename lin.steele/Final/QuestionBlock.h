#ifndef QUESTIONBLOCK_H
#define QUESTIONBLOCK_H


// Local includes
#include "Unit.h"


class QuestionBlock : public Unit
{
public:

	// Constructors
	QuestionBlock();
	QuestionBlock(Vector2 newPos);

	// Destructors
	~QuestionBlock();

	// Update functions
	void update(double newTimeBetweenFrames);
	void swapAnimation( string nameOfNewAnimation );

private:

	// Booleans
	bool mIsEmpty;

};


#endif // !QUESTIONBLOCK_H

