#include "Animation.h"

Animation::Animation()
{
	Animation animateMe[4*4];
}

void Animation::startAnim()
{
	GraphicsSystem* pGraphicsSystem;

	//Make smurf buffer
	GraphicsBuffer* pSmurfsBuffer = new GraphicsBuffer("..\\..\\shared\\assets\\", "smurf_sprites.png");

	//Make dean buffer
	GraphicsBuffer* pDeanSmurf = new GraphicsBuffer("..\\..\\shared\\assets\\", "dean_sprites.png");

	//Assert the buffer
	assert(pSmurfsBuffer);

	// Calculate the sprite width & height.
	int spriteWidth = pSmurfsBuffer->getWidth() / 4;
	int spriteHeight = pSmurfsBuffer->getHeight() / 4;

	// Create a separate sprite for each one on the sheet and add it to an array.
	for (int spriteRow = 0; spriteRow < 4; spriteRow++)
	{
		for (int spriteColumn = 0; spriteColumn < 4; spriteColumn++)
		{
			smurfSprites[spriteRow * 4 + spriteColumn] = Sprite(pSmurfsBuffer, spriteWidth * spriteColumn, spriteHeight * spriteRow, spriteWidth, spriteHeight);
		}
	}

	//Draw the current sprite to the screen
	pGraphicsSystem->draw(smurfSprites[0], 200, 150);


}

void Animation::update()
{
	//update animation
	for (int x = 0; x <= 15; x++) {
		smurfSprites[x];
	}
}

Sprite Animation::getCurrentSprite()
{
	return smurfSprites[0];
}

void Animation::speedAnim()
{
	//speed up the animation
}

void Animation::slowAnim()
{
	//slow down the animation
}

Animation::~Animation()
{
	smurfSprites->~Sprite();
	deanSprites->~Sprite();
}
