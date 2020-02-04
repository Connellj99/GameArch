#include "Unit.h"

enum Direction {
	NONE = 0,
	UP,
	LEFT,
	DOWN,
	RIGHT,
	NUM_DIRECTIONS
};

class Player : public Unit
{
	friend class Game;
public:
	Player();

	Player(int, int, float);

	~Player();

	void update(double) override;

	void setBounds(float*, float*);

	void move(int, int);

	float getSpeed() { return mSpeed; }

private:

	float mVectX;

	float mVectY;

	float* mLowerBounds;

	float* mUpperBounds;

	Sprite* mpSprite;

	float mSpeed;

	void setInitVals(int, int, float);

};