#ifndef BRICKBLOCK_H
#define BRICKBLOCK_H

// Local includes
#include "Unit.h"

class BrickBlock : public Unit
{
public:

	// Constructors
	BrickBlock();
	BrickBlock(Vector2 newPos);

	// Destructors
	~BrickBlock();

	// Update functions
	void update(double newTimeBetweenFrames);

private:

};

#endif // !BRICKBLOCK_H


