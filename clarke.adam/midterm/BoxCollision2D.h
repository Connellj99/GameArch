#ifndef BOX_COLLISION2D
#define BOX_COLLISION2D

#include "Trackable.h"

class BoxCollision2D : public Trackable
{
public:
	BoxCollision2D(BoxCollider2D* other)
		: mOther(other)
	{
	}

	BoxCollider2D* getOther() const { return mOther; }
private:
	BoxCollider2D* mOther;
};
#endif