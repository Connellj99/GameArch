#pragma once
#include "Event.h"
#include "GraphicsLib/InputSystem.h"

class ButtonPressEvent : public Event
{
public:
	ButtonPressEvent(keys k);
	~ButtonPressEvent();

	keys getKey() const {return mKey; };

private:
	keys mKey;
};