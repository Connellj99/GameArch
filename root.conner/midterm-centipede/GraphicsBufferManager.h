/*
Conner Root
EGP 310 - 01
*/

#pragma once

#include <PerformanceTracker.h>

#include "GraphicsBuffer.h"

class GraphicsBufferManager : public Trackable
{
private:
	vector<GraphicsBuffer*> mpBufferList;

public:
	// Constructor
	GraphicsBufferManager();

	// Add buffer
	void addBuffer(string);
	void addBuffer(string, int w, int h);

	// Accessors
	int findBuffer(string);
	GraphicsBuffer* getBuffer(string);
	
	// Delete buffers
	void deleteBuffer(string);
	void deleteAllBuffers();

	// Destructor
	~GraphicsBufferManager();
};