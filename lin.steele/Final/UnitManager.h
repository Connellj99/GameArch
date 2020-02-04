#ifndef UNITMANAGER_H
#define UNITMANAGER_H

// Local Includes
#include "Unit.h"
#include "Player.h"
#include "QuestionBlock.h"
#include "BrickBlock.h"
#include "Goomba.h"
#include "Prop.h"

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

	// Mutators
	void removeAllUnits();
	void createUnit( Vector2 newPos );
	void createPlayer( Vector2 newPos );
	void createQuestionBlock( Vector2 newPos );
	void createBrickBlock( Vector2 newPos );
	void createGoomba( Vector2 newPos );
	void createProp(Vector2 newPos, Animation * newAnim);
	void addAnimation( int index, Animation & newAnim );
	void destroyUnit( int index );
	void playOrStopUnitAnimations();
	void addPlayerAnimation(Animation & newAnim);
	void movePlayer(Vector2 newPos);

	// Update functions
	void update( double timeBetweenFrames );
	void draw();

private:

	// Vectors
	vector<Unit*> mUnits;
	vector<Prop*> mProps;

	// Players
	Player* mPlayer;

};



#endif // !UNITMANAGER_H

