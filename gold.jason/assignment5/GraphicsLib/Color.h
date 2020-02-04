#ifndef Color_h
#define Color_h

#include "Trackable.h"

class Color: public Trackable
{
public:

	Color(int r,int g, int b);
	~Color();
	int getRed()
	{
		return red;
	};
	int getGreen()
	{
		return green;
	};
	int getBlue()
	{
		return blue;
	};

private:
	int red;
	int green;
	int blue;

};

#endif // !Color_h

