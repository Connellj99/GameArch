/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Midterm
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#ifndef SNAKE_H
#define SNAKE_H

#include "Unit.h"
#include "Color.h"
#include "GameEvents.h"



class Node : public Unit
{
	friend class Snake;
public:
	Node(Sprite* = nullptr, Unit* = nullptr);
	~Node();
	virtual void update(double) override {};
	virtual void draw(float scale = 1) override;
private:
	Unit* mLink;
	Sprite* mSprite;
	bool mIsHead;
};


class Snake : public Unit
{
public:
	Snake(int=1, Point = Point(), int size = 20);
	~Snake() override;

	virtual void update(double) override;

	void addSegment();

	virtual void draw(float scale = 1) override;
	void setDir(Direction);
	int len() { return mBody.size(); }

private:
	Direction mDir = LEFT;
	int mSize;
	Node mHead;
	Sprite* mSpriteH;
	Sprite* mSpriteB;
	std::vector<Node*> mBody;
};

#endif // !SNAKE_H
