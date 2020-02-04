#pragma once
#ifndef GRAPHICS_BUFFER_MANAGER_H
#define GRAPHICS_BUFFER_MANAGER_H

#include "Trackable.h"
#include "GraphicsBuffer.h"
#include <vector>

class GraphicsBufferManager :public Trackable
{
private:
	bool mIsClear = false;

	vector<GraphicsBuffer*> mBuffers;

public:
	GraphicsBufferManager();
	~GraphicsBufferManager();
	void addBuffer(GraphicsBuffer* buffer);
	void removeBuffer(int bufferName);
	GraphicsBuffer* getBuffer(int bufferName);
	void clear();
};

#endif