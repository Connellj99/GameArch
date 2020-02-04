#ifndef Color_h
#define Color_h

#include "Trackable.h"
#include "allegro5/color.h"

class Color: public Trackable
{
public:

	Color();

	Color(int r,int g, int b);
	~Color();
	ALLEGRO_COLOR getColor()
	{
		return mCol;
	};

private:
	int red;
	int green;
	int blue;
	ALLEGRO_COLOR mCol;

};

#endif // !Color_h

