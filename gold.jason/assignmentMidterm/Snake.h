#pragma once

#include <allegro5/allegro.h>
#include <vector>
#include <allegro5/allegro_primitives.h>
#include <iostream>

using namespace std;

//enum Direction 
//{
//	UP_ARROW, 
//	DOWN_ARROW, 
//	LEFT_ARROW, 
//	RIGHT_ARROW
//};

class Snake
{
public:
	Snake();

	//void drawSnake();
	void initSnake();
	void moveSnake();
	//void setColor(ALLEGRO_COLOR NewColor);
	//void addSnakeCell(const vector<int> & cell);
	//void increaseSnakeLength();
	void resetSnakeDetails();
	bool ateFood(int foodX, int foodY);
	//const vector<vector<int> > & Snake::getSnakeCells() const;
	void setX(int newX);
	void setY(int newY);
	int getX();
	int getY();
	int getSize();

	~Snake();

private:
	int x;
	int y;
	int mSize;
	vector<vector<int>> mCells;
	vector<int> mPreviousHeadCoords;
	//ALLEGRO_COLOR mColor;
	int mPreviousTailX;
	int mPreviousTailY;
};