#ifndef VECTOR2_DATA_H
#define VECTOR2_DATA_H

//struct for the x and y coords
struct Vector2
{
	Vector2()//Default contructor that will just set the x and y values to 0
	{
		mX = 0;
		mY = 0;
	}

	Vector2(int x, int y)//This constructor on the otherhand sets the mx and my to whatever user passes in
	{
		mX = x;
		mY = y;
	}

	//member variables for the positions
	int mX;
	int mY;
};

#endif

