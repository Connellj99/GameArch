#pragma once

const int OPTIMAL_FRAME_RATE = 60;

class Player :
	public Unit
{
public:
	Player();

	~Player();

	void setDestination(int _positionX, int _positionY);

	void setQueueDestination(int _positionX, int _positionY);

	void setSpeed(double _speed);

	double getSpeed(double _deltaTime);

	double getSpeed();

	int getDestinationX();
	int getDestinationY();

	int getQueueDestinationX();
	int getQueueDestinationY();

	// Check if there is a collision at this unit.
	bool collision(int _positionX, int _positionY);

	void setDirection(int _direction);

	void setQueueDirection(int _direction);

	int getDirection();

	int getQueueDirection();

	void setDistance(int _distance);

	int getDistance();

	void move(double _deltaTime, LevelManager* _pLevelManager);

	void updateDestination();

	void updateDirection();

	void turnOffMovement();

	void turnOnMovement();

	bool canMove();

private:

	int mDestinationX = 0;

	int mDestinationY = 0;

	int mQueueDestinationX = 0;

	int mQueueDestinationY = 0;

	int mDirection = WEST;

	int mQueueDirection = WEST;

	double mSpeed = 0.2;

	int mDistance = 32;

	bool mMove = true;
};

