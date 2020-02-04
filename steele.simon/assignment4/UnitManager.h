#ifndef UNITMANAGER_H
#define UNITMANAGER_H

// Local Includes
#include "Unit.h"

// Constant Vector2's
const Vector2 CLICK_DIMENSIONS = Vector2( 35, 35 );

class UnitManager: public Trackable
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
	void createUnit(Vector2 newPos);
	void destroyUnit(int index);
	void removeAndDestroyAllUnits();
	void addAnimation( int index, Animation & newAnim );
	void swapAnimations( int index );
	void playOrStopUnitAnimations();
	void deleteUnitFromGivenPoint( Vector2 newPos );

	// Game Loop Functions
	void update( double timeBetweenFrames );
	void draw();

private:

	// Vectors
	vector<Unit*> mUnits;

};



#endif // !UNITMANAGER_H

