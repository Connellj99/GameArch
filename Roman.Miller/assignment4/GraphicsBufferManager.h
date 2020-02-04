#pragma once
#include "Trackable.h"
#include <vector>
#include "GraphicsSystem.h"
#include <map>


class GraphicsBufferManager :public Trackable
{
public:
	GraphicsBufferManager();
	GraphicsBufferManager(GraphicsBuffer* backBuffer);
	~GraphicsBufferManager();

	void addBuffer(string name,GraphicsBuffer* buffer);
	void deleteBuffer(string name);

	GraphicsBuffer* getBuffer(string name);
	GraphicsBuffer* getBuffer();

private:
	map<string, GraphicsBuffer*> mpMap;
	GraphicsBuffer* mpBackBuffer;
};
