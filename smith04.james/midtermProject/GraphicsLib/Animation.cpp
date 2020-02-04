#include "Animation.h"

Animation::Animation()
{

}

Animation::~Animation()
{
	cleanUp();
}

void Animation::loadSprites(GraphicsBuffer* spriteMap, int rows, int columns)
{
	if (mpAnimList != nullptr)
	{
		cleanUp();
		delete[] mpAnimList;
		size = 0;
	}
	
	size = rows * columns;
	mpAnimList = new Sprite*[size];

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			mpAnimList[(i*columns) + j] = new Sprite(j * spriteMap->getWidth() / columns, i * spriteMap->getHeight() / rows, spriteMap->getWidth() / columns, spriteMap->getHeight() / rows, spriteMap);
		}
	}
}

void Animation::update()
{
	if (currentIndex >= size - 1)
	{
		currentIndex = 0;
	}
	else
	{
		currentIndex++;
	}
}

Sprite* Animation::getCurrentSprite()
{
	return mpAnimList[currentIndex];
}

void Animation::adjustSpeed(float adjustment)
{

}

void Animation::cleanUp()
{
	for (int i = 0; i < size; i++)
	{
		delete mpAnimList[i];
	}
}