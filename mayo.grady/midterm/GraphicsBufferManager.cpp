/*
Author: Grady Mayo
Class: EGP-310 <Section 01>
Assignment: Assignment 4
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "GraphicsBufferManager.h"

GraphicsBufferManager::GraphicsBufferManager()
{

}

GraphicsBufferManager::~GraphicsBufferManager()
{
	cleanup();
}

GraphicsBuffer * GraphicsBufferManager::add(const GBKey& key, std::string filename)
{
	GraphicsBuffer * pBuffer = NULL;

	map<GBKey, GraphicsBuffer*>::iterator iter = mMap.find(key);

	if (iter == mMap.end())
	{
		pBuffer = new GraphicsBuffer(filename);
		mMap.insert({ key, pBuffer });
	}

	return pBuffer;
}

GraphicsBuffer * GraphicsBufferManager::add(const GBKey& key, int width, int height)
{
	GraphicsBuffer * pBuffer = NULL;

	map<GBKey, GraphicsBuffer*>::iterator iter = mMap.find(key);

	if (iter == mMap.end())
	{
		pBuffer = new GraphicsBuffer(width, height);
		mMap.insert({ key, pBuffer });
	}

	return pBuffer;
}

void GraphicsBufferManager::remove(const GBKey& key)
{
	map<GBKey, GraphicsBuffer*>::iterator iter = mMap.find(key);

	if (iter != mMap.end())
	{
		delete iter->second;
		mMap.erase(iter);
	}
}

GraphicsBuffer * GraphicsBufferManager::getBuffer(const GBKey& key)
{
	map<GBKey, GraphicsBuffer*>::const_iterator iter = mMap.find(key);

	if (iter != mMap.end())
	{
		return iter->second;
	}
	else
	{
		return NULL;
	}
}

void GraphicsBufferManager::cleanup()
{
	map<GBKey, GraphicsBuffer*>::iterator iter;

	for (iter = mMap.begin(); iter != mMap.end(); ++iter)
	{
		GraphicsBuffer * pBuffer = iter->second;
		delete pBuffer;
	}

	mMap.clear();
}