#ifndef UNITMANAGER_H
#define UNITMANAGER_H

// Local Includes
#include "Unit.h"

// Constant Vector2's
const Vector2 CLICK_DIMENSIONS = Vector2( 50, 50 );

class UnitManager
{
public:

	// Constructors
	UnitManager();

	// Destuctors
	~UnitManager();

	// Acessors
	Unit getUnit( int index );
	int getSize();

	// Mutators
	void removeAllUnits();
	void createUnit( Vector2 newPos );
	void addAnimation( int index, Animation & newAnim );
	void swapAnimations( int index );
	void destroyUnit( int index );
	void playOrStopUnitAnimations();
	void deleteUnitFromGivenPoint( Vector2 newPos );

	void update( double timeBetweenFrames );
	void draw();

private:

	// Vectors
	vector<Unit*> mUnits;

};



#endif // !UNITMANAGER_H

