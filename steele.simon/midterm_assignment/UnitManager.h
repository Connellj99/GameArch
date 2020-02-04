#ifndef UNITMANAGER_H
#define UNITMANAGER_H

// Local Includes
#include "Unit.h"
#include "Player.h"
#include "Bullet.h"
#include "Mushroom.h"
#include "CentipedeSegment.h"
#include "CentipedeManager.h"

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
	Unit * getUnit( int index );
	int getSize();
	Player* getPlayer();
	CentipedeManager* getCentipede(int elementTheCentipedeIsAt);
	int getCentipedeVectorSize();

	// Mutators
	void removeAllUnits();
	void createUnit( Vector2 newPos );
	void createBullet( Vector2 newPos );
	void createMushroom(Vector2 newPos);
	void createPlayer( Vector2 newPos );
	void createCentipedeSegment( Vector2 newPos );
	void createCentipede(Vector2 newPos, int amountOfSegments);
	void destroyCentipede(CentipedeSegment * segmentToBeDestroyed);
	void splitCentipede(CentipedeSegment * newHead);
	void addAnimation( int index, Animation & newAnim );
	void swapAnimations( int index );
	void destroyUnit( int index );
	void playOrStopUnitAnimations();
	void deleteUnitFromGivenPoint( Vector2 newPos );
	void addPlayerAnimation(Animation & newAnim);
	void swapPlayerAnimations();
	void movePlayer(Vector2 newPos);

	// Update functions
	void update( double timeBetweenFrames );
	void draw();

private:

	// Vectors
	vector<Unit*> mUnits;
	vector<CentipedeManager*> mCentipedes;

	// Players
	Player* mPlayer;

};



#endif // !UNITMANAGER_H

