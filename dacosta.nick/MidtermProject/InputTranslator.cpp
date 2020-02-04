/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 5											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#include <iostream>
#include <map>

#include "Trackable.h"

#include "KeyCodes.h"
#include "DirectionKeys.h"
#include "UnitTypes.h"

#include "EventTypes.h"

#include "Event.h"

#include "KeyboardEvent.h"
#include "MouseEvent.h"
#include "UnitEvents.h"
#include "GameEvents.h"
#include "EventListener.h"
#include "EventSystem.h"

#include "InputTranslator.h"

// Initialize the input translator.
void InputTranslator::initialize()
{
	EventSystem::getInstance()->addListener(MOUSE, this);

	EventSystem::getInstance()->addListener(KEYBOARD, this);

	return;
}

// Clean up the input translator.
void InputTranslator::cleanUp()
{
	EventSystem::getInstance()->removeListenerFromAllEvents(this);
	return;
}

void InputTranslator::handleEvent(const Event& _theEvent)
{
	EventSystem* pEventSystem = EventSystem::getInstance();

	switch (_theEvent.getType())
	{
		case MOUSE:
		{
			// Cast to a mouse event.
			MouseEvent mouseEvent = dynamic_cast<const MouseEvent&>(_theEvent);

			// The current state of the mouse buttons.
			bool mouseButtons[MOUSE_MAX] = { false };

			// Get the current state of the mouse buttons.
			mouseEvent.getButtons(mouseButtons);

			// Check if the left mouse button is pressed.
			if (mouseButtons[MOUSE_LEFT])
			{
				// Make sure the button isn't being held down.
				if (!mMouseButtons[MOUSE_LEFT])
				{
					// Left mouse button is pressed this frame.
					mMouseButtons[MOUSE_LEFT] = true;

					int positionX = 0;
					int positionY = 0;

					mouseEvent.getPosition(positionX, positionY);

					// Perform create unit event.
					pEventSystem->performEvent(CreateUnitEvent(positionX, positionY));
				}
			}
			else
			{
				// Left mouse button is not pressed this frame.
				mMouseButtons[MOUSE_LEFT] = false;
			}

			// Check if the right mouse button is pressed.
			if (mouseButtons[MOUSE_RIGHT])
			{
				// Make sure the button isn't being held down.
				if (!mMouseButtons[MOUSE_RIGHT])
				{
					// Right mouse button is pressed this frame.
					mMouseButtons[MOUSE_RIGHT] = true;

					// Create a position.
					int positionX = 0;
					int positionY = 0;

					// Get the mouse position.
					mouseEvent.getPosition(positionX, positionY);

					// Perform remove unit event.
					pEventSystem->performEvent(RemoveUnitEvent(positionX, positionY));
				}
			}
			else
			{
				// Right mouse button is not pressed this frame.
				mMouseButtons[MOUSE_RIGHT] = false;
			}
			break;
		}
		case KEYBOARD:
		{
			KeyboardEvent keyboardEvent = dynamic_cast<const KeyboardEvent&>(_theEvent);

			bool keys[KEY_MAX] = { false };
			keyboardEvent.getKeys(keys);

			// Check if the "Enter" key was pressed to switch the last unit's animation sprite.
			if (keys[KEY_ENTER])
			{
				// Make sure the key isn't help down.
				if (!mKeys[KEY_ENTER])
				{
					// The key has been pressed.
					mKeys[KEY_ENTER] = true;
					pEventSystem->performEvent(ToggleUnitSpriteEvent());
				}
			}
			else
			{
				// The key has been release.
				mKeys[KEY_ENTER] = false;
			}

			// Check if the "Space" key was pressed to toggle all units' animation.
			if (keys[KEY_SPACE])
			{
				// Make sure the key isn't help down.
				if (!mKeys[KEY_SPACE])
				{
					// The key has been pressed.
					mKeys[KEY_SPACE] = true;

					pEventSystem->performEvent(ChangeLevelEvent());
				}
			}
			else
			{
				// The key has been release.
				mKeys[KEY_SPACE] = false;
			}

			if (keys[KEY_LEFT] || keys[KEY_A])
			{
				if (!mKeys[KEY_LEFT] || !mKeys[KEY_A])
				{
					mKeys[KEY_LEFT] = true;
					mKeys[KEY_A] = true;

					pEventSystem->performEvent(ChangeUnitDirectionEvent(WEST));
				}
			}
			else
			{
				mKeys[KEY_LEFT] = false;
				mKeys[KEY_A] = false;
			}

			if (keys[KEY_UP] || keys[KEY_W])
			{
				if (!mKeys[KEY_UP] || !mKeys[KEY_W])
				{
					mKeys[KEY_UP] = true;
					mKeys[KEY_W] = true;

					pEventSystem->performEvent(ChangeUnitDirectionEvent(NORTH));
				}
			}
			else
			{
				mKeys[KEY_UP] = false;
				mKeys[KEY_W] = false;
			}

			if (keys[KEY_RIGHT] || keys[KEY_D])
			{
				if (!mKeys[KEY_RIGHT] || !mKeys[KEY_D])
				{
					mKeys[KEY_RIGHT] = true;
					mKeys[KEY_D] = true;

					pEventSystem->performEvent(ChangeUnitDirectionEvent(EAST));
				}
			}
			else
			{
				mKeys[KEY_RIGHT] = false;
				mKeys[KEY_D] = false;
			}

			if (keys[KEY_DOWN] || keys[KEY_S])
			{
				if (!mKeys[KEY_DOWN] || !mKeys[KEY_S])
				{
					mKeys[KEY_DOWN] = true;
					mKeys[KEY_S] = true;

					pEventSystem->performEvent(ChangeUnitDirectionEvent(SOUTH));
				}
			}
			else
			{
				mKeys[KEY_DOWN] = false;
				mKeys[KEY_S] = false;
			}

			// Check if the "Escape" key was pressed to exit the game.
			if (keys[KEY_ESCAPE])
			{
				pEventSystem->performEvent(ExitEvent());
			}
			break;
		}
	}
}