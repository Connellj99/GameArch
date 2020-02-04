#pragma once

#include <iostream>

#include <Trackable.h>

#include "BufferFlags.h"

#include "Color.h"
#include <GraphicsBuffer.h>
#include <map>
using namespace std;

typedef string buffKey;

class GraphicsBufferManager : public Trackable 
{
private:

	//making a map to store the graphics buffers
	map<buffKey, GraphicsBuffer*> mMap;
	
	//string to be used as a buffKey
	buffKey x;

public:

	//default constructor
	GraphicsBufferManager();

	//destructor
	~GraphicsBufferManager();

	//init
	void initGraphicsBufferManager();

	//add a buffer
	void addBuffToManager(GraphicsBuffer *buffAdd, string key);

	//delete a buffer based on a buffer
	void deleteBuffFromManager(GraphicsBuffer *buffDelete);

	//delete a buffer based on a key
	void deleteBuffFromManager(const buffKey& key);

	//get the specified buffer
	GraphicsBuffer* getBuffer(const buffKey& key);

	//delete everything
	void cleanup();



};