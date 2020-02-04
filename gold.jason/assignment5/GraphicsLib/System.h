#ifndef System_h
#define System_h
#include <Trackable.h>
#include "GraphicsSystem.h"
#include "EventSystem.h"
#include "InputSystem.h"

class System: public Trackable
{
public:
	System();
	~System();

	void InitSystem(int dispHeight, int dispWidth);
	void CleanUpSystem();
	GraphicsSystem* getGraphicsSystem();
	InputSystem* getInputSys();

private:
	GraphicsSystem* mpGraphicsSystem;
	InputSystem* mInputSys;

};

#endif // !System_h