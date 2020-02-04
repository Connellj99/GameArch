/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 5											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

class Event;

class EventListener :
	public Trackable
{
public:
	EventListener() { return; }
	virtual ~EventListener() { return; }

	virtual void handleEvent(const Event& _theEvent) = 0;
};

