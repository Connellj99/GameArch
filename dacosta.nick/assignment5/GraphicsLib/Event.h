/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 5											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

class Event :
	public Trackable
{
public:
	Event(EventType _type);

	virtual ~Event();

	EventType getType() const;

	const std::string& getEventName() const;

private:
	EventType mType;
};

