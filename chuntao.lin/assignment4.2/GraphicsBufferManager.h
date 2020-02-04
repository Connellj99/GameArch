#ifndef GRAPHICS_BUFFER_MANAGER_H
#define GRAPHICS_BUFFER_MANAGER_H

//standard library includes
#include <vector>

// project-local includes
#include "GraphicsBuffer.h"

class GraphicsBufferManager : public Trackable
{
	friend class Game;
public:

	GraphicsBufferManager();//constructor
	~GraphicsBufferManager();//destructor

	void addBuffer(GraphicsBuffer* passedBuffer);//add more buffers
	void removeBuffer(int index);//remove a certain buffer

	GraphicsBuffer* getBuffer(int index);//get a certain buffer

	void clearAllBuffers();//clear all buffers except backbuffer

private:
	vector<GraphicsBuffer*> mpListOfBuffers;
};
#endif