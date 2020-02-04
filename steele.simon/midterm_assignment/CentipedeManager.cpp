#include "CentipedeManager.h"
#include "Game.h"


// This function is the default constructor of the class
CentipedeManager::CentipedeManager()
{
	mHead = nullptr;
	mTimeElapsed = DEFAULT_ANIMATION_SPEED;
}





// This function is the destructor of the class
CentipedeManager::~CentipedeManager()
{
	if (mHead != nullptr) 
	{
		CentipedeSegment * segment = mHead;

		while (segment->getLastSegment() != nullptr)
		{
			segment = segment->getLastSegment();
			delete segment->getNextSegment();
		}

		delete segment;
	}
}





// This function adds a segment to the Centipede
void CentipedeManager::addSegmentToCentipede(CentipedeSegment* segmentToBeAdded) 
{
	// Is the Centipede one segment long?
	if (mHead == nullptr) 
	{
		// If yes, then a pointer to the segment before the segment added
		mHead = segmentToBeAdded;
	}
	else
	{
		// If no, then traverse the list until the end and then add the segment to the end of the list
		CentipedeSegment * segment = mHead;

		while (segment->getLastSegment() != nullptr)
		{
			segment = segment->getLastSegment();
		}

		segment->addLastSegment(segmentToBeAdded);
		segmentToBeAdded->addNextSegment(segment);
	}
}





// This function is the update function for this class
void CentipedeManager::update( double timeBetweenFrames )
{
	if (mHead == nullptr)
	{
		return;
	}

	mTimeElapsed -= timeBetweenFrames;

	if (mTimeElapsed <= 0.0)
	{
		mHead->updateAnimations();
		mTimeElapsed = DEFAULT_ANIMATION_SPEED;
	}

	mHead->update(timeBetweenFrames);
}





// This function is the draw function for this class
void CentipedeManager::draw() 
{
	CentipedeSegment * segment = mHead;

	// The following code draws all centipede segments

	if (mHead == nullptr) 
	{
		return;
	}

	segment->draw();

	while (segment->getLastSegment() != nullptr)
	{
		segment = segment->getLastSegment();
		segment->draw();
	}
}





// This function removes a given segment from the Centipede
void CentipedeManager::removeSegmentOfCentipede(CentipedeSegment * segmentToBeRemoved) 
{
	CentipedeSegment * segment = mHead;

	if (segmentToBeRemoved == mHead) 
	{
		if (mHead->getLastSegment() != nullptr) 
		{
			mHead->getLastSegment()->addNextSegment(nullptr);
			Game::getStaticInstance()->getUnitManager()->splitCentipede(mHead->getLastSegment());
		}
		delete segmentToBeRemoved;
		mHead = nullptr;
		return;
	}

	while (segment != nullptr)
	{
		if (segment == segmentToBeRemoved)
		{
			// If the Removed Segment is not the tail, then split the centipede
			//and have the segment after the removed segment be the head of the new centipede
			if (segment->getLastSegment() != nullptr)
			{
				segment->getLastSegment()->addNextSegment(nullptr);
				Game::getStaticInstance()->getUnitManager()->splitCentipede(segment->getLastSegment());
			}
			// If the Removed Segment is not the head, then make the segment before the removed segment the tail
			if (segment->getNextSegment() != nullptr)
			{
				segment->getNextSegment()->addLastSegment(nullptr);
			}

			delete segmentToBeRemoved;
			return;
		}
		else 
		{
			segment = segment->getLastSegment();
		}
	}
}





// This function adds an animation to all centipede segments
void CentipedeManager::addAnimation(Animation & newAnim) 
{
	CentipedeSegment * segment = mHead;


	// The following code sets the newly added animation to all centipede segments
	segment->setAnimation(newAnim);

	while (segment->getLastSegment() != nullptr)
	{
		segment = segment->getLastSegment();
		segment->setAnimation(newAnim);
	}
}





// This function switches the animation of the head
void CentipedeManager::changeHeadAnimation() 
{
	mHead->swapAnimation();
}




// This function resets all animation indexes
void CentipedeManager::resetAnimations() 
{
	CentipedeSegment * segment = mHead;

	while (segment->getLastSegment() != nullptr)
	{
		segment = segment->getLastSegment();
		segment->getCurrentAnimation()->resetAnimationIndex();
	}
}