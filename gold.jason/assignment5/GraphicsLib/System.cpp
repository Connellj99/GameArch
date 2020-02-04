#include"System.h"

System::System()
{

}

System::~System()
{

}

void System::InitSystem(int dispHeight, int dispWidth)
{
	mpGraphicsSystem = new GraphicsSystem(dispHeight, dispWidth);

	mInputSys = new InputSystem();
}


GraphicsSystem* System::getGraphicsSystem()
{
	return mpGraphicsSystem;
}

InputSystem* System::getInputSys()
{
	return mInputSys;
}

void System::CleanUpSystem()
{
	//mpGraphicsSystem->cleanUpGraphics();
	delete mpGraphicsSystem;
}
