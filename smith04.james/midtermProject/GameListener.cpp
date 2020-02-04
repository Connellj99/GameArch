#include "GameListener.h"
#include "Header.h"
#include "Event.h"
#include "Game.h"
#include "AddEvent.h"
#include "DeleteEvent.h"
#include "ExitEvent.h"
#include "FreezeEvent.h"
#include "DeanEvent.h"

GameListener::GameListener(EventSystem* mESys) : EventListener(mESys)
{
	
}

GameListener::~GameListener()
{
	
}

void GameListener::handleEvent(const Event& ev)
{
	if (ev.getType() == ADD_EVENT)
	{
		const AddEvent &temp = static_cast<const AddEvent&>(ev);
		pGame->getInstance()->addSmurf(temp.getX(), temp.getY());
	}
	else if (ev.getType() == DELETE_EVENT)
	{
		const DeleteEvent &temp = static_cast<const DeleteEvent&>(ev);
		pGame->getInstance()->removeUnitAt(temp.getX(), temp.getY());
	}
	else if (ev.getType() == EXIT_EVENT)
	{
		const ExitEvent &temp = static_cast<const ExitEvent&>(ev);
		pGame->getInstance()->shouldExit();
	}
	else if (ev.getType() == FREEZE_EVENT)
	{
		const FreezeEvent &temp = static_cast<const FreezeEvent&>(ev);
		pGame->getInstance()->enableUnitUpdating();
	}
	else if (ev.getType() == DEAN_EVENT)
	{
		const DeanEvent &temp = static_cast<const DeanEvent&>(ev);
		pGame->getInstance()->switchAnim();
	}
	else
	{
		std::cout << "ERROR! Event not recognized!" << std::endl;
	}
}