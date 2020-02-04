#include "Prop.h"
#include "Game.h"


// This function is the default constructor for the class 
Prop::Prop()
{

}





// This constructor moves the player Unit to a given position
Prop::Prop(Vector2 newPos, Animation * newAnim)
{
	mLocation = newPos;
	mCurrentAnimation = newAnim;
}





// This is the destructor for the class
Prop::~Prop()
{
}





// This function draws the unit's sprite to the screen
void Prop::draw()
{
	Game::getStaticInstance()->getCurrentSystem()->getGraphicsSystem().draw(mLocation, *mCurrentAnimation->getCurrentSprite(), DEFAULT_SCALING_VALUE);
}