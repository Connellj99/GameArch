#pragma once
#include "Trackable.h"
#include "Sprite.h"
#include "Unit.h"
using namespace std;



class SnakeManager : public Trackable
{
public:
	SnakeManager();
	~SnakeManager();

	void init(Unit Piece, int startSeg);

	void addSegment();
	void draw();
	void update(float frameTime);
	void head();

	void setDirection(int direction) { mDirection = direction; };

	void speedUp() { if (mTargetMoveTime > 50) { mTargetMoveTime -= 50; } };
	void slowDown() { mTargetMoveTime += 50; };

	void checkForCollision();
private:
	vector<Unit> mSnakeVector;
	Unit mSegment;
	float mCurrentTime; 
	float mTargetMoveTime;
	int mDirection;
	int mStartSeg;
	int mCurrentSegMove;
	/*
	0 up
	1 right
	2 down
	3 left
	*/
};