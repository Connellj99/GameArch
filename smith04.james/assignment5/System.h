#pragma once

#include "GraphicsSystem.h"
#include "GraphicsLib/InputSystem.h"

class System : public Trackable
{
private:
	GraphicsSystem* mpSys;
	InputSystem* mpInSys;

public:
	System(float w, float h);
	~System();

	void init(float w, float h);
	void cleanup();

	void draw(float x, float y, Sprite* spr, float s = 1.0);
	void draw(GraphicsBuffer* target, float x, float y, Sprite* spr, float s = 1.0);
	void writeText(float x, float y, Font* f, Color c, std::string text);
	void writeText(GraphicsBuffer* target, float x, float y, Font* f, Color c, std::string text);

	InputSystem* getInput() const {return mpInSys;};

	void flip();
};