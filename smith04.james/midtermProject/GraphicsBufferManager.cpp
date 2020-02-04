#include "GraphicsBufferManager.h"

GraphicsBufferManager::GraphicsBufferManager()
{

}

GraphicsBufferManager::~GraphicsBufferManager()
{
	cleanup();
}

void GraphicsBufferManager::init()
{

}

void GraphicsBufferManager::cleanup()
{
	for (int i = 0; i < mBufferList.size(); i++)
	{
		delete mBufferList[i];
		delete mPosList[i];
	}

	removeAllBuffers();
}

void GraphicsBufferManager::addNewBuffer(std::string path, float x, float y, bool doDraw)
{
	GraphicsBuffer* newBuff = new GraphicsBuffer(path.c_str());
	mBufferList.push_back(newBuff);

	Vector2D* newVec = new Vector2D();
	newVec->setX(x);
	newVec->setY(y);
	mPosList.push_back(newVec);

	bool newBool = doDraw;
	mDrawList.push_back(newBool);
}

GraphicsBuffer* GraphicsBufferManager::getBuffer(int index)
{
	return mBufferList[index];
}

int GraphicsBufferManager::getSize()
{
	return mBufferList.size();
}

void GraphicsBufferManager::removeBuffer(int index)
{
	if (index < mBufferList.size() && index >= 0)
	{
		delete mBufferList[index];

		std::vector<GraphicsBuffer*>::iterator it = mBufferList.begin();
		std::advance(it, index);
		mBufferList.erase(it);

		delete mPosList[index];
		std::vector<Vector2D*>::iterator itv = mPosList.begin();
		std::advance(itv, index);
		mPosList.erase(itv);

		std::vector<bool>::iterator itb = mDrawList.begin();
		std::advance(itb, index);
		mDrawList.erase(itb);
	}
}

void GraphicsBufferManager::removeAllBuffers()
{
	mBufferList.clear();
	mPosList.clear();
	mDrawList.clear();
}

void GraphicsBufferManager::draw()
{
	for (int i = 0; i < mBufferList.size(); i++)
	{
		if (mDrawList[i])
		{
			mBufferList[i]->draw(mPosList[i]->getX(), mPosList[i]->getY());
		}
	}
}

int GraphicsBufferManager::findIndex(GraphicsBuffer* gbuffer)
{
	for (int i = 0; i < mBufferList.size(); i++)
	{
		if (mBufferList[i] == gbuffer)
		{
			return i;
		}
	}

	return -1;
}