#pragma once

#include "GraphicsSystem.h"

class System : public Trackable {

private:

	bool isInit;
	GraphicsSystem* mGraphicSys;
	ALLEGRO_EVENT_QUEUE* eventQueue;
	ALLEGRO_EVENT ev;

public:

	System();
	void initSys();
	void getKeyState();
	bool getMouseState();
	void draw(GraphicsBuffer* buff);
	~System();
};