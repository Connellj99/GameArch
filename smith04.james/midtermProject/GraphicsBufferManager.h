#pragma once
#include "GraphicsLib/GraphicsBuffer.h"
#include <vector>
#include "Vector2D.h"

class GraphicsBufferManager : public Trackable
{
private:
	std::vector<GraphicsBuffer*> mBufferList;
	std::vector<Vector2D*> mPosList;
	std::vector<bool> mDrawList;

public:
	GraphicsBufferManager();
	~GraphicsBufferManager();

	void init();
	void cleanup();

	void addNewBuffer(std::string path, float x, float y, bool doDraw);

	GraphicsBuffer* getBuffer(int index);

	int getSize();

	void removeBuffer(int index);
	void removeAllBuffers();

	//void update(); I do not believe this is needed, but kept just in case it is down the line
	void draw();

	int findIndex(GraphicsBuffer* gBuffer);
};