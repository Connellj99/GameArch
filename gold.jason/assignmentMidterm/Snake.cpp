#include "Snake.h"
#include <allegro5/drawing.h>

Snake::Snake()
{
	initSnake();
	//mCells.clear();
	// starting coordinates
	x = 400;
	y = 300;

	//// create head cell
	//vector<int> cell(2);
	//cell[0] = x;
	//cell[1] = y;
	//mCells.push_back(cell);

	//// save head coords
	//mPreviousHeadCoords.clear();
	//mPreviousHeadCoords.push_back(mCells[0][0]);
	//mPreviousHeadCoords.push_back(mCells[0][1]);

	//// block size
	//mSize = 20;

	//// color
	//mColor = al_map_rgb(0, 255, 0);
}

void Snake::initSnake()
{
	bool initPrims;
	vector<int> temp (1, 0);
	mCells.push_back(temp);
	al_init_primitives_addon();
	initPrims = al_init_primitives_addon();
	if (initPrims = false) {
		cout << "FAILED TO INIT PRIMITIVES!" << endl;
		system("pause");
		return;
	}
}

//void Snake::drawSnake()
//{
//	for (unsigned int i = 0; i < mCells.size()-1; i++)
//	{
//		unneccesary i think?
//		al_draw_rounded_rectangle(mCells[i][0] - (mSize / 2), mCells[i][1] - (mSize / 2), mCells[i][0] + (mSize / 2), mCells[i][1] + (mSize / 2), 4, 4, mColor, 2.0);
//	}
//}

void Snake::moveSnake()
{
	// save head position
	mPreviousHeadCoords.clear();
	mPreviousHeadCoords.push_back(mCells[0][0]);
	mPreviousHeadCoords.push_back(mCells[0][1]);

	// save tail position
	mPreviousTailX = mCells[mCells.size() - 1][0];
	mPreviousTailY = mCells[mCells.size() - 1][1];

	// update cells vector
	vector<int> head(2);
	head[0] = x;
	head[1] = y;
	mCells.pop_back();
	mCells.insert(mCells.begin(), head);
}

//void Snake::setColor(ALLEGRO_COLOR NewColor)
//{
//	mColor = NewColor;
//}
//
//void Snake::addSnakeCell(const vector<int> & cell)
//{
//	mCells.push_back(cell);
//}
//
//void Snake::increaseSnakeLength()
//{
//	vector<int> temp(2);
//	temp[0] = mPreviousTailX;
//	temp[1] = mPreviousTailY;
//	addSnakeCell(temp);
//}

void Snake::resetSnakeDetails()
{
	//starting coordinates
	x = 400;
	y = 300;

	//// creating head cell
	//vector<int> cell(2);
	//cell[0] = x;
	//cell[1] = y;
	//mCells.clear();
	//mCells.push_back(cell);

	//// saving head coordinates
	//mPreviousHeadCoords.clear();
	//mPreviousHeadCoords.push_back(mCells[0][0]);
	//mPreviousHeadCoords.push_back(mCells[0][1]);

	////color
	//mColor = al_map_rgb(0, 255, 0);
}

bool Snake::ateFood(int foodX, int foodY)
{
	if ((x == foodX) && (y == foodY))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//const vector<vector<int> > & Snake::getSnakeCells() const
//{
//	return mCells;
//}

void Snake::setX(int newX)
{
	cout << "Changed X Value!" << endl;
	x = newX;
}

void Snake::setY(int newY)
{
	cout << "Changed Y Value!" << endl;
	y = newY;
}

int Snake::getX()
{
	return x;
}

int Snake::getY()
{
	return y;
}

int Snake::getSize()
{
	return mSize;
}


Snake::~Snake()
{

}