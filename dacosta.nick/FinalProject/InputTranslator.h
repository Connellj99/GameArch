/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 5											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

class InputTranslator :
	public EventListener
{
public:
	InputTranslator() { }
	~InputTranslator() { }

	// Initialize the input translator.
	void initialize();

	// Clean up the input translator.
	void cleanUp();

	// Handle the event.
	void handleEvent(const Event& _theEvent);

private:
	bool mKeys[KEY_MAX] = { false };
	bool mMouseButtons[MOUSE_MAX] = { false };
};