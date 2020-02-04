#ifndef VECTOR2_H
#define VECTOR2_H

// This struct is meant to represent a 2D coordinate
struct Vector2
{
	Vector2()
	{
		mX = 0;
		mY = 0;
	}

	Vector2(double x, double y)
	{
		mX = x;
		mY = y;
	}

	double mX;
	double mY;
};

#endif // !VECTOR2_H

