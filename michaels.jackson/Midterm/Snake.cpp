/*
Author:Jackson Michaels
Class: EGP-310-01
Assignment: Midterm
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "Snake.h"
#include "Game.h"


Snake::Snake(int len, Point start, int size)
{
	GraphicsBuffer* body = new GraphicsBuffer(size, size);
	Color  col(1.0f, 1.0f, 1.0f);
	body->setColor(&col);

	GraphicsBuffer* head = new GraphicsBuffer(size, size);
	Color colH(1.0f,0.0f,0.0f);
	head->setColor(&colH);

	mSpriteH = new Sprite(head, 0, 0, size, size);
	mSpriteB = new Sprite(body, 0, 0, size, size);

	mSize = size;
	mLoc = start;

	for (int i = 0; i < len; i++)
	{
		mBody.push_back(new Node(mSpriteB, this));
	}
}

void Snake::setDir(Direction dir)
{
	int op;
	if (dir == 0)
	{
		op = 2;
	}
	else if (dir == 1)
	{
		op = 3;
	}
	else if (dir == 2)
	{
		op = 0;
	}
	else {
		op = 1;
	}
	if (Direction(op) != mDir)
	{
		mDir = dir;
	}
}

Snake::~Snake()
{
	delete mSpriteB;
	delete mSpriteH;
	for (int i = mBody.size() - 1; mBody.size() > i; --i) 
	{
		delete (mBody[i]);
	}
}

void Snake::update(double dt)
{
	for (int i = mBody.size() - 1; mBody.size() > i; --i)
	{
		Node* cur = (mBody[i]);
		cur->mLoc = cur->mLink->getLoc();
	}
	switch (mDir)
	{
	case UP:
		mLoc.y -= mSize;
		break;

	case RIGHT:
		mLoc.x += mSize;
		break;

	case DOWN:
		mLoc.y += mSize;
		break;

	case LEFT:
		mLoc.x -= mSize;
		break;
	}
	for (int i = mBody.size() - 1; mBody.size() > i; --i) 
	{
		Node* cur = (mBody[i]);
		if (mLoc.x == cur->getLoc().x && mLoc.y == cur->getLoc().y)
		{
			Game::getInstance()->getEventSystem()->fireEvent(GameOverEvent());
		}
	}

	

	int height = Game::getInstance()->getSystem()->mGraphics.getWindowHeight();
	int width = Game::getInstance()->getSystem()->mGraphics.getWindowWidth();

	height -= height % mSize;
	width -= width % mSize;
	if (mLoc.x < 0)
	{
		mLoc.x = width;
	} else if (mLoc.x > width)
	{
		mLoc.x = 0;
	}

	if (mLoc.y < 0)
	{
		mLoc.y = height;
	}
	else if (mLoc.y > height)
	{
		mLoc.y = 0;
	}
}

void Snake::draw(float scale)
{
	for (int i = mBody.size() - 1; mBody.size() > i; --i) 
	{
		Node* cur = (mBody[i]);
		cur->draw();
	}
	Game::getInstance()->getSystem()->mGraphics.draw(mSpriteH, mLoc.x, mLoc.y, scale);
}

void Snake::addSegment()
{
	mBody.push_back(new Node(mSpriteB, mBody.back()));
}

Node::Node(Sprite* sprite, Unit* link)
{
	mSprite = sprite;
	mLink = link;
}

Node::~Node()
{
}

void Node::draw(float scale)
{
	Game::getInstance()->getSystem()->mGraphics.draw(mSprite, mLoc.x, mLoc.y, scale);
}
