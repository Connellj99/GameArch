/*
Author: Amelia Payne
Class: EGP-310 <2>
Assignment: pa 4
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/


#pragma once
#include "Unit.h"
#include <GraphicsBuffer.h>
#include <map> 
#include <iterator>
#include <Trackable.h>


class GraphicsBufferManager : public Trackable
{
private:

	std::map<std::string, GraphicsBuffer *> mGraphicsBuffers;

	bool mIsInit = false;

public:

	/*
	Set up the graphicsBuffer
	*/
	GraphicsBufferManager();

	/*
	Call clear to deallocate all data before destroying
	*/
	~GraphicsBufferManager();

	/*
	Remove all the items from mGraphicsBuffer and deallocate the memory
	*/
	void clear();

	/*
	Add a new key, value pair to the map of graphicsBuffers
	*/
	void addBuffer(std::string name, GraphicsBuffer* buffer);

	/*
	Delete a buffer with a given key
	*/
	void deleteBufferWithKey(std::string name);

	/*
	Get a buffer pointer with a given name (key)
	*/
	GraphicsBuffer * getBuffer(std::string name);

};