#pragma once
/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 4
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include <string>
#include <map>

#include "Trackable.h"
#include "GraphicsBuffer.h"

//class GraphicsBuffer;

typedef std::string GBKey;

class GraphicsBufferManager : public Trackable
{
private:
	//map of graphics buffers
	std::map<GBKey, GraphicsBuffer*> mMap;

public:
	//constructor
	GraphicsBufferManager();

	//destructor
	~GraphicsBufferManager();

	//add a buffer
	GraphicsBuffer * add(const GBKey& key, std::string filename);

	//delete a buffer
	void remove(const GBKey& key);

	//get a buffer
	GraphicsBuffer * getBuffer(const GBKey& key);

	//clear - remove and delete all buffers - except back buffer
	void cleanup();
};