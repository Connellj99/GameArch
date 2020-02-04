/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 5											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

class EventSystem : 
	public Trackable
{
public:
	// Get this instance.
	static EventSystem* getInstance();

	// Initialize this instance.
	static void initializeInstance();

	// Clean up this instance.
	static void cleanUpInstance();

	// Perform the event given.
	void performEvent(const Event& _theEvent);

	// Add a listener to the system.
	void addListener(EventType _type, EventListener* _pListener);

	// Remove a listener from the system.
	void removeListener(EventType _type, EventListener* _pListener);

	// Remove a listener from all the events.
	void removeListenerFromAllEvents(EventListener* _pListener);

private:
	EventSystem() { }
	~EventSystem() { }

	static EventSystem* smpInstance;

	// Multi-Map of listeners.
	std::multimap<EventType, EventListener*> mListenerMultiMap;

	// Dispatch all the specified events.
	void dispatchAllEvents(const Event& _theEvent);
};

