#ifndef SYSTEM_H
#define SYSTEM_H

// Graphics Library includes
#include "GraphicsSystem.h"

// Non-standard library includes
#include <string>





class System : public Trackable
{
public:

	// Constructors
	System();

	// Destructors
	~System();

	// Initializers
	void init( int screenWidth, int screenHeight );
	void initializeSystems();

	// Cleanups
	void cleanup();
	GraphicsSystem getGraphicsSystem();

	// Mutators
	void flipDisplay();

private:

	// Graphics Systems
	GraphicsSystem mCurrentGraphicsSystem;

	// Booleans
	bool mIsDisplaying;

};



#endif // !SYSTEM_H

